#pragma once

#include "F4SE/Core.hpp"
#include "F4SE/QueryInterface.hpp"

#include "REX/NotNull.hpp"
#include "REX/Own.hpp"

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
		inline static constexpr auto INTERFACE_ID{ QueryInterface::InterfaceID::kScaleform };
		inline static constexpr auto INTERFACE_VERSION{ 1ui32 };

		using RegisterCallback = bool F4SE_API(::Scaleform::GFx::Movie* a_movie, ::Scaleform::GFx::Value* a_value);

		ScaleformInterface() = delete;
		~ScaleformInterface() = delete;

		ScaleformInterface(const ScaleformInterface&) = delete;
		ScaleformInterface(ScaleformInterface&&) = delete;

		ScaleformInterface& operator=(const ScaleformInterface&) = delete;
		ScaleformInterface& operator=(ScaleformInterface&&) = delete;

		[[nodiscard]] std::uint32_t GetVersion() const noexcept;

		bool Register(const char* a_name, REX::NotNull<REX::Observer<RegisterCallback*>> a_callback) const;
	};
	static_assert(std::is_empty_v<ScaleformInterface>);
}
