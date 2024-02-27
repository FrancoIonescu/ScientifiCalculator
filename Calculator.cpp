
#include "Calculator.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

Calculator::Calculator()
{
    userInput = nullptr;
    result = 0;
    savedVariable = 0;
}

Calculator::Calculator(const char* _userInput) : result(0), userInput(nullptr), savedVariable(0)
{
    expMgr.setExpression(_userInput);
    expMgr.validateExpression();
    result = expMgr.evaluateExpression(_userInput);
    if (std::fmod(result, 1) == 0)
    {
        std::cout << "Rezultat: " << static_cast<int>(result) << std::endl;
    }
    else
    {
        std::cout << std::fixed << std::setprecision(4) << result << std::endl;
    }
}

Calculator::Calculator(const Calculator& calc) : userInput(calc.userInput), result(calc.result), name(calc.name), savedVariable(calc.savedVariable)
{
    if (this == &calc)
    {
        return;
    }

    this->result = calc.result;
    this->savedVariable = calc.savedVariable;

    if (calc.userInput != nullptr)
    {
        this->userInput = new char[strlen(calc.userInput) + 1];
        strcpy_s(this->userInput, strlen(calc.userInput) + 1, calc.userInput);
    }
    else
    {
        this->userInput = nullptr;
    }
}

Calculator::~Calculator()
{
    delete[] userInput;
}

Calculator& Calculator::operator=(const Calculator& calc)
{
    if (this == &calc)
    {
        return *this;
    }

    if (userInput != nullptr)
    {
        delete[] userInput;
        userInput = nullptr;
    }
    this->result = calc.result;

    if (calc.userInput != nullptr)
    {
        this->userInput = new char[strlen(calc.userInput) + 1];
        strcpy_s(this->userInput, strlen(calc.userInput) + 1, calc.userInput);
    }

    else
    {
        this->userInput = nullptr;
    }

    return *this;
}

void Calculator::setUserInput(const char* _userInput)
{
    if (this->userInput != nullptr)
    {
        delete[] userInput;
        userInput = nullptr;
    }

    if (_userInput == nullptr)
    {
        _userInput = nullptr;
        return;
    }

    userInput = new char[strlen(_userInput) + 1];
    strcpy_s(userInput, strlen(_userInput) + 1, _userInput);
}

std::string Calculator::classGroup = "E1065";

void Calculator::setResult(double _result)
{
    this->result = _result;
}

void Calculator::setSavedVariable(double savedVariable)
{
    this->savedVariable = savedVariable;
}

void Calculator::setClassGroup(std::string _classGroup)
{
    Calculator::classGroup = _classGroup;
}

char* Calculator::getUserInput()
{
    char* tmp = new char[strlen(userInput) + 1];
    strcpy_s(tmp, strlen(userInput) + 1, userInput);
    return tmp;
}

double Calculator::getResult()
{
    return result;
}

double& Calculator::getSavedVariable()
{
    return savedVariable;
}

std::string Calculator::getName()
{
    return name;
}

std::string Calculator::getClassGroup()
{
    return Calculator::classGroup;
}

ExpressionManager& Calculator::getExpMgr()
{
    return Calculator::expMgr;
}

std::ostream& operator<<(std::ostream& os, Calculator calc)
{
    if (calc.userInput != nullptr)
    {
        os << "User Input: ";
        os << calc.userInput << std::endl;
    }
    os << "Result: " << calc.result << std::endl;
    os << "Name: " << calc.name << std::endl;

    return os;
}

std::istream& operator>>(std::istream& is, Calculator& calc)
{
    char* tmp = new char[256];
    double result;

    std::cout << std::endl << std::endl;
    std::cout << "User Input: ";
    is.getline(tmp, 256);
    calc.setUserInput(tmp);

    std::cout << "Result: ";
    is >> result;
    calc.setResult(result);

    delete[] tmp;

    return is;
}

void Calculator::processInput()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true)
    {
        std::cout << "Introduceti o ecuatie (sau 'exit' pentru a iesi): ";
        const int maxInputSize = 100;
        userInput = new char[maxInputSize];
        std::cin.getline(userInput, maxInputSize);

        for (int i = 0; i < strlen(userInput); i++) {
            userInput[i] = toupper(userInput[i]);
        }

        if (strcmp(userInput, "EXIT") == 0)
        {
            std::cout << "------La revedere!------\n\n\n\n\n";
            break;
        }

        try
        {
            expMgr.setExpression(userInput);

            expMgr.validateExpression();

            result = expMgr.evaluateExpression(userInput);

            if (std::fmod(result, 1) == 0)
            {
                std::cout << "Rezultat: " << static_cast<int>(result) << std::endl;
            }
            else
            {
                std::cout << std::fixed << std::setprecision(4) << result << std::endl;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Eroare: " << e.what() << std::endl;
        }

        delete[] userInput;
    }
}

void Calculator::saveResultAsVariable(const std::string& filename)
{
    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "Eroare la deschiderea fisierului pentru scriere binara\n";
        return;
    }

    file.write(reinterpret_cast<const char*>(&savedVariable), sizeof(savedVariable));

    file.close();
}

void Calculator::loadVariableValue(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Eroare la deschiderea fisierului pentru citire binara\n";
        return;
    }

    file.read(reinterpret_cast<char*>(&savedVariable), sizeof(savedVariable));

    file.close();
}