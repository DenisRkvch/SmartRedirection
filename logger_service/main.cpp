#include <iostream>
#include "core/IoCContainer/IoCCore/IoC.h"
#include "core/Commands/InitIoCContainerCommand.h"
#include "core/Commands/RegisterLoggerCommand.h"
#include "endpoint/KafkaConsumer.h"

#include <string>

int main()
{
    try {

        InitIoCContainerCommand().execute();
        RegisterLoggerCommand().execute();

        KafkaConsumer* logger_service = IoC::Resolve<KafkaConsumer*>("KafkaConsumer");
       
        std::cout << "Press Enter to stop the client...\n";
        std::cin.get();

       
        logger_service->stop();
        delete logger_service;
        std::cout << "Client Finished" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;

        return 1;
    }

    return 0;

}
