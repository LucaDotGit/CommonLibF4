#pragma once

#include "RE/B/BIPED_PART.hpp"
#include "RE/C/COL_LAYER.hpp"

namespace RE
{
	class CFilter
	{
	public:
		struct Flag
		{
			enum Flags : std::uint32_t
			{
				kNone = 0,
				kBipedPart = 1 << 8,
				kNoCollision = 1 << 14,
				kLinkedGroup = 1 << 15,
				kSystemGroup = 1 << 16,

				kPartMask = 0x1F, // BIPED_PART
				kLayerMask = 0x7F // COL_LAYER
			};
		};
		using Flags = Flag::Flags;

		constexpr CFilter() noexcept = default;
		constexpr ~CFilter() noexcept = default;

		constexpr CFilter(const CFilter&) noexcept = default;
		constexpr CFilter(CFilter&&) noexcept = default;

		constexpr CFilter& operator=(const CFilter&) noexcept = default;
		constexpr CFilter& operator=(CFilter&&) noexcept = default;

		[[nodiscard]] constexpr COL_LAYER GetCollisionLayer() const noexcept
		{
			return static_cast<COL_LAYER>((filter & Flags::kLayerMask).underlying());
		}

		constexpr void SetCollisionLayer(COL_LAYER a_layer) noexcept
		{
			filter &= ~(Flags::kLayerMask);
			filter |= (std::to_underlying(a_layer) & Flags::kLayerMask);
		}

		[[nodiscard]] constexpr BIPED_PART GetBipedPart() const noexcept
		{
			return static_cast<BIPED_PART>(((filter >> 8) & Flags::kPartMask).underlying());
		}

		constexpr void SetBipedPart(BIPED_PART a_part) noexcept
		{
			filter &= ~(Flags::kPartMask << 8);
			filter |= ((std::to_underlying(a_part) & Flags::kPartMask) << 8);
		}

		[[nodiscard]] constexpr bool QNoCollision() const noexcept
		{
			return !((filter >> 14) & 1).empty();
		}

		constexpr void SetNoCollision(bool a_set) noexcept
		{
			filter.set(a_set, Flags::kNoCollision);
		}

		[[nodiscard]] constexpr bool QLinkedGroup() const noexcept
		{
			return !((filter >> 15) & 1).empty();
		}

		constexpr void SetLinkedGroup(bool a_set) noexcept
		{
			filter.set(a_set, Flags::kLinkedGroup);
		}

		[[nodiscard]] constexpr std::uint32_t GetSystemGroup() const noexcept
		{
			return (filter >> 16).underlying();
		}

		constexpr void SetSystemGroup(std::uint32_t a_group) noexcept
		{
			filter &= 0x0000FFFF;
			filter |= a_group << 16;
		}

		// members
		REX::EnumSet<Flags, std::uint32_t> filter; // 00
	};
	static_assert(sizeof(CFilter) == 0x04);
}
