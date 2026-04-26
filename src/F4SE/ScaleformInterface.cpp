#include "F4SE/ScaleformInterface.hpp"

#include "REX/Message.hpp"

namespace F4SE::Impl
{
	struct F4SEScaleformInterface final
	{
		std::uint32_t interfaceVersion;
		bool(F4SE_API* Register)(const char*, void*);
	};

	[[nodiscard]] static const F4SEScaleformInterface& GetProxy(const ScaleformInterface* a_interface) noexcept
	{
		return reinterpret_cast<const F4SEScaleformInterface&>(*a_interface);
	}
}

namespace F4SE
{
	std::uint32_t ScaleformInterface::GetVersion() const noexcept
	{
		return Impl::GetProxy(this).interfaceVersion;
	}

	bool ScaleformInterface::Register(const char* a_name, REX::NotNull<REX::Observer<RegisterCallback*>> a_callback) const
	{
		const auto result = Impl::GetProxy(this).Register(a_name, reinterpret_cast<void*>(a_callback.get()));
		if (!result) [[unlikely]] {
			REX::Fail(R"(Failed to register scaleform interface with name "{}".)"sv,
				a_name);
		}

		return result;
	}
}
