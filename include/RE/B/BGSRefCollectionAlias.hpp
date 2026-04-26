#pragma once

#include "RE/B/BGSRefAlias.hpp"

namespace RE
{
	class __declspec(novtable) BGSRefCollectionAlias
		: public BGSRefAlias // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSRefCollectionAlias };
		inline static constexpr auto VTABLE{ VTABLE::BGSRefCollectionAlias };
		inline static constexpr auto FORM_TYPE{ FormType::kRefCollectionAlias };
		inline static constexpr auto ALIAS_TYPE{ "RefColl"sv };

		~BGSRefCollectionAlias() override; // 00

		// override (BGSBaseAlias)
		bool Load() override;						   // 01
		void InitItem() override;					   // 02
		const BSFixedString& QType() const override;   // 03
		TESQuest* QExternalQuest() const override;	   // 04
		void ClearExternalQuest() override;			   // 05
		void UpdateFromExternalAlias() const override; // 06
		BGSBaseAlias* GetLinkedAlias() const override; // 07

		// members
		std::uint8_t maxInitialCount; // 48
	};
	static_assert(sizeof(BGSRefCollectionAlias) == 0x50);

	extern template bool BGSBaseAlias::Is<BGSRefCollectionAlias>() const noexcept;
	extern template bool BGSBaseAlias::IsNot<BGSRefCollectionAlias>() const noexcept;

	extern template BGSRefCollectionAlias* BGSBaseAlias::As<BGSRefCollectionAlias>() noexcept;
	extern template const BGSRefCollectionAlias* BGSBaseAlias::As<BGSRefCollectionAlias>() const noexcept;
}
