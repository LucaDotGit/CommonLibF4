#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSoundHandle.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/TESObjectREFR.hpp"

namespace RE
{
	class NiLight;

	class __declspec(novtable) Hazard
		: public TESObjectREFR // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::Hazard };
		inline static constexpr auto VTABLE{ VTABLE::Hazard };
		inline static constexpr auto FORM_TYPE{ FormType::kPlacedHazard };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t; // TODO

		// members
		void* hazardDBHandle;					  // 110 - TODO: `BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>, BSResource::EntryDBTraits<BSModelDB::DBTraits, BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSModelDB::DBTraits>>`
		ActorHandle ownerActor;					  // 118
		REX::Float32 age;						  // 11C
		REX::Float32 lifetime;					  // 120
		REX::Float32 targetTimer;				  // 124
		REX::Float32 radius;					  // 128
		REX::Float32 magnitude;					  // 12C
		BGSHazard* hazard;						  // 130
		NiPointer<NiLight> light;				  // 138
		BSSoundHandle sound;					  // 140
		REX::EnumSet<Flags, std::uint32_t> flags; // 148
	};
	static_assert(sizeof(Hazard) == 0x150);
}
