#pragma once

#include "F4SE/Core.hpp"
#include "F4SE/QueryInterface.hpp"
#include "REX/NotNull.hpp"
#include "REX/Ownership.hpp"

namespace Scaleform::GFx
{
	class Movie;
	class Value;
}

namespace F4SE
{
	class ScaleformInterface final
	{
	public:
		inline static constexpr auto INTERFACE_ID = QueryInterface::InterfaceID::Scaleform;
		inline static constexpr auto INTERFACE_VERSION = static_cast<std::uint32_t>(1);

		using RegisterCallback = bool F4SE_API(Scaleform::GFx::Movie* a_movie, Scaleform::GFx::Value* a_value);

		ScaleformInterface() = delete;
		~ScaleformInterface() = delete;

		ScaleformInterface(const ScaleformInterface&) = delete;
		ScaleformInterface(ScaleformInterface&&) = delete;

		auto operator=(const ScaleformInterface&) -> ScaleformInterface& = delete;
		auto operator=(ScaleformInterface&&) -> ScaleformInterface& = delete;

		[[nodiscard]]
		auto GetVersion() const noexcept -> F4SE::InterfaceVersion;

		void Register(const char* a_name, REX::NotNull<REX::Observer<RegisterCallback*>> a_callback) const;
	};

	static_assert(std::is_empty_v<ScaleformInterface>);
}
