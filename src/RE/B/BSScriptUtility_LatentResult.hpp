#pragma once

#include "RE/B/BSScriptUtility_Concepts.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"

namespace RE::BSScript
{
	class IVirtualMachine;

	enum class LatentStatus : std::uint8_t
	{
		Failed = 0,
		Started = 1
	};

	template <class T>
	class LatentResult
	{
	public:
		using value_type = T;

		static_assert(BSScript::ValidateReturn<value_type>());

		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr LatentResult(LatentStatus a_status) noexcept :
			_status(a_status)
		{
		}

		constexpr ~LatentResult() noexcept = default;

		constexpr LatentResult(const LatentResult&) noexcept = default;
		constexpr LatentResult(LatentResult&&) noexcept = default;

		constexpr auto operator=(const LatentResult&) noexcept -> LatentResult& = default;
		constexpr auto operator=(LatentResult&&) noexcept -> LatentResult& = default;

		[[nodiscard]]
		constexpr auto operator==(const LatentResult&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const LatentResult&) const noexcept = default;

		[[nodiscard]]
		constexpr explicit operator bool() const noexcept
		{
			return static_cast<bool>(_status);
		}

		[[nodiscard]]
		constexpr auto GetStatus() const noexcept -> LatentStatus
		{
			return _status;
		}

		[[nodiscard]]
		static auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>
		{
			return Impl::GetTypeInfo<value_type>(a_vm);
		}

	private:
		LatentStatus _status{LatentStatus::Failed};
	};
}
