#pragma once

#include "RE/B/BSTHashMap.hpp"

namespace RE::BSShaderTechniqueIDMap
{
	template <class T>
	class HashPolicy
	{
	public:
		[[nodiscard]] std::uint32_t operator()(const T a_shader) const noexcept
		{
			REX::Assert(a_shader != nullptr);
			return a_shader->id;
		}
	};

	template <class T>
	class ComparePolicy
	{
	public:
		[[nodiscard]] bool operator()(const T a_lhs, const T a_rhs) const noexcept
		{
			REX::Assert(a_lhs != nullptr);
			REX::Assert(a_rhs != nullptr);
			return a_lhs->id == a_rhs->id;
		}
	};

	template <class T>
	using MapType = BSTSet<T, HashPolicy<T>, ComparePolicy<T>>;
}
