#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/P/PipboyValue.hpp"

namespace RE
{
	class __declspec(novtable) PipboyObject : public PipboyValue // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyObject;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyObject;

		explicit PipboyObject(PipboyValue* a_parentValue) :
			PipboyValue(a_parentValue)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyObject() override; // 0x00

		// override (PipboyValue)
		void CleanDirtyToGame() override;														// 0x01
		void Serialize(Json::Value& a_json) override;											// 0x02
		void SerializeChanges(BSBinarySerializer& a_serializer, bool a_fullSerialize) override; // 0x03
		auto GetType() -> SERIALIZATION_DATA_TYPE override; // 0x04 - { return SERIALIZATION_DATA_TYPE::Object; }

		[[nodiscard]]
		auto GetMemberCount() const noexcept -> std::uint32_t
		{
			return memberMap.size();
		}

		[[nodiscard]]
		auto HasMember(const BSFixedString& a_name) const noexcept -> bool
		{
			return memberMap.contains(a_name);
		}

		[[nodiscard]]
		auto GetMember(const BSFixedString& a_name) const noexcept -> PipboyValue*
		{
			const auto memberIt = memberMap.find(a_name);
			if (memberIt == memberMap.end()) {
				return nullptr;
			}

			return memberIt->second;
		}

		void AddMember(const BSFixedString& a_name, std::unique_ptr<PipboyValue> a_member)
		{
			if (!a_member) {
				return;
			}

			const auto&& [_, hasInserted] = memberMap.emplace(a_name, a_member.get());
			if (!hasInserted) {
				return;
			}

			addedMemberIDs.insert(a_member->GetID());

			a_member->SetParentValue(this);
			std::ignore = a_member.release();

			SetIsDirty(true);
		}

		auto RemoveMember(const BSFixedString& a_name) -> bool
		{
			const auto memberIt = memberMap.find(a_name);
			if (memberIt == memberMap.end()) {
				return false;
			}

			auto*& oldMember = memberIt->second;
			if (oldMember) {
				removedMemberIDs.push_back(oldMember->GetID());

				delete oldMember;
				oldMember = nullptr;
			}

			memberMap.erase(memberIt);

			SetIsDirty(true);
			return true;
		}

		// members
		BSTHashMap<BSFixedString, PipboyValue*> memberMap; // 0x18
		BSTSet<std::uint32_t> addedMemberIDs;			   // 0x48
		BSTArray<std::uint32_t> removedMemberIDs;		   // 0x78
		bool newlyCreated{true};						   // 0x90
	};

	static_assert(sizeof(PipboyObject) == 0x98);
}
