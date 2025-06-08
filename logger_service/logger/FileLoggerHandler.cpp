#include "FileLoggerHandler.h"
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <filesystem>

FileLoggerHandler::FileLoggerHandler() : logFile(filename, std::ios::app)
{
    // ���������� ��� ����� � ��������� ������
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "log_%Y%m%d_%H%M%S.log");
    filename = ss.str();

    // ������� ����
    openLogFile();
}

FileLoggerHandler::~FileLoggerHandler()
{
    closeLogFile();
}

void FileLoggerHandler::processMessage(const std::vector<uint8_t>& raw_data)
{
    if (!logFile.is_open()) {
        openLogFile();
    }

    if (logFile.is_open()) {
        // �������� ������� �����
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;

        // ����������� �����
        std::stringstream time_ss;
        time_ss << std::put_time(std::localtime(&in_time_t), "[%Y-%m-%d %H:%M:%S")
            << '.' << std::setfill('0') << std::setw(3) << ms.count() << "] ";

        // ������������ ���������
        std::string message(raw_data.begin(), raw_data.end());

        // ���������� � ����
        logFile << time_ss.str() << message << std::endl;
        logFile.flush();
    }
}

void FileLoggerHandler::openLogFile() {
    // ��������� ���������� �� ����
    if (!std::filesystem::exists(filename)) {
        logFile.open(filename, std::ios::out);
    }
    else {
        // ���� ���� ����������, ��������� �������
        int counter = 1;
        std::string new_filename;
        do {
            new_filename = filename.substr(0, filename.size() - 4) +
                "_" + std::to_string(counter++) + ".log";
        } while (std::filesystem::exists(new_filename));

        filename = new_filename;
        logFile.open(filename, std::ios::out);
    }

    if (logFile.is_open()) {
        logFile << "Log file created: " << filename << "\n";
        logFile << "========================================\n";
        logFile.flush();
    }
}

void FileLoggerHandler::closeLogFile() {
    if (logFile.is_open()) {
        logFile << "\n========================================\n";
        logFile << "Log session ended\n";
        logFile.close();
    }
}
