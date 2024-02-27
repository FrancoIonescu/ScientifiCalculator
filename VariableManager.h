#ifndef VARIABLEMANAGER_H
#define VARIABLEMANAGER_H

#include <iostream>

class VariableManager {
private:
    char* variableNames;
    double* variableValues;
    int numberOfValues;

public:
    VariableManager();
    VariableManager(const char* _variableNames, const double* _variableValues, int _numberOfValues);
    VariableManager(const VariableManager& var);
    ~VariableManager();

    VariableManager& operator=(const VariableManager& var);

    friend std::ostream& operator<<(std::ostream& os, VariableManager var);
    friend std::istream& operator>>(std::istream& is, VariableManager& var);

    void setVariableNames(const char* _variableNames);
    void setVariableValues(const double* _variableValues, int _numberOfValues);
    void setNumberOfValues(int _numberOfValues);
    char* getVariableNames();
    double* getVariableValues();
    int getNumberOfValues();

    void setVariable(char variable, double value);
    double getVariableValue(char variable);
    void displayVariables();
};

#endif