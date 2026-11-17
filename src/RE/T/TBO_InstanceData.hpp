#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class BGSBlockBashData;
	class BGSKeywordForm;
	class NiAVObject;

	class __declspec(novtable) TBO_InstanceData : public BSIntrusiveRefCounted // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TBO_InstanceData;
		inline static constexpr const auto& VTABLE = VTABLE::TBO_InstanceData;

		virtual ~TBO_InstanceData(); // 0x00

		// add
		virtual auto GetKeywordData() const -> BGSKeywordForm*;					  // 0x01 - { return nullptr; }
		virtual void DeleteKeywordData();										  // 0x02 - { return; }
		virtual void CreateKeywordData();										  // 0x03 - { return; }
		virtual auto GetBlockBashData() const -> BGSBlockBashData*;				  // 0x04 - { return nullptr; }
		virtual void DeleteBlockBashData();										  // 0x05 - { return; }
		virtual void CreateBlockBashData();										  // 0x06 - { return; }
		virtual auto GetEnchantmentArray() const -> BSTArray<EnchantmentItem*>*;  // 0x07 - { return nullptr; }
		virtual void DeleteEnchantmentArray();									  // 0x08 - { return; }
		virtual void CreateEnchantmentArray();									  // 0x09 - { return; }
		virtual auto GetMaterialSwapArray() const -> BSTArray<BGSMaterialSwap*>*; // 0x0A - { return nullptr; }
		virtual void DeleteMaterialSwapArray();									  // 0x0B - { return; }
		virtual void CreateMaterialSwapArray();									  // 0x0C - { return; }
		virtual auto GetWeight() const -> REX::Float32;	 // 0x0D - { return static_cast<REX::Float32>(-1.0); }
		virtual auto GetValue() const -> std::int32_t;	 // 0x0E - { return -1; }
		virtual auto GetHealth() const -> std::uint32_t; // 0x0F - { return 0; }
		virtual auto GetColorRemappingIndex() const
			-> REX::Float32; // 0x10 - { return std::numeric_limits<REX::Float32>::max(); }
		virtual void PostAttach3D(NiAVObject* a_obj3D, TESObjectREFR* a_ref) const; // 0x11
		virtual void PostApplyMods(const TESBoundObject* a_object);					// 0x12 - { return; }
	};

	static_assert(sizeof(TBO_InstanceData) == 0x10);
}
