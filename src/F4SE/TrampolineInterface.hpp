#pragma once

#include "F4SE/Core.hpp"
#include "F4SE/QueryInterface.hpp"

namespace F4SE
{
	class TrampolineInterface final
	{
	public:
		inline static constexpr auto INTERFACE_ID = QueryInterface::InterfaceID::Trampoline;
		inline static constexpr auto INTERFACE_VERSION = static_cast<std::uint32_t>(1);

		TrampolineInterface() = delete;
		~TrampolineInterface() = delete;

		TrampolineInterface(const TrampolineInterface&) = delete;
		TrampolineInterface(TrampolineInterface&&) = delete;

		auto operator=(const TrampolineInterface&) -> TrampolineInterface& = delete;
		auto operator=(TrampolineInterface&&) -> TrampolineInterface& = delete;

		[[nodiscard]]
		auto GetVersion() const noexcept -> F4SE::InterfaceVersion;

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto AllocateFromBranchPool(std::size_t a_size) const -> std::byte*;
		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto AllocateFromLocalPool(std::size_t a_size) const -> std::byte*;
	};

	static_assert(std::is_empty_v<TrampolineInterface>);
}
