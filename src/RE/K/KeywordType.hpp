#pragma once

namespace RE
{
	enum class KeywordType : std::int32_t
	{
		None = 0,
		ComponentTechLevel = 1,
		AttachPoint = 2,
		ComponentProperty = 3,
		InstantiationFilter = 4,
		ModAssociation = 5,
		Sound = 6,
		AnimArchetype = 7,
		FunctionCall = 8,
		RecipeFilter = 9,
		AttractionType = 10,
		DialogueSubtype = 11,
		QuestTarget = 12,
		AnimFlavor = 13,
		AnimGender = 14,
		AnimFaceArchetype = 15,
		QuestGroup = 16,
		AnimInjured = 17,
		DispelEffect = 18,

		_Count = 19
	};
}
