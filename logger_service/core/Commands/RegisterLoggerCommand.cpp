#include "RegisterLoggerCommand.h"
#include "../IoCContainer/IoCCore/IoC.h"
#include "../endpoint/KafkaConsumer.h"
#include "../logger/ConsoleLoggerHandler.h"
#include "../logger/FileLoggerHandler.h"
#include "../ICommand.h"

void RegisterLoggerCommand::execute()
{
    IoC::Resolve<ICommand*>(
        "IoC.Register",
        std::string("KafkaConsumer"),
        New_Resolver((std::function<KafkaConsumer*()>)[]()->KafkaConsumer* {

            auto console_h = std::make_shared<ConsoleLoggerHandler>();
            auto file_h = std::make_shared<FileLoggerHandler>();

            // цепочка
            console_h->setNext(file_h);

            return new KafkaConsumer("localhost:9092", "logs-topic", console_h);
        })
    )->execute();
}