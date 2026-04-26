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

		BaseExtraList& operator=(const BaseExtraList&) = delete;
		BaseExtraList& operator=(BaseExtraList&&) = delete;

		[[nodiscard]] bool HasExtra(EXTRA_DATA_TYPE a_type) const noexcept;
		[[nodiscard]] BSExtraData* GetExtra(EXTRA_DATA_TYPE a_type) const noexcept;

		void AddExtra(BSExtraData* a_extra) noexcept;
		std::unique_ptr<BSExtraData> RemoveExtra(EXTRA_DATA_TYPE a_type) noexcept;

	private:
		inline static constexpr auto N = static_cast<std::size_t>((std::to_underlying(EXTRA_DATA_TYPE::kTotal) / 8) + 1);

		[[nodiscard]] static bool IsHighUseExtra(EXTRA_DATA_TYPE a_type) noexcept;

		[[nodiscard]] std::span<std::uint8_t> GetFlags() const noexcept;
		[[nodiscard]] std::span<std::uint8_t, N> GetOrCreateFlags() noexcept;

		void CreateFlags() noexcept;
		void MarkType(EXTRA_DATA_TYPE a_type, bool a_set) noexcept;

		// members
		BSExtraData* _head{ nullptr };				  // 00
		BSExtraData** _tail{ std::addressof(_head) }; // 08
		std::uint8_t* _flags{ nullptr };			  // 10
	};
	static_assert(sizeof(BaseExtraList) == 0x18);
}
