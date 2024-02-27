#include "EquationManager.h"
#include <iostream>
#include <fstream>
#include <string>

EquationManager::EquationManager() {}

void EquationManager::processEquation()
{
	std::cin.ignore();

	std::string equation;
	double a = 0.0, b = 0.0, c = 0.0;
	char equationOperator = '\0';
	size_t equationSignPosition;
	size_t equationXPosition;
	size_t equationOperatorPosition;
	while (true)
	{
		std::cout << "Introduceti o ecuatie (sau 'exit' pentru a iesi): ";
		std::getline(std::cin, equation);

		if (equation.compare("exit") == 0)
		{
			std::cout << "------La revedere!------\n\n\n\n\n";
			break;
		}
		for (int i = 0;i < equation.size();i++)
		{
			if (equation[i] == '+') equationOperator = '+';
			else if (equation[i] == '-') equationOperator = '-';
			else if (equation[i] == '*') equationOperator = '*';
			else if (equation[i] == '/') equationOperator = '/';
		}
		equationSignPosition = equation.find('=');
		equationXPosition = equation.find('x');
		equationOperatorPosition = equation.find(equationOperator);

		a = stod(equation.substr(0, equationOperatorPosition));
		b = stod(equation.substr(equationOperatorPosition + 1, equationSignPosition));
		c = stod(equation.substr(equationSignPosition + 1));

		if (equationXPosition < equationOperatorPosition && equationOperator == '+')
		{
			std::cout << "Rezultat: " << (c - b) / a << '\n';
		}

		if (equationXPosition > equationOperatorPosition && equationOperator == '+')
		{
			std::cout << "Rezultat: " << (c - a) / b << '\n';
		}

		if (equationXPosition < equationOperatorPosition && equationOperator == '-')
		{
			std::cout << "Rezultat: " << (c + b) / a << '\n';
		}

		if (equationXPosition > equationOperatorPosition && equationOperator == '-')
		{
			std::cout << "Rezultat: " << (c - a) / -b << '\n';
		}

		if (equationOperator == '*')
		{
			std::cout << "Rezultat: " << c / (a * b) << '\n';
		}

		if (equationOperator == '/')
		{
			std::cout << "Rezultat: " << c / (a / b) << '\n';
		}
	}
}

void EquationManager::processEquationFromFile(std::string& equation)
{
	double a = 0.0, b = 0.0, c = 0.0;
	char equationOperator = '\0';
	size_t equationSignPosition;
	size_t equationXPosition;
	size_t equationOperatorPosition;

	for (int i = 0;i < equation.size();i++)
	{
		if (equation[i] == '+') equationOperator = '+';
		else if (equation[i] == '-') equationOperator = '-';
		else if (equation[i] == '*') equationOperator = '*';
		else if (equation[i] == '/') equationOperator = '/';
	}
	equationSignPosition = equation.find('=');
	equationXPosition = equation.find('x');
	equationOperatorPosition = equation.find(equationOperator);

	a = stod(equation.substr(0, equationOperatorPosition));
	b = stod(equation.substr(equationOperatorPosition + 1, equationSignPosition));
	c = stod(equation.substr(equationSignPosition + 1));

	if (equationXPosition < equationOperatorPosition && equationOperator == '+')
	{
		std::cout << "Rezultat: " << (c - b) / a << '\n';
	}

	if (equationXPosition > equationOperatorPosition && equationOperator == '+')
	{
		std::cout << "Rezultat: " << (c - a) / b << '\n';
	}

	if (equationXPosition < equationOperatorPosition && equationOperator == '-')
	{
		std::cout << "Rezultat: " << (c + b) / a << '\n';
	}

	if (equationXPosition > equationOperatorPosition && equationOperator == '-')
	{
		std::cout << "Rezultat: " << (c - a) / -b << '\n';
	}

	if (equationOperator == '*')
	{
		std::cout << "Rezultat: " << c / (a * b) << '\n';
	}

	if (equationOperator == '/')
	{
		std::cout << "Rezultat: " << c / (a / b) << '\n';
	}
}

void EquationManager::saveResultAsVariable(const std::string& filename)
{
	std::ofstream file(filename, std::ios::binary);

	if (!file.is_open())
	{
		std::cerr << "Eroare la deschiderea fisierului pentru scriere binara\n";
		return;
	}

	file.write(reinterpret_cast<const char*>(&getSavedVariable()), sizeof(getSavedVariable()));

	file.close();
}

void EquationManager::loadVariableValue(const std::string& filename) {
	std::ifstream file(filename, std::ios::binary);

	if (!file.is_open()) {
		std::cerr << "Eroare la deschiderea fisierului pentru citire binara\n";
		return;
	}

	file.read(reinterpret_cast<char*>(&getSavedVariable()), sizeof(getSavedVariable()));

	file.close();
}