#pragma once

#include "RE/B/BSScriptUtil_Concepts.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"

namespace RE::BSScript
{
	enum class LatentStatus : std::uint8_t
	{
		kFailed = 0,
		kStarted = 1
	};

	template <class T>
	class LatentResult
	{
	public:
		using value_type = T;

		static_assert(BSScript::ValidateReturn<value_type>());

		constexpr LatentResult(LatentStatus a_status) noexcept
			: _status(a_status)
		{
		}

		constexpr ~LatentResult() noexcept = default;

		constexpr LatentResult(const LatentResult&) noexcept = default;
		constexpr LatentResult(LatentResult&&) noexcept = default;

		constexpr LatentResult& operator=(const LatentResult&) noexcept = default;
		constexpr LatentResult& operator=(LatentResult&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const LatentResult&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const LatentResult&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const LatentResult&) const noexcept = default;

		[[nodiscard]] constexpr explicit operator bool() const noexcept { return static_cast<bool>(_status); }

		[[nodiscard]] constexpr LatentStatus GetStatus() const noexcept { return _status; }

		[[nodiscard]] static TypeInfo GetTypeInfo()
		{
			const auto typeInfo = Impl::GetTypeInfo<value_type>();
			return typeInfo.value_or(nullptr);
		}

	private:
		LatentStatus _status{ LatentStatus::kFailed };
	};
}
