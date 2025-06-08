#ifndef KAFKALOGGERADAPTER_H
#define KAFKALOGGERADAPTER_H

#include "ILogger.h"
#include "KafkaProducer.h"
#include <mutex>

class KafkaLoggarAdapter : public ILogger
{
public:
	KafkaLoggarAdapter(const std::string& broker, const std::string& topic);
	void log(const std::string& massage) override;

private:
	KafkaProducer producer;
	std::mutex log_mutex;
};

#endif
