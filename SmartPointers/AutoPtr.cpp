#include <iostream>
#include <vector>
#include <memory>

template<typename T>
struct auto_ptr_ref 
{
	T* m_pointer;	

	auto_ptr_ref(T* pointer = nullptr) noexcept
		: m_pointer(pointer) {}	
};

template<typename T>
class auto_ptr
{
	using element_type = T;
public:
	explicit auto_ptr(T* pointer = nullptr) noexcept
		: m_pointer(pointer) {}
	auto_ptr(auto_ptr& other) noexcept
		: m_pointer(other.release()) {}
	template<typename U>
	auto_ptr(auto_ptr<U>& other) noexcept
		: m_pointer(other.release()) {}
	auto_ptr(auto_ptr_ref<T> other) noexcept
		: m_pointer(other.m_pointer) {}
	T& operator=(auto_ptr& other) noexcept;
	template<typename U>
	T& operator=(auto_ptr<U>& other) noexcept;
	T& operator=(auto_ptr_ref<T> other) noexcept;	
	~auto_ptr();
	T& operator*() const noexcept;
	T* operator->() const noexcept;
	T* get() const noexcept;
	T* release() noexcept;
	void reset(T* pointer = nullptr) noexcept;
	template<typename U>
	operator auto_ptr<U>() noexcept;
	template<typename U>
	operator auto_ptr_ref<U>() noexcept;
private:
	T* m_pointer;
};

template<>
class auto_ptr<void>
{
public:
	using element_type = void;
};

template<typename T>
T& auto_ptr<T>::operator = (auto_ptr& other) noexcept
{
	reset(other.release());
 	return *this;
}

template<typename T>
template<typename U>
T& auto_ptr<T>::operator = (auto_ptr<U>& other) noexcept
{
	reset(other.release());
	return *this;
}

template<typename T>
T& auto_ptr<T>::operator = (auto_ptr_ref<T> other) noexcept
{
	reset(other.m_pointer);
	return *this;
}

template<typename T>
auto_ptr<T>::~auto_ptr()
{
	delete m_pointer;
}

template<typename T>
T& auto_ptr<T>::operator * () const noexcept
{
	assert(m_pointer && "auto_ptr is not valid.");
	return *m_pointer;
}

template<typename T>
T* auto_ptr<T>::operator -> () const noexcept
{
	assert(m_pointer && "auto_ptr is not valid.");
	return m_pointer;
}

template<typename T>
T* auto_ptr<T>::get() const noexcept
{
	return m_pointer;
}

template<typename T>
T* auto_ptr<T>::release() noexcept
{
	T* temp_pointer = m_pointer;
	m_pointer = nullptr;
	return temp_pointer;
}

template<typename T>
void auto_ptr<T>::reset(T* pointer) noexcept
{
	if (m_pointer != pointer)
	{
		delete m_pointer;
		m_pointer = pointer;
	}
}

template<typename T>
template<typename U>
auto_ptr<T>::operator auto_ptr<U>() noexcept
{
	return auto_ptr<U>(release());
}

template<typename T>
template<typename U>
auto_ptr<T>::operator auto_ptr_ref<U>() noexcept
{
	return auto_ptr_ref<U>(release());
}

int main()
{
	auto_ptr<int> smart_ptr{ new int() };
	auto_ptr<int> another_smart_ptr{ smart_ptr };

	auto_ptr_ref<int> smart_ptr_ref{ another_smart_ptr };

	std::vector<auto_ptr_ref<int>> vector_smart_ptr_refs{ 5u };
	for (auto ref : vector_smart_ptr_refs)
	{
		ref = smart_ptr_ref;
		assert(ref.m_pointer);
	}

	auto_ptr<int> result_smart_ptr{ smart_ptr_ref };
	assert(result_smart_ptr.get() && !smart_ptr.get() && !another_smart_ptr.get());

	return EXIT_SUCCESS;
}

