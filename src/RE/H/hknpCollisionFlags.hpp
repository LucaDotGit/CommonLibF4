#pragma once

namespace RE
{
	enum class hknpCollisionFlags : std::uint32_t
	{
		IsStatic = 1 << 0,
		IsDynamic = 1 << 1,
		IsKeyframed = 1 << 2,
		IsActive = 1 << 3,
		RaiseTriggerEvents = 1 << 4,
		RaiseManifoldStatusEvents = 1 << 5,
		RaiseManifoldProcessedEvents = 1 << 6,
		RaiseContactImpulseEvents = 1 << 7,
		DontCollide = 1 << 8,
		DontBuildContactJacobians = 1 << 9,
		TempRebuildCollisionCaches = 1 << 10,
		TempDropNewCvxCvxCollisions = 1 << 11,
		TempBodyOrAABBIsModified = 1 << 12,
		TempRebuildContactCaches = 1 << 13,
		IsNonRuntime = 1 << 14,
		IsBreakable = 1 << 15,
		UserFlag0 = 1 << 16,
		UserFlag1 = 1 << 17,
		UserFlag2 = 1 << 18,
		UserFlag3 = 1 << 19,
		EnableRestitution = 1 << 20,
		EnableTriggerModifier = 1 << 21,
		EnableImpulseClipping = 1 << 22,
		EnableMassChanger = 1 << 23,
		EnableSoftContacts = 1 << 24,
		EnableSurfaceVelocity = 1 << 25,
		UserFlag4 = 1 << 26,
		UserFlag5 = 1 << 27,
		UserFlag6 = 1 << 28,

		MaskInternalBodyFlags = IsStatic | IsDynamic | IsKeyframed | IsActive,

		MaskTempFlags = TempRebuildCollisionCaches |
			TempDropNewCvxCvxCollisions |
			TempBodyOrAABBIsModified |
			TempRebuildContactCaches,

		MaskAutoMaterialFlags = EnableRestitution |
			EnableTriggerModifier |
			EnableImpulseClipping |
			EnableMassChanger |
			EnableSoftContacts |
			EnableSurfaceVelocity,

		MaskAllFlags = std::numeric_limits<std::uint32_t>::max()
	};
}
