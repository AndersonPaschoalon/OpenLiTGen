#include "Utils.h"

/**
std::vector<std::string> removeDuplicates(const std::vector<std::string>& strVec) 
{
    std::set<std::string> uniqueStrings;
    for (const auto& str : strVec) 
    {
        uniqueStrings.insert(str);
    }

    std::vector<std::string> result(uniqueStrings.begin(), uniqueStrings.end());
    return result;
}

bool appendToFile(std::string fileName, std::string content)
{
    std::ofstream outFile(fileName, std::ios_base::app);
    if (!outFile) 
    {
        // If the file doesn't exist, create a new one
        outFile.open(fileName);
        if (!outFile) 
        {
            std::cerr << "Error creating file: " << fileName << std::endl;
            return false;
        }
    }

    outFile << content;
    outFile.close();
    return true;
}

std::string getFileName(const char *fullPath, bool removeExtension)
{
    std::string fileName(fullPath);
    size_t lastSlash = fileName.find_last_of("/\\");
    if (lastSlash != std::string::npos) {
        fileName = fileName.substr(lastSlash + 1);
    }

    if (removeExtension) 
    {
        size_t lastDot = fileName.find_last_of(".");
        if (lastDot != std::string::npos) {
            fileName = fileName.substr(0, lastDot);
        }
    }

    return fileName;
}

bool fileExists(const char *fileName)
{
    std::ifstream file(fileName);
    return file.good();
}

template <typename T>
std::string toCsv(const std::vector<T>& src, char separator) 
{
    std::ostringstream oss;
    for (size_t i = 0; i < src.size(); ++i) 
    {
        oss << src[i];
        if (i < src.size() - 1) 
        {
            oss << std::string(separator);
        }
    }
    return oss.str();
}

template <typename T>
std::vector<T> toVec(const std::string& src, char separator) 
{
    std::vector<T> result;
    std::istringstream iss(src);
    std::string token;
    // while (std::getline(iss, token, ',')) 
    while (std::getline(iss, token, separator)) 
    {
        std::istringstream converter(token);
        T value;
        converter >> value;
        result.push_back(value);
    }
    return result;
}





**/