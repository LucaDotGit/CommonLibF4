#pragma once

namespace RE
{
	class TESMagicTargetForm
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESMagicTargetForm;
	};

	static_assert(std::is_empty_v<TESMagicTargetForm>);
}
