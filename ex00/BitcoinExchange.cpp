
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	try
	{
		loadDatabase("data.csv");
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other)
{
	this->database = other.database;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other)
{
	if (this != &other)
	{
		this->database = other.database;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::loadDatabase(const std::string& filename)
{
	try
	{
		std::fstream file;

		file.open(filename);
		if(!file.is_open())
		{
			throw std::runtime_error("Error: Could not open file!");
		}
		std::string buffer;
		bool isFirstLine = true;

		while(std::getline(file, buffer))
		{
			if (isFirstLine)
			{
				isFirstLine = false;
				continue;
			}

			size_t cepPos = buffer.find(',');
			if (cepPos == std::string::npos)
			{
				std::cerr << "Error: bad format in database -> " << buffer << std::endl;
				continue;
			}

			std::string date = buffer.substr(0, cepPos);
			std::string priceStr = buffer.substr(cepPos + 1);

			try
			{
				double price = std::stod(priceStr);
				database[date] = price;
			}
			catch (const std::exception &e)
			{
				std::cerr << "Error: invalid price format in database -> " << buffer << std::endl;
			}
		}
		file.close();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

void BitcoinExchange::processInputFile(const std::string& filename)
{
	try
	{
		std::fstream file;

		file.open(filename);
		if(!file.is_open())
		{
			throw std::runtime_error("Error: Could not open file!");
		}
		std::string buffer;
		bool isFirstLine = true;

		while(std::getline(file, buffer))
		{
			if (isFirstLine)
			{
				isFirstLine = false;
				continue;
			}

			size_t cepPos = buffer.find('|');
			if (cepPos == std::string::npos)
			{
				std::cerr << "Error: bad format in inputfile -> " << buffer << ". Needs value!" << std::endl;
				continue;
			}

			std::string date = trim(buffer.substr(0, cepPos));
			if (!validateFormat(date))
			{
				std::cerr << "Error: bad input => " + date << std::endl;
				continue;
			}
			std::string valueStr = trim(buffer.substr(cepPos + 1));

			try
			{
				float value = std::stof(valueStr);
				if (value < 0)
					throw std::runtime_error("Error: not a positive number.");
				else if(value > 1000)
					throw std::runtime_error("Error: too large a number.");

				std::string foundDate = getClosestLowerDate(date);
				std::cout << date << " => " << value << " = " << (database[foundDate] * value) << std::endl;
			}
			catch (const std::exception &e)
			{
				std::cerr << e.what() << '\n';
			}
		}
		file.close();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

std::string BitcoinExchange::getClosestLowerDate(const std::string& inputDate)
{
    auto it = database.lower_bound(inputDate);

    if (it != database.end() && it->first == inputDate)
        return it->first;

    if (it == database.begin())
        throw std::runtime_error("Error: No lower date found for " + inputDate);;

    return std::prev(it)->first;
}

bool	validateFormat(const std::string &date)
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    std::istringstream yearStream(date.substr(0, 4));
    std::istringstream monthStream(date.substr(5, 2));
    std::istringstream dayStream(date.substr(8, 2));

    int year, month, day;
    if (!(yearStream >> year) || !(monthStream >> month) || !(dayStream >> day))
        return false;

    if (year < 1000 || year > 9999 || month < 1 || month > 12 || day < 1)
        return false;

    const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (day > daysInMonth[month - 1])
        return false;

    return true;
}



std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos)
        return "";

    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

