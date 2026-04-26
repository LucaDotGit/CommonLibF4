#pragma once

#include "RE/N/NiObject.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class ImageSpaceModifierInstanceForm;
	class NiAVObject;

	class __declspec(novtable) ImageSpaceModifierInstance
		: public NiObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ImageSpaceModifierInstance };
		inline static constexpr auto VTABLE{ VTABLE::ImageSpaceModifierInstance };

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kPermanent = 1 << 0,
			kCrossfade = 1 << 1,
			kPreviousCrossfade = 1 << 2,
			kMenuIMOD = 1 << 3,
			kStopped = 1 << 4
		};

		~ImageSpaceModifierInstance() override; // 00

		// add
		virtual bool IsExpired();						  // 28
		virtual void Apply() = 0;						  // 29
		virtual void PrintInfo(char* a_buffer) = 0;		  // 2A
		virtual ImageSpaceModifierInstanceForm* IsForm(); // 2B

		void Stop()
		{
			using FuncType = decltype(&ImageSpaceModifierInstance::Stop);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::ImageSpaceModifierInstance::Stop };
			FUNC(this);
		}

		// members
		REX::Float32 strength;					  // 10
		NiPointer<NiAVObject> target;			  // 18
		REX::Float32 age;						  // 20
		REX::EnumSet<Flags, std::uint32_t> flags; // 24
	};
	static_assert(sizeof(ImageSpaceModifierInstance) == 0x28);
}
