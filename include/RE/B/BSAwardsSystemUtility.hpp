#pragma once

namespace RE
{
	class __declspec(novtable) BSAwardsSystemUtility
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSAwardsSystemUtility };
		inline static constexpr auto VTABLE{ VTABLE::BSAwardsSystemUtility };

		virtual ~BSAwardsSystemUtility() = default; // 00

		[[nodiscard]] static BSAwardsSystemUtility& GetSingleton()
		{
			using FuncType = decltype(&BSAwardsSystemUtility::GetSingleton);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSAwardsSystemUtility::Singleton };
			return std::invoke(FUNC);
		}

		// add
		virtual void DoInitialize();				   // 01 - { return; }
		virtual void DoClearAward(std::int32_t a_id);  // 02 - { return; }
		virtual void DoDestroy();					   // 03 - { return; }
		virtual void DoRegister();					   // 04 - { return; }
		virtual void DoUnlockAward(std::int32_t a_id); // 05 - { return; }
		virtual bool DoGetUltimateAwardEarned() const; // 06 - { return false; }
	};
	static_assert(sizeof(BSAwardsSystemUtility) == 0x08);
}
