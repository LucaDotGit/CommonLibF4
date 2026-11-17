#pragma once

#include "RE/H/hkReferencedObject.hpp"

namespace RE
{
	class __declspec(novtable) hkHardwareInfo : public hkReferencedObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hkHardwareInfo;
		inline static constexpr const auto& VTABLE = VTABLE::hkHardwareInfo;

		[[nodiscard]]
		static auto CalcNumHardwareThreads() -> std::int32_t
		{
			using FuncType = decltype(&hkHardwareInfo::CalcNumHardwareThreads);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hkHardwareInfo::CalcNumHardwareThreads);
			return std::invoke(FUNC);
		}

		// members
		std::int32_t numHardwareThreads; // 0x10
		std::uint32_t cpuFeatures;		 // 0x14
	};

	static_assert(sizeof(hkHardwareInfo) == 0x18);
}
