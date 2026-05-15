#pragma once

#include "RE/B/BGSSaveLoadScrapBuffer.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class __declspec(novtable) BGSLoadGameBuffer
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSLoadGameBuffer };
		inline static constexpr auto VTABLE{ VTABLE::BGSLoadGameBuffer };

		virtual ~BGSLoadGameBuffer();

		// add
		virtual std::uint8_t GetVersion(); // 01

		GAME_HEAP_REDEFINE_NEW(BGSLoadGameBuffer);

		void LoadDataEndian(void* a_data, std::uint32_t a_offset, std::uint32_t a_size)
		{
			using FuncType = decltype(&BGSLoadGameBuffer::LoadDataEndian);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSLoadGameBuffer::LoadDataEndian };
			std::invoke(FUNC, this, a_data, a_offset, a_size);
		}

		// members
		BGSSaveLoadScrapBuffer buffer; // 08
		std::uint32_t bufferSize;	   // 20
		std::uint32_t bufferPosition;  // 24
	};
	static_assert(sizeof(BGSLoadGameBuffer) == 0x28);
}
