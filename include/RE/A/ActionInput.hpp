#pragma once

#include "RE/N/NiPointer.hpp"

namespace RE
{
	class __declspec(novtable) ActionInput
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ActionInput };
		inline static constexpr auto VTABLE{ VTABLE::ActionInput };

		enum class ACTIONPRIORITY : std::int32_t
		{
			kImperative = 0,
			kQueue = 1,
			kTry = 2
		};

		class Data
		{
		public:
			// members
			union
			{
				std::int32_t int32;
				std::uint32_t uint32;
				REX::Float32 float32;
			}; // 00
		};

		virtual ~ActionInput(); // 00

		// members
		NiPointer<TESObjectREFR> ref;					  // 08
		NiPointer<TESObjectREFR> targetRef;				  // 10
		BGSAction* action;								  // 18
		REX::Enum<ACTIONPRIORITY, std::int32_t> priority; // 20
		Data actionData;								  // 24
	};
	static_assert(sizeof(ActionInput) == 0x28);
}
