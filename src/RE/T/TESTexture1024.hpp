#pragma once

#include "RE/T/TESTexture.hpp"

namespace RE
{
	class __declspec(novtable) TESTexture1024 : public TESTexture // 0x10
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESTexture1024;
		inline static constexpr const auto& VTABLE = VTABLE::TESTexture1024;

		// override (TESTexture)
		auto GetMaxAllowedSize() -> std::uint32_t override // 0x07
		{
			return 0x400;
		}
	};

	static_assert(sizeof(TESTexture1024) == 0x10);
}
