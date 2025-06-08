#include "RegisterLoggerCommand.h"
#include "../IoCContainer/IoCCore/IoC.h"
#include "../logger/KafkaLoggerAdapter.h"
#include "../logger/FallbackLogger.h"
#include "../logger/ILogger.h"
#include <iostream>

void RegisterLoggerCommand::execute(void)
{
    IoC::Resolve<ICommand*>(
        "IoC.Register",
        std::string("Logger"),
        New_Resolver((std::function<ILogger * ()>)[]()->ILogger* {
        static ILogger* global_kafka_logger_ptr;
        static bool first = true;

        // при первом запуске проверка доступности брокеров. Если недоступны, то переключаемся на терминал
        if (first) {
            first = false;
            try {         
                static KafkaLoggarAdapter globalKafkaLogger("localhost:9092", "logs-topic");
                global_kafka_logger_ptr = &globalKafkaLogger;
            }
            catch (std::exception& e)
            {
                std::cout << "Kafka Logger connection error: " << e.what() << std::endl
                    << "Switching logger to terminal... " << std::endl;
                static FallbackLogger fallbackLLogger;
                global_kafka_logger_ptr = &fallbackLLogger;
            }
        }

            return global_kafka_logger_ptr;
        })
    )->execute();
}
