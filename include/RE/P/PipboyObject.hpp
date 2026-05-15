#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/P/PipboyValue.hpp"

namespace RE
{
	class __declspec(novtable) PipboyObject
		: public PipboyValue // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyObject };
		inline static constexpr auto VTABLE{ VTABLE::PipboyObject };

		~PipboyObject() override; // 00

		// override (PipboyValue)
		void CleanDirtyToGame() override;														// 01
		void Serialize(Json::Value* a_json) override;											// 02
		void SerializeChanges(BSBinarySerializer& a_serializer, bool a_fullSerialize) override; // 03
		SERIALIZATION_DATA_TYPE GetType() override;												// 04

		void AddMember(const BSFixedString* a_name, PipboyValue* a_member)
		{
			using FuncType = decltype(&PipboyObject::AddMember);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyObject::AddMember };
			std::invoke(FUNC, this, a_name, a_member);
		}

		template <class T>
		[[nodiscard]] T GetMember(const BSFixedString& a_name)
		{
			const auto memberIt = memberMap.find(a_name);
			return (memberIt != memberMap.end()) ? static_cast<T>(memberIt->second) : nullptr;
		}

		// members
		BSTHashMap<BSFixedString, PipboyValue*> memberMap; // 18
		BSTSet<std::uint32_t> addedMemberIDs;			   // 48
		BSTArray<std::uint32_t> removedMemberIDs;		   // 78
		bool newlyCreated;								   // 90
	};
	static_assert(sizeof(PipboyObject) == 0x98);
}
