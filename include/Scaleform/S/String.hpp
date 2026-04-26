#pragma once

namespace Scaleform
{
	class String
	{
	public:
		class DataDesc
		{
		public:
			// members
			std::uint64_t size;				// 00
			volatile std::int32_t refCount; // 08
			std::array<char, 1> data;		// 0C
		};
		static_assert(sizeof(DataDesc) == 0x10);

		[[nodiscard]] const char* data() const noexcept
		{
			return std::bit_cast<const char*>((heapTypeBits & 0xFFFFFFFFFFFFFFFC) + 12);
		}

		[[nodiscard]] const char* c_str() const noexcept
		{
			return data();
		}

		[[nodiscard]] bool empty() const noexcept
		{
			return ((heapTypeBits & 0xFFFFFFFFFFFFFFFC) & 0x7FFFFFFFFFFFFFFF) == 0;
		}

		// members
		union
		{
			DataDesc* dataDesc{ nullptr };
			std::uint64_t heapTypeBits;
		}; // 00
	};
	static_assert(sizeof(String) == 0x08);
}
