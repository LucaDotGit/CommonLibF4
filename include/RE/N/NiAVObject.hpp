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

	class __declspec(novtable) NiAVObject
		: public NiObjectNET // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiAVObject };
		inline static constexpr auto VTABLE{ VTABLE::NiAVObject };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiAVObject };

		enum class Flags : std::uint64_t
		{
			kNone = 0ui64,
			kAppCulled = 1ui64 << 0,
			kShadowCaster = 1ui64 << 40
		};

		NiAVObject();

		~NiAVObject() override; // 00

		// add
		virtual void UpdateControllers(NiUpdateData& a_data);															// 28
		virtual void PerformOp(PerformOpFunc& a_operation);																// 29
		virtual void AttachProperty(NiAlphaProperty* a_prop);															// 2A - { return; }
		virtual void SetMaterialNeedsUpdate(bool a_set);																// 2B - { return; }
		virtual void SetDefaultMaterialNeedsUpdateFlag(bool a_set);														// 2C - { return; }
		virtual void SetAppCulled(bool a_appCulled);																	// 2D
		virtual NiAVObject* GetObjectByName(const BSFixedString& a_name);												// 2E - { return name == a_name ? this : nullptr; }
		virtual void SetSelectiveUpdateFlags(bool& a_selectiveUpdate, bool a_selectiveUpdateTransforms, bool& a_rigid); // 2F
		virtual void UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags);									// 30
		virtual void UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags);							// 31
		virtual void UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags);								// 32
		virtual void UpdateWorldBound();																				// 33 - { return; }
		virtual void UpdateWorldData(NiUpdateData* a_data);																// 34
		virtual void UpdateTransformAndBounds(NiUpdateData& a_data);													// 35
		virtual void UpdateTransforms(NiUpdateData& a_data);															// 36 - { UpdateWorldData(std::addressof(a_data)); }
		virtual void PreAttachUpdate(NiNode* a_eventualParent, NiUpdateData& a_data);									// 37
		virtual void PostAttachUpdate();																				// 38
		virtual void OnVisible(NiCullingProcess& a_culler);																// 39 - { return; }

		GAME_HEAP_REDEFINE_ALIGNED_NEW(NiAVObject);

		void CullGeometry(bool a_cull);
		void CullNode(bool a_cull);
		void Update(NiUpdateData& a_data);

		// members
		NiNode* parent{ nullptr };							// 027
		NiTransform local{ NiTransform::IDENTITY };			// 030
		NiTransform world{ NiTransform::IDENTITY };			// 070
		NiBound worldBound;									// 0B0
		NiTransform previousWorld{ NiTransform::IDENTITY }; // 0C0
		NiPointer<NiCollisionObject> collisionObject;		// 100
		REX::EnumSet<Flags, std::uint64_t> flags{ 0x0E };	// 108
		std::uintptr_t userData{ 0 };						// 110
		REX::Float32 fadeAmount{ 1.0_f32 };					// 118
		std::int8_t multType{ 0 };							// 11C
		std::int8_t meshLODFadingLevel{ 0 };				// 11D
		std::int8_t currentMeshLODLevel{ 0 };				// 11E
		std::int8_t previousMeshLODLevel{ 0 };				// 11F
	};
	static_assert(sizeof(NiAVObject) == 0x120);
}
