#pragma once

#include <memory>
#include <stdexcept>
#include <string>

template <typename ... Args>
inline std::string StringFormat(const std::string& format, Args... args)
{
	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	if (size <= 0)
	{
		throw std::runtime_error("Error during formatting.");
	}
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

template <typename T>
inline int Sign(T val)
{
	return (T(0) < val) - (val < T(0));
}

template <typename T>
inline bool InRange(T _value, T _min, T _max)
{
	return _value >= _min && _value <= _max;
}

template<typename Base, typename T>
inline bool InstanceOf(const T*)
{
	return std::is_base_of<Base, T>::value;
}

template<typename Base, typename T>
inline bool InstanceOf(const T&)
{
	return std::is_base_of<Base, T>::value;
}
