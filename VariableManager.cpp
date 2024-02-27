#include "VariableManager.h"
#include <cstring>

VariableManager::VariableManager()
{
    variableNames = nullptr;
    variableValues = nullptr;
    numberOfValues = 0;
}

VariableManager::VariableManager(const char* _variableNames, const double* _variableValues, int _numberOfValues)
{
    if (_variableNames != nullptr)
    {
        this->variableNames = new char[strlen(_variableNames) + 1];
        strcpy_s(this->variableNames, strlen(_variableNames) + 1, _variableNames);
    }
    else
    {
        this->variableNames = nullptr;
    }
    if (_variableValues != nullptr)
    {
        this->numberOfValues = _numberOfValues;
        for (int i = 0;i < _numberOfValues;i++)
        {
            this->variableValues[i] = _variableValues[i];
        }
    }
    else
    {
        this->numberOfValues = 0;
        this->variableValues = nullptr;
    }
}

VariableManager::VariableManager(const VariableManager& var) : variableNames(nullptr), variableValues(nullptr), numberOfValues(0)
{
    if (this == &var)
    {
        return;
    }

    if (var.variableValues != nullptr && var.numberOfValues != 0)
    {
        this->numberOfValues = var.numberOfValues;
        this->variableValues = new double[var.numberOfValues];
        for (int i = 0;i < var.numberOfValues;i++)
        {
            this->variableValues[i] = var.variableValues[i];
        }
    }

    else
    {
        this->variableValues = nullptr;
        this->numberOfValues = 0;
    }

    if (var.variableNames != nullptr)
    {
        this->variableNames = new char[strlen(var.variableNames) + 1];
        strcpy_s(this->variableNames, strlen(var.variableNames) + 1, var.variableNames);
    }
    else
    {
        this->variableNames = nullptr;
    }

}

VariableManager& VariableManager::operator=(const VariableManager& var)
{
    if (this == &var)
        return *this;

    if (variableValues != nullptr)
    {
        delete[] variableValues;
        variableValues = nullptr;
    }

    if (variableNames != nullptr)
    {
        delete[] variableNames;
        variableNames = nullptr;
    }

    if (var.variableValues != nullptr && var.numberOfValues != 0)
    {
        this->numberOfValues = var.numberOfValues;
        this->variableValues = new double[var.numberOfValues];
        for (int i = 0; i < var.numberOfValues; i++)
        {
            this->variableValues[i] = var.variableValues[i];
        }
    }
    else
    {
        this->variableValues = nullptr;
        this->numberOfValues = 0;
    }

    if (var.variableNames != nullptr)
    {
        this->variableNames = new char[strlen(var.variableNames) + 1];
        strcpy_s(this->variableNames, strlen(var.variableNames) + 1, var.variableNames);
    }
    else
    {
        this->variableNames = nullptr;
    }

    return *this;
}

VariableManager::~VariableManager()
{
    delete[] variableNames;
    delete[] variableValues;
}

char* VariableManager::getVariableNames()
{
    char* tmp = new char[strlen(variableNames) + 1];
    strcpy_s(tmp, strlen(variableNames) + 1, variableNames);
    return tmp;
}

double* VariableManager::getVariableValues()
{
    double* tmp = new double[numberOfValues];
    for (int i = 0; i < numberOfValues; i++)
        tmp[i] = variableValues[i];
    return tmp;
}

int VariableManager::getNumberOfValues()
{
    return numberOfValues;
}

void VariableManager::setVariableNames(const char* _variableNames)
{
    if (this->variableNames != nullptr)
    {
        delete[] variableNames;
        variableNames = nullptr;
    }

    if (_variableNames == nullptr)
    {
        _variableNames = nullptr;
        return;
    }

    variableNames = new char[strlen(_variableNames) + 1];
    strcpy_s(variableNames, strlen(_variableNames) + 1, _variableNames);
}

void VariableManager::setVariableValues(const double* _variableValues, int _numberOfValues)
{
    if (this->variableValues != nullptr && this->numberOfValues != 0)
    {
        delete[] variableValues;
        variableValues = nullptr;
        numberOfValues = 0;
    }

    if (_variableValues == nullptr)
    {
        _variableValues = nullptr;
        return;
    }
    this->variableValues = new double[_numberOfValues];
    for (int i = 0; i < _numberOfValues; i++)
    {
        this->variableValues[i] = _variableValues[i];
    }

}

void VariableManager::setNumberOfValues(int _numberOfValues)
{
    numberOfValues = _numberOfValues;
}


std::ostream& operator<<(std::ostream& os, VariableManager var)
{
    if (var.variableNames != nullptr)
    {
        os << "Nume variabila: ";
        os << var.variableNames << std::endl;
    }

    if (var.variableValues != nullptr && var.numberOfValues != 0)
    {
        os << "Valori: ";
        for (int i = 0;i < var.numberOfValues;i++)
        {
            os << var.variableValues[i] << " ";
        }
    }
    return os;
}

std::istream& operator>>(std::istream& is, VariableManager& var)
{
    char* tmp = new char[256];
    double* tmpNr = new double[128];
    double* values = new double[128];

    std::cout << "Variable name: ";
    is.getline(tmp, 256);
    var.setVariableNames(tmp);

    std::cout << "Number of values: ";
    is >> var.numberOfValues;
    std::cout << "Values for " << var.numberOfValues << " numbers: ";
    for (int i = 0;i < var.numberOfValues;i++)
    {
        is >> tmpNr[i];
        values[i] = tmpNr[i];
    }
    var.setVariableValues(values, var.numberOfValues);

    delete[] tmp;
    delete[] tmpNr;

    return is;
}

void VariableManager::setVariable(char variable, double value) {
    size_t index = 0;
    while (index < numberOfValues && variableNames[index] != variable) {
        ++index;
    }

    if (index < numberOfValues) {
        variableValues[index] = value;
    }
    else {
        char* newVariableNames = new char[numberOfValues + 1];
        double* newVariableValues = new double[numberOfValues + 1];

        std::memcpy(newVariableNames, variableNames, numberOfValues * sizeof(char));
        std::memcpy(newVariableValues, variableValues, numberOfValues * sizeof(double));

        newVariableNames[numberOfValues] = variable;
        newVariableValues[numberOfValues] = value;

        delete[] variableNames;
        delete[] variableValues;

        variableNames = newVariableNames;
        variableValues = newVariableValues;
        ++numberOfValues;
    }
}

double VariableManager::getVariableValue(char variable) {
    size_t index = 0;
    while (index < numberOfValues && variableNames[index] != variable) {
        ++index;
    }

    if (index < numberOfValues) {
        return variableValues[index];
    }
    else {
        std::cerr << "Variabila '" << variable << "' nu a fost definita." << std::endl;
        return 0.0;
    }
}

void VariableManager::displayVariables() {
    if (numberOfValues > 0) {
        std::cout << "Variabile definite: ";
        for (size_t i = 0; i < numberOfValues; ++i) {
            std::cout << variableNames[i] << "=" << variableValues[i] << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Nicio variabila definita." << std::endl;
    }
}
