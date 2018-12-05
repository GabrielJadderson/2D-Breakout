#pragma once
#include "pch.h"




inline float lerp(float v0, float v1, float t) {
	return v0 + t * (v1 - v0);
}

using byte = unsigned char;

template<typename T>
static std::array<byte, sizeof(T)> to_bytes(const T& object)
{
	std::array<byte, sizeof(T) > bytes;

	const byte* begin = reinterpret_cast<const byte*>(std::addressof(object));
	const byte* end = begin + sizeof(T);
	std::copy(begin, end, std::begin(bytes));

	return bytes;
}

template<typename T>
static T& from_bytes(const std::array< byte, sizeof(T) >& bytes, T& object)
{
	// http://en.cppreference.com/w/cpp/types/is_trivially_copyable
	static_assert(std::is_trivially_copyable<T>::value, "not a TriviallyCopyable type");

	byte* begin_object = reinterpret_cast<byte*>(std::addressof(object));
	std::copy(std::begin(bytes), std::end(bytes), begin_object);

	return object;
}

class Util
{
public:

	static char* CopyString(const std::string& s);
	static std::string ConvertToStringAndAddNull(char* s, int length);
	static std::string ConvertToString(char* s, int length);

protected:
private:
};
