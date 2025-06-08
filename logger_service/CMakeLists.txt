cmake_minimum_required(VERSION 3.10)


add_executable(LoggerService 
 "main.cpp"
 "core/Commands/RegisterLoggerCommand.h" 
 "core/ICommand.h" 
  
 "core/Commands/InitIoCContainerCommand.cpp" "core/Commands/InitIoCContainerCommand.h" "core/Commands/RegisterLoggerCommand.cpp" "logger/ChainMessageHandler.cpp" "logger/ChainMessageHandler.h" "logger/FileLoggerHandler.h" "logger/FileLoggerHandler.cpp")


add_subdirectory(endpoint)
add_subdirectory(core/IoCContainer)

target_link_libraries(LoggerService
    PRIVATE 
    Endpoint
    LoggerIoC

)


# Настройка стандарта C++
set_target_properties(LoggerService PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)