#pragma once

#include "RE/B/BSGraphics_Vertex.hpp"

namespace RE::BSGraphics
{
	class VertexDesc
	{
	public:
		[[nodiscard]]
		auto HasFlag(Vertex::Flags a_flag) const noexcept -> bool
		{
			return ((desc >> 44) & a_flag) != 0;
		}

		void SetFlag(Vertex::Flags a_flag) noexcept
		{
			desc |= (static_cast<std::uint64_t>(a_flag) << 44);
		}

		void ClearFlag(Vertex::Flags a_flag) noexcept
		{
			desc &= ~(static_cast<std::uint64_t>(a_flag) << 44);
		}

		[[nodiscard]]
		auto GetAttributeOffset(Vertex::Attribute a_attribute) const noexcept -> std::uint32_t
		{
			return (desc >> (4 * static_cast<std::uint8_t>(a_attribute) + 2)) & 0x3C;
		}

		void SetAttributeOffset(Vertex::Attribute a_attribute, std::uint32_t a_offset) noexcept
		{
			if (a_attribute != Vertex::Attribute::VA_POSITION) {
				const auto lhs = static_cast<std::uint64_t>(a_offset)
								 << (4 * static_cast<std::uint8_t>(a_attribute) + 2);
				const auto rhs =
					desc & ~static_cast<std::uint64_t>(15 << (4 * static_cast<std::uint8_t>(a_attribute) + 4));

				desc = lhs | rhs;
			}
		}

		void ClearAttributeOffsets() noexcept
		{
			desc &= Vertex::Masks::DESC_MASK_OFFSET;
		}

		[[nodiscard]]
		auto GetFlags() const noexcept -> Vertex::Flags
		{
			return static_cast<Vertex::Flags>((desc & Vertex::Masks::DESC_MASK_OFFSET) >> 44);
		}

		void SetFlags(Vertex::Flags a_flags) noexcept
		{
			desc |= (static_cast<std::uint64_t>(a_flags) << 44) | (desc & Vertex::Masks::DESC_MASK_FLAGS);
		}

		[[nodiscard]]
		auto GetSize() const noexcept -> std::uint32_t
		{
			return (desc & 0xF) * 4;
		}

		// members
		std::uint64_t desc; // 0x00
	};

	static_assert(sizeof(VertexDesc) == 0x08);
}
