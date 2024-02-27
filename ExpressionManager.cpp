#include "ExpressionManager.h"
#include <iostream>
#include <cmath>
#include <cctype>
#include <cstring>

ExpressionManager::ExpressionManager()
{
    expression = nullptr;
    values = nullptr;
    nrValues = 0;
}

ExpressionManager::ExpressionManager(const char* _exp, const double* _values, int _nrValues)
{
    setExpression(_exp);
    setValues(_values, _nrValues);
    setNrValues(_nrValues);
}

ExpressionManager::ExpressionManager(const ExpressionManager& exp) : expression(nullptr), values(nullptr), nrValues(0)
{
    if (this == &exp)
        return;

    if (exp.values != nullptr && exp.nrValues != 0)
    {
        this->nrValues = exp.nrValues;
        this->values = new double[exp.nrValues];
        for (int i = 0; i < exp.nrValues; i++)
        {
            this->values[i] = exp.values[i];
        }
    }
    else
    {
        this->values = nullptr;
        this->nrValues = 0;
    }

    if (exp.expression != nullptr)
    {
        this->expression = new char[strlen(exp.expression) + 1];
        strcpy_s(this->expression, strlen(exp.expression) + 1, exp.expression);
    }
    else
    {
        this->expression = nullptr;
    }
}

ExpressionManager& ExpressionManager::operator=(const ExpressionManager& exp)
{
    if (this == &exp)
        return *this;

    if (values != nullptr)
    {
        delete[] values;
        values = nullptr;
    }

    if (expression != nullptr)
    {
        delete[] expression;
        expression = nullptr;
    }

    if (exp.values != nullptr && exp.nrValues != 0)
    {
        this->nrValues = exp.nrValues;
        this->values = new double[exp.nrValues];
        for (int i = 0; i < exp.nrValues; i++)
        {
            this->values[i] = exp.values[i];
        }
    }
    else
    {
        this->values = nullptr;
        this->nrValues = 0;
    }

    if (exp.expression != nullptr)
    {
        this->expression = new char[strlen(exp.expression) + 1];
        strcpy_s(this->expression, strlen(exp.expression) + 1, exp.expression);
    }
    else
    {
        this->expression = nullptr;
    }

    return *this;
}

ExpressionManager::~ExpressionManager()
{
    delete[] expression;
    delete[] values;
}

char* ExpressionManager::getExpression()
{
    char* tmp = new char[strlen(expression) + 1];
    strcpy_s(tmp, strlen(expression) + 1, expression);
    return tmp;
}

double* ExpressionManager::getValues()
{
    double* tmp = new double[nrValues];
    for (int i = 0; i < nrValues; i++)
        tmp[i] = values[i];
    return tmp;
}

int ExpressionManager::getNrValues()
{
    return nrValues;
}

void ExpressionManager::setExpression(const char* _expression)
{
    if (this->expression != nullptr)
    {
        delete[] expression;
        expression = nullptr;
    }

    if (_expression == nullptr)
    {
        _expression = nullptr;
        return;
    }

    expression = new char[strlen(_expression) + 1];
    strcpy_s(expression, strlen(_expression) + 1, _expression);
}

void ExpressionManager::setValues(const double* _values, int _nrValues)
{
    if (this->values != nullptr && this->nrValues != 0)
    {
        delete[] values;
        values = nullptr;
        nrValues = 0;
    }

    if (_values == nullptr)
    {
        _values = nullptr;
        return;
    }
    this->values = new double[_nrValues];
    for (int i = 0; i < _nrValues; i++)
    {
        this->values[i] = _values[i];
    }

}

void ExpressionManager::setNrValues(int _nrValues)
{
    nrValues = _nrValues;
}

std::ostream& operator<<(std::ostream& os, ExpressionManager expMgr)
{
    if (expMgr.expression != nullptr)
    {
        os << "Expresie: ";
        os << expMgr.expression << std::endl;
    }

    if (expMgr.values != nullptr && expMgr.nrValues != 0)
    {
        os << "Valori: ";
        for (int i = 0;i < expMgr.nrValues;i++)
        {
            os << expMgr.values[i] << " ";
        }
    }
    return os;
}

std::istream& operator>>(std::istream& is, ExpressionManager& expMgr)
{
    char* tmp = new char[256];
    double* tmpNr = new double[128];
    double* values = new double[128];

    std::cout << "Expression: ";
    is.getline(tmp, 256);
    expMgr.setExpression(tmp);

    std::cout << "Number of values: ";
    is >> expMgr.nrValues;
    std::cout << "Valori pentru " << expMgr.nrValues << " numere: ";
    for (int i = 0;i < expMgr.nrValues;i++)
    {
        is >> tmpNr[i];
        values[i] = tmpNr[i];
    }
    expMgr.setValues(values, expMgr.nrValues);

    delete[] tmp;
    delete[] tmpNr;

    return is;
}

void ExpressionManager::extractValues(const std::string& exp) {

    delete[] values;
    values = nullptr;
    nrValues = 0;

    size_t expressionIndex = 0;

    while (expressionIndex < exp.size()) {
        char c = exp[expressionIndex];

        if (std::isdigit(c) || c == '.' || std::isalpha(c)) {
            std::string identifier;
            while (expressionIndex < exp.size() && (std::isdigit(c) || c == '.' || std::isalpha(c))) {
                identifier += c;
                ++expressionIndex;
                if (expressionIndex < exp.size())
                    c = exp[expressionIndex];
            }
            --expressionIndex;

            if (std::isalpha(identifier[0])) {

                double value = variableManager.getVariableValue(identifier[0]);

                double* newValues = new double[static_cast<size_t>(nrValues) + 1];
                std::memcpy(newValues, values, static_cast<size_t>(nrValues) * sizeof(double));
                newValues[nrValues] = value;

                delete[] values;
                values = newValues;
                nrValues++;
            }
            else {

                double value = std::stod(identifier);

                double* newValues = new double[static_cast<size_t>(nrValues) + 1];
                std::memcpy(newValues, values, nrValues * sizeof(double));
                newValues[nrValues] = value;

                delete[] values;
                values = newValues;
                nrValues++;
            }
        }

        ++expressionIndex;
    }
}


void ExpressionManager::validateExpression()
{
    std::vector<char> parenthesesStack;
    int numOfDots = 0;

    for (size_t i = 0; i < strlen(expression); ++i)
    {
        char c = expression[i];

        if (c == '(' || c == '[')
            parenthesesStack.push_back(c);
        else if (c == ')' || c == ']')
        {
            if (parenthesesStack.empty())
                throw std::invalid_argument("Paranteze gresite");
            parenthesesStack.pop_back();
        }
        if (c == '.')
        {
            numOfDots++;
        }
        if (numOfDots > 1)
        {
            throw std::invalid_argument("Numar invalid");
        }
    }

    if (!parenthesesStack.empty())
        throw std::invalid_argument("Paranteze gresite");
}

double ExpressionManager::evaluateExpression(const std::string& exp)
{
    std::vector<double> valueStack;
    std::vector<char> operatorStack;
    size_t expressionIndex = 0;

    while (expressionIndex < exp.size())
    {
        char c = exp[expressionIndex];

        if (std::isdigit(c) || c == '.')
        {
            std::string number;
            while (expressionIndex < exp.size() && (std::isdigit(c) || c == '.'))
            {
                number += c;
                ++expressionIndex;
                if (expressionIndex < exp.size())
                    c = exp[expressionIndex];
            }
            --expressionIndex;
            valueStack.push_back(std::stod(number));
        }
        else if (c == '(' || c == '[')
        {
            size_t closingBracketIndex = exp.find((c == '(') ? ')' : ']', expressionIndex);
            if (closingBracketIndex == std::string::npos)
                throw std::invalid_argument("Paranteze gresite");

            std::string subExpression = exp.substr(expressionIndex + 1, closingBracketIndex - expressionIndex - 1);
            expressionIndex = closingBracketIndex;

            double subExpressionResult = evaluateExpression(subExpression);
            valueStack.push_back(subExpressionResult);
        }
        else if (isOperator(c))
        {
            while (!operatorStack.empty() && getPrecedence(c) <= getPrecedence(operatorStack.back()))
            {
                evaluateOperator(valueStack, operatorStack.back());
                operatorStack.pop_back();
            }
            operatorStack.push_back(c);
        }

        ++expressionIndex;
    }

    while (!operatorStack.empty())
    {
        evaluateOperator(valueStack, operatorStack.back());
        operatorStack.pop_back();
    }

    if (!valueStack.empty())
    {
        return valueStack.back();
    }

    else
    {
        std::cerr << "Operatie invalida\n";
        return 0;
    }
}

bool ExpressionManager::isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '#');
}

int ExpressionManager::getPrecedence(char c)
{
    if (c == '^' || c == '#')
        return 3;
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return 0;
}

void ExpressionManager::evaluateOperator(std::vector<double>& values, char op)
{
    double result = 0.0;
    if (values.empty())
        throw std::invalid_argument("Expresie invalida");

    double operand1 = values.back();
    values.pop_back();

    if (op == '#')
    {
        if (values.empty())
            throw std::invalid_argument("Expresie invalida");

        double operand2 = values.back();
        values.pop_back();

        values.push_back(std::pow(operand2, 1 / operand1));
    }
    else
    {
        if (values.empty())
            throw std::invalid_argument("Expresie invalida");

        double operand2 = values.back();
        values.pop_back();

        switch (op)
        {
        case '+':
            values.push_back(operand2 + operand1);
            break;
        case '-':
            values.push_back(operand2 - operand1);
            break;
        case '*':
            values.push_back(operand2 * operand1);
            break;
        case '/':
            if (operand1 != 0)
            {
                values.push_back(operand2 / operand1);
            }
            else
            {
                std::cerr << "Impartire la zero nepermisa!\n";
            }
            break;
        case '^':
            values.push_back(std::pow(operand2, operand1));
            break;
        default:
            std::cerr << "Operator necunoscut\n";
        }
    }
}
