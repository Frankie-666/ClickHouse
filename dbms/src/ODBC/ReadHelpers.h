#pragma once

#include <iostream>
#include <stdexcept>


/// В формате VarUInt.
inline void readSize(uint64_t & res, std::istream & istr)
{
	static constexpr auto MAX_LENGTH_OF_SIZE = 4;	/// Ограничивает размер 256 мегабайтами (2 ^ (7 * 4)).

	res = 0;
	for (size_t i = 0; i < MAX_LENGTH_OF_SIZE; ++i)
	{
		int byte = istr.get();

		if (byte == EOF)
			throw std::runtime_error("Incomplete result received.");

		res |= (static_cast<uint64_t>(byte) & 0x7F) << (7 * i);

		if (!(byte & 0x80))
			return;
	}

	throw std::runtime_error("Too large size.");
}


inline void readString(std::string & res, std::istream & istr)
{
	uint64_t size = 0;
	readSize(size, istr);

	res.resize(size);
	istr.read(&res[0], size);

	if (!istr.good())
		throw std::runtime_error("Incomplete result received.");
}
