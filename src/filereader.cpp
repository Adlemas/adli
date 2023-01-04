#include <filereader.h>

FileReader::FileReader(const char *filename)
{
    m_file.open(filename);

    if (!m_file.is_open())
    {
        throw std::runtime_error("Could not open file at " + std::string(filename));
    }
}

FileReader::~FileReader()
{
    m_file.close();
}

std::string FileReader::read()
{
    // Read the whole file into a string
    std::string content;

    while (!m_file.eof())
    {
        std::string line;
        std::getline(m_file, line);
        content += line + "\n";
    }

    return content;
}