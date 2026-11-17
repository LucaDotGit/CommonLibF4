#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSTDataBuffer.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/T/TBO_InstanceData.hpp"

namespace RE::BGSMod
{
	class ObjectIndexData;
}

namespace RE::BGSMod::Template
{
	class Item;
}

namespace RE
{
	class BGSAttachParentArray;
	class INSTANCE_FILTER;

	class __declspec(novtable) BGSObjectInstanceExtra : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSObjectInstanceExtra;
		inline static constexpr const auto& VTABLE = VTABLE::BGSObjectInstanceExtra;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::ObjectInstance;

		BGSObjectInstanceExtra();
		BGSObjectInstanceExtra(
			const BGSMod::Template::Item* a_item,
			TESForm* a_parentForm,
			const INSTANCE_FILTER* a_filter);

		~BGSObjectInstanceExtra() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override;	// 0x01
		auto CompareForUI(const BSExtraData* a_compare) const -> bool override; // 0x02

		void AddMod(
			const BGSMod::Attachment::Mod& a_newMod,
			std::uint8_t a_attachIndex,
			std::uint8_t a_rank,
			bool a_removeInvalidMods);
		static auto AttachModToReference(
			TESObjectREFR& a_ref,
			BGSMod::Attachment::Mod& a_mod,
			std::uint8_t a_attachIndex,
			std::uint8_t a_rank) -> bool;
		void CreateBaseInstanceData(const TESBoundObject& a_object, BSTSmartPointer<TBO_InstanceData>& a_instanceData)
			const;
		[[nodiscard]]
		auto GetNumMods(bool a_ignoreCollections) const -> std::uint32_t;
		[[nodiscard]]
		auto GetIndexData() const noexcept -> std::span<BGSMod::ObjectIndexData>;
		[[nodiscard]]
		auto HasMod(const BGSMod::Attachment::Mod& a_mod) const -> bool;
		auto RemoveInvalidMods(const BGSAttachParentArray* a_baseObjectParents) -> std::uint32_t;
		auto RemoveMod(const BGSMod::Attachment::Mod* a_mod, std::uint8_t a_attachIndex) -> std::uint32_t;

		// members
		BSTDataBuffer<1>* values{nullptr}; // 0x18
		std::uint16_t itemIndex{0};		   // 0x20
	};

	static_assert(sizeof(BGSObjectInstanceExtra) == 0x28);
}
