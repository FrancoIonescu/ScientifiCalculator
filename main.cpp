#include "Calculator.h"
#include "FileManager.h"
#include "EquationManager.h"
#include <iostream>

int main() {
    Calculator calculator;
    FileManager fileManager;
    EquationManager equationManager;

    int choice;
    do {
        std::cout << "\n------CALCULATOR MENU------\n";
        std::cout << "1. Introduceti o ecuatie\n";
        std::cout << "2. Introduceti ecuatia din fisier text\n";
        std::cout << "3. Afisati rezultatele la consola\n";
        std::cout << "4. Afisati rezultatele intr-un fisier text\n";
        std::cout << "5. Introducerea unei ecuatii de tipul ax + b = c\n";
        std::cout << "0. Iesire\n";
        std::cout << "Alegeti o optiune: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            calculator.processInput();
            break;
        }
        case 2: {
            fileManager.readEquationsFromFile("input.txt");
            break;
        }
        case 3: {
            if (calculator.getResult() != 0) {
                std::cout << "Rezultat: " << calculator.getResult() << std::endl;
            }
            else {
                std::cout << "Niciun rezultat de afisat. Va rugam introduceti o ecuatie.\n";
            }
            break;
        }
        case 4: {
            if (calculator.getResult() != 0) {
                fileManager.writeResultToFile("output.txt", calculator.getResult());
                std::cout << "Rezultat salvat in fisierul output.txt\n";
            }
            else {
                std::cout << "Niciun rezultat de salvat. Va rugam introduceti o ecuatie.\n";
            }
            break;
        }
        case 5: {
            equationManager.processEquation();
            break;
        }
        case 0: {
            std::cout << "Iesire din program.\n";
            break;
        }
        default: {
            std::cout << "Optiune invalida. Va rugam selectati o optiune valida.\n";
            break;
        }
        }

    } while (choice != 0);

    return 0;
}
