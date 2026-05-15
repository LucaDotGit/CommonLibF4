#pragma once

namespace RE
{
	enum class hknpCollisionFlags : std::uint32_t
	{
		kIsStatic = 1 << 0,
		kIsDynamic = 1 << 1,
		kIsKeyframed = 1 << 2,
		kIsActive = 1 << 3,
		kRaiseTriggerEvents = 1 << 4,
		kRaiseManifoldStatusEvents = 1 << 5,
		kRaiseManifoldProcessedEvents = 1 << 6,
		kRaiseContactImpulseEvents = 1 << 7,
		kDontCollide = 1 << 8,
		kDontBuildContactJacobians = 1 << 9,
		kTempRebuildCollisionCaches = 1 << 10,
		kTempDropNewCvxCvxCollisions = 1 << 11,
		kTempBodyOrAABBIsModified = 1 << 12,
		kTempRebuildContactCaches = 1 << 13,
		kIsNonRuntime = 1 << 14,
		kIsBreakable = 1 << 15,
		kUserFlag0 = 1 << 16,
		kUserFlag1 = 1 << 17,
		kUserFlag2 = 1 << 18,
		kUserFlag3 = 1 << 19,
		kEnableRestitution = 1 << 20,
		kEnableTriggerModifier = 1 << 21,
		kEnableImpulseClipping = 1 << 22,
		kEnableMassChanger = 1 << 23,
		kEnableSoftContacts = 1 << 24,
		kEnableSurfaceVelocity = 1 << 25,
		kUserFlag4 = 1 << 26,
		kUserFlag5 = 1 << 27,
		kUserFlag6 = 1 << 28,

		kMaskInternalBodyFlags = kIsStatic |
								 kIsDynamic |
								 kIsKeyframed |
								 kIsActive,

		kMaskTempFlags = kTempRebuildCollisionCaches |
						 kTempDropNewCvxCvxCollisions |
						 kTempBodyOrAABBIsModified |
						 kTempRebuildContactCaches,

		kMaskAutoMaterialFlags = kEnableRestitution |
								 kEnableTriggerModifier |
								 kEnableImpulseClipping |
								 kEnableMassChanger |
								 kEnableSoftContacts |
								 kEnableSurfaceVelocity,

		kMaskAllFlags = std::numeric_limits<std::uint32_t>::max()
	};
}
