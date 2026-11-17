#pragma once

#include "RE/N/NiIntegerExtraData.hpp"

namespace RE
{
	class __declspec(novtable) BSXFlags : public NiIntegerExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSXFlags;
		inline static constexpr const auto& VTABLE = VTABLE::BSXFlags;
		inline static constexpr auto Ni_RTTI = Ni_RTTI::BSXFlags;

		enum class Flag : std::int32_t
		{
			None = 0,
			Animated = 1 << 0,
			Havok = 1 << 1,
			Ragdoll = 1 << 2,
			Complex = 1 << 3,
			Addon = 1 << 4,
			EditorMarker = 1 << 5,
			Dynamic = 1 << 6,
			Articulated = 1 << 7,
			NeedsTransformUpdate = 1 << 8,
			ExternalEmit = 1 << 9,
			MagicShaderParticles = 1 << 10,
			Lights = 1 << 11,
			Breakable = 1 << 12,
			SearchedBreakable = 1 << 13
		};

		BSXFlags() :
			BSXFlags(static_cast<Flag>(0))
		{
			REL::EmplaceVtable(this);
		}

		explicit BSXFlags(Flag a_value) :
			NiIntegerExtraData(GetExtraName(), static_cast<std::int32_t>(a_value))
		{
			REL::EmplaceVtable(this);
		}

		[[nodiscard]]
		auto GetFlags() const noexcept -> Flag
		{
			return static_cast<Flag>(value);
		}

		void SetFlags(Flag a_value) noexcept
		{
			value = static_cast<std::int32_t>(a_value);
		}

		[[nodiscard]]
		static auto GetExtraName() -> const BSFixedString&
		{
			static const auto EXTRA_NAME = BSFixedString("BSX"sv);
			return EXTRA_NAME;
		}
	};

	static_assert(sizeof(BSXFlags) == 0x20);
}
