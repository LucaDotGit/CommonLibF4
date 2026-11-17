#pragma once

namespace RE
{
	class __declspec(novtable) CXAPOBase : public REX::W32::IXAPO // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::CXAPOBase;

		// add
		virtual auto ValidateFormatDefault(REX::W32::WAVEFORMATEX* a_format, REX::W32::BOOL a_overwrite) noexcept
			-> REX::W32::HRESULT = 0;	// 0x09
		virtual ~CXAPOBase() = default; // 0x0A

		// members
		REX::W32::XAPO_REGISTRATION_PROPERTIES* registrationProperties{nullptr}; // 0x08
		void* matrixMixFunction{nullptr};										 // 0x10
		REX::Float32* matrixCoefficients{nullptr};								 // 0x18
		std::uint32_t srcFormatType{0};											 // 0x20
		REX::W32::BOOL isScalarMatrix{false};									 // 0x24
		REX::W32::BOOL isLocked{false};											 // 0x28
		std::int32_t referenceCount{0};											 // 0x2C
	};

	static_assert(sizeof(CXAPOBase) == 0x30);
}
