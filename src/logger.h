#ifndef LOGGER
#define LOGGER

#include <iostream>
#include <fstream>

class Logger
{
private:
    std::string log_text;
    int counter;
public:
    explicit Logger(std::string folder_path);
    virtual ~Logger();
    void writeToLog(std::string picture_1, std::string picture_2, int distance);
    void saveLog(std::string save_path);
};

#endif
