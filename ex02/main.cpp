
#include "PmergeMe.hpp"

// template function to check if list is sorted. can take vector or deque as parameter
template <typename T>
bool isSorted(T &list)
{
	typename T::iterator it = list.begin();
	typename T::iterator ite = list.end();
	typename T::iterator it2 = list.begin();
	it2++;
	while (it2 != ite)
	{
		if (*it > *it2)
			return false;
		it++;
		it2++;
	}
	return true;
}

int main(int ac, char **av)
{
	std::cout << CLEAR;
	if (ac < 2)
	{
		std::cerr << RED << "Usage: ./ex02 [integers]" << RESET << std::endl;
		return 1;
	}

	std::vector<int> v;
	std::deque<int> d;

	PmergeMe pmm(av);

	v = pmm.getVInput();
	d = pmm.getDInput();

	pmm.setStartV();
	pmm.mergeVectorList(v);
	pmm.setVList(v);
	pmm.setEndV();
	pmm.setStartD();
	pmm.mergeDequeList(d);
	pmm.setDList(d);
	pmm.setEndD();
	std::cout << CYAN;
	pmm.printInput();
	pmm.printVList();
	// pmm.printDList();
	pmm.printTime();
	std::cout << RESET;
	if (!isSorted(v))
	{
		std::cerr << RED << "Vector is not sorted" << RESET << std::endl;
		return 1;
	}
	if (!isSorted(d))
	{
		std::cerr << RED << "Deque is not sorted" << RESET << std::endl;
		return 1;
	}
	return 0;
}
