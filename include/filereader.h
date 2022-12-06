#ifndef FILE_READER_H
#define FILE_READER_H

#include <fstream>
#include <string>

class FileReader
{
    std::ifstream m_file;

public:
    explicit FileReader(const char *filename);
    ~FileReader();

    std::string read();
};

#endif