#include "KafkaProducer.h"
#include <stdexcept>

KafkaProducer::KafkaProducer(const std::string& broker, const std::string& name)
    : topic_name(name) {

    std::string errstr;

    RdKafka::Conf* conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    if (!conf) {
        throw std::runtime_error("KafkaProducer: failed to create Kafka config");
    }

    if (conf->set("bootstrap.servers", broker, errstr) != RdKafka::Conf::CONF_OK) {
        delete conf;
        throw std::runtime_error("KafkaProducer: config error: " + errstr);
    }

    // Настройки надежности
    conf->set("socket.timeout.ms", "5000", errstr);
    conf->set("message.timeout.ms", "30000", errstr);
    conf->set("request.required.acks", "all", errstr);

    producer = RdKafka::Producer::create(conf, errstr);
    delete conf;

    if (!producer) {
        throw std::runtime_error("KafkaProducer: failed to create producer: " + errstr);
    }
    // Проверка подключения
    RdKafka::Metadata* metadata;
    if (producer->metadata(false, nullptr, &metadata, 5000) != RdKafka::ERR_NO_ERROR) {
        delete producer;
        throw std::runtime_error("KafkaProducer: cannot connect to Kafka brokers");
    }
    delete metadata;

    RdKafka::Conf* topic_conf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);
    if (!topic_conf) {
        throw std::runtime_error("KafkaProducer: failed to create topic config");
    }

    topic = RdKafka::Topic::create(producer, topic_name, nullptr, errstr);
    delete topic_conf;

    if (!topic) {
        delete producer;
        throw std::runtime_error("KafkaProducer: failed to create topic: " + errstr);
    }

}

KafkaProducer::~KafkaProducer() {
    // Очистка в обратном порядке создания
    if (topic) {
        delete topic;
    }

    if (producer) {
        // Вызываем flush для отправки всех сообщений и ожидания завершения
        producer->flush(5000); // 5 секунд таймаут

        delete producer;
    }
}

void KafkaProducer::produce(const std::string& message) {
    if (!producer || !topic) {
        throw std::runtime_error("KafkaProducer: producer not initialized");
    }

    RdKafka::ErrorCode resp = producer->produce(
        topic,
        RdKafka::Topic::PARTITION_UA,
        RdKafka::Producer::RK_MSG_COPY,
        const_cast<char*>(message.data()),
        message.size(),
        nullptr,
        nullptr
    );

    if (resp != RdKafka::ERR_NO_ERROR) {
        
        throw std::runtime_error("KafkaProducer: produce failed :" + RdKafka::err2str(resp));
    }
    producer->poll(0);
}
