#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/P/PipboyValue.hpp"

namespace RE
{
	class __declspec(novtable) PipboyArray : public PipboyValue // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyArray;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyArray;

		explicit PipboyArray(PipboyValue* a_parentValue) :
			PipboyValue(a_parentValue)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyArray() override; // 0x00

		// override (PipboyValue)
		void CleanDirtyToGame() override;														// 0x01
		void Serialize(Json::Value& a_json) override;											// 0x02
		void SerializeChanges(BSBinarySerializer& a_serializer, bool a_fullSerialize) override; // 0x03
		auto GetType() -> SERIALIZATION_DATA_TYPE override; // 0x04 - { return SERIALIZATION_DATA_TYPE::Array; }

		[[nodiscard]]
		auto GetElementCount() const noexcept -> std::uint32_t
		{
			return elements.size();
		}

		[[nodiscard]]
		auto GetElementAt(std::uint32_t a_index) const noexcept -> PipboyValue*
		{
			if (a_index >= elements.size()) {
				return nullptr;
			}

			return elements[a_index];
		}

		auto AddElement(std::unique_ptr<PipboyValue> a_element) -> bool
		{
			if (!a_element) {
				return false;
			}

			elements.push_back(a_element.get());
			addedElementIDs.insert(a_element->GetID());

			a_element->SetParentValue(this);
			std::ignore = a_element.release();

			SetIsDirty(true);
			return true;
		}

		auto SetElementAt(std::uint32_t a_index, std::unique_ptr<PipboyValue> a_element) -> bool
		{
			if (!a_element || a_index >= elements.size()) {
				return false;
			}

			auto*& oldElement = elements[a_index];
			if (oldElement) {
				removedElementIDs.push_back(oldElement->GetID());

				delete oldElement;
				oldElement = nullptr;
			}

			oldElement = a_element.get();
			addedElementIDs.insert(a_element->GetID());

			a_element->SetParentValue(this);
			std::ignore = a_element.release();

			SetIsDirty(true);
			return true;
		}

		auto RemoveElementAt(std::uint32_t a_index) -> bool
		{
			if (a_index >= elements.size()) {
				return false;
			}

			auto*& oldElement = elements[a_index];
			if (oldElement) {
				removedElementIDs.push_back(oldElement->GetID());

				delete oldElement;
				oldElement = nullptr;
			}

			elements.erase(elements.begin() + a_index);

			SetIsDirty(true);
			return true;
		}

		// members
		BSTArray<PipboyValue*> elements;		   // 0x18
		BSTSet<std::uint32_t> addedElementIDs;	   // 0x30
		BSTArray<std::uint32_t> removedElementIDs; // 0x60
		bool newlyCreated{true};				   // 0x78
	};

	static_assert(sizeof(PipboyArray) == 0x80);
}
