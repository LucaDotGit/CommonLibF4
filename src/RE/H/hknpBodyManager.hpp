#pragma once

#include "RE/H/hkArray.hpp"
#include "RE/H/hkBitField.hpp"
#include "RE/H/hkMap.hpp"
#include "RE/H/hknpBodyId.hpp"

namespace RE
{
	class hkAabb16;
	class hknpBody;
	class hknpMotionManager;
	class hknpWorld;
	class hkStringPtr;

	class hknpBodyManager
	{
	public:
		enum class ScheduledBodyFlagsEnum : std::uint16_t; // To-Do

		class BodyIterator
		{
		public:
			// members
			hknpBodyManager* bodyManager; // 0x00
			std::int32_t bodyIndex;		  // 0x08
		};

		static_assert(sizeof(BodyIterator) == 0x10);

		class PropertyBuffer
		{
		public:
			// members
			std::int32_t bufferSize{0};	  // 0x00
			std::int32_t propertySize{0}; // 0x04
			hkBitField occupancy;		  // 0x08
			void* properties{nullptr};	  // 0x20
		};

		static_assert(sizeof(PropertyBuffer) == 0x28);

		class ScheduledBodyChange
		{
		public:
			// members
			hknpBodyId bodyId;														// 0x00
			REX::EnumSet<ScheduledBodyFlagsEnum, std::uint16_t> scheduledBodyFlags; // 0x04
			std::uint32_t pendingAddIndex;											// 0x08
		};

		static_assert(sizeof(ScheduledBodyChange) == 0x0C);

		// members
		hknpWorld* world;								   // 0x00
		hknpMotionManager* motionManager;				   // 0x08
		hkArray<hknpBody> bodies;						   // 0x10
		bool bodyBufferIsUserOwned;						   // 0x20
		hknpBodyId firstFreeBodyId;						   // 0x24
		hkArray<hkAabb16> previousAabbs;				   // 0x28
		hkArray<hkStringPtr> bodyNames;					   // 0x38
		hkMap<std::uint16_t, PropertyBuffer*> propertyMap; // 0x48
		std::uint32_t numAllocatedBodies;				   // 0x58
		std::uint32_t numMarkedBodies;					   // 0x5C
		std::uint32_t peakBodyIndex;					   // 0x60
		hkArray<hknpBodyId> activeBodyIds;				   // 0x68
		hkArray<std::uint8_t> bodyIdToCellIndexMap;		   // 0x78
		hkArray<ScheduledBodyChange> scheduledBodyChanges; // 0x88
		hkArray<std::uint32_t> scheduledBodyChangeIndices; // 0x98
		hkArray<hknpBodyId> bodiesToAddAsActive;		   // 0xA8
		hkArray<hknpBodyId> bodiesToAddAsInactive;		   // 0xB8
	};

	static_assert(sizeof(hknpBodyManager) == 0xC8);
}
