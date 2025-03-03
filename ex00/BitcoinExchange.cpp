
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	std::cout << "BitcoinExchange constructor" << std::endl;
	loadDatabase("data.csv");
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
	std::cout << "BitcoinExchange deconstructor" << std::endl;
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
				std::cerr << "Error: bad format in inputfile -> " << buffer << std::endl;
				continue;
			}

			std::string date = trim(buffer.substr(0, cepPos));

			std::string valueStr = trim(buffer.substr(cepPos + 1));

			try
			{
				float value = std::stof(valueStr);
				if (value < 0 || value > 1000)
					throw std::runtime_error("Error: value is out of bounds!\nValue should be between 0 and 1000.");

				std::string foundDate = getClosestLowerDate(date);
				std::cout << "closest date: " << foundDate << std::endl;
			}
			catch (const std::exception &e)
			{
				std::cerr << e.what() << "\nValue is -> " << buffer << "\n\n";
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

    if (it != database.begin())
        return std::prev(it)->first;

    throw std::runtime_error("Error: No lower date found for " + inputDate);
}

void	BitcoinExchange::printMap()
{
	for (auto i : this->database)
	{
		std::cout << i.first << " \t\t\t " << i.second << std::endl;
	}
}

std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos)
        return "";

    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

