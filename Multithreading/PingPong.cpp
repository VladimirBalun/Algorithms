#include <atomic>
#include <thread>
#include <string>
#include <cstdint>
#include <iostream>

#define PING_STATE true
#define PONG_STATE false
#define COUNT_MESSAGES 500

std::atomic_bool flag{true};

void write_message(const std::string& message, bool current_state)
{
    std::uint16_t counter = 0;
    while (counter != COUNT_MESSAGES)
    {
        if (current_state == flag.load())
        {
            std::cout << message << "\n";
            flag.store(!current_state);
            counter++;
        }
        else
        {
            std::this_thread::yield();
        }
    }
}

int main()
{
    std::thread ping_thread(write_message, "ping", PING_STATE);
    std::thread pong_thread(write_message, "pong", PONG_STATE);
    ping_thread.detach();
    pong_thread.join();

    return EXIT_SUCCESS;
}
