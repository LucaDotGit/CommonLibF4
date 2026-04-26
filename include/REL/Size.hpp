#pragma once

#include "REL/Module.hpp"
#include "REL/Runtime.hpp"

#include "REX/Hash.hpp"

namespace REL
{
	inline constexpr auto INVALID_SIZE = std::numeric_limits<std::size_t>::max();

	class ISize
	{
	public:
		using value_type = std::size_t;

		virtual ~ISize() noexcept = default;

		[[nodiscard]] virtual value_type GetSize() const noexcept = 0;
	};

	template <Runtime R0 = Runtime::LATEST, Runtime... R>
	class Size final
		: public ISize
	{
	public:
		using value_type = ISize::value_type;

		static_assert(REL::Impl::ValidateRuntimeValues<R0, R...>());
		static_assert(REL::Impl::ValidateRuntimeOrder<R0, R...>());

		inline static constexpr auto RUNTIMES = std::array{ R0, R... };

		constexpr Size() noexcept = default;
		constexpr ~Size() noexcept override = default;

		template <class... V>
		constexpr explicit Size(V&&... a_sizes) //
			noexcept((std::is_nothrow_convertible_v<V, value_type> && ...))
			requires((std::is_convertible_v<V, value_type> && ...) &&
					 (sizeof...(V) == sizeof...(R) + 1))
			: _sizes{ static_cast<value_type>(std::forward<V>(a_sizes))... }
		{
		}

		constexpr Size(const Size&) noexcept = default;
		constexpr Size(Size&&) noexcept = default;

		constexpr Size& operator=(const Size&) noexcept = default;
		constexpr Size& operator=(Size&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const Size&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const Size&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const Size&) const noexcept = default;

		[[nodiscard]] constexpr const auto& GetSizes() const noexcept { return _sizes; }

		[[nodiscard]] constexpr value_type GetSize(Runtime a_runtime) const noexcept
		{
			if constexpr (RUNTIMES.size() == 1) {
				if (a_runtime > RUNTIMES.front()) {
					return INVALID_SIZE;
				}

				return _sizes.front();
			}
			else {
				const auto runtimeIt = std::ranges::upper_bound(RUNTIMES, a_runtime);
				if (runtimeIt == RUNTIMES.begin()) {
					return INVALID_SIZE;
				}

				const auto index = static_cast<std::size_t>(std::distance(RUNTIMES.begin(), runtimeIt - 1));
				return _sizes[index];
			}
		}

		[[nodiscard]] value_type GetSize() const noexcept override
		{
			const auto currentRuntime = REL::Module::GetSingleton()->GetRuntime();
			return GetSize(currentRuntime);
		}

		constexpr void swap(Size& a_other) noexcept
		{
			std::swap(_sizes, a_other._sizes);
		}

	private:
		std::array<value_type, RUNTIMES.size()> _sizes;
	};

	template <Runtime R0 = Runtime::LATEST, Runtime... R>
	constexpr void swap(Size<R0, R...>& a_lhs, Size<R0, R...>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	template <class V>
	[[nodiscard]] constexpr auto CreateSize(V&& a_size) //
		noexcept(std::is_nothrow_constructible_v<Size<>, V>)
		requires(std::is_constructible_v<Size<>, V>)
	{
		return Size<>(std::forward<V>(a_size));
	}

	template <Runtime R0, Runtime... R, class... V>
	[[nodiscard]] constexpr auto CreateSize(V&&... a_sizes) //
		noexcept(std::is_nothrow_constructible_v<Size<R0, R...>, V...>)
		requires(std::is_constructible_v<Size<R0, R...>, V...> &&
				 (sizeof...(V) == sizeof...(R) + 1))
	{
		return Size<R0, R...>(std::forward<V>(a_sizes)...);
	}
}

namespace std
{
	template <class T>
		requires(std::derived_from<T, REL::ISize>)
	struct hash<T>
	{
	public:
		[[nodiscard]] std::size_t operator()(const T& a_key) const noexcept
		{
			return REX::Hash(a_key.GetSize());
		}
	};
}
