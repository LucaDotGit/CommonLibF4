#pragma once

#include "RE/B/BGSMod_Template_Items.hpp"
#include "RE/B/BGSPreviewTransform.hpp"
#include "RE/B/BGSSoundTagComponent.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSString.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiNPShortPoint3.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/TBO_InstanceData.hpp"
#include "RE/T/TESObject.hpp"

namespace RE
{
	enum class COMMAND_REFUSAL_TYPE : std::int32_t;

	class BGSObjectInstanceExtra;

	class __declspec(novtable) TESBoundObject : public TESObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESBoundObject;
		inline static constexpr const auto& VTABLE = VTABLE::TESBoundObject;
		inline static constexpr auto FORM_TYPE = FormType::None;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				Value = 1 << 1,
				FullName = 1 << 2
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

		class BOUND_DATA
		{
		public:
			// members
			NiNPShortPoint3 boundMin; // 0x00
			NiNPShortPoint3 boundMax; // 0x06
		};

		static_assert(sizeof(BOUND_DATA) == 0x0C);

		~TESBoundObject() override; // 0x00

		// add
		virtual auto CreateInstanceData(const TBO_InstanceData* a_instanceData) const
			-> TBO_InstanceData*;														// 0x56 - { return nullptr; }
		virtual auto GetBaseInstanceData() const -> const TBO_InstanceData*;			// 0x57 - { return nullptr; }
		virtual auto GetAttachedMarkersVisible(NiAVObject* a_object) const -> bool;		// 0x58 - { return false; }
		virtual void SetAttachedMarkersVisible(NiAVObject* a_object, bool a_set) const; // 0x59 - { return; }
		virtual auto QSupportsCountPerInstance() const -> bool;							// 0x5A - { return false; }
		virtual void SetObjectVoiceType(BGSVoiceType* a_voiceType);						// 0x5B - { return; }
		virtual auto GetObjectVoiceType() const -> BGSVoiceType*;						// 0x5C - { return nullptr; }
		virtual auto GetSoundForTag(const BSFixedString& a_tag) const -> BGSSoundDescriptorForm*; // 0x5D
		virtual void Clone3D(
			TESObjectREFR* a_requester,
			NiPointer<NiAVObject>& a_obj3D); // 0x5E - { TESObject::Clone3D(a_requester, a_obj3D, false); }
		virtual auto ReplaceModel(const char* a_filename) -> bool;										// 0x5F
		virtual auto GetActivateText(TESObjectREFR* a_itemActivated, BSString& a_resultString) -> bool; // 0x60
		virtual auto CalculateDoFavor(
			Actor* a_actor,
			bool a_owned,
			TESObjectREFR*,
			REX::Float32 a_moralityMult) const -> COMMAND_REFUSAL_TYPE;	  // 0x61
		virtual void HandleRemoveItemFromContainer(TESObjectREFR* a_ref); // 0x62 - { return; }
		virtual void OnRemove3D(NiAVObject* a_object);					  // 0x63 - { return; }
		virtual void OnCheckModels();									  // 0x64 - { return; }
		virtual void OnCopyReference();									  // 0x65 - { return; }
		virtual void OnFinishScale();									  // 0x66 - { return; }

		void ApplyMods(BSTSmartPointer<TBO_InstanceData>& a_target, const BGSObjectInstanceExtra* a_extra) const
		{
			using FuncType = decltype(&TESBoundObject::ApplyMods);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESBoundObject::ApplyMods);
			std::invoke(FUNC, this, a_target, a_extra);
		}

		// members
		BOUND_DATA boundData;					// 0x20
		BGSMod::Template::Items objectTemplate; // 0x30
		BGSPreviewTransform previewTransform;	// 0x50
		BGSSoundTagComponent soundTagComponent; // 0x60
	};

	static_assert(sizeof(TESBoundObject) == 0x68);
}
