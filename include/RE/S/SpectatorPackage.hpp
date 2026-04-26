#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/TESPackage.hpp"

namespace RE
{
	class NiAVObject;
	class SpectatorThreatInfo;

	class __declspec(novtable) SpectatorPackage
		: public TESPackage // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::SpectatorPackage };
		inline static constexpr auto VTABLE{ VTABLE::SpectatorPackage };
		inline static constexpr auto FORM_TYPE{ FormType::kPackage };

		~SpectatorPackage() override; // 00

		// members
		std::uint64_t lastPathRequestTime;		   // 0C8
		REX::Float32 timer;						   // 0D0
		REX::Float32 conversationTimer;			   // 0D4
		REX::Float32 eventRadius;				   // 0D8
		bool flagCompleted;						   // 0DC
		NiPoint3 eventCenter;					   // 0E0
		BSTArray<SpectatorThreatInfo> threatInfos; // 0F0
		NiPointer<NiAVObject> debugGeometry;	   // 108
	};
	static_assert(sizeof(SpectatorPackage) == 0x110);
}
