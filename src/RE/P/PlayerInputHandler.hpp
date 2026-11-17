#pragma once

#include "RE/B/BSInputEventUser.hpp"
#include "RE/P/PlayerControlsData.hpp"

namespace RE
{
	class __declspec(novtable) PlayerInputHandler : public BSInputEventUser // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PlayerInputHandler;
		inline static constexpr const auto& VTABLE = VTABLE::PlayerInputHandler;

		explicit PlayerInputHandler(PlayerControlsData& a_data) noexcept :
			data(a_data)
		{
			REL::EmplaceVtable(this);
		}

		~PlayerInputHandler() override; // 0x00

		// add
		virtual void PerFrameUpdate(); // 0x09

		// members
		PlayerControlsData& data;	  // 0x10 - NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
		bool inQuickContainer{false}; // 0x18
	};

	static_assert(sizeof(PlayerInputHandler) == 0x20);
}
