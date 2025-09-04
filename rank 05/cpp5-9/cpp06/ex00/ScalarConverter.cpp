#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
    std::cout << "converter Default contructor called" << std::endl;
}


ScalarConverter::ScalarConverter(const std::string input): _input(input)
{
    std::cout << "conversion for: " << _input << " called" << std::endl;
    _double = atof(_input.c_str());
    convert();
    printout();
}

ScalarConverter::~ScalarConverter()
{
    std::cout << "destructor called" << std::endl;
}

ScalarConverter::ScalarConverter(const ScalarConverter &copy): _input (copy.getInput())
{
    std::cout << "conversion copy constructor called" << std::endl;
    *this = copy;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &copy)
{
	std::cout << "Conversion Assignation operator called" << std::endl;
	if (this == &copy)
		return *this;

	this->_type = copy.getType();
	this->_char = copy.getChar();
	this->_int = copy.getInt();
	this->_float = copy.getFloat();
	this->_double = copy.getDouble();
	return *this;
}

void ScalarConverter::convert(void)
{
	void (ScalarConverter::*functionPTRS[])(void) = {&ScalarConverter::fromChar, &ScalarConverter::fromInt, &ScalarConverter::fromFloat, &ScalarConverter::fromDouble};
	int types[] = {CHAR, INT, FLOAT, DOUBLE};

	this->_type = check_input();

	if (getType() == NAN_INF)
		return ;
	int i;
	for (i = 0; i < 4; i++)
	{
		if (getType() == types[i])
		{
			(this->*functionPTRS[i])();
			break ;
		}
	}
	if (i == 4)
		throw ScalarConverter::Exception();
}

void ScalarConverter::printout(void)
{
	if (getType() != NAN_INF && getDouble() <= UCHAR_MAX && getDouble() >= 0)
	{
		if (isprint(getChar()))
			std::cout << "char: '" << getChar() << "'" << std::endl;
		else
			std::cout << "char: Non displayable" << std::endl;
	}
	else
		std::cout << "char: impossible" << std::endl;
	if (getType() != NAN_INF && getDouble() >= std::numeric_limits<int>::min() && getDouble() <= std::numeric_limits<int>::max())
	{
		std::cout << "int: " << getInt() << std::endl;
	}
	else
		std::cout << "int: impossible" << std::endl;
	if (getType() != NAN_INF)
	{
		std::cout << "float: " << getFloat();
		if (getFloat() - getInt() == 0)
			std::cout << ".0f" << std::endl;
		else
			std::cout << "f" << std::endl;
	}
	else
	{
		if (getInput() == "nan" || getInput() == "nanf")
			std::cout << "float: nanf" << std::endl;
		else if (getInput()[0] == '+')
			std::cout << "float: +inff" << std::endl;
		else
			std::cout << "float: -inff" << std::endl;
	}
	if (getType() != NAN_INF)
	{
		std::cout << "double: " << getDouble();
		if (getDouble() < std::numeric_limits<int>::min() || getDouble() > std::numeric_limits<int>::max() ||
			getDouble() - getInt() == 0)
		{
			std::cout << ".0" << std::endl;
		}
		else
			std::cout << std::endl;
	}
	else
	{
		if (getInput() == "nan" || getInput() == "nanf")
			std::cout << "double: nan" << std::endl;
		else if (getInput()[0] == '+')
			std::cout << "double: +inf" << std::endl;
		else
			std::cout << "double: -inf" << std::endl;
	}
}

int ScalarConverter::check_input(void)
{
	if (getInput().compare("nan") == 0 || getInput().compare("+inf") == 0 ||
		getInput().compare("-inf") == 0 || getInput().compare("+inff") == 0 ||
		getInput().compare("-inff") == 0)
	{
		return (NAN_INF);
	}
	else if (getInput().length() == 1 &&
		(getInput()[0] == '+' || getInput()[0] == '-' ||
		getInput()[0] == 'f' || getInput()[0] == '.'))
	{
		return (CHAR);
	}
	else if (getInput().find_first_of("+-") != getInput().find_last_of("+-"))
		return (ERROR);
	else if (getInput().find_first_not_of("+-0123456789") == std::string::npos)
		return (INT);
	else if (getInput().find_first_not_of("+-0123456789.") == std::string::npos)
	{
		if (getInput().find_first_of(".") != getInput().find_last_of(".") ||
			isdigit(getInput()[getInput().find_first_of(".") + 1]) == false ||
			getInput().find_first_of(".") == 0)
			return (ERROR);
		else
			return (DOUBLE);
	}
	else if (getInput().find_first_not_of("+-0123456789.f") == std::string::npos)
	{
		if (getInput().find_first_of("f") != getInput().find_last_of("f") ||
			getInput().find_first_of(".") != getInput().find_last_of(".") ||
			getInput().find_first_of("f") - getInput().find_first_of(".") == 1 ||
			getInput().find_first_of(".") == 0 ||
			getInput()[getInput().find_first_of("f") + 1] != '\0')
			return (ERROR);
		else
			return (FLOAT);
	}
	else if ((getInput().length() == 1 && std::isprint(getInput()[0])) ||
		(getInput().length() == 1 && std::isalpha(getInput()[0])))
	{
		return (CHAR);
	}
	else
		return (ERROR);
}

void ScalarConverter::fromChar(void)
{
	this->_char = static_cast<unsigned char>(getInput()[0]);
	this->_int = static_cast<int>(getChar());
	this->_float = static_cast<float>(getChar());
	this->_double = static_cast<double>(getChar());
}
void ScalarConverter::fromInt(void)
{
	this->_int = static_cast<int>(getDouble());
	this->_char = static_cast<unsigned char>(getInt());
	this->_float = static_cast<float>(getDouble());
}
void ScalarConverter::fromFloat(void)
{
	this->_float = static_cast<float>(getDouble());
	this->_char = static_cast<char>(getFloat());
	this->_int = static_cast<int>(getFloat());
}
void ScalarConverter::fromDouble(void)
{
	this->_char = static_cast<char>(getDouble());
	this->_int = static_cast<int>(getDouble());
	this->_float = static_cast<float>(getDouble());
}

std::string ScalarConverter::getInput(void) const
{
    return _input;
}

int ScalarConverter::getType(void) const
{
    return _type;
}

char ScalarConverter::getChar(void) const
{
    return _char;
}

int ScalarConverter::getInt(void) const
{
    return _int;
}

float ScalarConverter::getFloat(void) const
{
    return _float;
}

double ScalarConverter::getDouble(void) const
{
    return _double;
}


const char *ScalarConverter::Exception::what() const throw()
{
    return "Conversion is imposible";
}
