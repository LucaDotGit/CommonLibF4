#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSoundHandle.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/TESObjectREFR.hpp"

namespace RE
{
	class NiLight;

	class __declspec(novtable) Hazard : public TESObjectREFR // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::Hazard;
		inline static constexpr const auto& VTABLE = VTABLE::Hazard;
		inline static constexpr auto FORM_TYPE = FormType::PlacedHazard;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t; // To-Do

		// members
		void* hazardDBHandle;	  // 0x110 - To-Do: `BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>,
								  // BSResource::EntryDBTraits<BSModelDB::DBTraits,
								  // BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>,
								  // BSResource::EntryDB<BSModelDB::DBTraits>>`
		ActorHandle ownerActor;	  // 0x118
		REX::Float32 age;		  // 0x11C
		REX::Float32 lifetime;	  // 0x120
		REX::Float32 targetTimer; // 0x124
		REX::Float32 radius;	  // 0x128
		REX::Float32 magnitude;	  // 0x12C
		BGSHazard* hazard;		  // 0x130
		NiPointer<NiLight> light; // 0x138
		BSSoundHandle sound;	  // 0x140
		REX::EnumSet<Flags, std::uint32_t> flags; // 0x148
	};

	static_assert(sizeof(Hazard) == 0x150);
}
