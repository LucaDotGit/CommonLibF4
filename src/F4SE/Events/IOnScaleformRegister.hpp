#pragma once

namespace F4SE
{
	class ScaleformInterface;
}

namespace F4SE::Events
{
	class IOnScaleformRegister
	{
	public:
		IOnScaleformRegister() noexcept = default;
		virtual ~IOnScaleformRegister() noexcept = default;

		IOnScaleformRegister(const IOnScaleformRegister&) noexcept = default;
		IOnScaleformRegister(IOnScaleformRegister&&) noexcept = default;

		auto operator=(const IOnScaleformRegister&) noexcept -> IOnScaleformRegister& = default;
		auto operator=(IOnScaleformRegister&&) noexcept -> IOnScaleformRegister& = default;

		virtual void OnScaleformRegister(const F4SE::ScaleformInterface* a_interface) = 0;
	};
}
