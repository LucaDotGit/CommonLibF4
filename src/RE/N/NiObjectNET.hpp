#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/N/NiExtraData.hpp"
#include "RE/N/NiObject.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiTimeController.hpp"

namespace RE::BSContainer
{
	enum class ForEachResult : std::int32_t;
}

namespace RE
{
	class NiExtraDataContainer;

	class __declspec(novtable) NiObjectNET : public NiObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiObjectNET;
		inline static constexpr const auto& VTABLE = VTABLE::NiObjectNET;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiObjectNET;

		enum class CopyType : std::int32_t
		{
			None = 0,
			Exact = 1,
			Unique = 2
		};

		NiObjectNET();

		~NiObjectNET() override; // 0x00

		[[nodiscard]]
		auto GetName() const noexcept -> BSFixedString
		{
			return name;
		}

		void SetName(BSFixedString a_name) noexcept
		{
			name = std::move(a_name);
		}

		[[nodiscard]]
		static auto FormatExtraDataName(const NiExtraData& a_extraData, std::uint32_t a_extraDataSize)
			-> std::optional<BSFixedString>;

		[[nodiscard]]
		auto HasExtraData(const BSFixedString& a_key) const noexcept -> bool;
		[[nodiscard]]
		auto GetExtraData(const BSFixedString& a_key) const noexcept -> NiPointer<NiExtraData>;
		auto AddExtraData(NiPointer<NiExtraData> a_extraData) -> bool;
		auto InsertExtraData(NiPointer<NiExtraData> a_extraData) -> bool;
		auto RemoveExtraData(const BSFixedString& a_key) const -> bool;

		auto ForEachExtraData(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<NiExtraData>&)
														   const>>& a_predicate) const -> BSContainer::ForEachResult;

		// members
		BSFixedString name;						 // 0x10
		NiPointer<NiTimeController> controllers; // 0x18
		NiExtraDataContainer* extra{nullptr};	 // 0x20
	};

	static_assert(sizeof(NiObjectNET) == 0x28);
}
