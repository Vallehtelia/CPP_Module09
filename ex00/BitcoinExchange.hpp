
#pragma once

#include <iostream>
#include <fstream>
#include <exception>
#include <map>
#include <string>
#include <sstream>

class BitcoinExchange
{
private:
	std::map<std::string, double> database;

public:
	BitcoinExchange();
	BitcoinExchange(BitcoinExchange const &other);
	BitcoinExchange &operator=(BitcoinExchange const &other);
	~BitcoinExchange();

	const std::map<std::string, double> *getClosestData();

	void loadDatabase(const std::string& filename);
    void processInputFile(const std::string& filename);
	std::string getClosestLowerDate(const std::string& inputDate);
};

std::string trim(const std::string &str);
bool	validateFormat(const std::string &date);
