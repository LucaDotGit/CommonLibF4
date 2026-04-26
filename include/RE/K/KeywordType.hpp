#pragma once

namespace RE
{
	enum class KeywordType : std::int32_t
	{
		kNone = 0,
		kComponentTechLevel = 1,
		kAttachPoint = 2,
		kComponentProperty = 3,
		kInstantiationFilter = 4,
		kModAssociation = 5,
		kSound = 6,
		kAnimArchetype = 7,
		kFunctionCall = 8,
		kRecipeFilter = 9,
		kAttractionType = 10,
		kDialogueSubtype = 11,
		kQuestTarget = 12,
		kAnimFlavor = 13,
		kAnimGender = 14,
		kAnimFaceArchetype = 15,
		kQuestGroup = 16,
		kAnimInjured = 17,
		kDispelEffect = 18,

		kTotal = 19
	};
}
