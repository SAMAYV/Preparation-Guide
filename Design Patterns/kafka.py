from dataclasses import dataclass
from typing import Dict, List, Optional
from collections import defaultdict
import threading
import hashlib

@dataclass
class Message:
    key: str
    value: str
    offset: int


class Partition:
    def __init__(self, partition_id: int):
        self.partition_id = partition_id
        self.messages: List[Message] = []
        self.lock = threading.Lock()

    def append(self, key: str, value: str) -> int:
        with self.lock:
            offset = len(self.messages)
            msg = Message(key=key, value=value, offset=offset)
            self.messages.append(msg)
            return offset

    def read(self, offset: int, max_messages: int):
        with self.lock:
            return self.messages[offset:offset + max_messages]
        

class Topic:
    def __init__(self, name: str, partitions: int):
        self.name = name
        self.partitions = [
            Partition(i)
            for i in range(partitions)
        ]

    def get_partition(self, key: str) -> Partition:
        partition_id = (
            int(hashlib.md5(key.encode()).hexdigest(), 16)
            % len(self.partitions)
        )
        return self.partitions[partition_id]
    

class Broker:
    def __init__(self):
        self.topics: Dict[str, Topic] = {}

    def create_topic(self, topic_name: str, partitions: int):
        if topic_name in self.topics:
            raise Exception("Topic exists")
        self.topics[topic_name] = Topic(topic_name, partitions)

    def get_topic(self, topic_name: str):
        return self.topics[topic_name]
    

class Producer:
    def __init__(self, broker: Broker):
        self.broker = broker

    def send(self, topic_name: str, key: str, value: str):
        topic = self.broker.get_topic(topic_name)
        partition = topic.get_partition(key)
        offset = partition.append(key, value)
        print(f"Published to partition {partition.partition_id} offset={offset}")


class OffsetManager:
    def __init__(self):
        self.offsets = defaultdict(dict)

    def commit(self, group_id: str, topic: str, partition: int, offset: int):
        self.offsets[group_id][(topic, partition)] = offset

    def get_offset(self, group_id: str, topic: str, partition: int):
        return self.offsets[group_id].get((topic, partition), 0)
    

class ConsumerGroup:
    def __init__(self, group_id: str):
        self.group_id = group_id
        self.consumers = []

    def add_consumer(self, consumer):
        self.consumers.append(consumer)

    def assign(self, partitions: List[Partition]):
        assignments = defaultdict(list)

        for idx, partition in enumerate(partitions):
            consumer = self.consumers[idx % len(self.consumers)]
            assignments[consumer].append(partition)

        for consumer, partitions in assignments.items():
            consumer.assign(partitions)

        return assignments
    

class Consumer:
    def __init__(self, consumer_id, group_id, broker, offset_manager):
        self.consumer_id = consumer_id
        self.group_id = group_id
        self.broker = broker
        self.offset_manager = offset_manager
        self.assigned_partitions = []

    def assign(self, partitions):
        self.assigned_partitions = partitions

    def poll(self, topic_name, batch_size=10):
        result = []
        for partition in self.assigned_partitions:
            offset = (
                self.offset_manager.get_offset(
                    self.group_id,
                    topic_name,
                    partition.partition_id
                )
            )
            msgs = partition.read(offset, batch_size)
            if msgs:
                result.extend(msgs)
                last_offset = msgs[-1].offset + 1
                self.offset_manager.commit(
                    self.group_id,
                    topic_name,
                    partition.partition_id,
                    last_offset
                )
        return result


def main():
    broker = Broker()
    broker.create_topic("orders", partitions=3)

    producer = Producer(broker)
    producer.send("orders", "user1", "order-1")
    producer.send("orders", "user2", "order-2")
    producer.send("orders", "user3", "order-3")

    offset_manager = OffsetManager()

    c1 = Consumer("c1", "group1", broker, offset_manager)
    c2 = Consumer("c2", "group1", broker, offset_manager)

    consumer_group = ConsumerGroup("group1")
    consumer_group.add_consumer(c1)
    consumer_group.add_consumer(c2)

    topic = broker.get_topic("orders")

    consumer_group.assign(topic.partitions)

    print("Consumer 1")
    print(c1.poll("orders"))

    print("Consumer 2")
    print(c2.poll("orders"))


if __name__ == "__main__":
    main()
