#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BaseExtraList.hpp"

namespace RE
{
	enum class EXTRA_DATA_TYPE : std::int32_t;

	class BSExtraData;
}

namespace RE::Impl
{
	template <class T>
	concept ExtraDataListConstraint =
		std::derived_from<T, BSExtraData> &&
		!std::is_pointer_v<T> &&
		!std::is_reference_v<T> &&
		std::same_as<std::remove_cv_t<decltype(T::EXTRA_TYPE)>, EXTRA_DATA_TYPE>;
}

namespace RE
{
	class TBO_InstanceData;

	class ExtraDataList
		: public BSIntrusiveRefCounted // 00
	{
	public:
		using ComparisonQualifier = bool (*)(const BSExtraData* a_extraData);

		enum class CLEAR_FOR : std::int32_t
		{
			kContainer = 0,
			kReference = 1
		};

		ExtraDataList() noexcept = default;
		~ExtraDataList() noexcept = default;

		ExtraDataList(const ExtraDataList&) = delete;
		ExtraDataList(ExtraDataList&&) = delete;

		ExtraDataList& operator=(const ExtraDataList&) = delete;
		ExtraDataList& operator=(ExtraDataList&&) = delete;

		[[nodiscard]] bool HasExtra(EXTRA_DATA_TYPE a_type) const noexcept;

		template <Impl::ExtraDataListConstraint T>
		[[nodiscard]] bool HasExtra() const noexcept
		{
			return HasExtra(T::EXTRA_TYPE);
		}

		[[nodiscard]] BSExtraData* GetExtra(EXTRA_DATA_TYPE a_type) const noexcept;

		template <Impl::ExtraDataListConstraint T>
		[[nodiscard]] T* GetExtra() const noexcept
		{
			return static_cast<T*>(GetExtra(T::EXTRA_TYPE));
		}

		void AddExtra(BSExtraData* a_extra) noexcept;

		template <Impl::ExtraDataListConstraint T>
		T* GetOrCreateExtra()
			requires(std::is_default_constructible_v<T>)
		{
			const auto extraLock = BSAutoWriteLock(extraRWLock);

			auto* extra = GetExtra<T>();
			if (extra) {
				return extra;
			}

			extra = new T();
			AddExtra(extra);
			return extra;
		}

		std::unique_ptr<BSExtraData> RemoveExtra(EXTRA_DATA_TYPE a_type) noexcept;

		template <Impl::ExtraDataListConstraint T>
		std::unique_ptr<T> RemoveExtra() noexcept
		{
			return std::unique_ptr<T>{ static_cast<T*>(RemoveExtra(T::EXTRA_TYPE).release()) };
		}

		[[nodiscard]] bool CompareList(const ExtraDataList* a_compare, ComparisonQualifier a_qualifier);
		[[nodiscard]] bool CompareListForContainer(const ExtraDataList* a_compare);
		[[nodiscard]] bool CompareListForUI(const ExtraDataList* a_compare);

		[[nodiscard]] TBO_InstanceData* CreateInstanceData(TESBoundObject* a_object, bool a_generateName);

		// members
		BaseExtraList extraData;			 // 08
		mutable BSReadWriteLock extraRWLock; // 20
	};
	static_assert(sizeof(ExtraDataList) == 0x28);
}
