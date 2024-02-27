#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include "Calculator.h"
#include "EquationManager.h"

class FileManager {
public:
    static void readEquationsFromFile(const std::string& filename);
    static void writeResultToFile(const std::string& filename, double result, bool append = false);
    static void saveResultToBinaryFile(const std::string& filename, double result);
    static double loadResultFromBinaryFile(const std::string& filename);
};

#endif 
