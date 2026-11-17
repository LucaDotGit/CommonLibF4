#pragma once

#include "REL/Module.hpp"
#include "REL/Runtime.hpp"
#include "REX/Hashing.hpp"

namespace REL
{
	class IOffset
	{
	public:
		using value_type = std::ptrdiff_t;

		inline static constexpr auto INVALID_OFFSET = std::numeric_limits<value_type>::max();
		inline static constexpr auto INVALID_OFFSET_ADDRESS = std::numeric_limits<std::uintptr_t>::min();

		IOffset() noexcept = default;
		virtual ~IOffset() noexcept = default;

		IOffset(const IOffset&) = delete;
		IOffset(IOffset&&) noexcept = default;

		auto operator=(const IOffset&) -> IOffset& = delete;
		auto operator=(IOffset&&) noexcept -> IOffset& = default;

		[[nodiscard]]
		auto operator==(const IOffset& a_rhs) const noexcept -> bool
		{
			return GetOffset() == a_rhs.GetOffset();
		}

		[[nodiscard]]
		auto operator<=>(const IOffset& a_rhs) const noexcept -> auto
		{
			return GetOffset() <=> a_rhs.GetOffset();
		}

		[[nodiscard]]
		virtual auto GetOffset() const noexcept -> value_type = 0;
		[[nodiscard]]
		virtual auto GetAddress() const noexcept -> std::uintptr_t = 0;
	};

	template <REL::Runtime R0 = REL::Runtime::LATEST, REL::Runtime... R>
	class Offset final : public IOffset
	{
	public:
		using IOffset::value_type;

		static_assert(REL::Impl::ValidateRuntimeValues<R0, R...>());
		static_assert(REL::Impl::ValidateRuntimeOrder<R0, R...>());

		inline static constexpr auto RUNTIMES = std::array{R0, R...};

		constexpr Offset() noexcept = default;
		constexpr ~Offset() noexcept override = default;

		template <class... V>
		constexpr explicit Offset(V&&... a_offsets) noexcept((std::is_nothrow_convertible_v<V, value_type> && ...))
			requires((std::is_convertible_v<V, value_type> && ...) && (sizeof...(V) == sizeof...(R) + 1))
			:
			_offsets{static_cast<value_type>(std::forward<V>(a_offsets))...}
		{
		}

		constexpr Offset(const Offset& a_rhs) noexcept :
			_offsets(a_rhs._offsets)
		{
		}

		constexpr Offset(Offset&&) noexcept = default;

		constexpr auto operator=(const Offset& a_rhs) noexcept -> Offset&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_offsets = a_rhs._offsets;
			return *this;
		}

		constexpr auto operator=(Offset&&) noexcept -> Offset& = default;

		[[nodiscard]]
		constexpr auto GetOffsets() const noexcept -> const auto&
		{
			return _offsets;
		}

		[[nodiscard]]
		constexpr auto GetOffset(REL::Runtime a_runtime) const noexcept -> value_type
		{
			if (a_runtime == REL::Runtime::INVALID) [[unlikely]] {
				return INVALID_OFFSET;
			}

			if constexpr (RUNTIMES.front() == REL::Runtime::LATEST) {
				return _offsets.front();
			}
			else {
				const auto runtimeIt = std::ranges::upper_bound(RUNTIMES, a_runtime);
				if (runtimeIt == RUNTIMES.begin()) [[unlikely]] {
					return INVALID_OFFSET;
				}

				const auto index = static_cast<std::size_t>(std::distance(RUNTIMES.begin(), std::prev(runtimeIt)));
				return _offsets[index];
			}
		}

		[[nodiscard]]
		auto GetOffset() const noexcept -> value_type override
		{
			const auto currentRuntime = REL::Module::GetSingleton().GetRuntime();
			return GetOffset(currentRuntime);
		}

		[[nodiscard]]
		auto GetAddress() const noexcept -> std::uintptr_t override
		{
			const auto offset = GetOffset();
			if (offset == INVALID_OFFSET) {
				return INVALID_OFFSET_ADDRESS;
			}

			const auto baseAddress = REL::Module::GetSingleton().GetBaseAddress();
			return baseAddress + static_cast<std::uintptr_t>(offset);
		}

		constexpr void swap(Offset& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_offsets, a_other._offsets);
		}

	private:
		std::array<value_type, RUNTIMES.size()> _offsets;
	};

	template <class T>
	[[nodiscard]]
	constexpr auto CreateOffset(T&& a_offset) noexcept(std::is_nothrow_constructible_v<Offset<>, T>)
		requires(std::is_constructible_v<Offset<>, T>)
	{
		return Offset<>{std::forward<T>(a_offset)};
	}

	template <REL::Runtime R0, REL::Runtime... R, class... V>
	[[nodiscard]]
	constexpr auto CreateOffset(V&&... a_offsets) noexcept(std::is_nothrow_constructible_v<Offset<R0, R...>, V...>)
		requires(std::is_constructible_v<Offset<R0, R...>, V...> && (sizeof...(V) == sizeof...(R) + 1))
	{
		return Offset<R0, R...>{std::forward<V>(a_offsets)...};
	}

	static_assert([]() consteval noexcept -> bool {
		constexpr auto TEST_RUNTIME_01 = REL::CreateRuntime(1, 0, 0, 0);
		constexpr auto TEST_RUNTIME_02 = REL::CreateRuntime(1, 0, 0, 1);

		constexpr auto TEST_OFFSET_01 = CreateOffset<TEST_RUNTIME_01, TEST_RUNTIME_02>(12'345'678, 23'456'789);
		constexpr auto TEST_OFFSET_02 = CreateOffset<TEST_RUNTIME_02>(34'567'890);
		constexpr auto TEST_OFFSET_03 = CreateOffset<>(45'678'901);

		return (TEST_OFFSET_01.GetOffset(TEST_RUNTIME_01) == 12'345'678) &&
			   (TEST_OFFSET_01.GetOffset(TEST_RUNTIME_02) == 23'456'789) &&
			   (TEST_OFFSET_01.GetOffset(Runtime::LATEST) == 23'456'789) &&
			   (TEST_OFFSET_02.GetOffset(TEST_RUNTIME_01) == IOffset::INVALID_OFFSET) &&
			   (TEST_OFFSET_02.GetOffset(TEST_RUNTIME_02) == 34'567'890) &&
			   (TEST_OFFSET_02.GetOffset(Runtime::LATEST) == 34'567'890) &&
			   (TEST_OFFSET_03.GetOffset(TEST_RUNTIME_01) == 45'678'901) &&
			   (TEST_OFFSET_03.GetOffset(TEST_RUNTIME_02) == 45'678'901) &&
			   (TEST_OFFSET_03.GetOffset(Runtime::LATEST) == 45'678'901);
	}());
}

namespace std
{
	template <class T>
		requires(std::derived_from<T, REL::IOffset>)
	struct hash<T>
	{
	public:
		[[nodiscard]]
		auto operator()(const T& a_key) const noexcept -> std::size_t
		{
			return REX::Hash(a_key.GetOffset());
		}
	};
}
