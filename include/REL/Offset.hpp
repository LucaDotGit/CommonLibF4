#pragma once

#include "REL/Module.hpp"
#include "REL/Runtime.hpp"

#include "REX/Hash.hpp"

namespace REL
{
	inline constexpr auto INVALID_OFFSET = std::numeric_limits<std::ptrdiff_t>::max();
	inline constexpr auto INVALID_OFFSET_ADDRESS = std::numeric_limits<std::uintptr_t>::min();

	class IOffset
	{
	public:
		using value_type = std::ptrdiff_t;

		virtual ~IOffset() noexcept = default;

		[[nodiscard]] virtual value_type GetOffset() const noexcept = 0;
		[[nodiscard]] virtual std::uintptr_t GetAddress() const noexcept = 0;
	};

	template <Runtime R0 = Runtime::LATEST, Runtime... R>
	class Offset final
		: public IOffset
	{
	public:
		using value_type = IOffset::value_type;

		static_assert(REL::Impl::ValidateRuntimeValues<R0, R...>());
		static_assert(REL::Impl::ValidateRuntimeOrder<R0, R...>());

		inline static constexpr auto RUNTIMES = std::array{ R0, R... };

		constexpr Offset() noexcept = default;
		constexpr ~Offset() noexcept override = default;

		template <class... V>
		constexpr explicit Offset(V&&... a_offsets) //
			noexcept((std::is_nothrow_convertible_v<V, value_type> && ...))
			requires((std::is_convertible_v<V, value_type> && ...) &&
					 (sizeof...(V) == sizeof...(R) + 1))
			: _offsets{ static_cast<value_type>(std::forward<V>(a_offsets))... }
		{
		}

		constexpr Offset(const Offset&) noexcept = default;
		constexpr Offset(Offset&&) noexcept = default;

		constexpr Offset& operator=(const Offset&) noexcept = default;
		constexpr Offset& operator=(Offset&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const Offset&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const Offset&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const Offset&) const noexcept = default;

		[[nodiscard]] constexpr const auto& GetOffsets() const noexcept { return _offsets; }

		[[nodiscard]] constexpr value_type GetOffset(Runtime a_runtime) const noexcept
		{
			if constexpr (RUNTIMES.size() == 1) {
				if (a_runtime > RUNTIMES.front()) {
					return INVALID_OFFSET;
				}

				return _offsets.front();
			}
			else {
				const auto runtimeIt = std::ranges::upper_bound(RUNTIMES, a_runtime);
				if (runtimeIt == RUNTIMES.begin()) {
					return INVALID_OFFSET;
				}

				const auto index = static_cast<std::size_t>(std::distance(RUNTIMES.begin(), runtimeIt - 1));
				return _offsets[index];
			}
		}

		[[nodiscard]] value_type GetOffset() const noexcept override
		{
			const auto currentRuntime = REL::Module::GetSingleton()->GetRuntime();
			return GetOffset(currentRuntime);
		}

		[[nodiscard]] std::uintptr_t GetAddress() const noexcept override
		{
			const auto offset = GetOffset();
			if (offset == INVALID_OFFSET) {
				return INVALID_OFFSET_ADDRESS;
			}

			const auto baseAddress = REL::Module::GetSingleton()->GetBaseAddress();
			return baseAddress + offset;
		}

		constexpr void swap(Offset& a_other) noexcept
		{
			std::swap(_offsets, a_other._offsets);
		}

	private:
		std::array<value_type, RUNTIMES.size()> _offsets;
	};

	template <Runtime R0 = Runtime::LATEST, Runtime... R>
	constexpr void swap(Offset<R0, R...>& a_lhs, Offset<R0, R...>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	template <class V>
	[[nodiscard]] constexpr auto CreateOffset(V&& a_offset) //
		noexcept(std::is_nothrow_constructible_v<Offset<>, V>)
		requires(std::is_constructible_v<Offset<>, V>)
	{
		return Offset<>{ std::forward<V>(a_offset) };
	}

	template <Runtime R0, Runtime... R, class... V>
	[[nodiscard]] constexpr auto CreateOffset(V&&... a_offsets) //
		noexcept(std::is_nothrow_constructible_v<Offset<R0, R...>, V...>)
		requires(std::is_constructible_v<Offset<R0, R...>, V...> &&
				 (sizeof...(V) == sizeof...(R) + 1))
	{
		return Offset<R0, R...>{ std::forward<V>(a_offsets)... };
	}
}

namespace std
{
	template <class T>
		requires(std::derived_from<T, REL::IOffset>)
	struct hash<T>
	{
	public:
		[[nodiscard]] std::size_t operator()(const T& a_key) const noexcept
		{
			return REX::Hash(a_key.GetOffset());
		}
	};
}
