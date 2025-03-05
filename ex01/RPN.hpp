
#pragma once

#include <iostream>
#include <stack>

class RPN {
	private:
		std::stack<int> stack;

	public:
		RPN();
		RPN(RPN const &other);
		RPN &operator=(RPN const &other);
		~RPN();

		std::stack<int> getStack() const;

		void	push(int value);
		void	pop();
};

bool	doOperation(RPN &rpn, char op);
bool	validateArgs(int ac, std::string av);
