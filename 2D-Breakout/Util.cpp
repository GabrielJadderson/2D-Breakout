#include "pch.h"


char* Util::CopyString(const std::string& s)
{
	auto out = new char[s.length() + 1];
	strcpy_s(out, s.length() + 1, s.c_str());
	return out;
}

std::string Util::ConvertToStringAndAddNull(char* s, int length)
{
	auto out = new char[length + 1];
	strcpy_s(out, length, s);
	return std::string(out);
}

std::string Util::ConvertToString(char* s, int length)
{
	auto out = new char[length];
	strcpy_s(out, length, s);
	return std::string(out);
}



void bytesTest()
{
	double d = 123.456789;
	const auto bytes = to_bytes(d);

	std::cout << std::hex << std::setfill('0');
	for (byte b : bytes) std::cout << std::setw(2) << int(b) << ' ';
	std::cout << '\n';

	d = 0;
	from_bytes(bytes, d);
	std::cout << std::fixed << d << '\n';

	int arr[] = { 1, 63, 256, 511, 1024 };
	const auto array_bytes = to_bytes(arr);

	for (byte b : array_bytes) std::cout << std::setw(2) << int(b) << ' ';
	std::cout << '\n';

	for (int& v : arr) v = -1;
	from_bytes(array_bytes, arr);
	for (int v : arr) std::cout << std::dec << v << ' ';
	std::cout << '\n';
}