
#include "PmergeMe.hpp"

PmergeMe::PmergeMe(char **av)
{
	int i = 1;
	int num;

	while (av[i])
	{
		int j = 0;
		while (av[i][j])
		{
			if (std::isdigit(av[i][j]) == 0)
			{
				std::cerr << RED << "Error: only positive energ.. Krohom.. sorry, integers please!" << RESET << std::endl;
				exit(1);
			}
			j++;
		}
		try
		{
			num = std::stoi(av[i]);
		}
		catch (std::exception &e)
		{
			std::cerr << RED << "Error: we need integers, not whatever that is!" << RESET << std::endl;
			exit(1);
		}
		vInput.push_back(num);
		dInput.push_back(num);
		i++;
	}
}

PmergeMe::PmergeMe(PmergeMe const &other)
{
	*this = other;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &other)
{
	if (this != &other)
	{
		vInput = other.vInput;
		dInput = other.dInput;
		vList = other.vList;
		dList = other.dList;
		startV = other.startV;
		endV = other.endV;
		startD = other.startD;
		endD = other.endD;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

std::vector<int> PmergeMe::getVInput() const
{
	return vInput;
}

std::deque<int> PmergeMe::getDInput() const
{
	return dInput;
}

std::vector<int> PmergeMe::getVList() const
{
	return vList;
}

std::deque<int> PmergeMe::getDList() const
{
	return dList;
}

std::chrono::high_resolution_clock::time_point PmergeMe::getStartV() const
{
	return startV;
}

std::chrono::high_resolution_clock::time_point PmergeMe::getEndV() const
{
	return endV;
}

std::chrono::high_resolution_clock::time_point PmergeMe::getStartD() const
{
	return startD;
}

std::chrono::high_resolution_clock::time_point PmergeMe::getEndD() const
{
	return endD;
}

void PmergeMe::setStartV()
{
	startV = std::chrono::high_resolution_clock::now();
}

void PmergeMe::setEndV()
{
	endV = std::chrono::high_resolution_clock::now();
}

void PmergeMe::setStartD()
{
	startD = std::chrono::high_resolution_clock::now();
}

void PmergeMe::setEndD()
{
	endD = std::chrono::high_resolution_clock::now();
}

void PmergeMe::setVList(std::vector<int> &v)
{
	vList = v;
}

void PmergeMe::setDList(std::deque<int> &d)
{
	dList = d;
}

void PmergeMe::printInput()
{
	int size = vInput.size();
	if (size > 20)
	{
		std::cout << "Before: " << GREEN;
		for (int i = 0; i < 5; i++)
		{
			std::cout << vInput[i] << " ";
		}
		std::cout << "[...]" << " ";
		for (int i = size - 5; i < size; i++)
		{
			std::cout << vInput[i] << " ";
		}
		std::cout << CYAN << std::endl;
		return;
	}
	std::cout << "Before: " << GREEN;
	for (std::vector<int>::iterator it = vInput.begin(); it != vInput.end(); it++)
	{

		std::cout << *it << " ";
	}
	std::cout << CYAN << std::endl;
}

void PmergeMe::printVList()
{
	int size = vList.size();
	if (size > 20)
	{
		std::cout << "After: " << GREEN;
		for (int i = 0; i < 5; i++)
		{
			std::cout << vList[i] << " ";
		}
		std::cout << "[...]" << " ";
		for (int i = size - 5; i < size; i++)
		{
			std::cout << vList[i] << " ";
		}
		std::cout << CYAN << std::endl;
		return;
	}
	std::cout << "After: " << GREEN;
	for (std::vector<int>::iterator it = vList.begin(); it != vList.end(); it++)
		std::cout << *it << " ";
	std::cout << CYAN << std::endl;
}

void PmergeMe::printDList()
{
	int size = dList.size();
	if (size > 20)
	{
		std::cout << "Deque After: " << GREEN;
		for (int i = 0; i < 5; i++)
		{
			std::cout << dList[i] << " ";
		}
		std::cout << "[...]" << " ";
		for (int i = size - 5; i < size; i++)
		{
			std::cout << dList[i] << " ";
		}
		std::cout << CYAN << std::endl;
		return;
	}
	std::cout << "Deque After: " << GREEN;
	for (std::deque<int>::iterator it = dList.begin(); it != dList.end(); it++)
		std::cout << *it << " ";
	std::cout << CYAN << std::endl;
}

void PmergeMe::printTime()
{
	auto elapsedV = std::chrono::duration<double, std::micro>(endV - startV).count();
	auto elapsedD = std::chrono::duration<double, std::micro>(endD - startD).count();
	std::cout << "Time to process a range of " << vInput.size() << " elements with std::vector: " << GREEN << elapsedV << " us" << CYAN << std::endl;
	std::cout << "Time to process a range of " << dInput.size() << " elements with std::deque: " << GREEN << elapsedD << " us" << std::endl;
}

void PmergeMe::mergeVectorList(std::vector<int> &winners)
{
	std::vector<int> v1;
	std::vector<int> v2;

	if (winners.size() == 1)
		return;
	else if (winners.size() == 2)
	{
		int i1 = winners[0];
		int i2 = winners[1];
		if (i1 > i2)
		{
			winners[0] = i2;
			winners[1] = i1;
		}
		return;
	}
	for (size_t i = 0; i < winners.size(); i++)
	{
		if (i == winners.size() - 1)
		{
			v1.push_back(winners[i]);
			break;
		}
		int i1 = winners[i];
		int i2 = winners[++i];
		if (i1 < i2){v1.push_back(i1); v2.push_back(i2);}
		else{v1.push_back(i2); v2.push_back(i1);}
	}
	mergeVectorList(v1);

	for (std::vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
	{
		std::vector<int>::iterator low = std::lower_bound(v1.begin(), v1.end(), *it);
		v1.insert(low, *it);
	}
	if (v1.size() == winners.size())
		winners = v1;
}

void	PmergeMe::mergeDequeList(std::deque<int> &winners)
{
	std::deque<int> d1;
	std::deque<int> d2;

	if (winners.size() == 1)
		return;
	else if (winners.size() == 2)
	{
		int i1 = winners[0];
		int i2 = winners[1];
		if (i1 > i2)
		{
			winners[0] = i2;
			winners[1] = i1;
		}
		return;
	}
	for (size_t i = 0; i < winners.size(); i++)
	{
		if (i == winners.size() - 1)
		{
			d1.push_back(winners[i]);
			break;
		}
		int i1 = winners[i];
		int i2 = winners[++i];
		if (i1 < i2){d1.push_back(i1); d2.push_back(i2);}
		else{d1.push_back(i2); d2.push_back(i1);}
	}
	mergeDequeList(d1);

	for (std::deque<int>::iterator it = d2.begin(); it != d2.end(); it++)
	{
		std::deque<int>::iterator low = std::lower_bound(d1.begin(), d1.end(), *it);
		d1.insert(low, *it);
	}
	if (d1.size() == winners.size())
		winners = d1;
}
