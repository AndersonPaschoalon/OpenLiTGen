#ifndef __UTILS__H__
#define __UTILS__H__ 1

#include <iostream>
#include <string>


void splitString(const char* input, const char separator,  std::string& firstHalf, std::string& secondHalf);


/*
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <set>


/// @brief Remove duplicate elements from string vector.
/// @param strVec 
/// @return 
std::vector<std::string> removeDuplicates(const std::vector<std::string>& strVec);

/// @brief 
/// @param fileName 
/// @param content 
/// @return 
bool appendToFile(std::string fileName, std::string content);

/// @brief Convert a std vector to a CSV list.
/// @param src vector of objects, such as int, double or strings.
/// @param separator CSV separator, default is comma (,)
/// @return CSV string.
template <typename T>
std::string toCsv(const std::vector<T>& src, char separator=',');

/// @brief Convert a CSV string to an std::vector. 
/// @param src CSV string list.
/// @param separator CSV separator, default is comma (,)
/// @return 
template <typename T>
std::vector<T> toVec(const std::string& src, char separator=',');

/// @brief This function getFileName takes a full path as input and returns the file name 
/// according to your specifications. It works by finding the last slash or backslash in 
/// the path to extract the file name. If removeExtension is true, it also removes the file 
/// extension by finding the last dot in the file name.
/// @param fullPath 
/// @param removeExtension 
/// @return 
std::string getFileName(const char* fullPath, bool removeExtension);

/// @brief Check if a file exists.
/// @param fileName The name of the file to check.
/// @return True if the file exists, false otherwise.
bool fileExists(const char* fileName);

**/

#endif // __UTILS__H__


