#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/TESPackage.hpp"

namespace RE
{
	class NiAVObject;
	class SpectatorThreatInfo;

	class __declspec(novtable) SpectatorPackage : public TESPackage // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::SpectatorPackage;
		inline static constexpr const auto& VTABLE = VTABLE::SpectatorPackage;
		inline static constexpr auto FORM_TYPE = FormType::Package;

		~SpectatorPackage() override; // 0x00

		// members
		std::uint64_t lastPathRequestTime;		   // 0x0C8
		REX::Float32 timer;						   // 0x0D0
		REX::Float32 conversationTimer;			   // 0x0D4
		REX::Float32 eventRadius;				   // 0x0D8
		bool flagCompleted;						   // 0x0DC
		NiPoint3 eventCenter;					   // 0x0E0
		BSTArray<SpectatorThreatInfo> threatInfos; // 0x0F0
		NiPointer<NiAVObject> debugGeometry;	   // 0x108
	};

	static_assert(sizeof(SpectatorPackage) == 0x110);
}
