
#include "RPN.hpp"

// Mode 0: Follow the subject
// Mode 1: Test the class with some ready test cases
#define MODE 0

std::string arg_array[5];
std::string invalid_array[5];

#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define CLEAR "\033[2J\033[1;1H"

int main(int ac, char **av)
{
	if (MODE == 0)
	{
		if (ac != 2)
		{
			std::cerr << "Usage: ./rpn_calculator \"expression\"" << std::endl;
			return 1;
		}
		if (!validateArgs(ac, av[1]))
			return 1;
		RPN rpn;

		size_t i = 0;
		while (av[1][i])
		{
			if (isdigit(av[1][i]) || (av[1][i] == '-' && isdigit(av[1][i + 1])))
				{
					try
					{
						rpn.push(std::stoi(av[1] + i));
						while ((av[1][i] && isdigit(av[1][i])) || (av[1][i] == '-' && isdigit(av[1][i + 1])))
							i++;
						i--;
					}
					catch(const std::exception& e)
					{
						std::cerr << "Error: " << e.what() << std::endl;
						i++;
						break;
					}
				}
			else if (av[1][i] != ' ')
			{
				if (!doOperation(rpn, av[1][i]))
				{
					std::cerr << "Invalid expression" << std::endl;
					return 1;
				}
			}
			i++;
		}
		if (rpn.getStack().size() != 1)
		{
			std::cerr << "Invalid expression" << std::endl;
			return 1;
		}
		std::cout << rpn.getStack().top() << std::endl;

		return 0;
	}
	else if (MODE == 1)
	{
		arg_array[0] = "8 9 * 9 - 9 - 9 - 4 - 1 +";
		arg_array[1] = "89 8 * 9 - 9 - 9 - 4 - 1 +";
		arg_array[2] = "7 7 * 7 -";
		arg_array[3] = "8 9 * -9 - 9 - 9 - 4 - 1 +";
		arg_array[4] = "123798791 2 *";

		invalid_array[0] = "89 * 9 - 9 - 9 - 4 - 1 + 1";
		invalid_array[1] = "89.001 8 * 9 - 9 -";
		invalid_array[2] = "7 *";
		invalid_array[3] = "8 9 * + -";
		invalid_array[4] = "1237987918732123123 2 * 1";

		RPN rpn;

		bool failed = false;

		std::cout << CLEAR << GREEN << "\n\n----------------Valid tests----------------" << RESET << std::endl;
		size_t i = 0;
		while (i < 5)
		{
			std::cout << CYAN << "Test " << arg_array[i] << RESET << std::endl;
			if (!validateArgs(2, arg_array[i]))
			{
				i++;
				continue;
			}


			size_t j = 0;
			while (arg_array[i][j])
			{
				failed = false;
				if (isdigit(arg_array[i][j]) || (arg_array[i][j] == '-' && isdigit(arg_array[i][j + 1])))
				{
					try
					{
						rpn.push(std::stoi(arg_array[i].substr(j)));
						while ((arg_array[i][j] && isdigit(arg_array[i][j])) || (arg_array[i][j] == '-' && isdigit(arg_array[i][j + 1])))
							j++;
						j--;
					}
					catch(const std::exception& e)
					{
						std::cerr << "Error: " << e.what() << std::endl;
						i++;
						failed = true;
						break;
					}
				}
				else if (arg_array[i][j] != ' ')
				{
					if (!doOperation(rpn, arg_array[i][j]))
					{
						std::cerr << "Invalid expression" << std::endl;
						i++;
						failed = true;
						break;
					}
				}
				j++;
			}
			if (failed)
			{
				while(rpn.getStack().size() > 0)
					rpn.pop();
				continue;
			}
			if (rpn.getStack().size() != 1)
			{
				std::cerr << "Invalid expression" << std::endl;
				i++;
				continue;
			}
			std::cout << rpn.getStack().top() << std::endl;
			while(rpn.getStack().size() > 0)
				rpn.pop();
			i++;
		}

		while(rpn.getStack().size() > 0)
			rpn.pop();

		std::cout << GREEN << "\n----------------Invalid tests----------------" << RESET << std::endl;
		i = 0;

		while (i < 5)
		{
			std::cout << CYAN << "Test " << invalid_array[i] << RESET << std::endl;
			if (!validateArgs(2, invalid_array[i]))
			{
				i++;
				continue;
			}

			size_t j = 0;
			while (invalid_array[i][j])
			{
				failed = false;
				if (isdigit(invalid_array[i][j]) || (invalid_array[i][j] == '-' && isdigit(invalid_array[i][j + 1])))
				{
					try
					{
						rpn.push(std::stoi(invalid_array[i].substr(j)));
						while ((invalid_array[i][j] && isdigit(invalid_array[i][j])) || (invalid_array[i][j] == '-' && isdigit(invalid_array[i][j + 1])))
							j++;
						j--;
					}
					catch(const std::exception& e)
					{
						std::cerr << "Error: " << e.what() << std::endl;
						i++;
						failed = true;
						break;
					}
				}
				else if (invalid_array[i][j] != ' ')
				{
					if (!doOperation(rpn, invalid_array[i][j]))
					{
						std::cerr << "Invalid expression" << std::endl;
						i++;
						failed = true;
						break;
					}
				}
				j++;
			}
			if (failed)
			{
				while(rpn.getStack().size() > 0)
					rpn.pop();
				continue;
			}
			if (rpn.getStack().size() != 1)
			{
				std::cerr << "Invalid expression" << std::endl;
				i++;
				continue;
			}
			std::cout << rpn.getStack().top() << std::endl;
			i++;
			while(rpn.getStack().size() > 0)
				rpn.pop();
		}

		return 0;
	}
	return 0;
}
