#pragma once

#include "RE/N/NiRefObject.hpp"

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
	class NiCloningProcess;
	class NiControllerManager;
	class NiGeometry;
	class NiLight;
	class NiNode;
	class NiObjectGroup;
	class NiParticles;
	class NiParticleSystem;
	class NiRTTI;
	class NiStream;
	class NiSwitchNode;
	class NiTriBasedGeom;
	class NiTriShape;
	class NiTriStrips;

	class __declspec(novtable) NiObject : public NiRefObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiObject;
		inline static constexpr const auto& VTABLE = VTABLE::NiObject;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiObject;

		NiObject();

		~NiObject() override = default; // 0x00

		// add
		virtual auto GetRTTI() const -> const NiRTTI*;							  // 0x02 - { return nullptr; }
		virtual auto IsNode() const -> const NiNode*;							  // 0x03 - { return nullptr; }
		virtual auto IsNode() -> NiNode*;										  // 0x04 - { return nullptr; }
		virtual auto IsSwitchNode() -> NiSwitchNode*;							  // 0x05 - { return nullptr; }
		virtual auto IsFadeNode() -> BSFadeNode*;								  // 0x06 - { return nullptr; }
		virtual auto IsMultiBoundNode() -> BSMultiBoundNode*;					  // 0x07 - { return nullptr; }
		virtual auto IsGeometry() -> BSGeometry*;								  // 0x08 - { return nullptr; }
		virtual auto IsTriStrips() -> NiTriStrips*;								  // 0x09 - { return nullptr; }
		virtual auto IsTriShape() -> BSTriShape*;								  // 0x0A - { return nullptr; }
		virtual auto IsDynamicTriShape() -> BSDynamicTriShape*;					  // 0x0B - { return nullptr; }
		virtual auto IsSegmentedTriShape() -> BSSegmentedTriShape*;				  // 0x0C - { return nullptr; }
		virtual auto IsSubIndexTriShape() -> BSSubIndexTriShape*;				  // 0x0D - { return nullptr; }
		virtual auto IsNiGeometry() -> NiGeometry*;								  // 0x0E - { return nullptr; }
		virtual auto IsNiTriBasedGeom() -> NiTriBasedGeom*;						  // 0x0F - { return nullptr; }
		virtual auto IsNiTriShape() -> NiTriShape*;								  // 0x10 - { return nullptr; }
		virtual auto IsParticlesGeom() -> NiParticles*;							  // 0x11 - { return nullptr; }
		virtual auto IsParticleSystem() -> NiParticleSystem*;					  // 0x12 - { return nullptr; }
		virtual auto IsLinesGeom() -> BSLines*;									  // 0x13 - { return nullptr; }
		virtual auto IsLight() -> NiLight*;										  // 0x14 - { return nullptr; }
		virtual auto IsBhkNiCollisionObject() -> bhkNiCollisionObject*;			  // 0x15 - { return nullptr; }
		virtual auto IsBhkBlendCollisionObject() -> bhkBlendCollisionObject*;	  // 0x16 - { return nullptr; }
		virtual auto IsBhkRigidBody() -> bhkRigidBody*;							  // 0x17 - { return nullptr; }
		virtual auto IsBhkLimitedHingeConstraint() -> bhkLimitedHingeConstraint*; // 0x18 - { return nullptr; }
		virtual auto IsbhkNPCollisionObject() -> bhkNPCollisionObject*;			  // 0x19 - { return nullptr; }
		virtual auto CreateClone(NiCloningProcess& a_cloneData) -> NiObject*;	  // 0x1A - { return nullptr; }
		virtual void LoadBinary(NiStream& a_stream);							  // 0x1B - { return; }
		virtual void LinkObject(NiStream& a_stream);							  // 0x1C - { return; }
		virtual auto RegisterStreamables(NiStream& a_stream) -> bool;			  // 0x1D
		virtual void SaveBinary(NiStream& a_stream);							  // 0x1E - { return; }
		virtual auto IsEqual(NiObject* a_object) -> bool;						  // 0x1F
		virtual void ProcessClone(NiCloningProcess& a_cloning);					  // 0x20
		virtual void PostLinkObject(NiStream& a_stream);						  // 0x21 - { return; }
		virtual auto StreamCanSkip() -> bool;									  // 0x22 - { return false; }
		virtual auto GetStreamableRTTI() -> const NiRTTI*;						  // 0x23 - { return GetRTTI(); }
		virtual auto GetBlockAllocationSize() -> std::uint32_t;					  // 0x24 - { return 0; }
		virtual auto GetGroup() const -> NiObjectGroup*;						  // 0x25 - { return nullptr; }
		virtual void SetGroup(NiObjectGroup* a_group);							  // 0x26 - { return; }
		virtual auto IsNiControllerManager() -> NiControllerManager*;			  // 0x27 - { return nullptr; }
	};

	static_assert(sizeof(NiObject) == 0x10);
}
