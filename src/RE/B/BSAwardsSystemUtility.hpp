#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class __declspec(novtable) BSAwardsSystemUtility
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSAwardsSystemUtility;
		inline static constexpr const auto& VTABLE = VTABLE::BSAwardsSystemUtility;

		virtual ~BSAwardsSystemUtility() = default; // 0x00

		// add
		virtual void DoInitialize();						   // 0x01 - { return; }
		virtual void DoClearAward(std::int32_t a_id);		   // 0x02 - { return; }
		virtual void DoDestroy();							   // 0x03 - { return; }
		virtual void DoRegister();							   // 0x04 - { return; }
		virtual void DoUnlockAward(std::int32_t a_id);		   // 0x05 - { return; }
		virtual auto DoGetUltimateAwardEarned() const -> bool; // 0x06 - { return false; }

		GAME_HEAP_REDEFINE_NEW(BSAwardsSystemUtility);

		[[nodiscard]]
		static auto GetSingleton() -> BSAwardsSystemUtility&
		{
			using FuncType = decltype(&BSAwardsSystemUtility::GetSingleton);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSAwardsSystemUtility::Singleton);
			return std::invoke(FUNC);
		}
	};

	static_assert(sizeof(BSAwardsSystemUtility) == 0x08);
}
