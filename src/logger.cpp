#include "logger.h"

Logger::Logger(std::string folder_path)
{
    log_text = "Log file for pictures in folder " + folder_path + "\n\n";
    counter = 0;
}

Logger::~Logger() {}

void Logger::writeToLog(std::string picture_1, std::string picture_2, int distance)
{
    log_text += std::to_string(++counter) + "\n";
    log_text += "Picture 1: " + picture_1 + "\n";
    log_text += "Picture 2: " + picture_2 + "\n";
    log_text += "Hamming distance: " + std::to_string(distance) + "\n";
    log_text += "\n";
}

void Logger::saveLog(std::string save_path)
{
    std::ofstream out_log(save_path);
    out_log << log_text;
    out_log.close();
}
