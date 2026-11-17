#pragma once

#include "RE/N/NiFrustum.hpp"
#include "RE/N/NiFrustumPlanes.hpp"

namespace RE
{
	class bhkBlendCollisionObject;
	class bhkLimitedHingeConstraint;
	class bhkNiCollisionObject;
	class bhkNPCollisionObject;
	class bhkRigidBody;
	class BSDynamicTriShape;
	class BSFadeNode;
	class BSGeometry;
	class BSLines;
	class BSMultiBoundNode;
	class BSSegmentedTriShape;
	class BSSubIndexTriShape;
	class BSTriShape;
	class NiAVObject;
	class NiCamera;
	class NiGeometry;
	class NiLight;
	class NiNode;
	class NiParticles;
	class NiParticleSystem;
	class NiRTTI;
	class NiSwitchNode;
	class NiTriBasedGeom;
	class NiTriShape;
	class NiTriStrips;
	class NiVisibleArray;

	class __declspec(novtable) NiCullingProcess
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiCullingProcess;
		inline static constexpr const auto& VTABLE = VTABLE::NiCullingProcess;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiCullingProcess;

		// add
		virtual auto GetRTTI() const -> const NiRTTI*;													   // 0x00
		virtual auto IsNode() const -> const NiNode*;													   // 0x01
		virtual auto IsNode() -> NiNode*;																   // 0x02
		virtual auto IsSwitchNode() -> NiSwitchNode*;													   // 0x03
		virtual auto IsFadeNode() -> BSFadeNode*;														   // 0x04
		virtual auto IsMultiBoundNode() -> BSMultiBoundNode*;											   // 0x05
		virtual auto IsGeometry() -> BSGeometry*;														   // 0x06
		virtual auto IsTriStrips() -> NiTriStrips*;														   // 0x07
		virtual auto IsTriShape() -> BSTriShape*;														   // 0x08
		virtual auto IsDynamicTriShape() -> BSDynamicTriShape*;											   // 0x09
		virtual auto IsSegmentedTriShape() -> BSSegmentedTriShape*;										   // 0x0A
		virtual auto IsSubIndexTriShape() -> BSSubIndexTriShape*;										   // 0x0B
		virtual auto IsNiGeometry() -> NiGeometry*;														   // 0x0C
		virtual auto IsNiTriBasedGeom() -> NiTriBasedGeom*;												   // 0x0D
		virtual auto IsNiTriShape() -> NiTriShape*;														   // 0x0E
		virtual auto IsParticlesGeom() -> NiParticles*;													   // 0x0F
		virtual auto IsParticleSystem() -> NiParticleSystem*;											   // 0x10
		virtual auto IsLinesGeom() -> BSLines*;															   // 0x11
		virtual auto IsLight() -> NiLight*;																   // 0x12
		virtual auto IsBhkNiCollisionObject() -> bhkNiCollisionObject*;									   // 0x13
		virtual auto IsBhkBlendCollisionObject() -> bhkBlendCollisionObject*;							   // 0x14
		virtual auto IsBhkRigidBody() -> bhkRigidBody*;													   // 0x15
		virtual auto IsBhkLimitedHingeConstraint() -> bhkLimitedHingeConstraint*;						   // 0x16
		virtual auto IsbhkNPCollisionObject() -> bhkNPCollisionObject*;									   // 0x17
		virtual ~NiCullingProcess();																	   // 0x18
		virtual void Process(NiAVObject* a_object);														   // 0x19
		virtual void Process(const NiCamera* a_camera, NiAVObject* a_scene, NiVisibleArray* a_visibleSet); // 0x1A
		virtual void AppendVirtual(BSGeometry* a_visible);												   // 0x1B

		void SetFrustum(const NiFrustum& a_frustum)
		{
			using FuncType = decltype(&NiCullingProcess::SetFrustum);
			static const auto FUNC = REL::Relocation<FuncType>(ID::NiCullingProcess::SetFrustum);
			std::invoke(FUNC, this, a_frustum);
		}

		// members
		bool useVirtualAppend;			  // 0x008
		NiVisibleArray* visibleSet;		  // 0x010
		NiCamera* camera;				  // 0x018
		NiFrustum frustum;				  // 0x020
		NiFrustumPlanes planes;			  // 0x03C
		NiFrustumPlanes customCullPlanes; // 0x0AC
		bool cameraRelatedUpdates;		  // 0x11C
		bool updateAccumulateFlag;		  // 0x11D
		bool ignorePreprocess;			  // 0x11E
		bool bCustomCullPlanes;			  // 0x11F
	};

	static_assert(sizeof(NiCullingProcess) == 0x120);
}
