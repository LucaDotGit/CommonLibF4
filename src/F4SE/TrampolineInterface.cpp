#include "F4SE/TrampolineInterface.hpp"

#include "F4SE/Api.hpp"
#include "F4SE/Core.hpp"
#include "REX/Macros.hpp"
#include "REX/Message.hpp"

namespace F4SE::Impl
{
	namespace
	{
		class F4SETrampolineInterface final
		{
		public:
			F4SETrampolineInterface() = delete;
			~F4SETrampolineInterface() = delete;

			F4SETrampolineInterface(const F4SETrampolineInterface&) = delete;
			F4SETrampolineInterface(F4SETrampolineInterface&&) = delete;

			auto operator=(const F4SETrampolineInterface&) -> F4SETrampolineInterface& = delete;
			auto operator=(F4SETrampolineInterface&&) -> F4SETrampolineInterface& = delete;

			F4SE::InterfaceVersion interfaceVersion;
			void*(F4SE_API* allocateFromBranchPool)(std::uint32_t, std::size_t);
			void*(F4SE_API* allocateFromLocalPool)(std::uint32_t, std::size_t);
		};

		[[nodiscard]] [[REX_ALWAYS_INLINE]]
		auto GetProxy(const TrampolineInterface& a_interface) noexcept -> const F4SETrampolineInterface&
		{
			return reinterpret_cast<const F4SETrampolineInterface&>(a_interface);
		}
	}
}

namespace F4SE
{
	auto TrampolineInterface::GetVersion() const noexcept -> F4SE::InterfaceVersion
	{
		return Impl::GetProxy(*this).interfaceVersion;
	}

	__declspec(allocator) __declspec(restrict) auto TrampolineInterface::AllocateFromBranchPool(
		std::size_t a_size) const -> std::byte*
	{
		auto* result = Impl::GetProxy(*this).allocateFromBranchPool(F4SE::GetPluginHandle(), a_size);
		if (!result) [[unlikely]] {
			REX::Fail("Failed to allocate {} bytes from branch pool."sv, a_size);
		}

		return static_cast<std::byte*>(result);
	}

	__declspec(allocator) __declspec(restrict) auto TrampolineInterface::AllocateFromLocalPool(std::size_t a_size) const
		-> std::byte*
	{
		auto* result = Impl::GetProxy(*this).allocateFromLocalPool(F4SE::GetPluginHandle(), a_size);
		if (!result) [[unlikely]] {
			REX::Fail("Failed to allocate {} bytes from local pool."sv, a_size);
		}

		return static_cast<std::byte*>(result);
	}
}
