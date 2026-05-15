#pragma once

#include "RE/B/BGSMod_Template_Items.hpp"
#include "RE/B/BGSPreviewTransform.hpp"
#include "RE/B/BGSSoundTagComponent.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSStringT.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiNPShortPoint3.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/TBO_InstanceData.hpp"
#include "RE/T/TESObject.hpp"

namespace RE
{
	enum class COMMAND_REFUSAL_TYPE : std::int32_t;

	class BGSObjectInstanceExtra;

	class __declspec(novtable) TESBoundObject
		: public TESObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESBoundObject };
		inline static constexpr auto VTABLE{ VTABLE::TESBoundObject };
		inline static constexpr auto FORM_TYPE{ FormType::kNone };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kValue = 1 << 1,
				kFullName = 1 << 2
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

		class BOUND_DATA
		{
		public:
			// members
			NiNPShortPoint3 boundMin; // 00
			NiNPShortPoint3 boundMax; // 06
		};
		static_assert(sizeof(BOUND_DATA) == 0x0C);

		// add
		virtual TBO_InstanceData* CreateInstanceData(const TBO_InstanceData* a_instanceData) const;										// 56 - { return nullptr; }
		virtual const TBO_InstanceData* GetBaseInstanceData() const;																	// 57 - { return nullptr; }
		virtual bool GetAttachedMarkersVisible(NiAVObject* a_object) const;																// 58 - { return false; }
		virtual void SetAttachedMarkersVisible(NiAVObject* a_object, bool a_set) const;													// 59 - { return; }
		virtual bool QSupportsCountPerInstance() const;																					// 5A - { return false; }
		virtual void SetObjectVoiceType(BGSVoiceType* a_voiceType);																		// 5B - { return; }
		virtual BGSVoiceType* GetObjectVoiceType() const;																				// 5C - { return nullptr; }
		virtual BGSSoundDescriptorForm* GetSoundForTag(const BSFixedString& a_tag) const;												// 5D
		virtual void Clone3D(TESObjectREFR* a_requester, NiPointer<NiAVObject>& a_obj3D);												// 5E - { TESObject::Clone3D(a_requester, a_obj3D, false); }
		virtual bool ReplaceModel(const char* a_filename);																				// 5F
		virtual bool GetActivateText(TESObjectREFR* a_itemActivated, BSString& a_resultString);											// 60
		virtual COMMAND_REFUSAL_TYPE CalculateDoFavor(Actor* a_actor, bool a_owned, TESObjectREFR*, REX::Float32 a_moralityMult) const; // 61
		virtual void HandleRemoveItemFromContainer(TESObjectREFR* a_ref);																// 62 - { return; }
		virtual void OnRemove3D(NiAVObject* a_object);																					// 63 - { return; }
		virtual void OnCheckModels();																									// 64 - { return; }
		virtual void OnCopyReference();																									// 65 - { return; }
		virtual void OnFinishScale();																									// 66 - { return; }

		void ApplyMods(BSTSmartPointer<TBO_InstanceData>& a_dest, const BGSObjectInstanceExtra* a_extra) const
		{
			using FuncType = decltype(&TESBoundObject::ApplyMods);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESBoundObject::ApplyMods };
			std::invoke(FUNC, this, a_dest, a_extra);
		}

		// members
		BOUND_DATA boundData;					// 20
		BGSMod::Template::Items objectTemplate; // 30
		BGSPreviewTransform previewTransform;	// 50
		BGSSoundTagComponent soundTagComponent; // 60
	};
	static_assert(sizeof(TESBoundObject) == 0x68);
}
