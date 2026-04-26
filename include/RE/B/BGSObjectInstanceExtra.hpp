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

	class __declspec(novtable) BGSObjectInstanceExtra
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSObjectInstanceExtra };
		inline static constexpr auto VTABLE{ VTABLE::BGSObjectInstanceExtra };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kObjectInstance };

		BGSObjectInstanceExtra();
		BGSObjectInstanceExtra(const BGSMod::Template::Item* a_item, TESForm* a_parentForm, const INSTANCE_FILTER* a_filter);

		~BGSObjectInstanceExtra() override; // 00

		void AddMod(const BGSMod::Attachment::Mod& a_newMod, std::uint8_t a_attachIndex, std::uint8_t a_rank, bool a_removeInvalidMods);
		static bool AttachModToReference(TESObjectREFR& a_ref, BGSMod::Attachment::Mod& a_mod, std::uint8_t a_attachIndex, std::uint8_t a_rank);
		void CreateBaseInstanceData(const TESBoundObject& a_object, BSTSmartPointer<TBO_InstanceData>& a_instanceData) const;
		[[nodiscard]] std::uint32_t GetNumMods(bool a_ignoreCollections) const;
		[[nodiscard]] std::span<BGSMod::ObjectIndexData> GetIndexData() const noexcept;
		[[nodiscard]] bool HasMod(const BGSMod::Attachment::Mod& a_mod) const;
		std::uint32_t RemoveInvalidMods(const BGSAttachParentArray* a_baseObjectParents);
		std::uint32_t RemoveMod(const BGSMod::Attachment::Mod* a_mod, std::uint8_t a_attachIndex);

		// members
		BSTDataBuffer<1>* values{ nullptr }; // 18
		std::uint16_t itemIndex{ 0 };		 // 20
	};
	static_assert(sizeof(BGSObjectInstanceExtra) == 0x28);
}
