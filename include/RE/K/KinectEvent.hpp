#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/I/IDEvent.hpp"

namespace RE
{
	class __declspec(novtable) KinectEvent
		: public IDEvent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::KinectEvent };
		inline static constexpr auto VTABLE{ VTABLE::KinectEvent };
		inline static constexpr auto INPUT_TYPE{ INPUT_EVENT_TYPE::kKinect };

		~KinectEvent() override = default; // 00

		// members
		BSFixedString strHeard; // 38
	};
	static_assert(sizeof(KinectEvent) == 0x40);

	extern template KinectEvent* InputEvent::As() noexcept;
	extern template const KinectEvent* InputEvent::As() const noexcept;
}
