#pragma once

#include "RE/B/BSInputEventUser.hpp"
#include "RE/P/PlayerControlsData.hpp"

namespace RE
{
	class __declspec(novtable) PlayerInputHandler
		: public BSInputEventUser // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PlayerInputHandler };
		inline static constexpr auto VTABLE{ VTABLE::PlayerInputHandler };

		explicit PlayerInputHandler(const PlayerControlsData& a_data) noexcept
			: data(a_data)
		{
		}

		~PlayerInputHandler() override = default; // 00

		// add
		virtual void PerFrameUpdate() { return; } // 09

		// members
		const PlayerControlsData& data; // 10 - NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
		bool inQuickContainer{ false }; // 18
	};
	static_assert(sizeof(PlayerInputHandler) == 0x20);
}
