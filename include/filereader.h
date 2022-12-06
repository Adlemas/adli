#ifndef FILE_READER_H
#define FILE_READER_H

#include <fstream>
#include <string>

// FileReader class
// helper class to read a file
class FileReader
{
    // private members such as file stream
    std::ifstream m_file;

public:
    // constructor, destructor
    explicit FileReader(const char *filename);
    ~FileReader();

    // read the file
    std::string read();
};

#endif