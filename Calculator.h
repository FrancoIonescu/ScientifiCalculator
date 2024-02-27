
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include "ExpressionManager.h"

class Calculator
{
private:

    ExpressionManager expMgr;
    char* userInput;
    double result;
    double savedVariable;
    const std::string name = "Franco Ionescu";
    static std::string classGroup;

public:

    Calculator();
    Calculator(const char* _userInput);
    Calculator(const Calculator& calc);
    ~Calculator();

    Calculator& operator=(const Calculator& calc);

    friend std::ostream& operator<<(std::ostream& os, Calculator calc);
    friend std::istream& operator>>(std::istream& is, Calculator& calc);

    void setUserInput(const char* _userInput);
    void setResult(double _result);
    void setSavedVariable(double savedVariable);
    static void setClassGroup(std::string _classGroup);
    std::string getName();
    static std::string getClassGroup();
    char* getUserInput();
    double getResult();
    double& getSavedVariable();
    void processInput();
    ExpressionManager& getExpMgr();

    virtual void saveResultAsVariable(const std::string& filename);
    virtual void loadVariableValue(const std::string& filename);

};

#endif
