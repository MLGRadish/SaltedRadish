#pragma once
#include <vector>
#include <string>

class IOManager {
public:
    static bool readToFileBuffer(std::string filePath ,std::vector<unsigned char>& buffer);
};
