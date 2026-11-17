#pragma once

#include "REL/Iddb.hpp"
#include "REL/Module.hpp"
#include "REL/Runtime.hpp"
#include "REX/Hashing.hpp"

namespace REL
{
	class IId
	{
	public:
		using value_type = std::uintptr_t;

		inline static constexpr auto INVALID_ID = std::numeric_limits<value_type>::max();
		inline static constexpr auto INVALID_ID_OFFSET = std::numeric_limits<std::ptrdiff_t>::max();
		inline static constexpr auto INVALID_ID_ADDRESS = std::numeric_limits<std::uintptr_t>::min();

		IId() noexcept = default;
		virtual ~IId() noexcept = default;

		IId(const IId&) = delete;
		IId(IId&&) noexcept = default;

		auto operator=(const IId&) -> IId& = delete;
		auto operator=(IId&&) noexcept -> IId& = default;

		[[nodiscard]]
		auto operator==(const IId& a_rhs) const noexcept -> bool
		{
			return GetId() == a_rhs.GetId();
		}

		[[nodiscard]]
		auto operator<=>(const IId& a_rhs) const noexcept -> auto
		{
			return GetId() <=> a_rhs.GetId();
		}

		[[nodiscard]]
		virtual auto GetId() const noexcept -> value_type = 0;
		[[nodiscard]]
		virtual auto GetOffset() const noexcept -> std::ptrdiff_t = 0;
		[[nodiscard]]
		virtual auto GetAddress() const noexcept -> std::uintptr_t = 0;
	};

	template <REL::Runtime R0 = REL::Runtime::LATEST, REL::Runtime... R>
	class Id final : public IId
	{
	public:
		using IId::value_type;

		static_assert(REL::Impl::ValidateRuntimeValues<R0, R...>());
		static_assert(REL::Impl::ValidateRuntimeOrder<R0, R...>());

		inline static constexpr auto RUNTIMES = std::array{R0, R...};

		constexpr Id() noexcept = default;
		constexpr ~Id() noexcept override = default;

		template <class... V>
		constexpr explicit Id(V&&... a_ids) noexcept((std::is_nothrow_convertible_v<V, value_type> && ...))
			requires((std::is_convertible_v<V, value_type> && ...) && (sizeof...(V) == sizeof...(R) + 1))
			:
			_ids{static_cast<value_type>(std::forward<V>(a_ids))...}
		{
		}

		constexpr Id(const Id& a_rhs) noexcept :
			_ids(a_rhs._ids)
		{
		}

		constexpr Id(Id&&) noexcept = default;

		constexpr auto operator=(const Id& a_rhs) noexcept -> Id&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_ids = a_rhs._ids;
			return *this;
		}

		constexpr auto operator=(Id&&) noexcept -> Id& = default;

		[[nodiscard]]
		constexpr auto GetIds() const noexcept -> const auto&
		{
			return _ids;
		}

		[[nodiscard]]
		constexpr auto GetId(REL::Runtime a_runtime) const noexcept -> value_type
		{
			if (a_runtime == REL::Runtime::INVALID) [[unlikely]] {
				return INVALID_ID;
			}

			if constexpr (RUNTIMES.front() == REL::Runtime::LATEST) {
				return _ids.front();
			}
			else {
				const auto runtimeIt = std::ranges::upper_bound(RUNTIMES, a_runtime);
				if (runtimeIt == RUNTIMES.begin()) [[unlikely]] {
					return INVALID_ID;
				}

				const auto index = static_cast<std::size_t>(std::distance(RUNTIMES.begin(), std::prev(runtimeIt)));
				return _ids[index];
			}
		}

		[[nodiscard]]
		auto GetId() const noexcept -> value_type override
		{
			const auto currentRuntime = REL::Module::GetSingleton().GetRuntime();
			return GetId(currentRuntime);
		}

		[[nodiscard]]
		auto GetOffset() const noexcept -> std::ptrdiff_t override
		{
			const auto id = GetId();
			if (id == INVALID_ID) {
				return INVALID_ID_OFFSET;
			}

			return REL::Iddb::GetSingleton().GetOffset(id);
		}

		[[nodiscard]]
		auto GetAddress() const noexcept -> std::uintptr_t override
		{
			const auto offset = GetOffset();
			if (offset == INVALID_ID_OFFSET) {
				return INVALID_ID_ADDRESS;
			}

			const auto baseAddress = REL::Module::GetSingleton().GetBaseAddress();
			return baseAddress + static_cast<std::uintptr_t>(offset);
		}

		constexpr void swap(Id& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_ids, a_other._ids);
		}

	private:
		std::array<value_type, RUNTIMES.size()> _ids;
	};

	template <class T>
	[[nodiscard]]
	constexpr auto CreateId(T&& a_id) noexcept(std::is_nothrow_constructible_v<Id<>, T>)
		requires(std::is_constructible_v<Id<>, T>)
	{
		return Id<>{std::forward<T>(a_id)};
	}

	template <REL::Runtime R0, REL::Runtime... R, class... V>
	[[nodiscard]]
	constexpr auto CreateId(V&&... a_ids) noexcept(std::is_nothrow_constructible_v<Id<R0, R...>, V...>)
		requires(std::is_constructible_v<Id<R0, R...>, V...> && (sizeof...(V) == sizeof...(R) + 1))
	{
		return Id<R0, R...>{std::forward<V>(a_ids)...};
	}

	static_assert([]() consteval noexcept -> bool {
		constexpr auto TEST_RUNTIME_01 = REL::CreateRuntime(1, 0, 0, 0);
		constexpr auto TEST_RUNTIME_02 = REL::CreateRuntime(1, 0, 0, 1);

		constexpr auto TEST_ID_01 = CreateId<TEST_RUNTIME_01, TEST_RUNTIME_02>(12'345'678, 23'456'789);
		constexpr auto TEST_ID_02 = CreateId<TEST_RUNTIME_02>(34'567'890);
		constexpr auto TEST_ID_03 = CreateId<>(45'678'901);

		return (TEST_ID_01.GetId(TEST_RUNTIME_01) == 12'345'678) &&
			   (TEST_ID_01.GetId(TEST_RUNTIME_02) == 23'456'789) &&
			   (TEST_ID_01.GetId(Runtime::LATEST) == 23'456'789) &&
			   (TEST_ID_02.GetId(TEST_RUNTIME_01) == IId::INVALID_ID) &&
			   (TEST_ID_02.GetId(TEST_RUNTIME_02) == 34'567'890) &&
			   (TEST_ID_02.GetId(Runtime::LATEST) == 34'567'890) &&
			   (TEST_ID_03.GetId(TEST_RUNTIME_01) == 45'678'901) &&
			   (TEST_ID_03.GetId(TEST_RUNTIME_02) == 45'678'901) &&
			   (TEST_ID_03.GetId(Runtime::LATEST) == 45'678'901);
	}());
}

namespace std
{
	template <class T>
		requires(std::derived_from<T, REL::IId>)
	struct hash<T>
	{
	public:
		[[nodiscard]]
		auto operator()(const T& a_key) const noexcept -> std::size_t
		{
			return REX::Hash(a_key.GetId());
		}
	};
}
