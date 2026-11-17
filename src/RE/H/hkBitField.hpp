#pragma once

#include "RE/H/hkArray.hpp"
#include "RE/H/hkLocalArray.hpp"

namespace RE
{
	template <class T>
	class hkBitFieldStorage
	{
	public:
		// members
		T words;			  // 0x00
		std::int32_t numBits; // 0x??
	};

	template <class T>
	class hkOffsetBitFieldStorage
	{
	public:
		// members
		T words;			 // 0x00
		std::int32_t offset; // 0x??
	};

	template <class T>
	class hkBitFieldBase
	{
	public:
		// members
		T storage; // 0x00
	};

	class hkBitField : public hkBitFieldBase<hkBitFieldStorage<hkArray<std::uint32_t>>>
	{
	public:
	};

	class hkBitFieldEx : public hkBitField // 0x00
	{
	public:
	};

	class hkOffsetBitField : public hkBitFieldBase<hkOffsetBitFieldStorage<hkArray<std::uint32_t>>>
	{
	public:
	};

	class hkOffsetBitFieldLocal : public hkBitFieldBase<hkOffsetBitFieldStorage<hkLocalArray<std::uint32_t>>>
	{
	public:
	};
}
