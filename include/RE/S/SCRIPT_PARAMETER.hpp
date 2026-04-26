#pragma once

namespace RE
{
	enum class SCRIPT_PARAM_TYPE : std::int32_t;

	class SCRIPT_PARAMETER
	{
	public:
		// members
		const char* paramName{ "" };						  // 00
		REX::Enum<SCRIPT_PARAM_TYPE, std::int32_t> paramType; // 08
		bool optional{ false };								  // 0C
	};
	static_assert(sizeof(SCRIPT_PARAMETER) == 0x10);
}
