#pragma once

#include "RE/B/BGSRefAlias.hpp"

namespace RE
{
	class __declspec(novtable) BGSRefCollectionAlias : public BGSRefAlias // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSRefCollectionAlias;
		inline static constexpr const auto& VTABLE = VTABLE::BGSRefCollectionAlias;
		inline static constexpr auto FORM_TYPE = FormType::RefCollectionAlias;
		inline static constexpr auto ALIAS_TYPE = "RefColl"sv;

		~BGSRefCollectionAlias() override; // 0x00

		// override (BGSBaseAlias)
		auto Load() -> bool override;						   // 0x01
		void InitItem() override;							   // 0x02
		auto QType() const -> const BSFixedString& override;   // 0x03
		auto QExternalQuest() const -> TESQuest* override;	   // 0x04
		void ClearExternalQuest() override;					   // 0x05
		void UpdateFromExternalAlias() const override;		   // 0x06
		auto GetLinkedAlias() const -> BGSBaseAlias* override; // 0x07

		// members
		std::uint8_t maxInitialCount; // 0x48
	};

	static_assert(sizeof(BGSRefCollectionAlias) == 0x50);
}
