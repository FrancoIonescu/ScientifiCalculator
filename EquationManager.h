#ifndef EQUATIONMANAGER_H
#define EQUATIONMANAGER_H

#include "Calculator.h"
#include <iostream>

class EquationManager : public Calculator
{
public:
	EquationManager();
	void processEquation();
	void processEquationFromFile(std::string& equation);
	void saveResultAsVariable(const std::string& filename);
	void loadVariableValue(const std::string& filename);

};

#endif