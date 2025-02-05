#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTHashMap.hpp"

namespace RE
{
	namespace Json
	{
		class Value;
	}

	class BSBinarySerializer;
	class PipboyObject;

	class __declspec(novtable) PipboyValue
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyValue };
		inline static constexpr auto VTABLE{ VTABLE::PipboyValue };

		enum SERIALIZATION_DATA_TYPE : std::uint8_t
		{
			kBool = 0x0,
			kInt8 = 0x1,
			kUint8 = 0x2,
			kInt32 = 0x3,
			kUint32 = 0x4,
			kFloat = 0x5,
			kString = 0x6,
			kArray = 0x7,
			kObject = 0x8,
		};

		virtual ~PipboyValue(); // 00

		// add
		virtual void CleanDirtyToGame();													   // 01
		virtual void Serialize(Json::Value* a_json) = 0;									   // 02
		virtual void SerializeChanges(BSBinarySerializer& a_serializer, bool a_fullSerialize); // 03
		virtual SERIALIZATION_DATA_TYPE GetType() = 0;										   // 04

		// members
		std::uint32_t id;		  // 08
		bool isDirtyGame;		  // 0C
		bool isDirtyToCompanion;  // 0D
		PipboyValue* parentValue; // 10
	};
	static_assert(sizeof(PipboyValue) == 0x18);

	class __declspec(novtable) PipboyObject
		: public PipboyValue
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyObject };
		inline static constexpr auto VTABLE{ VTABLE::PipboyObject };

		virtual ~PipboyObject(); // 00

		// override
		virtual void CleanDirtyToGame() override;														// 01
		virtual void Serialize(Json::Value* a_json) override;											// 02
		virtual void SerializeChanges(BSBinarySerializer& a_serializer, bool a_fullSerialize) override; // 03
		virtual SERIALIZATION_DATA_TYPE GetType() override;												// 04

		// members
		BSTHashMap<BSFixedString, PipboyValue*> memberMap; // 18
		BSTSet<std::uint32_t> addedMemberIDs;			   // 48
		BSTArray<std::uint32_t> removedMemberIDs;		   // 78
		bool newlyCreated;								   // 90
	};
	static_assert(sizeof(PipboyObject) == 0x98);
}
