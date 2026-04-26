#pragma once

namespace RE
{
	enum class FormFlags : std::int32_t;
	enum class FormType : std::int32_t;

	class FORM
	{
	public:
		// members
		REX::Enum<FormType, std::int32_t> formType;		  // 00
		std::uint32_t dataSize;							  // 04
		REX::EnumSet<FormFlags, std::uint32_t> formFlags; // 08
		TESFormID formID;								  // 0C
		std::uint32_t versionControl;					  // 10
		std::uint16_t formVersion;						  // 14
		std::uint16_t vcVersion;						  // 16
	};
	static_assert(sizeof(FORM) == 0x18);
}
