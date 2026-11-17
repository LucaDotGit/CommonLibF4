#pragma once

#include "RE/C/CXAPOBase.hpp"

namespace RE
{
	class __declspec(novtable) MonitorAPO : public CXAPOBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::__MonitorAPO;
		inline static constexpr const auto& VTABLE = VTABLE::__MonitorAPO;

		// override (IXAPO)
		void Reset() noexcept override; // 0x03
		auto LockForProcess(
			std::uint32_t a_inputLockedParameterCount,
			const REX::W32::XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS* a_inputLockedParameters,
			std::uint32_t a_outputLockedParameterCount,
			const REX::W32::XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS* a_outputLockedParameters) noexcept
			-> REX::W32::HRESULT override; // 0x04
		void Process(
			std::uint32_t a_inputProcessParameterCount,
			const REX::W32::XAPO_PROCESS_BUFFER_PARAMETERS* a_inputProcessParameters,
			uint32_t a_outputProcessParameterCount,
			REX::W32::XAPO_PROCESS_BUFFER_PARAMETERS* a_outputProcessParameters,
			REX::W32::BOOL a_isEnabled) noexcept override; // 0x06

		~MonitorAPO() override; // 0x0A

		// members
		std::uint32_t numChannels;		// 0x30
		REX::Float32 peak;				// 0x34
		REX::Float32 peakDecayScalar;	// 0x38
		REX::Float32 peakDecayHalflife; // 0x3C
	};

	static_assert(sizeof(MonitorAPO) == 0x40);
}
