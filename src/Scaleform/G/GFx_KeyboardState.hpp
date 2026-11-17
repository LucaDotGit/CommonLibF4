#pragma once

#include "Scaleform/R/RefCountBase.hpp"

namespace Scaleform::GFx
{
	class EventId;
	class InteractiveObject;

	class __declspec(novtable) KeyboardState : public RefCountBase<KeyboardState, 2> // 0x00
	{
	public:
		class __declspec(novtable) IListener
		{
		public:
			virtual ~IListener(); // 0x00

			// add
			virtual void OnKeyDown(
				InteractiveObject* a_movie,
				const EventId& a_eventID,
				std::int32_t a_keyMask) = 0; // 0x01
			virtual void OnKeyUp(
				InteractiveObject* a_movie,
				const EventId& a_eventID,
				std::int32_t a_keyMask) = 0;				   // 0x02
			virtual void Update(const EventId& a_eventID) = 0; // 0x03
		};

		static_assert(sizeof(IListener) == 0x08);

		~KeyboardState() override; // 0x00

		// members
		std::array<std::byte, 0x688 - 0x10> unk00; // 0x10 - To-Do
	};

	static_assert(sizeof(KeyboardState) == 0x688);
}
