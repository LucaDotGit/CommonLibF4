#pragma once

#include "REL/Module.hpp"
#include "REL/Runtime.hpp"
#include "REX/Hashing.hpp"

namespace REL
{
	class ISize
	{
	public:
		using value_type = std::size_t;

		inline static constexpr auto INVALID_SIZE = std::numeric_limits<value_type>::max();

		ISize() noexcept = default;
		virtual ~ISize() noexcept = default;

		ISize(const ISize&) = delete;
		ISize(ISize&&) noexcept = default;

		auto operator=(const ISize&) -> ISize& = delete;
		auto operator=(ISize&&) noexcept -> ISize& = default;

		[[nodiscard]]
		auto operator==(const ISize& a_rhs) const noexcept -> bool
		{
			return GetSize() == a_rhs.GetSize();
		}

		[[nodiscard]]
		auto operator<=>(const ISize& a_rhs) const noexcept -> auto
		{
			return GetSize() <=> a_rhs.GetSize();
		}

		[[nodiscard]]
		virtual auto GetSize() const noexcept -> value_type = 0;
	};

	template <REL::Runtime R0 = REL::Runtime::LATEST, REL::Runtime... R>
	class Size final : public ISize
	{
	public:
		using ISize::value_type;

		static_assert(REL::Impl::ValidateRuntimeValues<R0, R...>());
		static_assert(REL::Impl::ValidateRuntimeOrder<R0, R...>());

		inline static constexpr auto RUNTIMES = std::array{R0, R...};

		constexpr Size() noexcept = default;
		constexpr ~Size() noexcept override = default;

		template <class... V>
		constexpr explicit Size(V&&... a_sizes) noexcept((std::is_nothrow_convertible_v<V, value_type> && ...))
			requires((std::is_convertible_v<V, value_type> && ...) && (sizeof...(V) == sizeof...(R) + 1))
			:
			_sizes{static_cast<value_type>(std::forward<V>(a_sizes))...}
		{
		}

		constexpr Size(const Size& a_rhs) noexcept :
			_sizes(a_rhs._sizes)
		{
		}

		constexpr Size(Size&&) noexcept = default;

		constexpr auto operator=(const Size& a_rhs) noexcept -> Size&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_sizes = a_rhs._sizes;
			return *this;
		}

		constexpr auto operator=(Size&&) noexcept -> Size& = default;

		[[nodiscard]]
		constexpr auto GetSizes() const noexcept -> const auto&
		{
			return _sizes;
		}

		[[nodiscard]]
		constexpr auto GetSize(REL::Runtime a_runtime) const noexcept -> value_type
		{
			if (a_runtime == REL::Runtime::INVALID) [[unlikely]] {
				return INVALID_SIZE;
			}

			if constexpr (RUNTIMES.front() == REL::Runtime::LATEST) {
				return _sizes.front();
			}
			else {
				const auto runtimeIt = std::ranges::upper_bound(RUNTIMES, a_runtime);
				if (runtimeIt == RUNTIMES.begin()) [[unlikely]] {
					return INVALID_SIZE;
				}

				const auto index = static_cast<std::size_t>(std::distance(RUNTIMES.begin(), std::prev(runtimeIt)));
				return _sizes[index];
			}
		}

		[[nodiscard]]
		auto GetSize() const noexcept -> value_type override
		{
			const auto currentRuntime = REL::Module::GetSingleton().GetRuntime();
			return GetSize(currentRuntime);
		}

		constexpr void swap(Size& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_sizes, a_other._sizes);
		}

	private:
		std::array<value_type, RUNTIMES.size()> _sizes;
	};

	template <class T>
	[[nodiscard]]
	constexpr auto CreateSize(T&& a_size) noexcept(std::is_nothrow_constructible_v<Size<>, T>)
		requires(std::is_constructible_v<Size<>, T>)
	{
		return Size<>{std::forward<T>(a_size)};
	}

	template <REL::Runtime R0, REL::Runtime... R, class... V>
	[[nodiscard]]
	constexpr auto CreateSize(V&&... a_sizes) noexcept(std::is_nothrow_constructible_v<Size<R0, R...>, V...>)
		requires(std::is_constructible_v<Size<R0, R...>, V...> && (sizeof...(V) == sizeof...(R) + 1))
	{
		return Size<R0, R...>{std::forward<V>(a_sizes)...};
	}

	static_assert([]() consteval noexcept -> bool {
		constexpr auto TEST_RUNTIME_01 = REL::CreateRuntime(1, 0, 0, 0);
		constexpr auto TEST_RUNTIME_02 = REL::CreateRuntime(1, 0, 0, 1);

		constexpr auto TEST_SIZE_01 = CreateSize<TEST_RUNTIME_01, TEST_RUNTIME_02>(12'345'678, 23'456'789);
		constexpr auto TEST_SIZE_02 = CreateSize<TEST_RUNTIME_02>(34'567'890);
		constexpr auto TEST_SIZE_03 = CreateSize<>(45'678'901);

		return (TEST_SIZE_01.GetSize(TEST_RUNTIME_01) == 12'345'678) &&
			   (TEST_SIZE_01.GetSize(TEST_RUNTIME_02) == 23'456'789) &&
			   (TEST_SIZE_01.GetSize(Runtime::LATEST) == 23'456'789) &&
			   (TEST_SIZE_02.GetSize(TEST_RUNTIME_01) == ISize::INVALID_SIZE) &&
			   (TEST_SIZE_02.GetSize(TEST_RUNTIME_02) == 34'567'890) &&
			   (TEST_SIZE_02.GetSize(Runtime::LATEST) == 34'567'890) &&
			   (TEST_SIZE_03.GetSize(TEST_RUNTIME_01) == 45'678'901) &&
			   (TEST_SIZE_03.GetSize(TEST_RUNTIME_02) == 45'678'901) &&
			   (TEST_SIZE_03.GetSize(Runtime::LATEST) == 45'678'901);
	}());
}

namespace std
{
	template <class T>
		requires(std::derived_from<T, REL::ISize>)
	struct hash<T>
	{
	public:
		[[nodiscard]]
		auto operator()(const T& a_key) const noexcept -> std::size_t
		{
			return REX::Hash(a_key.GetSize());
		}
	};
}
