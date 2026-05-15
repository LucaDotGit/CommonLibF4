#pragma once

#include "RE/H/hkReferencedObject.hpp"

namespace RE
{
	class __declspec(novtable) hkHardwareInfo
		: public hkReferencedObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hkHardwareInfo };
		inline static constexpr auto VTABLE{ VTABLE::hkHardwareInfo };

		[[nodiscard]] static std::int32_t CalcNumHardwareThreads()
		{
			using FuncType = decltype(&hkHardwareInfo::CalcNumHardwareThreads);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::hkHardwareInfo::CalcNumHardwareThreads };
			return std::invoke(FUNC);
		}

		// members
		std::int32_t numHardwareThreads; // 10
		std::uint32_t cpuFeatures;		 // 14
	};
	static_assert(sizeof(hkHardwareInfo) == 0x18);
}
