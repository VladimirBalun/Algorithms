#include <iostream>

// | 5 | 6 | 7 | 8 | 9 | 10 | 4 |

template<typename T, size_t N>
class CircularBuffer
{
public:
	void push(const T& value)
	{
		if (m_write_index == m_read_index && m_size != 0u)
			m_read_index = (m_read_index + 1) % N;

		m_buffer[m_write_index++] = value;
		m_write_index %= N;

		if (m_size != N)
			++m_size;
	}

	T pop()
	{
		if (m_size == 0u)
			throw std::logic_error("buffer is empty");

		T value = m_buffer[m_read_index];
		m_buffer[m_read_index++].~T();
		m_read_index %= N;
		--m_size;

		return value;
	}

private:
	T m_buffer[N];
	size_t m_size = 0u;
	size_t m_write_index = N / 2;
	size_t m_read_index = N / 2;
};

int main(int argc, char** argv)
{
	CircularBuffer<int, 7> buffer;

	buffer.push(1);
	buffer.push(2);
	buffer.push(3);
	assert(buffer.pop() == 1);
	assert(buffer.pop() == 2);

	buffer.push(4);
	buffer.push(5);
	buffer.push(6);
	buffer.push(7);
	buffer.push(8);
	buffer.push(9);
	buffer.push(10);
	assert(buffer.pop() == 4);
	assert(buffer.pop() == 5);
	assert(buffer.pop() == 6);
	assert(buffer.pop() == 7);
	assert(buffer.pop() == 8);
	assert(buffer.pop() == 9);
	assert(buffer.pop() == 10);

	return EXIT_SUCCESS;
}