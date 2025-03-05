
#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(RPN const &other)
{
	*this = other;
}

RPN &RPN::operator=(RPN const &other)
{
	if (this != &other)
		this->stack = other.stack;
	return *this;
}

RPN::~RPN() {}


std::stack<int>	RPN::getStack() const
{
	return this->stack;
}

void		RPN::push(int value)
{
	this->stack.push(value);
}

void		RPN::pop()
{
	if (this->stack.empty())
	{
		std::cerr << "Stack is empty" << std::endl;
		return;
	}
	this->stack.pop();
}

bool	validateArgs(int ac, std::string av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: ./rpn_calculator \"expression\"" << std::endl;
		return false;
	}
	if (av.find_first_not_of("0123456789+-*/ ") != std::string::npos)
	{
		std::cerr << "Invalid expression" << std::endl;
		return false;
	}
	return true;
}

bool	doOperation(RPN &rpn, char op)
{
	if (rpn.getStack().size() < 2)
		return false;
	int a = rpn.getStack().top();
	rpn.pop();
	int b = rpn.getStack().top();
	rpn.pop();
	if (op == '+')
		rpn.push(a + b);
	else if (op == '-')
		rpn.push(b - a);
	else if (op == '*')
		rpn.push(a * b);
	else if (op == '/')
		rpn.push(b / a);
	return true;
}

