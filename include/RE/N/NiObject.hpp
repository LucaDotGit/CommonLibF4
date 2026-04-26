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

	class __declspec(novtable) NiObject
		: public NiRefObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiObject };
		inline static constexpr auto VTABLE{ VTABLE::NiObject };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiObject };

		NiObject();

		~NiObject() override = default; // 00

		// add
		virtual const NiRTTI* GetRTTI() const;							  // 02 - { return nullptr; }
		virtual NiNode* AsNode();										  // 04 - { return nullptr; }
		virtual const NiNode* AsNode() const;							  // 03 - { return nullptr; }
		virtual NiSwitchNode* AsSwitchNode();							  // 05 - { return nullptr; }
		virtual BSFadeNode* AsFadeNode();								  // 06 - { return nullptr; }
		virtual BSMultiBoundNode* AsMultiBoundNode();					  // 07 - { return nullptr; }
		virtual BSGeometry* AsGeometry();								  // 08 - { return nullptr; }
		virtual NiTriStrips* AsTriStrips();								  // 09 - { return nullptr; }
		virtual BSTriShape* AsTriShape();								  // 0A - { return nullptr; }
		virtual BSDynamicTriShape* AsDynamicTriShape();					  // 0B - { return nullptr; }
		virtual BSSegmentedTriShape* AsSegmentedTriShape();				  // 0C - { return nullptr; }
		virtual BSSubIndexTriShape* AsSubIndexTriShape();				  // 0D - { return nullptr; }
		virtual NiGeometry* AsNiGeometry();								  // 0E - { return nullptr; }
		virtual NiTriBasedGeom* AsNiTriBasedGeom();						  // 0F - { return nullptr; }
		virtual NiTriShape* AsNiTriShape();								  // 10 - { return nullptr; }
		virtual NiParticles* AsParticlesGeom();							  // 11 - { return nullptr; }
		virtual NiParticleSystem* AsParticleSystem();					  // 12 - { return nullptr; }
		virtual BSLines* AsLinesGeom();									  // 13 - { return nullptr; }
		virtual NiLight* AsLight();										  // 14 - { return nullptr; }
		virtual bhkNiCollisionObject* AsBhkNiCollisionObject();			  // 15 - { return nullptr; }
		virtual bhkBlendCollisionObject* AsBhkBlendCollisionObject();	  // 16 - { return nullptr; }
		virtual bhkRigidBody* AsBhkRigidBody();							  // 17 - { return nullptr; }
		virtual bhkLimitedHingeConstraint* AsBhkLimitedHingeConstraint(); // 18 - { return nullptr; }
		virtual bhkNPCollisionObject* AsbhkNPCollisionObject();			  // 19 - { return nullptr; }
		virtual NiObject* CreateClone(NiCloningProcess& a_cloneData);	  // 1A - { return nullptr; }
		virtual void LoadBinary(NiStream& a_stream);					  // 1B - { return; }
		virtual void LinkObject(NiStream& a_stream);					  // 1C - { return; }
		virtual bool RegisterStreamables(NiStream& a_stream);			  // 1D
		virtual void SaveBinary(NiStream& a_stream);					  // 1E - { return; }
		virtual bool IsEqual(NiObject* a_object);						  // 1F
		virtual void ProcessClone(NiCloningProcess& a_cloning);			  // 20
		virtual void PostLinkObject(NiStream& a_stream);				  // 21 - { return; }
		virtual bool StreamCanSkip();									  // 22 - { return false; }
		virtual const NiRTTI* GetStreamableRTTI();						  // 23 - { return GetRTTI(); }
		virtual std::uint32_t GetBlockAllocationSize();					  // 24 - { return 0; }
		virtual NiObjectGroup* GetGroup() const;						  // 25 - { return nullptr; }
		virtual void SetGroup(NiObjectGroup* a_group);					  // 26 - { return; }
		virtual NiControllerManager* AsNiControllerManager();			  // 27 - { return nullptr; }
	};
	static_assert(sizeof(NiObject) == 0x10);
}
