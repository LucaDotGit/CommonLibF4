#include "F4SE/TrampolineInterface.hpp"

#include "F4SE/API.hpp"
#include "F4SE/Core.hpp"

#include "REX/Message.hpp"

namespace F4SE::Impl
{
	struct F4SETrampolineInterface final
	{
		std::uint32_t interfaceVersion;
		void*(F4SE_API* AllocateFromBranchPool)(std::uint32_t, std::size_t);
		void*(F4SE_API* AllocateFromLocalPool)(std::uint32_t, std::size_t);
	};

	[[nodiscard]] static const F4SETrampolineInterface& GetProxy(const TrampolineInterface* a_interface) noexcept
	{
		return reinterpret_cast<const F4SETrampolineInterface&>(*a_interface);
	}
}

namespace F4SE
{
	std::uint32_t TrampolineInterface::GetVersion() const noexcept
	{
		return Impl::GetProxy(this).interfaceVersion;
	}

	std::byte* TrampolineInterface::AllocateFromBranchPool(std::size_t a_size) const
	{
		auto* result = Impl::GetProxy(this).AllocateFromBranchPool(F4SE::GetPluginHandle(), a_size);
		if (!result) [[unlikely]] {
			REX::Fail("Failed to allocate {} bytes from branch pool."sv,
				a_size);
		}

		return reinterpret_cast<std::byte*>(result);
	}

	std::byte* TrampolineInterface::AllocateFromLocalPool(std::size_t a_size) const
	{
		auto* result = Impl::GetProxy(this).AllocateFromLocalPool(F4SE::GetPluginHandle(), a_size);
		if (!result) [[unlikely]] {
			REX::Fail("Failed to allocate {} bytes from local pool."sv,
				a_size);
		}

		return reinterpret_cast<std::byte*>(result);
	}
}
