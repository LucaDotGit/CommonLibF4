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
			std::size_t size;				// 0x00
			volatile std::int32_t refCount; // 0x08
			REX::StaticString<1> data;		// 0x0C
		};

		static_assert(sizeof(DataDesc) == 0x10);

		[[nodiscard]]
		auto data() const noexcept -> const char*
		{
			return std::bit_cast<const char*>((heapTypeBits & 0xFFFF'FFFF'FFFF'FFFC) + 12);
		}

		[[nodiscard]]
		auto c_str() const noexcept -> const char*
		{
			return data();
		}

		[[nodiscard]]
		auto empty() const noexcept -> bool
		{
			return ((heapTypeBits & 0xFFFF'FFFF'FFFF'FFFC) & 0x7FFF'FFFF'FFFF'FFFF) == 0;
		}

		// members
		union
		{
		public:
			DataDesc* dataDesc{nullptr};
			std::uint64_t heapTypeBits;
		}; // 0x00
	};

	static_assert(sizeof(String) == 0x08);
}
