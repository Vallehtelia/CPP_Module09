
#pragma once

#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <limits>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define CYAN "\033[36m"
#define RESET "\033[0m"
#define CLEAR "\033[2J\033[1;1H"


class PmergeMe
{
	private:
		std::vector<int> vInput;
		std::deque<int> dInput;
		std::vector<int> vList;
		std::deque<int> dList;

		std::chrono::high_resolution_clock::time_point startV;
		std::chrono::high_resolution_clock::time_point endV;
		std::chrono::high_resolution_clock::time_point startD;
		std::chrono::high_resolution_clock::time_point endD;

		PmergeMe();

	public:
		PmergeMe(char **av);
		PmergeMe(PmergeMe const &other);
		PmergeMe &operator=(PmergeMe const &other);
		~PmergeMe();

		std::vector<int> getVInput() const;
		std::deque<int> getDInput() const;
		std::vector<int> getVList() const;
		std::deque<int> getDList() const;
		std::chrono::high_resolution_clock::time_point getStartV() const;
		std::chrono::high_resolution_clock::time_point getEndV() const;
		std::chrono::high_resolution_clock::time_point getStartD() const;
		std::chrono::high_resolution_clock::time_point getEndD() const;

		void setStartV();
		void setEndV();
		void setStartD();
		void setEndD();

		void setVList(std::vector<int> &v);
		void setDList(std::deque<int> &d);

		void printInput();
		void printVList();
		void printDList();
		void printTime();
		void mergeVectorList(std::vector<int> &winners);
		void mergeDequeList(std::deque<int> &winners);
};

