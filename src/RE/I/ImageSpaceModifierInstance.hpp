#pragma once

#include "RE/N/NiObject.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class ImageSpaceModifierInstanceForm;
	class NiAVObject;

	class __declspec(novtable) ImageSpaceModifierInstance : public NiObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ImageSpaceModifierInstance;
		inline static constexpr const auto& VTABLE = VTABLE::ImageSpaceModifierInstance;

		enum class Flags : std::uint32_t
		{
			None = 0,
			Permanent = 1 << 0,
			Crossfade = 1 << 1,
			PreviousCrossfade = 1 << 2,
			MenuIMOD = 1 << 3,
			Stopped = 1 << 4
		};

		~ImageSpaceModifierInstance() override; // 0x00

		// add
		virtual auto IsExpired() -> bool;						  // 0x28
		virtual void Apply() = 0;								  // 0x29
		virtual void PrintInfo(char* a_buffer) = 0;				  // 0x2A
		virtual auto IsForm() -> ImageSpaceModifierInstanceForm*; // 0x2B

		void Stop()
		{
			using FuncType = decltype(&ImageSpaceModifierInstance::Stop);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ImageSpaceModifierInstance::Stop);
			std::invoke(FUNC, this);
		}

		// members
		REX::Float32 strength;					  // 0x10
		NiPointer<NiAVObject> target;			  // 0x18
		REX::Float32 age;						  // 0x20
		REX::EnumSet<Flags, std::uint32_t> flags; // 0x24
	};

	static_assert(sizeof(ImageSpaceModifierInstance) == 0x28);
}
