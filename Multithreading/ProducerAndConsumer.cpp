#include <iostream>
#include <queue>
#include <random>
#include <ctime>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mutex;
std::condition_variable conditionVar;

std::queue<int> buffer;

void produce()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::unique_lock<std::mutex> lock(mutex);
        conditionVar.wait(lock, [&]() { return buffer.size() < 2; });
        int generatedValue = 1 + rand() % 50;
        std::cout << "Was produced: " << generatedValue << std::endl;
        buffer.push(generatedValue);
        conditionVar.notify_one();
    }
}

void consume()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::unique_lock<std::mutex> lock(mutex);
        conditionVar.wait(lock, [&]() { return !buffer.empty(); });
        std::cout << "Was consumed: " << buffer.front() << std::endl;
        buffer.pop();
        conditionVar.notify_one();
    }
}

int main()
{
    std::thread consumer(consume);
    std::thread producer(produce);

    consumer.join();
    producer.detach();

    return EXIT_SUCCESS;
}
