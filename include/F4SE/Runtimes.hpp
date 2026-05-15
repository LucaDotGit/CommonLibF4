#pragma once

#include "F4SE/Versions.hpp"

#include "REL/Id.hpp"
#include "REL/Offset.hpp"
#include "REL/Runtime.hpp"
#include "REL/Size.hpp"
#include "REL/Value.hpp"

#include "REX/Version.hpp"

namespace F4SE::Impl
{
	void InitRuntime(REX::Version a_runtimeVersion);
}

namespace F4SE
{
	enum class RuntimeType : std::int32_t
	{
		kNone = 0,
		kVR,
		kOG,
		kNG,
		kAE
	};

	[[nodiscard]] RuntimeType GetRuntimeType() noexcept;

	[[nodiscard]] bool IsRuntimeAtLeastVR() noexcept;
	[[nodiscard]] bool IsRuntimeAtLeastOG() noexcept;
	[[nodiscard]] bool IsRuntimeAtLeastNG() noexcept;
	[[nodiscard]] bool IsRuntimeAtLeastAE() noexcept;

	[[nodiscard]] bool IsRuntimeOnlyVR() noexcept;
	[[nodiscard]] bool IsRuntimeOnlyOG() noexcept;
	[[nodiscard]] bool IsRuntimeOnlyNG() noexcept;
	[[nodiscard]] bool IsRuntimeOnlyAE() noexcept;

	using VariantId = REL::Id<
		RUNTIME_LATEST_OG,
		RUNTIME_LATEST_NG,
		RUNTIME_LATEST_AE>;
	using VRVariantId = REL::Id<
		RUNTIME_LATEST_VR,
		RUNTIME_LATEST_OG,
		RUNTIME_LATEST_NG,
		RUNTIME_LATEST_AE>;

	using VariantOffset = REL::Offset<
		RUNTIME_LATEST_OG,
		RUNTIME_LATEST_NG,
		RUNTIME_LATEST_AE>;
	using VRVariantOffset = REL::Offset<
		RUNTIME_LATEST_VR,
		RUNTIME_LATEST_OG,
		RUNTIME_LATEST_NG,
		RUNTIME_LATEST_AE>;

	using VariantSize = REL::Size<
		RUNTIME_LATEST_OG,
		RUNTIME_LATEST_NG,
		RUNTIME_LATEST_AE>;
	using VRVariantSize = REL::Size<
		RUNTIME_LATEST_VR,
		RUNTIME_LATEST_OG,
		RUNTIME_LATEST_NG,
		RUNTIME_LATEST_AE>;

	template <class T>
	using VariantValue = REL::Value<T,
		RUNTIME_LATEST_OG,
		RUNTIME_LATEST_NG,
		RUNTIME_LATEST_AE>;

	template <class T>
	using VRVariantValue = REL::Value<T,
		RUNTIME_LATEST_VR,
		RUNTIME_LATEST_OG,
		RUNTIME_LATEST_NG,
		RUNTIME_LATEST_AE>;

	[[nodiscard]] constexpr auto CreateVariantId(
		std::uintptr_t a_ogId,
		std::uintptr_t a_ngId,
		std::uintptr_t a_aeId) noexcept
	{
		return REL::CreateId<
			RUNTIME_LATEST_OG,
			RUNTIME_LATEST_NG,
			RUNTIME_LATEST_AE>(
			a_ogId,
			a_ngId,
			a_aeId);
	}

	[[nodiscard]] constexpr auto CreateVRVariantId(
		std::uintptr_t a_vrId,
		std::uintptr_t a_ogId,
		std::uintptr_t a_ngId,
		std::uintptr_t a_aeId) noexcept
	{
		return REL::CreateId<
			RUNTIME_LATEST_VR,
			RUNTIME_LATEST_OG,
			RUNTIME_LATEST_NG,
			RUNTIME_LATEST_AE>(
			a_vrId,
			a_ogId,
			a_ngId,
			a_aeId);
	}

	[[nodiscard]] constexpr auto CreateVariantOffset(
		std::ptrdiff_t a_ogOffset,
		std::ptrdiff_t a_ngOffset,
		std::ptrdiff_t a_aeOffset) noexcept
	{
		return REL::CreateOffset<
			RUNTIME_LATEST_OG,
			RUNTIME_LATEST_NG,
			RUNTIME_LATEST_AE>(
			a_ogOffset,
			a_ngOffset,
			a_aeOffset);
	}

	[[nodiscard]] constexpr auto CreateVRVariantOffset(
		std::ptrdiff_t a_vrOffset,
		std::ptrdiff_t a_ogOffset,
		std::ptrdiff_t a_ngOffset,
		std::ptrdiff_t a_aeOffset) noexcept
	{
		return REL::CreateOffset<
			RUNTIME_LATEST_VR,
			RUNTIME_LATEST_OG,
			RUNTIME_LATEST_NG,
			RUNTIME_LATEST_AE>(
			a_vrOffset,
			a_ogOffset,
			a_ngOffset,
			a_aeOffset);
	}

	[[nodiscard]] constexpr auto CreateVariantSize(
		std::size_t a_ogSize,
		std::size_t a_ngSize,
		std::size_t a_aeSize) noexcept
	{
		return REL::CreateSize<
			RUNTIME_LATEST_OG,
			RUNTIME_LATEST_NG,
			RUNTIME_LATEST_AE>(
			a_ogSize,
			a_ngSize,
			a_aeSize);
	}

	[[nodiscard]] constexpr auto CreateVRVariantSize(
		std::size_t a_vrSize,
		std::size_t a_ogSize,
		std::size_t a_ngSize,
		std::size_t a_aeSize) noexcept
	{
		return REL::CreateSize<
			RUNTIME_LATEST_VR,
			RUNTIME_LATEST_OG,
			RUNTIME_LATEST_NG,
			RUNTIME_LATEST_AE>(
			a_vrSize,
			a_ogSize,
			a_ngSize,
			a_aeSize);
	}

	template <class T>
	[[nodiscard]] constexpr auto CreateVariantValue(
		T&& a_ogValue,
		T&& a_ngValue,
		T&& a_aeValue) //
		noexcept(noexcept(REL::CreateValue<
			RUNTIME_LATEST_OG,
			RUNTIME_LATEST_NG,
			RUNTIME_LATEST_AE>(
			std::forward<T>(a_ogValue),
			std::forward<T>(a_ngValue),
			std::forward<T>(a_aeValue))))
	{
		return REL::CreateValue<
			RUNTIME_LATEST_OG,
			RUNTIME_LATEST_NG,
			RUNTIME_LATEST_AE>(
			std::forward<T>(a_ogValue),
			std::forward<T>(a_ngValue),
			std::forward<T>(a_aeValue));
	}

	template <class T>
	[[nodiscard]] constexpr auto CreateVRVariantValue(
		T&& a_vrValue,
		T&& a_ogValue,
		T&& a_ngValue,
		T&& a_aeValue) //
		noexcept(noexcept(REL::CreateValue<
			RUNTIME_LATEST_VR,
			RUNTIME_LATEST_OG,
			RUNTIME_LATEST_NG,
			RUNTIME_LATEST_AE>(
			std::forward<T>(a_vrValue),
			std::forward<T>(a_ogValue),
			std::forward<T>(a_ngValue),
			std::forward<T>(a_aeValue))))
	{
		return REL::CreateValue<
			RUNTIME_LATEST_VR,
			RUNTIME_LATEST_OG,
			RUNTIME_LATEST_NG,
			RUNTIME_LATEST_AE>(
			std::forward<T>(a_vrValue),
			std::forward<T>(a_ogValue),
			std::forward<T>(a_ngValue),
			std::forward<T>(a_aeValue));
	}
}
