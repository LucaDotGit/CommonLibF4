#pragma once

#include "RE/B/BSScript_IObjectHandlePolicy.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE::GameScript
{
	class FormOrInventoryObj;
	class RefrOrInventoryObj;

	class __declspec(novtable) HandlePolicy
		: public BSScript::IObjectHandlePolicy // 00
	{
	private:
		inline static constexpr auto QUEST_ID_BIT_SIZE = static_cast<BSScript::ObjectHandle>(sizeof(TESFormID) * CHAR_BIT);
		inline static constexpr auto CONTAINER_ID_BIT_SIZE = static_cast<BSScript::ObjectHandle>(sizeof(TESFormID) * CHAR_BIT);
		inline static constexpr auto TARGET_ACTOR_ID_BIT_SIZE = static_cast<BSScript::ObjectHandle>(sizeof(TESFormID) * CHAR_BIT);

	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__HandlePolicy };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__HandlePolicy };

		inline static constexpr auto HANDLE_LOW_MASK = static_cast<BSScript::ObjectHandle>(std::numeric_limits<std::uint32_t>::max());
		inline static constexpr auto HANDLE_HIGH_MASK = static_cast<BSScript::ObjectHandle>(std::numeric_limits<BSScript::ObjectHandle>::max() & ~HANDLE_LOW_MASK);

		inline static constexpr auto EMPTY_ALIAS_HANDLE = static_cast<BSScript::ObjectHandle>(0x00000000000000);
		inline static constexpr auto EMPTY_FORM_HANDLE = static_cast<BSScript::ObjectHandle>(0xFFFF00000000);
		inline static constexpr auto EMPTY_INVENTORY_OBJECT_HANDLE = static_cast<BSScript::ObjectHandle>(0x1000000000000);
		inline static constexpr auto EMPTY_ACTIVE_EFFECT_HANDLE = static_cast<BSScript::ObjectHandle>(0x2000000000000);
		inline static constexpr auto EMPTY_INPUT_ENABLE_LAYER_HANDLE = static_cast<BSScript::ObjectHandle>(0x30000000000000);

		inline static constexpr auto EMPTY_HANDLE = EMPTY_FORM_HANDLE;

		~HandlePolicy() override; // 00

		// override (BSScript::IObjectHandlePolicy)
		bool HandleIsType(FormType a_type, BSScript::ObjectHandle a_objectHandle) const override;				   // 01
		bool GetHandleType(BSScript::ObjectHandle a_objectHandle, FormType& a_typeID) const override;			   // 02
		bool IsHandleLoaded(BSScript::ObjectHandle a_objectHandle) const override;								   // 03
		bool IsHandleObjectAvailable(BSScript::ObjectHandle a_objectHandle) const override;						   // 04
		bool ShouldAttemptToCleanHandle(BSScript::ObjectHandle a_objectHandle) const override;					   // 05
		BSScript::ObjectHandle EmptyHandle() const override;													   // 06 - { return EMPTY_HANDLE; }
		BSScript::ObjectHandle GetHandleForObject(FormType a_type, const void* a_object) const override;		   // 07 - does not seem to work with active effects nor input layers :(
		bool HasParent(BSScript::ObjectHandle a_childHandle) const override;									   // 08
		BSScript::ObjectHandle GetParentHandle(BSScript::ObjectHandle a_childHandle) const override;			   // 09
		BSScript::ObjectHandle GetHandleScriptsMovedFrom(BSScript::ObjectHandle a_newHandle) const override;	   // 0A
		BSScript::ObjectHandle GetSaveRemappedHandle(BSScript::ObjectHandle a_saveHandle) const override;		   // 0B
		void* GetObjectForHandle(FormType a_type, BSScript::ObjectHandle a_objectHandle) const override;		   // 0C
		void PersistHandle(BSScript::ObjectHandle a_objectHandle) override;										   // 0D
		void ReleaseHandle(BSScript::ObjectHandle a_objectHandle) override;										   // 0E
		void ConvertHandleToString(BSScript::ObjectHandle a_objectHandle, BSFixedString& a_string) const override; // 0F

		void DropSaveLoadRemapData();
		void GetInventoryObjFromHandle(BSScript::ObjectHandle a_cobject, TESObjectREFR*& a_container, ContainerID& a_uniqueID, TESObjectREFR*& a_inWorldRef) const;
		void GetInventoryObjOrFormFromHandle(BSScript::ObjectHandle a_cobject, TESObjectREFR*& a_container, ContainerID& a_uniqueID) const;
		void UpdatePersistence();

		[[nodiscard]] static constexpr bool IsHandleValid(BSScript::ObjectHandle a_objectHandle) noexcept
		{
			return a_objectHandle != EMPTY_HANDLE;
		}

		[[nodiscard]] static constexpr bool IsAliasHandle(BSScript::ObjectHandle a_objectHandle) noexcept
		{
			return a_objectHandle < EMPTY_FORM_HANDLE;
		}

		[[nodiscard]] static constexpr bool IsFormHandle(BSScript::ObjectHandle a_objectHandle) noexcept
		{
			return (a_objectHandle & EMPTY_FORM_HANDLE) == EMPTY_FORM_HANDLE;
		}

		[[nodiscard]] static constexpr bool IsInventoryObjectHandle(BSScript::ObjectHandle a_objectHandle) noexcept
		{
			return (a_objectHandle & EMPTY_INVENTORY_OBJECT_HANDLE) == EMPTY_INVENTORY_OBJECT_HANDLE;
		}

		[[nodiscard]] static constexpr bool IsActiveEffectHandle(BSScript::ObjectHandle a_objectHandle) noexcept
		{
			return (a_objectHandle & EMPTY_ACTIVE_EFFECT_HANDLE) == EMPTY_ACTIVE_EFFECT_HANDLE;
		}

		[[nodiscard]] static constexpr bool IsInputEnableLayerHandle(BSScript::ObjectHandle a_objectHandle) noexcept
		{
			return (a_objectHandle & EMPTY_INPUT_ENABLE_LAYER_HANDLE) == EMPTY_INPUT_ENABLE_LAYER_HANDLE;
		}

		[[nodiscard]] static constexpr BSScript::ObjectHandle GetHandleForAlias(std::uint16_t a_aliasID, TESFormID a_questID) noexcept
		{
			return static_cast<BSScript::ObjectHandle>(a_questID) |
				   (static_cast<BSScript::ObjectHandle>(a_aliasID) << QUEST_ID_BIT_SIZE) |
				   EMPTY_ALIAS_HANDLE;
		}

		[[nodiscard]] static constexpr std::uint16_t GetAliasIDByHandle(BSScript::ObjectHandle a_objectHandle) noexcept
		{
			return static_cast<std::uint16_t>(a_objectHandle >> QUEST_ID_BIT_SIZE);
		}

		[[nodiscard]] static constexpr TESFormID GetAliasOwningQuestIDByHandle(BSScript::ObjectHandle a_objectHandle) noexcept
		{
			return a_objectHandle & HANDLE_LOW_MASK;
		}

		[[nodiscard]] static constexpr BSScript::ObjectHandle GetHandleForForm(TESFormID a_formID) noexcept
		{
			return EMPTY_FORM_HANDLE | static_cast<BSScript::ObjectHandle>(a_formID);
		}

		[[nodiscard]] static constexpr TESFormID GetFormIDByHandle(BSScript::ObjectHandle a_objectHandle) noexcept
		{
			return a_objectHandle & HANDLE_LOW_MASK;
		}

		[[nodiscard]] static constexpr BSScript::ObjectHandle GetHandleForInventoryObject(std::uint16_t a_objectID, TESFormID a_containerID) noexcept
		{
			return static_cast<BSScript::ObjectHandle>(a_containerID) |
				   (static_cast<BSScript::ObjectHandle>(a_objectID) << CONTAINER_ID_BIT_SIZE) |
				   EMPTY_INVENTORY_OBJECT_HANDLE;
		}

		[[nodiscard]] static constexpr std::uint16_t GetInventoryObjectIDByHandle(BSScript::ObjectHandle a_objectHandle) noexcept
		{
			return static_cast<std::uint16_t>(a_objectHandle >> CONTAINER_ID_BIT_SIZE);
		}

		[[nodiscard]] static constexpr TESFormID GetInventoryContainerIDByHandle(BSScript::ObjectHandle a_objectHandle) noexcept
		{
			return a_objectHandle & HANDLE_LOW_MASK;
		}

		[[nodiscard]] static constexpr BSScript::ObjectHandle GetHandleForActiveEffect(std::uint16_t a_activeEffectID, TESFormID a_targetActorID) noexcept
		{
			return static_cast<BSScript::ObjectHandle>(a_targetActorID) |
				   (static_cast<BSScript::ObjectHandle>(a_activeEffectID) << TARGET_ACTOR_ID_BIT_SIZE) |
				   EMPTY_ACTIVE_EFFECT_HANDLE;
		}

		[[nodiscard]] static constexpr std::uint16_t GetActiveEffectIDByHandle(BSScript::ObjectHandle a_objectHandle) noexcept
		{
			return static_cast<std::uint16_t>(a_objectHandle >> TARGET_ACTOR_ID_BIT_SIZE);
		}

		[[nodiscard]] static constexpr TESFormID GetActiveEffectTargetActorIDByHandle(BSScript::ObjectHandle a_objectHandle) noexcept
		{
			return a_objectHandle & HANDLE_LOW_MASK;
		}

		[[nodiscard]] static constexpr BSScript::ObjectHandle GetHandleForInputEnableLayer(std::uint32_t a_layerID) noexcept
		{
			return static_cast<BSScript::ObjectHandle>(a_layerID) | EMPTY_INPUT_ENABLE_LAYER_HANDLE;
		}

		[[nodiscard]] static constexpr std::uint32_t GetInputEnableLayerIDByHandle(BSScript::ObjectHandle a_objectHandle) noexcept
		{
			return a_objectHandle & HANDLE_LOW_MASK;
		}

		[[nodiscard]] static BSScript::ObjectHandle GetHandleForAlias(const BGSBaseAlias* a_alias);
		[[nodiscard]] static BSScript::ObjectHandle GetHandleForForm(const TESForm* a_form);
		[[nodiscard]] static BSScript::ObjectHandle GetHandleForFormOrInventoryObject(const FormOrInventoryObj& a_inventoryObject);
		[[nodiscard]] static BSScript::ObjectHandle GetHandleForRefOrInventoryObject(const RefrOrInventoryObj& a_inventoryObject);
		[[nodiscard]] static BSScript::ObjectHandle GetHandleForActiveEffect(const ActiveEffect* a_activeEffect);
		[[nodiscard]] static BSScript::ObjectHandle GetHandleForInputEnableLayer(const BSInputEnableLayer* a_inputEnableLayer);

		template <class T>
		[[nodiscard]] static BSScript::ObjectHandle GetHandleForTemplateObject(const T& a_object)
		{
			if constexpr (std::derived_from<T, BGSBaseAlias>) {
				return GetHandleForAlias(std::addressof(a_object));
			}
			else if constexpr (std::derived_from<T, TESForm>) {
				return GetHandleForForm(std::addressof(a_object));
			}
			else if constexpr (std::same_as<T, FormOrInventoryObj>) {
				return GetHandleForFormOrInventoryObject(a_object);
			}
			else if constexpr (std::same_as<T, RefrOrInventoryObj>) {
				return GetHandleForRefOrInventoryObject(a_object);
			}
			else if constexpr (std::same_as<T, ActiveEffect>) {
				return GetHandleForActiveEffect(std::addressof(a_object));
			}
			else if constexpr (std::same_as<T, BSInputEnableLayer>) {
				return GetHandleForInputEnableLayer(std::addressof(a_object));
			}
			else {
				static_assert(false, "The object type is invalid.");
			}
		}

		// members
		mutable BSSpinLock persistLock;									   // 08
		BSTHashMap<BSScript::ObjectHandle, std::uint32_t> persistRefCount; // 10
		BSTHashMap<BSScript::ObjectHandle, bool> queuedPromotes;		   // 40
		mutable BSSpinLock remapLock;									   // 70
		BSTHashMap<TESFormID, TESFormID> changedFormIDs;				   // 78
	};
	static_assert(sizeof(HandlePolicy) == 0xA8);
}
