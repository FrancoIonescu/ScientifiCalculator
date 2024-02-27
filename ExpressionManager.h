
#ifndef EXPRESSIONMANAGER_H
#define EXPRESSIONMANAGER_H

#include "VariableManager.h"
#include <iostream>
#include <string>
#include <vector>


class ExpressionManager {
private:
    char* expression;
    double* values;
    int nrValues;
    VariableManager variableManager;
    bool isOperator(char c);
    int getPrecedence(char c);
    void evaluateOperator(std::vector<double>& values, char op);

public:
    ExpressionManager();
    ExpressionManager(const char* exp, const double* values, int nrValues);
    ExpressionManager(const ExpressionManager& exp);
    ~ExpressionManager();

    ExpressionManager& operator=(const ExpressionManager& exp);

    friend std::ostream& operator<<(std::ostream& os, ExpressionManager expMgr);
    friend std::istream& operator>>(std::istream& is, ExpressionManager& expMgr);

    char* getExpression();
    double* getValues();
    int getNrValues();

    void setExpression(const char* _expression);
    void setValues(const double* _values, int _nrValues);
    void setNrValues(int _nrValues);

    void extractValues(const std::string& exp);
    void validateExpression();
    double evaluateExpression(const std::string& exp);

};

#endif