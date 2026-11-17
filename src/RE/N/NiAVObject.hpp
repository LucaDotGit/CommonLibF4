#pragma once

#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiBound.hpp"
#include "RE/N/NiCollisionObject.hpp"
#include "RE/N/NiObjectNET.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiTransform.hpp"

namespace RE
{
	class NiAlphaProperty;
	class NiCullingProcess;
	class NiNode;
	class NiUpdateData;
	class PerformOpFunc;

	class __declspec(novtable) NiAVObject : public NiObjectNET // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiAVObject;
		inline static constexpr const auto& VTABLE = VTABLE::NiAVObject;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiAVObject;

		enum class Flags : std::uint64_t
		{
			None = 0,
			AppCulled = static_cast<std::uint64_t>(1) << 0,
			ShadowCaster = static_cast<std::uint64_t>(1) << 40
		};

		NiAVObject();

		~NiAVObject() override; // 0x00

		// add
		virtual void UpdateControllers(NiUpdateData& a_data);		// 0x28
		virtual void PerformOp(PerformOpFunc& a_operation);			// 0x29
		virtual void AttachProperty(NiAlphaProperty* a_prop);		// 0x2A - { return; }
		virtual void SetMaterialNeedsUpdate(bool a_set);			// 0x2B - { return; }
		virtual void SetDefaultMaterialNeedsUpdateFlag(bool a_set); // 0x2C - { return; }
		virtual void SetAppCulled(bool a_appCulled);				// 0x2D
		virtual auto GetObjectByName(const BSFixedString& a_name)
			-> NiAVObject*; // 0x2E - { return name == a_name ? this : nullptr; }
		virtual void SetSelectiveUpdateFlags(
			bool& a_selectiveUpdate,
			bool a_selectiveUpdateTransforms,
			bool& a_rigid);																	  // 0x2F
		virtual void UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags);		  // 0x30
		virtual void UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags); // 0x31
		virtual void UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags);	  // 0x32
		virtual void UpdateWorldBound();													  // 0x33 - { return; }
		virtual void UpdateWorldData(NiUpdateData* a_data);									  // 0x34
		virtual void UpdateTransformAndBounds(NiUpdateData& a_data);						  // 0x35
		virtual void UpdateTransforms(NiUpdateData& a_data); // 0x36 - { UpdateWorldData(std::addressof(a_data)); }
		virtual void PreAttachUpdate(NiNode* a_eventualParent, NiUpdateData& a_data); // 0x37
		virtual void PostAttachUpdate();											  // 0x38
		virtual void OnVisible(NiCullingProcess& a_culler);							  // 0x39 - { return; }

		GAME_HEAP_REDEFINE_ALIGNED_NEW(NiAVObject);

		void CullGeometry(bool a_cull);
		void CullNode(bool a_cull);
		void Update(NiUpdateData& a_data);

		// members
		NiNode* parent{nullptr};								 // 0x027
		NiTransform local{NiTransform::IDENTITY};				 // 0x030
		NiTransform world{NiTransform::IDENTITY};				 // 0x070
		NiBound worldBound;										 // 0x0B0
		NiTransform previousWorld{NiTransform::IDENTITY};		 // 0x0C0
		NiPointer<NiCollisionObject> collisionObject;			 // 0x100
		REX::EnumSet<Flags, std::uint64_t> flags{0x0E};			 // 0x108
		std::uintptr_t userData{0};								 // 0x110
		REX::Float32 fadeAmount{static_cast<REX::Float32>(1.0)}; // 0x118
		std::int8_t multType{0};								 // 0x11C
		std::int8_t meshLODFadingLevel{0};						 // 0x11D
		std::int8_t currentMeshLODLevel{0};						 // 0x11E
		std::int8_t previousMeshLODLevel{0};					 // 0x11F
	};

	static_assert(sizeof(NiAVObject) == 0x120);
}
