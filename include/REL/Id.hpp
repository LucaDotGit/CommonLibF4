#pragma once

#include "REL/Iddb.hpp"
#include "REL/Module.hpp"
#include "REL/Runtime.hpp"

#include "REX/Hash.hpp"

namespace REL
{
	inline constexpr auto INVALID_ID = std::numeric_limits<std::uintptr_t>::max();
	inline constexpr auto INVALID_ID_OFFSET = std::numeric_limits<std::ptrdiff_t>::max();
	inline constexpr auto INVALID_ID_ADDRESS = std::numeric_limits<std::uintptr_t>::min();

	class IId
	{
	public:
		using value_type = std::uintptr_t;

		virtual ~IId() noexcept = default;

		[[nodiscard]] virtual value_type GetId() const noexcept = 0;
		[[nodiscard]] virtual std::ptrdiff_t GetOffset() const noexcept = 0;
		[[nodiscard]] virtual std::uintptr_t GetAddress() const noexcept = 0;
	};

	template <Runtime R0 = Runtime::LATEST, Runtime... R>
	class Id final
		: public IId
	{
	public:
		using value_type = IId::value_type;

		static_assert(REL::Impl::ValidateRuntimeValues<R0, R...>());
		static_assert(REL::Impl::ValidateRuntimeOrder<R0, R...>());

		inline static constexpr auto RUNTIMES = std::array{ R0, R... };

		constexpr Id() noexcept = default;
		constexpr ~Id() noexcept override = default;

		template <class... V>
		constexpr explicit Id(V&&... a_ids) //
			noexcept((std::is_nothrow_convertible_v<V, value_type> && ...))
			requires((std::is_convertible_v<V, value_type> && ...) &&
					 (sizeof...(V) == sizeof...(R) + 1))
			: _ids{ static_cast<value_type>(std::forward<V>(a_ids))... }
		{
		}

		constexpr Id(const Id&) noexcept = default;
		constexpr Id(Id&&) noexcept = default;

		constexpr Id& operator=(const Id&) noexcept = default;
		constexpr Id& operator=(Id&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const Id&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const Id&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const Id&) const noexcept = default;

		[[nodiscard]] constexpr const auto& GetIds() const noexcept { return _ids; }

		[[nodiscard]] constexpr value_type GetId(Runtime a_runtime) const noexcept
		{
			if constexpr (RUNTIMES.size() == 1) {
				if (a_runtime > RUNTIMES.front()) {
					return INVALID_ID;
				}

				return _ids.front();
			}
			else {
				const auto runtimeIt = std::ranges::upper_bound(RUNTIMES, a_runtime);
				if (runtimeIt == RUNTIMES.begin()) {
					return INVALID_ID;
				}

				const auto index = static_cast<std::size_t>(std::distance(RUNTIMES.begin(), runtimeIt - 1));
				return _ids[index];
			}
		}

		[[nodiscard]] value_type GetId() const noexcept override
		{
			const auto currentRuntime = REL::Module::GetSingleton()->GetRuntime();
			return GetId(currentRuntime);
		}

		[[nodiscard]] std::ptrdiff_t GetOffset() const noexcept override
		{
			const auto id = GetId();
			if (id == INVALID_ID) {
				return INVALID_ID_OFFSET;
			}

			return REL::Iddb::GetSingleton()->GetOffset(id);
		}

		[[nodiscard]] std::uintptr_t GetAddress() const noexcept override
		{
			const auto offset = GetOffset();
			if (offset == INVALID_ID_OFFSET) {
				return INVALID_ID_ADDRESS;
			}

			const auto baseAddress = REL::Module::GetSingleton()->GetBaseAddress();
			return baseAddress + offset;
		}

		constexpr void swap(Id& a_other) noexcept
		{
			std::swap(_ids, a_other._ids);
		}

	private:
		std::array<value_type, RUNTIMES.size()> _ids;
	};

	template <Runtime R0 = Runtime::LATEST, Runtime... R>
	constexpr void swap(Id<R0, R...>& a_lhs, Id<R0, R...>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	template <class V>
	[[nodiscard]] constexpr auto CreateId(V&& a_id) //
		noexcept(std::is_nothrow_constructible_v<Id<>, V>)
		requires(std::is_constructible_v<Id<>, V>)
	{
		return Id<>{ std::forward<V>(a_id) };
	}

	template <Runtime R0, Runtime... R, class... V>
	[[nodiscard]] constexpr auto CreateId(V&&... a_ids) //
		noexcept(std::is_nothrow_constructible_v<Id<R0, R...>, V...>)
		requires(std::is_constructible_v<Id<R0, R...>, V...> &&
				 (sizeof...(V) == sizeof...(R) + 1))
	{
		return Id<R0, R...>{ std::forward<V>(a_ids)... };
	}
}

namespace std
{
	template <class T>
		requires(std::derived_from<T, REL::IId>)
	struct hash<T>
	{
	public:
		[[nodiscard]] std::size_t operator()(const T& a_key) const noexcept
		{
			return REX::Hash(a_key.GetId());
		}
	};
}
