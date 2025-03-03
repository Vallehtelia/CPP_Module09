
#include "BitcoinExchange.hpp"

int	main(int ac, char **av)
{
	(void)av;
	if (ac == 2)
	{
		BitcoinExchange exchange;

		// exchange.printMap();
		exchange.processInputFile(av[1]);
	}
	else
	{
		std::cout << "Error: Need input.txt as an argument!" << std::endl;
	}
}
