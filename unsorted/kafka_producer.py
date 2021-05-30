import json
from kafka import KafkaProducer

KAFKA_TOPIC = 'TOPIC'
KAFKA_BROKERS = 'localhost:9092'
JSON_FILE = 'filename.json'


def main():
    with open(JSON_FILE, 'r', encoding="utf-8") as json_file:
        data = json.load(json_file)

    producer = KafkaProducer(value_serializer=lambda v: json.dumps(v).encode('utf-8'), bootstrap_servers=KAFKA_BROKERS)

    producer.send(KAFKA_TOPIC, data)

    producer.close()


if __name__ == "__main__":
    main()
