#include "RE/C/CFilter.hpp"

#include "RE/B/BIPED_PART.hpp"
#include "RE/C/COL_LAYER.hpp"

namespace RE
{
	auto CFilter::GetCollisionLayer() const noexcept -> COL_LAYER
	{
		return static_cast<COL_LAYER>(filter & Flags::LayerMask);
	}

	void CFilter::SetCollisionLayer(COL_LAYER a_layer) noexcept
	{
		const auto layer = static_cast<std::uint32_t>(a_layer) & Flags::LayerMask;
		filter = (filter & ~Flags::LayerMask) | layer;
	}

	auto CFilter::GetBipedPart() const noexcept -> BIPED_PART
	{
		return static_cast<BIPED_PART>((filter & Flags::BipedPartMask) >> Flags::BipedPartShift);
	}

	void CFilter::SetBipedPart(BIPED_PART a_part) noexcept
	{
		const auto part = (static_cast<std::uint32_t>(a_part) & Flags::PartMask) << Flags::BipedPartShift;
		filter = (filter & ~Flags::BipedPartMask) | part;
	}

	auto CFilter::GetNoCollision() const noexcept -> bool
	{
		return (filter & Flags::NoCollision) != 0;
	}

	void CFilter::SetNoCollision(bool a_set) noexcept
	{
		if (a_set) {
			filter |= Flags::NoCollision;
		}
		else {
			filter &= ~Flags::NoCollision;
		}
	}

	auto CFilter::GetLinkedGroup() const noexcept -> bool
	{
		return (filter & Flags::LinkedGroup) != 0;
	}

	void CFilter::SetLinkedGroup(bool a_set) noexcept
	{
		if (a_set) {
			filter |= Flags::LinkedGroup;
		}
		else {
			filter &= ~Flags::LinkedGroup;
		}
	}

	auto CFilter::GetSystemGroup() const noexcept -> std::uint32_t
	{
		return filter >> Flags::SystemGroupShift;
	}

	void CFilter::SetSystemGroup(std::uint32_t a_group) noexcept
	{
		filter &= ~Flags::SystemGroupMask;
		filter |= a_group << Flags::SystemGroupShift;
	}
}
