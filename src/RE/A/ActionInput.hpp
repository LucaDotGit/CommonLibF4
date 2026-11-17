#pragma once

#include "RE/N/NiPointer.hpp"

namespace RE
{
	class __declspec(novtable) ActionInput
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ActionInput;
		inline static constexpr const auto& VTABLE = VTABLE::ActionInput;

		enum class ACTIONPRIORITY : std::int32_t
		{
			Imperative = 0,
			Queue = 1,
			Try = 2
		};

		virtual ~ActionInput(); // 0x00

		// members
		NiPointer<TESObjectREFR> ref;					  // 0x08
		NiPointer<TESObjectREFR> targetRef;				  // 0x10
		BGSAction* action;								  // 0x18
		REX::Enum<ACTIONPRIORITY, std::int32_t> priority; // 0x20

		struct
		{
		public:
			// members
			union
			{
			public:
				std::int32_t int32;
				std::uint32_t uint32;
				REX::Float32 float32;
			}; // 0x00
		} actionData; // 0x24
	};

	static_assert(sizeof(ActionInput) == 0x28);
}
