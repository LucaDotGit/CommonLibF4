#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class BGSBlockBashData;
	class BGSKeywordForm;
	class NiAVObject;

	class __declspec(novtable) TBO_InstanceData
		: public BSIntrusiveRefCounted // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TBO_InstanceData };
		inline static constexpr auto VTABLE{ VTABLE::TBO_InstanceData };

		virtual ~TBO_InstanceData(); // 00

		// add
		virtual BGSKeywordForm* GetKeywordData() const;								// 01 - { return nullptr; }
		virtual void DeleteKeywordData();											// 02 - { return; }
		virtual void CreateKeywordData();											// 03 - { return; }
		virtual BGSBlockBashData* GetBlockBashData() const;							// 04 - { return nullptr; }
		virtual void DeleteBlockBashData();											// 05 - { return; }
		virtual void CreateBlockBashData();											// 06 - { return; }
		virtual BSTArray<EnchantmentItem*>* GetEnchantmentArray() const;			// 07 - { return nullptr; }
		virtual void DeleteEnchantmentArray();										// 08 - { return; }
		virtual void CreateEnchantmentArray();										// 09 - { return; }
		virtual BSTArray<BGSMaterialSwap*>* GetMaterialSwapArray() const;			// 0A - { return nullptr; }
		virtual void DeleteMaterialSwapArray();										// 0B - { return; }
		virtual void CreateMaterialSwapArray();										// 0C - { return; }
		virtual REX::Float32 GetWeight() const;										// 0D - { return -1.0_f32; }
		virtual std::int32_t GetValue() const;										// 0E - { return -1; }
		virtual std::uint32_t GetHealth() const;									// 0F - { return 0; }
		virtual REX::Float32 GetColorRemappingIndex() const;						// 10 - { return std::numeric_limits<REX::Float32>::max(); }
		virtual void PostAttach3D(NiAVObject* a_obj3D, TESObjectREFR* a_ref) const; // 11
		virtual void PostApplyMods(const TESBoundObject* a_object);					// 12 - { return; }
	};
	static_assert(sizeof(TBO_InstanceData) == 0x10);
}
