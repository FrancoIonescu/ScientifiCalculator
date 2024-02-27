#include "FileManager.h"
#include <fstream>
#include <iomanip>
#include <iostream>

void FileManager::readEquationsFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    Calculator calculator;
    EquationManager equationManager;

    if (!inputFile.is_open()) {
        std::cerr << "Eroare la deschiderea fisierului: " << filename << std::endl;
        return;
    }

    std::string equation;
    bool isEquation = false;

    while (std::getline(inputFile, equation)) {
        calculator.setUserInput(equation.c_str());

        try {

            for (int i = 0; i < equation.size();i++)
            {
                if (equation[i] == 'x') isEquation = true;
            }

            if (isEquation)
            {
                equationManager.processEquationFromFile(equation);
            }

            else
            {
                calculator.getExpMgr().setExpression(calculator.getUserInput());
                calculator.getExpMgr().validateExpression();
                double result = calculator.getExpMgr().evaluateExpression(calculator.getUserInput());

                if (std::fmod(result, 1) == 0) {
                    std::cout << "Rezultat: " << static_cast<int>(result) << std::endl;
                }
                else {
                    std::cout << std::fixed << std::setprecision(4) << result << std::endl;
                }
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Eroare la procesarea ecuatiei din fisier: " << e.what() << std::endl;
        }
    }

    inputFile.close();
}

void FileManager::writeResultToFile(const std::string& filename, double result, bool append) {
    std::ofstream outputFile(filename, append ? std::ios::app : std::ios::trunc);

    if (!outputFile.is_open()) {
        std::cerr << "Eroare la deschiderea fisierului: " << filename << std::endl;
        return;
    }

    if (std::fmod(result, 1) == 0) {
        outputFile << "Rezultat: " << static_cast<int>(result) << std::endl;
    }
    else {
        outputFile << std::fixed << std::setprecision(4) << result << std::endl;
    }

    outputFile.close();
}

void FileManager::saveResultToBinaryFile(const std::string& filename, double result) {
    std::ofstream binaryFile(filename, std::ios::binary | std::ios::app);

    if (!binaryFile.is_open()) {
        std::cerr << "Eroare la deschiderea fisierului binar: " << filename << std::endl;
        return;
    }

    binaryFile.write(reinterpret_cast<const char*>(&result), sizeof(result));

    binaryFile.close();
}

double FileManager::loadResultFromBinaryFile(const std::string& filename) {
    std::ifstream binaryFile(filename, std::ios::binary);

    if (!binaryFile.is_open()) {
        std::cerr << "Eroare la deschiderea fisierului binar: " << filename << std::endl;
        return 0.0;
    }

    double result;
    binaryFile.read(reinterpret_cast<char*>(&result), sizeof(result));

    binaryFile.close();

    return result;
}