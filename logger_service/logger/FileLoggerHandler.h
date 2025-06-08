#ifndef FILELOGGERHANDLER_H
#define FILELOGGERHANDLER_H

#include "ChainMessageHandler.h"
#include <fstream>

class FileLoggerHandler : public ChainMessageHandler 
{
public:
    FileLoggerHandler();

    ~FileLoggerHandler();

private:
    void processMessage(const std::vector<uint8_t>& raw_data) override;
    void openLogFile(void);
    void closeLogFile(void);
    std::string filename;
    std::ofstream logFile;
};

#endif // FILELOGGERHANDLER_H