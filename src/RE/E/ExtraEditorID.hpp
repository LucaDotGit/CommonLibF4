#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class __declspec(novtable) ExtraEditorID : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraEditorID;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraEditorID;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::EditorID;

		ExtraEditorID() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraEditorID() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		BSFixedString editorID; // 0x18
	};

	static_assert(sizeof(ExtraEditorID) == 0x20);
}
