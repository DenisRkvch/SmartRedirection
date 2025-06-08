#include "KafkaLoggerAdapter.h"
#include "iostream"

KafkaLoggarAdapter::KafkaLoggarAdapter(const std::string& broker, const std::string& topic) : producer(broker, topic)
{
	std::cout << "Kafla Logger connected succeed!" << std::endl;
}

void KafkaLoggarAdapter::log(const std::string& message)
{
	std::lock_guard<std::mutex> lock(log_mutex);	// захват мьютекса

	try {
		producer.produce(message);
	}
	catch (std::exception& e)
	{
		std::cerr << "[" << std::this_thread::get_id() << "] "
			<< "Logging error: " << e.what() << std::endl;
	}
}
