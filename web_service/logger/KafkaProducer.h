#ifndef KAFKAPRODUCER_H_INCLUDED
#define KAFKAPRODUCER_H_INCLUDED

#include <string>
#include <librdkafka/rdkafkacpp.h>

class KafkaProducer {
public:
    KafkaProducer(const std::string& broker, const std::string& topic_name);
    ~KafkaProducer();
    void produce(const std::string& message);

private:
    RdKafka::Producer* producer;
    RdKafka::Topic* topic;
    std::string topic_name;
};


#endif