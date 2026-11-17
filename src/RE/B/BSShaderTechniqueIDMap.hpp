#pragma once

#include "RE/B/BSTHashMap.hpp"

namespace RE::BSShaderTechniqueIDMap
{
	template <class T>
	class HashPolicy
	{
	public:
		[[nodiscard]]
		auto operator()(const T& a_key) const noexcept -> std::uint32_t
		{
			REX::Assert(a_key != nullptr);

			return a_key->id;
		}
	};

	template <class T>
	class ComparePolicy
	{
	public:
		[[nodiscard]]
		auto operator()(const T& a_lhs, const T& a_rhs) const noexcept -> bool
		{
			REX::Assert(a_lhs != nullptr);
			REX::Assert(a_rhs != nullptr);

			return a_lhs->id == a_rhs->id;
		}
	};

	template <class T>
	using MapType = BSTSet<T, HashPolicy<T>, ComparePolicy<T>>;
}
