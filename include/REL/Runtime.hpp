#pragma once

#include "REX/Version.hpp"

namespace REL
{
	enum class RuntimeType : std::int16_t
	{
		kStandard = 0,
		kVR
	};

	struct Runtime final
	{
	public:
		static const Runtime INVALID;
		static const Runtime LATEST;

		constexpr Runtime() noexcept = default;
		constexpr ~Runtime() noexcept = default;

		constexpr explicit Runtime(REX::Version a_version) noexcept
			: _version(a_version)
		{
		}

		constexpr explicit Runtime(REX::Version a_version, RuntimeType a_type) noexcept
			: _version(a_version),
			  _type(a_type)
		{
		}

		constexpr Runtime(const Runtime&) noexcept = default;
		constexpr Runtime(Runtime&&) noexcept = default;

		constexpr Runtime& operator=(const Runtime&) noexcept = default;
		constexpr Runtime& operator=(Runtime&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const Runtime&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const Runtime&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const Runtime&) const noexcept = default;

		[[nodiscard]] constexpr REX::Version GetVersion() const noexcept { return _version; }
		[[nodiscard]] constexpr RuntimeType GetType() const noexcept { return _type; }

		REX::Version _version;
		RuntimeType _type{ RuntimeType::kStandard };
	};

	inline constexpr auto Runtime::INVALID = Runtime(REX::Version::MIN);
	inline constexpr auto Runtime::LATEST = Runtime(REX::Version::MAX);

	static_assert(std::is_standard_layout_v<Runtime>);
	static_assert(std::is_trivially_destructible_v<Runtime>);
	static_assert(std::is_trivially_copyable_v<Runtime>);

	static_assert(sizeof(RuntimeType) == alignof(REX::Version));

	[[nodiscard]] constexpr bool operator==(Runtime a_lhs, REX::Version a_rhs) noexcept
	{
		return a_lhs.GetVersion() == a_rhs;
	}

	[[nodiscard]] constexpr bool operator==(REX::Version a_lhs, Runtime a_rhs) noexcept
	{
		return a_lhs == a_rhs.GetVersion();
	}

	[[nodiscard]] constexpr auto operator<=>(Runtime a_lhs, REX::Version a_rhs) noexcept
	{
		return a_lhs.GetVersion() <=> a_rhs;
	}

	[[nodiscard]] constexpr auto operator<=>(REX::Version a_lhs, Runtime a_rhs) noexcept
	{
		return a_lhs <=> a_rhs.GetVersion();
	}

	template <class... Args>
	[[nodiscard]] constexpr Runtime CreateRuntime(Args&&... a_args) noexcept
		requires(std::is_constructible_v<REX::Version, Args...>)
	{
		return Runtime(REX::Version(std::forward<Args>(a_args)...));
	}

	template <class... Args>
	[[nodiscard]] constexpr Runtime CreateVRRuntime(Args&&... a_args) noexcept
		requires(std::is_constructible_v<REX::Version, Args...>)
	{
		return Runtime(REX::Version(std::forward<Args>(a_args)...), RuntimeType::kVR);
	}
}

namespace REL::Impl
{
	template <Runtime... R>
	concept valid_runtime_values = []() consteval noexcept {
		constexpr auto RUNTIMES = std::array{ R... };

		if (RUNTIMES.size() == 0) {
			return false;
		}

		return std::ranges::all_of(RUNTIMES, [](const Runtime& a_runtime) {
			return a_runtime != Runtime::INVALID;
		});
	}();

	template <Runtime... R>
	concept valid_runtime_order = []() consteval noexcept {
		constexpr auto RUNTIMES = std::array{ R... };

		if (RUNTIMES.size() <= 1) {
			return true;
		}

		const auto runtimeIt = std::ranges::adjacent_find(RUNTIMES, [](const Runtime& a_lhs, const Runtime& a_rhs) {
			return a_lhs < a_rhs;
		});

		return runtimeIt != RUNTIMES.end();
	}();

	template <Runtime... R>
	[[nodiscard]] consteval bool ValidateRuntimeValues() noexcept
	{
		static_assert(valid_runtime_values<R...>,
			"All runtimes must be non-zero.");

		return true;
	}

	template <Runtime... R>
	[[nodiscard]] consteval bool ValidateRuntimeOrder() noexcept
	{
		static_assert(valid_runtime_order<R...>,
			"All runtimes must be unique and in ascending order.");

		return true;
	}
}
