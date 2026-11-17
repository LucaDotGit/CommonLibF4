#pragma once

namespace Scaleform::GFx
{
	class Movie;
	class Value;
}

namespace F4SE::Events
{
	class IOnScaleformMenuCreate
	{
	public:
		IOnScaleformMenuCreate() noexcept = default;
		virtual ~IOnScaleformMenuCreate() noexcept = default;

		IOnScaleformMenuCreate(const IOnScaleformMenuCreate&) noexcept = default;
		IOnScaleformMenuCreate(IOnScaleformMenuCreate&&) noexcept = default;

		auto operator=(const IOnScaleformMenuCreate&) noexcept -> IOnScaleformMenuCreate& = default;
		auto operator=(IOnScaleformMenuCreate&&) noexcept -> IOnScaleformMenuCreate& = default;

		virtual void OnScaleformMenuCreate(Scaleform::GFx::Movie& a_movie, Scaleform::GFx::Value& a_value) = 0;
	};
}
