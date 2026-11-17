#pragma once

#include "F4SE/Versions.hpp"
#include "REL/Id.hpp"
#include "REL/Offset.hpp"
#include "REL/Runtime.hpp"
#include "REL/Size.hpp"
#include "REL/Value.hpp"

namespace F4SE
{
	[[nodiscard]]
	auto IsRuntimeAtLeastVR() noexcept -> bool;

	[[nodiscard]]
	auto IsRuntimeAtLeastOG() noexcept -> bool;

	[[nodiscard]]
	auto IsRuntimeAtLeastNG() noexcept -> bool;

	[[nodiscard]]
	auto IsRuntimeAtLeastAE() noexcept -> bool;

	[[nodiscard]]
	auto IsRuntimeOnlyVR() noexcept -> bool;

	[[nodiscard]]
	auto IsRuntimeOnlyOG() noexcept -> bool;

	[[nodiscard]]
	auto IsRuntimeOnlyNG() noexcept -> bool;

	[[nodiscard]]
	auto IsRuntimeOnlyAE() noexcept -> bool;

	using VariantId = REL::Id<RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>;

	using VariantIdVR = REL::Id<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>;

	using VariantOffset = REL::Offset<RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>;

	using VariantOffsetVR = REL::Offset<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>;

	using VariantSize = REL::Size<RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>;

	using VariantSizeVR = REL::Size<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>;

	template <class T>
	using VariantValue = REL::Value<T, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>;

	template <class T>
	using VariantValueVR = REL::Value<T, RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>;

	[[nodiscard]]
	constexpr auto CreateVariantId(std::uintptr_t a_ogId, std::uintptr_t a_ngId) noexcept
	{
		return REL::CreateId<RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(a_ogId, a_ngId, a_ngId);
	}

	[[nodiscard]]
	constexpr auto CreateVariantId(std::uintptr_t a_ogId, std::uintptr_t a_ngId, std::uintptr_t a_aeId) noexcept
	{
		return REL::CreateId<RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(a_ogId, a_ngId, a_aeId);
	}

	[[nodiscard]]
	constexpr auto CreateVariantIdVR(std::uintptr_t a_vrId, std::uintptr_t a_ogId) noexcept
	{
		return REL::CreateId<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			a_vrId,
			a_ogId,
			a_ogId,
			a_ogId);
	}

	[[nodiscard]]
	constexpr auto CreateVariantIdVR(std::uintptr_t a_vrId, std::uintptr_t a_ogId, std::uintptr_t a_ngId) noexcept
	{
		return REL::CreateId<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			a_vrId,
			a_ogId,
			a_ngId,
			a_ngId);
	}

	[[nodiscard]]
	constexpr auto CreateVariantIdVR(
		std::uintptr_t a_vrId,
		std::uintptr_t a_ogId,
		std::uintptr_t a_ngId,
		std::uintptr_t a_aeId) noexcept
	{
		return REL::CreateId<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			a_vrId,
			a_ogId,
			a_ngId,
			a_aeId);
	}

	[[nodiscard]]
	constexpr auto CreateVariantOffset(std::ptrdiff_t a_ogOffset, std::ptrdiff_t a_ngOffset) noexcept
	{
		return REL::CreateOffset<RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			a_ogOffset,
			a_ngOffset,
			a_ngOffset);
	}

	[[nodiscard]]
	constexpr auto CreateVariantOffset(std::ptrdiff_t a_ogOffset, std::ptrdiff_t a_ngOffset, std::ptrdiff_t a_aeOffset)
		noexcept
	{
		return REL::CreateOffset<RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			a_ogOffset,
			a_ngOffset,
			a_aeOffset);
	}

	[[nodiscard]]
	constexpr auto CreateVariantOffsetVR(std::ptrdiff_t a_vrOffset, std::ptrdiff_t a_ogOffset) noexcept
	{
		return REL::CreateOffset<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			a_vrOffset,
			a_ogOffset,
			a_ogOffset,
			a_ogOffset);
	}

	[[nodiscard]]
	constexpr auto CreateVariantOffsetVR(
		std::ptrdiff_t a_vrOffset,
		std::ptrdiff_t a_ogOffset,
		std::ptrdiff_t a_ngOffset) noexcept
	{
		return REL::CreateOffset<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			a_vrOffset,
			a_ogOffset,
			a_ngOffset,
			a_ogOffset);
	}

	[[nodiscard]]
	constexpr auto CreateVariantOffsetVR(
		std::ptrdiff_t a_vrOffset,
		std::ptrdiff_t a_ogOffset,
		std::ptrdiff_t a_ngOffset,
		std::ptrdiff_t a_aeOffset) noexcept
	{
		return REL::CreateOffset<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			a_vrOffset,
			a_ogOffset,
			a_ngOffset,
			a_aeOffset);
	}

	[[nodiscard]]
	constexpr auto CreateVariantSize(std::size_t a_ogSize, std::size_t a_ngSize) noexcept
	{
		return REL::CreateSize<RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(a_ogSize, a_ngSize, a_ngSize);
	}

	[[nodiscard]]
	constexpr auto CreateVariantSize(std::size_t a_ogSize, std::size_t a_ngSize, std::size_t a_aeSize) noexcept
	{
		return REL::CreateSize<RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(a_ogSize, a_ngSize, a_aeSize);
	}

	[[nodiscard]]
	constexpr auto CreateVariantSizeVR(std::size_t a_vrSize, std::size_t a_ogSize) noexcept
	{
		return REL::CreateSize<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			a_vrSize,
			a_ogSize,
			a_ogSize,
			a_ogSize);
	}

	[[nodiscard]]
	constexpr auto CreateVariantSizeVR(std::size_t a_vrSize, std::size_t a_ogSize, std::size_t a_ngSize) noexcept
	{
		return REL::CreateSize<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			a_vrSize,
			a_ogSize,
			a_ngSize,
			a_ogSize);
	}

	[[nodiscard]]
	constexpr auto CreateVariantSizeVR(
		std::size_t a_vrSize,
		std::size_t a_ogSize,
		std::size_t a_ngSize,
		std::size_t a_aeSize) noexcept
	{
		return REL::CreateSize<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			a_vrSize,
			a_ogSize,
			a_ngSize,
			a_aeSize);
	}

	template <class T>
	[[nodiscard]]
	constexpr auto CreateVariantValue(const T& a_ogValue, const T& a_ngValue) noexcept(noexcept(
		REL::CreateValue<RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(a_ogValue, a_ngValue, a_ngValue)))
		requires(requires {
			REL::CreateValue<RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(a_ogValue, a_ngValue, a_ngValue);
		})
	{
		return REL::CreateValue<RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			a_ogValue,
			a_ngValue,
			a_ngValue);
	}

	template <class T>
	[[nodiscard]]
	constexpr auto CreateVariantValue(T&& a_ogValue, T&& a_ngValue, T&& a_aeValue)
		noexcept(noexcept(REL::CreateValue<RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			std::forward<T>(a_ogValue),
			std::forward<T>(a_ngValue),
			std::forward<T>(a_aeValue))))
		requires(requires {
			REL::CreateValue<RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
				std::forward<T>(a_ogValue),
				std::forward<T>(a_ngValue),
				std::forward<T>(a_aeValue));
		})
	{
		return REL::CreateValue<RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			std::forward<T>(a_ogValue),
			std::forward<T>(a_ngValue),
			std::forward<T>(a_aeValue));
	}

	template <class T>
	[[nodiscard]]
	constexpr auto CreateVariantValueVR(const T& a_vrValue, const T& a_ogValue)
		noexcept(noexcept(REL::CreateValue<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			a_vrValue,
			a_ogValue,
			a_ogValue,
			a_ogValue)))
		requires(requires {
			REL::CreateValue<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
				a_vrValue,
				a_ogValue,
				a_ogValue,
				a_ogValue);
		})
	{
		return REL::CreateValue<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			a_vrValue,
			a_ogValue,
			a_ogValue,
			a_ogValue);
	}

	template <class T>
	[[nodiscard]]
	constexpr auto CreateVariantValueVR(const T& a_vrValue, const T& a_ogValue, const T& a_ngValue)
		noexcept(noexcept(REL::CreateValue<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			a_vrValue,
			a_ogValue,
			a_ngValue,
			a_ngValue)))
		requires(requires {
			REL::CreateValue<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
				a_vrValue,
				a_ogValue,
				a_ngValue,
				a_ngValue);
		})
	{
		return REL::CreateValue<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			a_vrValue,
			a_ogValue,
			a_ngValue,
			a_ngValue);
	}

	template <class T>
	[[nodiscard]]
	constexpr auto CreateVariantValueVR(T&& a_vrValue, T&& a_ogValue, T&& a_ngValue, T&& a_aeValue)
		noexcept(noexcept(REL::CreateValue<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			std::forward<T>(a_vrValue),
			std::forward<T>(a_ogValue),
			std::forward<T>(a_ngValue),
			std::forward<T>(a_aeValue))))
		requires(requires {
			REL::CreateValue<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
				std::forward<T>(a_vrValue),
				std::forward<T>(a_ogValue),
				std::forward<T>(a_ngValue),
				std::forward<T>(a_aeValue));
		})
	{
		return REL::CreateValue<RUNTIME_LATEST_VR, RUNTIME_LATEST_OG, RUNTIME_LATEST_NG, RUNTIME_LATEST_AE>(
			std::forward<T>(a_vrValue),
			std::forward<T>(a_ogValue),
			std::forward<T>(a_ngValue),
			std::forward<T>(a_aeValue));
	}
}
