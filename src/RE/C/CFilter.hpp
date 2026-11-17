#pragma once

namespace RE
{
	enum class BIPED_PART : std::int32_t;
	enum class COL_LAYER : std::int32_t;

	class CFilter
	{
	public:
		struct Flag
		{
			enum Flags : std::uint32_t
			{
				NoCollision = 1 << 14,
				LinkedGroup = 1 << 15,

				BipedPartShift = 8,
				SystemGroupShift = 16,

				LayerMask = 0x7F,
				PartMask = 0x1F,
				BipedPartMask = 0x1F00,
				SystemGroupMask = 0xFFFF'0000
			};
		};

		using Flags = Flag::Flags;

		CFilter() noexcept = default;
		~CFilter() noexcept = default;

		CFilter(const CFilter&) noexcept = default;
		CFilter(CFilter&&) noexcept = default;

		auto operator=(const CFilter&) noexcept -> CFilter& = default;
		auto operator=(CFilter&&) noexcept -> CFilter& = default;

		[[nodiscard]]
		auto GetCollisionLayer() const noexcept -> COL_LAYER;
		void SetCollisionLayer(COL_LAYER a_layer) noexcept;

		[[nodiscard]]
		auto GetBipedPart() const noexcept -> BIPED_PART;
		void SetBipedPart(BIPED_PART a_part) noexcept;

		[[nodiscard]]
		auto GetNoCollision() const noexcept -> bool;
		void SetNoCollision(bool a_set) noexcept;

		[[nodiscard]]
		auto GetLinkedGroup() const noexcept -> bool;
		void SetLinkedGroup(bool a_set) noexcept;

		[[nodiscard]]
		auto GetSystemGroup() const noexcept -> std::uint32_t;
		void SetSystemGroup(std::uint32_t a_group) noexcept;

		// members
		std::uint32_t filter; // 0x00
	};

	static_assert(sizeof(CFilter) == 0x04);
}
