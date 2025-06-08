#include "JsonFileLoader.h"
#include <fstream>

JsonFileLoader::JsonFileLoader(const std::string& path) : path_to_json(path)
{
}

json JsonFileLoader::getJson()
{
    // �������� ����� ������
    if (!std::filesystem::exists(path_to_json)) {
        throw std::runtime_error("JsonFileLoader: file '" + path_to_json + "' not found!");
    }
    // ��������� ���� ������
    std::ifstream file(path_to_json);
    if (!file.is_open()) {
        throw std::runtime_error("JsonFileLoader: error open file '" + path_to_json + "'!");
    }
    json file_data;

    try {
        // ������ JSON �� �����
        file_data = json::parse(file);
    }
    catch (const json::exception& e) {
        // ��������� ������ ��������
        throw std::runtime_error(std::string("JsonFileLoader: parse error: ") + e.what());
    }

    return std::move(file_data);
}