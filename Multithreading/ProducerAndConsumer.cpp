#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <chrono>
#include <thread>
#include <mutex>

std::mutex mutex;
std::condition_variable conditionVar;

const short BUFF_SIZE = 10;
std::vector<int> buffer;

void produce() 
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));

		std::unique_lock<std::mutex> lock(mutex);
		conditionVar.wait(lock, [&]() { return buffer.size() < BUFF_SIZE; });
		int generatedValue = 1 + rand() % 50;
		std::cout << "Was produced: " << generatedValue << std::endl;
		buffer.push_back(generatedValue);
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
		std::cout << "Was consumed: " << buffer.at(buffer.size() - 1) << std::endl;
		buffer.pop_back();
		conditionVar.notify_one();
	}
}

int main()
{	
	std::thread consumer(consume);
	std::thread producer(produce);
	
	consumer.detach();
	producer.join();

	return EXIT_SUCCESS;
}