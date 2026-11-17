#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSReadWriteLock.hpp"
#include "RE/B/BaseExtraList.hpp"

namespace RE
{
	enum class EXTRA_DATA_TYPE : std::int32_t;

	class BSExtraData;
}

namespace RE::Impl
{
	template <class T>
	concept ExtraDataListConstraint = std::derived_from<T, BSExtraData> &&
									  !REX::pointer<T> &&
									  !REX::reference<T> &&
									  std::same_as<std::remove_cv_t<decltype(T::EXTRA_TYPE)>, EXTRA_DATA_TYPE>;
}

namespace RE
{
	class TBO_InstanceData;

	class ExtraDataList : public BSIntrusiveRefCounted // 0x00
	{
	public:
		using ComparisonQualifier = bool (*)(const BSExtraData* a_extraData);

		enum class CLEAR_FOR : std::int32_t
		{
			Container = 0,
			Reference = 1
		};

		ExtraDataList() noexcept = default;
		~ExtraDataList() noexcept = default;

		ExtraDataList(const ExtraDataList&) = delete;
		ExtraDataList(ExtraDataList&&) = delete;

		auto operator=(const ExtraDataList&) -> ExtraDataList& = delete;
		auto operator=(ExtraDataList&&) -> ExtraDataList& = delete;

		[[nodiscard]]
		auto HasExtra(EXTRA_DATA_TYPE a_type) const noexcept -> bool;

		template <Impl::ExtraDataListConstraint T>
		[[nodiscard]]
		auto HasExtra() const noexcept -> bool
		{
			return HasExtra(T::EXTRA_TYPE);
		}

		[[nodiscard]]
		auto GetExtra(EXTRA_DATA_TYPE a_type) const noexcept -> BSExtraData*;

		template <Impl::ExtraDataListConstraint T>
		[[nodiscard]]
		auto GetExtra() const noexcept -> T*
		{
			return static_cast<T*>(GetExtra(T::EXTRA_TYPE));
		}

		auto AddExtra(std::unique_ptr<BSExtraData> a_extra) noexcept -> BSExtraData*;

		template <Impl::ExtraDataListConstraint T>
		auto AddExtra(std::unique_ptr<T> a_extra) noexcept -> T*
		{
			return static_cast<T*>(AddExtra(std::unique_ptr<BSExtraData>(std::move(a_extra))));
		}

		template <Impl::ExtraDataListConstraint T>
		auto GetOrCreateExtra() -> T*
			requires(std::is_default_constructible_v<T>)
		{
			const auto extraLock = BSAutoWriteLock(extraRWLock);

			auto* extraData = GetExtra<T>();
			if (extraData) {
				return extraData;
			}

			auto newExtraData = std::make_unique<T>();
			return AddExtra(std::move(newExtraData));
		}

		auto RemoveExtra(EXTRA_DATA_TYPE a_type) noexcept -> std::unique_ptr<BSExtraData>;

		template <Impl::ExtraDataListConstraint T>
		auto RemoveExtra() noexcept -> std::unique_ptr<T>
		{
			return std::unique_ptr<T>(static_cast<T*>(RemoveExtra(T::EXTRA_TYPE).release()));
		}

		[[nodiscard]]
		auto CompareList(const ExtraDataList* a_compare, ComparisonQualifier a_qualifier) -> bool;
		[[nodiscard]]
		auto CompareListForContainer(const ExtraDataList* a_compare) -> bool;
		[[nodiscard]]
		auto CompareListForUI(const ExtraDataList* a_compare) -> bool;

		void CopyList(const ExtraDataList* a_source);
		[[nodiscard]]
		auto CreateInstanceData(TESBoundObject* a_object, bool a_generateName) -> TBO_InstanceData*;

		// members
		BaseExtraList extraList;			 // 0x08
		mutable BSReadWriteLock extraRWLock; // 0x20
	};

	static_assert(sizeof(ExtraDataList) == 0x28);
}
