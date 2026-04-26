#pragma once

#include "F4SE/QueryInterface.hpp"

namespace F4SE
{
	class TrampolineInterface final
	{
	public:
		inline static constexpr auto INTERFACE_ID{ QueryInterface::InterfaceID::kTrampoline };
		inline static constexpr auto INTERFACE_VERSION{ 1ui32 };

		TrampolineInterface() = delete;
		~TrampolineInterface() = delete;

		TrampolineInterface(const TrampolineInterface&) = delete;
		TrampolineInterface(TrampolineInterface&&) = delete;

		TrampolineInterface& operator=(const TrampolineInterface&) = delete;
		TrampolineInterface& operator=(TrampolineInterface&&) = delete;

		[[nodiscard]] std::uint32_t GetVersion() const noexcept;

		[[nodiscard]] std::byte* AllocateFromBranchPool(std::size_t a_size) const;
		[[nodiscard]] std::byte* AllocateFromLocalPool(std::size_t a_size) const;
	};
	static_assert(std::is_empty_v<TrampolineInterface>);
}
