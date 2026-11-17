#pragma once

#include "REX/Hashing.hpp"
#include "REX/StaticString.hpp"
#include "REX/Version.hpp"

namespace REL
{
	inline constexpr auto DEFAULT_RUNTIME_FILE_EXTENSION = ".bin"sv;
	inline constexpr auto DEFAULT_RUNTIME_FILE_EXTENSION_VR = ".csv"sv;

	class Runtime final
	{
	public:
		inline static constexpr auto MAX_FILE_EXTENSION_SIZE = static_cast<std::size_t>(sizeof(REX::Version));

		static const Runtime INVALID;
		static const Runtime LATEST;

		constexpr explicit Runtime(REX::Version a_version) noexcept :
			_minVersion(a_version)
		{
		}

		constexpr explicit Runtime(REX::Version a_version, std::string_view a_fileExtension) noexcept :
			_minVersion(a_version),
			_fileExtension{
				a_fileExtension.data(),
				a_fileExtension.data() + std::min(a_fileExtension.size(), MAX_FILE_EXTENSION_SIZE)
			}
		{
		}

		constexpr explicit Runtime(REX::Version a_version, std::span<const char> a_fileExtension) noexcept :
			_minVersion(a_version),
			_fileExtension{
				a_fileExtension.data(),
				a_fileExtension.data() + std::min(a_fileExtension.size(), MAX_FILE_EXTENSION_SIZE)
			}
		{
		}

		constexpr ~Runtime() noexcept = default;

		constexpr Runtime(const Runtime&) noexcept = default;
		constexpr Runtime(Runtime&&) noexcept = default;

		constexpr auto operator=(const Runtime&) noexcept -> Runtime& = default;
		constexpr auto operator=(Runtime&&) noexcept -> Runtime& = default;

		[[nodiscard]]
		constexpr auto operator==(const Runtime&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const Runtime&) const noexcept = default;

		[[nodiscard]]
		constexpr auto GetMinVersion() const noexcept
		{
			return _minVersion;
		}

		[[nodiscard]]
		constexpr auto GetFileExtension() const noexcept
		{
			return std::string_view(_fileExtension);
		}

		// private:
		// NOLINTBEGIN(readability-identifier-naming)
		REX::Version _minVersion;
		REX::StaticString<MAX_FILE_EXTENSION_SIZE> _fileExtension;
		// NOLINTEND(readability-identifier-naming)
	};

	inline constexpr auto Runtime::INVALID = Runtime(REX::Version::MIN);
	inline constexpr auto Runtime::LATEST = Runtime(REX::Version::MAX);

	static_assert(std::is_standard_layout_v<Runtime>);
	static_assert(std::is_trivially_destructible_v<Runtime>);
	static_assert(std::is_trivially_copyable_v<Runtime>);
	static_assert(std::is_trivially_move_constructible_v<Runtime>);

	template <class... Args>
	[[nodiscard]]
	constexpr auto CreateRuntime(Args&&... a_args) noexcept -> Runtime
		requires(std::is_constructible_v<REX::Version, Args...>)
	{
		return Runtime(REX::Version(std::forward<Args>(a_args)...), DEFAULT_RUNTIME_FILE_EXTENSION);
	}

	template <class... Args>
	[[nodiscard]]
	constexpr auto CreateRuntimeVR(Args&&... a_args) noexcept -> Runtime
		requires(std::is_constructible_v<REX::Version, Args...>)
	{
		return Runtime(REX::Version(std::forward<Args>(a_args)...), DEFAULT_RUNTIME_FILE_EXTENSION_VR);
	}
}

namespace REL::Impl
{
	template <Runtime... R>
	concept valid_runtime_values = []() consteval noexcept -> bool {
		constexpr auto RUNTIMES = std::array{R...};

		if (RUNTIMES.empty()) {
			return false;
		}

		return std::ranges::all_of(RUNTIMES, [](Runtime a_runtime) noexcept -> bool {
			return a_runtime != Runtime::INVALID;
		});
	}();

	template <Runtime... R>
	concept valid_runtime_order = []() consteval noexcept -> bool {
		constexpr auto RUNTIMES = std::array{R...};

		if (RUNTIMES.empty()) {
			return false;
		}

		if (!std::ranges::is_sorted(RUNTIMES)) {
			return false;
		}

		return std::ranges::adjacent_find(RUNTIMES, std::equal_to<Runtime>()) == RUNTIMES.end();
	}();

	template <Runtime... R>
	[[nodiscard]]
	consteval auto ValidateRuntimeValues() noexcept -> bool
	{
		static_assert(valid_runtime_values<R...>, "All runtimes must be non-zero.");

		return true;
	}

	template <Runtime... R>
	[[nodiscard]]
	consteval auto ValidateRuntimeOrder() noexcept -> bool
	{
		static_assert(valid_runtime_order<R...>, "All runtimes must be unique and in ascending order.");

		return true;
	}
}

namespace std
{
	template <>
	struct hash<REL::Runtime>
	{
	public:
		[[nodiscard]]
		auto operator()(const REL::Runtime& a_key) const noexcept -> std::size_t
		{
			return REX::HashCombine(a_key.GetMinVersion(), a_key.GetFileExtension());
		}
	};
}
