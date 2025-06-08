#include <iostream>
#include "http/HttpServer.h"
#include "http/RedirectorRequestHandler.h"
#include "core/Commands/InitIoCContainerCommand.h"
#include "core/Commands/RegisterConditionsCommand.h"
#include "core/Commands/RegisterRuleEngineCommand.h"
#include "core/Commands/RegisterLoggerCommand.h"
#include "core/IoCContainer/IoCCore/IoC.h"
#include "logger/ILogger.h"

int main() {

    try {
        // Инициализация IoC контейнера
        InitIoCContainerCommand().execute();

        // Регистрация логгера
        RegisterLoggerCommand().execute();

        // Регистрация разрешателя условий
        RegisterConditionsCommand().execute();

        // Регистрация движка правил
        RegisterRuleEngineCommand().execute();

        // Создание движка-интерпретатора правил (DI)
        std::shared_ptr<IRuleEngine>rule_interpreter = IoC::Resolve<std::shared_ptr<IRuleEngine>>("RuleEngine");

        // создание обработчика Http запроса
        RedirectorRequestHandler request_handler(rule_interpreter);

        // создание асинхронного сервера
        HttpServer server("127.0.0.1", 8080, &request_handler); // Оборачиваем обработчик (декоратор)

        // запуск
        server.start();

        IoC::Resolve<ILogger*>("Logger")->log("Server Started! \n");

        std::cout << "Press Enter to stop the server...\n";
        std::cin.get();

        IoC::Resolve<ILogger*>("Logger")->log("Server finished! \n");
        server.stop();
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;

        return 1;
    }

    return 0;
}

