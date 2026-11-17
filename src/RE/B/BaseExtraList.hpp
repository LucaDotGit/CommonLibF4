#pragma once

#include "RE/E/EXTRA_DATA_TYPE.hpp"

namespace RE
{
	class BSExtraData;

	class BaseExtraList
	{
	public:
		BaseExtraList() noexcept = default;
		~BaseExtraList() noexcept = default;

		BaseExtraList(const BaseExtraList&) = delete;
		BaseExtraList(BaseExtraList&&) = delete;

		auto operator=(const BaseExtraList&) -> BaseExtraList& = delete;
		auto operator=(BaseExtraList&&) -> BaseExtraList& = delete;

		[[nodiscard]]
		auto HasExtra(EXTRA_DATA_TYPE a_extraType) const noexcept -> bool;
		[[nodiscard]]
		auto GetExtra(EXTRA_DATA_TYPE a_extraType) const noexcept -> BSExtraData*;

		auto AddExtra(std::unique_ptr<BSExtraData> a_extraData) noexcept -> BSExtraData*;
		auto RemoveExtra(EXTRA_DATA_TYPE a_extraType) noexcept -> std::unique_ptr<BSExtraData>;

	private:
		inline static constexpr auto N = static_cast<std::size_t>(std::to_underlying(EXTRA_DATA_TYPE::_Count) / 8) + 1;

		[[nodiscard]]
		static auto IsHighUseExtra(EXTRA_DATA_TYPE a_extraType) noexcept -> bool;

		[[nodiscard]]
		auto GetFlags() const noexcept -> std::span<std::uint8_t>;
		[[nodiscard]]
		auto GetOrCreateFlags() noexcept -> std::span<std::uint8_t, N>;

		void CreateFlags() noexcept;
		void MarkType(EXTRA_DATA_TYPE a_extraType, bool a_set) noexcept;

		// members
		BSExtraData* _head{nullptr};				// 0x00
		BSExtraData** _tail{std::addressof(_head)}; // 0x08
		std::uint8_t* _flags{nullptr};				// 0x10
	};

	static_assert(sizeof(BaseExtraList) == 0x18);
}
