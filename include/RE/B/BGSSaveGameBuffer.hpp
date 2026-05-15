#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BGSSaveLoadBuffer;

	class __declspec(novtable) BGSSaveGameBuffer
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSaveGameBuffer };
		inline static constexpr auto VTABLE{ VTABLE::BGSSaveGameBuffer };

		virtual ~BGSSaveGameBuffer();

		// add
		virtual TESForm* GetForm();			   // 01 - { return nullptr; }
		virtual TESObjectREFR* GetReference(); // 02 - { return nullptr; }
		virtual Actor* GetActor();			   // 03 - { return nullptr; }

		GAME_HEAP_REDEFINE_NEW(BGSSaveGameBuffer);

		void SaveDataEndian(const void* a_data, std::uint32_t a_size)
		{
			using FuncType = decltype(&BGSSaveGameBuffer::SaveDataEndian);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSaveGameBuffer::SaveDataEndian };
			std::invoke(FUNC, this, a_data, a_size);
		}

		// members
		BGSSaveLoadBuffer* buffer;	  // 08
		std::uint32_t size;			  // 10
		std::uint32_t bufferPosition; // 14
	};
	static_assert(sizeof(BGSSaveGameBuffer) == 0x18);
}
