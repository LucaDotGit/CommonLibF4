#pragma once

namespace RE
{
	enum class FormFlags : std::int32_t;
	enum class FormType : std::int32_t;

	class FORM
	{
	public:
		// members
		REX::Enum<FormType, std::int32_t> formType;		  // 0x00
		std::uint32_t dataSize;							  // 0x04
		REX::EnumSet<FormFlags, std::uint32_t> formFlags; // 0x08
		TESFormID formID;								  // 0x0C
		std::uint32_t versionControl;					  // 0x10
		std::uint16_t formVersion;						  // 0x14
		std::uint16_t vcVersion;						  // 0x16
	};

	static_assert(sizeof(FORM) == 0x18);
}
