#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BGSSaveLoadBuffer;

	class __declspec(novtable) BGSSaveGameBuffer
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSSaveGameBuffer;
		inline static constexpr const auto& VTABLE = VTABLE::BGSSaveGameBuffer;

		virtual ~BGSSaveGameBuffer();

		// add
		virtual auto GetForm() -> TESForm*;			   // 0x01 - { return nullptr; }
		virtual auto GetReference() -> TESObjectREFR*; // 0x02 - { return nullptr; }
		virtual auto GetActor() -> Actor*;			   // 0x03 - { return nullptr; }

		GAME_HEAP_REDEFINE_NEW(BGSSaveGameBuffer);

		void SaveDataEndian(const void* a_data, std::uint32_t a_size)
		{
			using FuncType = decltype(&BGSSaveGameBuffer::SaveDataEndian);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSSaveGameBuffer::SaveDataEndian);
			std::invoke(FUNC, this, a_data, a_size);
		}

		// members
		BGSSaveLoadBuffer* buffer;	  // 0x08
		std::uint32_t size;			  // 0x10
		std::uint32_t bufferPosition; // 0x14
	};

	static_assert(sizeof(BGSSaveGameBuffer) == 0x18);
}
