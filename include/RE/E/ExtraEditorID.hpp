#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class __declspec(novtable) ExtraEditorID
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraEditorID };
		inline static constexpr auto VTABLE{ VTABLE::ExtraEditorID };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kEditorID };

		ExtraEditorID()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraEditorID() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		BSFixedString editorID; // 18
	};
	static_assert(sizeof(ExtraEditorID) == 0x20);
}
