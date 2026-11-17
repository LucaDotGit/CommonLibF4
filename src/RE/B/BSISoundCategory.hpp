#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE::BSISoundCategoryUtils
{
	enum class FadeType : std::int32_t;
}

namespace RE
{
	class __declspec(novtable) BSISoundCategory
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSISoundCategory;
		inline static constexpr const auto& VTABLE = VTABLE::BSISoundCategory;

		virtual ~BSISoundCategory() = default; // 0x00

		// add
		virtual auto Matches(BSISoundCategory* a_toCheck, bool a_exclusive) const -> bool = 0;					// 0x01
		virtual auto GetCategoryVolume() const -> REX::Float32 = 0;												// 0x02
		virtual void SetCategoryVolume(REX::Float32 a_newVolume) = 0;											// 0x03
		virtual auto GetCategoryFrequency() const -> REX::Float32 = 0;											// 0x04
		virtual void SetCategoryFrequency(REX::Float32 a_newFreq) = 0;											// 0x05
		virtual auto GetCategoryAttenuation(BSISoundCategoryUtils::FadeType a_type) const -> std::uint16_t = 0; // 0x06
		virtual void SetCategoryAttenuation(
			BSISoundCategoryUtils::FadeType a_type,
			std::uint16_t a_attenuation) = 0;								 // 0x07
		virtual auto CategoryPaused() const -> bool = 0;					 // 0x08
		virtual void SetCategoryPaused(bool a_paused, bool a_exclusive) = 0; // 0x09
		virtual auto CategoryMute() const -> bool = 0;						 // 0x0A
		virtual void SetCategoryMute(bool a_mute, bool a_exclusive) = 0;	 // 0x0B
		virtual auto GetMinFrequencyMult() const -> REX::Float32 = 0;		 // 0x0C
		virtual auto GetBlockSpeedChange() const -> bool = 0;				 // 0x0D
		virtual auto GetSkipOPMOverrides() const -> bool = 0;				 // 0x0E
		virtual auto GetDebugID() const -> const char* = 0;					 // 0x0F

		GAME_HEAP_REDEFINE_NEW(BSISoundCategory);
	};

	static_assert(sizeof(BSISoundCategory) == 0x08);
}
