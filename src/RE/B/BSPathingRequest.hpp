#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSPathingActorAttributes.hpp"
#include "RE/B/BSPathingGoal.hpp"
#include "RE/B/BSPathingRestrictions.hpp"
#include "RE/B/BSPathingSearchParameters.hpp"
#include "RE/B/BSPathingStart.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/M/MeanderSettingsData.hpp"
#include "RE/M/MovementActorAvoidanceParameters.hpp"

namespace RE
{
	class BSPathingStreamRead;
	class BSPathingStreamWrite;
	class IDebugText;
	class IMovementParameters;

	class __declspec(novtable) BSPathingRequest : public BSIntrusiveRefCounted // 0x008
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSPathingRequest;
		inline static constexpr const auto& VTABLE = VTABLE::BSPathingRequest;

		virtual ~BSPathingRequest();							 // 0x00
		virtual auto GetType() -> std::uint32_t;				 // 0x01
		virtual void CopyTo(BSPathingRequest& a_target);		 // 0x02
		virtual void Write(BSPathingStreamWrite& a_target);		 // 0x03
		virtual void Read(BSPathingStreamRead& a_source);		 // 0x04
		virtual void CheckValid();								 // 0x05
		virtual void PrintDebugText(IDebugText& a_outDebugText); // 0x06
		virtual auto UpdateRequest() -> bool;					 // 0x07

		// members
		BSPathingStart start;									// 0x010
		BSPathingGoal goal;										// 0x048
		BSPathingRestrictions restrictions;						// 0x098
		BSPathingSearchParameters searchParameters;				// 0x0B0
		BSPathingActorAttributes actorAttributes;				// 0x0C0
		MovementActorAvoidanceParameters avoidanceParameters;	// 0x0E0
		BSTSmartPointer<IMovementParameters> defaultParameters; // 0x100
		MeanderSettingsData meanderSettings;					// 0x108
		BSTArray<BSPathingStart> optionalStartArray;			// 0x120
		bool shouldMotionCorrectStartIdle;						// 0x138
		bool requiresPathStartIdle;								// 0x139
		bool disablePathEndIdle;								// 0x13A
	};

	static_assert(sizeof(BSPathingRequest) == 0x140);
}
