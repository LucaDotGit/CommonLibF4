#pragma once

#include "RE/B/BSScript_IObjectHandlePolicy.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE::GameScript
{
	class FormOrInventoryObj;
	class RefrOrInventoryObj;

	class __declspec(novtable) HandlePolicy : public BSScript::IObjectHandlePolicy // 0x00
	{
	private:
		inline static constexpr auto QUEST_ID_BIT_SIZE =
			static_cast<BSScript::ObjectHandle>(sizeof(TESFormID) * std::numeric_limits<std::uint8_t>::digits);
		inline static constexpr auto CONTAINER_ID_BIT_SIZE =
			static_cast<BSScript::ObjectHandle>(sizeof(TESFormID) * std::numeric_limits<std::uint8_t>::digits);
		inline static constexpr auto TARGET_ACTOR_ID_BIT_SIZE =
			static_cast<BSScript::ObjectHandle>(sizeof(TESFormID) * std::numeric_limits<std::uint8_t>::digits);

	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__HandlePolicy;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__HandlePolicy;

		inline static constexpr auto HANDLE_LOW_MASK =
			static_cast<BSScript::ObjectHandle>(std::numeric_limits<std::uint32_t>::max());
		inline static constexpr auto HANDLE_HIGH_MASK =
			static_cast<BSScript::ObjectHandle>(std::numeric_limits<BSScript::ObjectHandle>::max() & ~HANDLE_LOW_MASK);

		inline static constexpr auto EMPTY_ALIAS_HANDLE = static_cast<BSScript::ObjectHandle>(0x00'0000'0000'0000);
		inline static constexpr auto EMPTY_FORM_HANDLE = static_cast<BSScript::ObjectHandle>(0xFFFF'0000'0000);
		inline static constexpr auto EMPTY_INVENTORY_OBJECT_HANDLE =
			static_cast<BSScript::ObjectHandle>(0x1'0000'0000'0000);
		inline static constexpr auto EMPTY_ACTIVE_EFFECT_HANDLE =
			static_cast<BSScript::ObjectHandle>(0x2'0000'0000'0000);
		inline static constexpr auto EMPTY_INPUT_ENABLE_LAYER_HANDLE =
			static_cast<BSScript::ObjectHandle>(0x30'0000'0000'0000);

		inline static constexpr auto EMPTY_HANDLE = EMPTY_FORM_HANDLE;

		~HandlePolicy() override; // 0x00

		// override (BSScript::IObjectHandlePolicy)
		auto HandleIsType(FormType a_type, BSScript::ObjectHandle a_objectHandle) const -> bool override;	  // 0x01
		auto GetHandleType(BSScript::ObjectHandle a_objectHandle, FormType& a_typeID) const -> bool override; // 0x02
		auto IsHandleLoaded(BSScript::ObjectHandle a_objectHandle) const -> bool override;					  // 0x03
		auto IsHandleObjectAvailable(BSScript::ObjectHandle a_objectHandle) const -> bool override;			  // 0x04
		auto ShouldAttemptToCleanHandle(BSScript::ObjectHandle a_objectHandle) const -> bool override;		  // 0x05
		auto EmptyHandle() const -> BSScript::ObjectHandle override; // 0x06 - { return EMPTY_HANDLE; }
		auto GetHandleForObject(FormType a_type, const void* a_object) const
			-> BSScript::ObjectHandle override; // 0x07 - does not seem to work with active effects nor input layers :(
		auto HasParent(BSScript::ObjectHandle a_childHandle) const -> bool override;						 // 0x08
		auto GetParentHandle(BSScript::ObjectHandle a_childHandle) const -> BSScript::ObjectHandle override; // 0x09
		auto GetHandleScriptsMovedFrom(BSScript::ObjectHandle a_newHandle) const
			-> BSScript::ObjectHandle override; // 0x0A
		auto GetSaveRemappedHandle(BSScript::ObjectHandle a_saveHandle) const
			-> BSScript::ObjectHandle override;																	 // 0x0B
		auto GetObjectForHandle(FormType a_type, BSScript::ObjectHandle a_objectHandle) const -> void* override; // 0x0C
		void PersistHandle(BSScript::ObjectHandle a_objectHandle) override;										 // 0x0D
		void ReleaseHandle(BSScript::ObjectHandle a_objectHandle) override;										 // 0x0E
		void ConvertHandleToString(BSScript::ObjectHandle a_objectHandle, BSFixedString& a_string)
			const override; // 0x0F

		void DropSaveLoadRemapData();
		void GetInventoryObjFromHandle(
			BSScript::ObjectHandle a_cobject,
			TESObjectREFR*& a_outContainer,
			ContainerID& a_outUniqueID,
			TESObjectREFR*& a_outInWorldRef) const;
		void GetInventoryObjOrFormFromHandle(
			BSScript::ObjectHandle a_cobject,
			TESObjectREFR*& a_outContainer,
			ContainerID& a_outUniqueID) const;
		void UpdatePersistence();

		[[nodiscard]]
		static constexpr auto IsHandleValid(BSScript::ObjectHandle a_objectHandle) noexcept -> bool
		{
			return a_objectHandle != EMPTY_HANDLE;
		}

		[[nodiscard]]
		static constexpr auto IsAliasHandle(BSScript::ObjectHandle a_objectHandle) noexcept -> bool
		{
			return a_objectHandle < EMPTY_FORM_HANDLE;
		}

		[[nodiscard]]
		static constexpr auto IsFormHandle(BSScript::ObjectHandle a_objectHandle) noexcept -> bool
		{
			return (a_objectHandle & EMPTY_FORM_HANDLE) == EMPTY_FORM_HANDLE;
		}

		[[nodiscard]]
		static constexpr auto IsInventoryObjectHandle(BSScript::ObjectHandle a_objectHandle) noexcept -> bool
		{
			return (a_objectHandle & EMPTY_INVENTORY_OBJECT_HANDLE) == EMPTY_INVENTORY_OBJECT_HANDLE;
		}

		[[nodiscard]]
		static constexpr auto IsActiveEffectHandle(BSScript::ObjectHandle a_objectHandle) noexcept -> bool
		{
			return (a_objectHandle & EMPTY_ACTIVE_EFFECT_HANDLE) == EMPTY_ACTIVE_EFFECT_HANDLE;
		}

		[[nodiscard]]
		static constexpr auto IsInputEnableLayerHandle(BSScript::ObjectHandle a_objectHandle) noexcept -> bool
		{
			return (a_objectHandle & EMPTY_INPUT_ENABLE_LAYER_HANDLE) == EMPTY_INPUT_ENABLE_LAYER_HANDLE;
		}

		[[nodiscard]]
		static constexpr auto GetHandleForAlias(std::uint16_t a_aliasID, TESFormID a_questID) noexcept
			-> BSScript::ObjectHandle
		{
			return static_cast<BSScript::ObjectHandle>(a_questID) |
				   (static_cast<BSScript::ObjectHandle>(a_aliasID) << QUEST_ID_BIT_SIZE) |
				   EMPTY_ALIAS_HANDLE;
		}

		[[nodiscard]]
		static constexpr auto GetAliasIDByHandle(BSScript::ObjectHandle a_objectHandle) noexcept -> std::uint16_t
		{
			return static_cast<std::uint16_t>(a_objectHandle >> QUEST_ID_BIT_SIZE);
		}

		[[nodiscard]]
		static constexpr auto GetAliasOwningQuestIDByHandle(BSScript::ObjectHandle a_objectHandle) noexcept -> TESFormID
		{
			return a_objectHandle & HANDLE_LOW_MASK;
		}

		[[nodiscard]]
		static constexpr auto GetHandleForForm(TESFormID a_formID) noexcept -> BSScript::ObjectHandle
		{
			return EMPTY_FORM_HANDLE | static_cast<BSScript::ObjectHandle>(a_formID);
		}

		[[nodiscard]]
		static constexpr auto GetFormIDByHandle(BSScript::ObjectHandle a_objectHandle) noexcept -> TESFormID
		{
			return a_objectHandle & HANDLE_LOW_MASK;
		}

		[[nodiscard]]
		static constexpr auto GetHandleForInventoryObject(std::uint16_t a_objectID, TESFormID a_containerID) noexcept
			-> BSScript::ObjectHandle
		{
			return static_cast<BSScript::ObjectHandle>(a_containerID) |
				   (static_cast<BSScript::ObjectHandle>(a_objectID) << CONTAINER_ID_BIT_SIZE) |
				   EMPTY_INVENTORY_OBJECT_HANDLE;
		}

		[[nodiscard]]
		static constexpr auto GetInventoryObjectIDByHandle(BSScript::ObjectHandle a_objectHandle) noexcept
			-> std::uint16_t
		{
			return static_cast<std::uint16_t>(a_objectHandle >> CONTAINER_ID_BIT_SIZE);
		}

		[[nodiscard]]
		static constexpr auto GetInventoryContainerIDByHandle(BSScript::ObjectHandle a_objectHandle) noexcept
			-> TESFormID
		{
			return a_objectHandle & HANDLE_LOW_MASK;
		}

		[[nodiscard]]
		static constexpr auto GetHandleForActiveEffect(std::uint16_t a_activeEffectID, TESFormID a_targetActorID)
			noexcept -> BSScript::ObjectHandle
		{
			return static_cast<BSScript::ObjectHandle>(a_targetActorID) |
				   (static_cast<BSScript::ObjectHandle>(a_activeEffectID) << TARGET_ACTOR_ID_BIT_SIZE) |
				   EMPTY_ACTIVE_EFFECT_HANDLE;
		}

		[[nodiscard]]
		static constexpr auto GetActiveEffectIDByHandle(BSScript::ObjectHandle a_objectHandle) noexcept -> std::uint16_t
		{
			return static_cast<std::uint16_t>(a_objectHandle >> TARGET_ACTOR_ID_BIT_SIZE);
		}

		[[nodiscard]]
		static constexpr auto GetActiveEffectTargetActorIDByHandle(BSScript::ObjectHandle a_objectHandle) noexcept
			-> TESFormID
		{
			return a_objectHandle & HANDLE_LOW_MASK;
		}

		[[nodiscard]]
		static constexpr auto GetHandleForInputEnableLayer(std::uint32_t a_layerID) noexcept -> BSScript::ObjectHandle
		{
			return static_cast<BSScript::ObjectHandle>(a_layerID) | EMPTY_INPUT_ENABLE_LAYER_HANDLE;
		}

		[[nodiscard]]
		static constexpr auto GetInputEnableLayerIDByHandle(BSScript::ObjectHandle a_objectHandle) noexcept
			-> std::uint32_t
		{
			return a_objectHandle & HANDLE_LOW_MASK;
		}

		[[nodiscard]]
		static auto GetHandleForAlias(const BGSBaseAlias* a_alias) -> BSScript::ObjectHandle;
		[[nodiscard]]
		static auto GetHandleForForm(const TESForm* a_form) -> BSScript::ObjectHandle;
		[[nodiscard]]
		static auto GetHandleForFormOrInventoryObject(const FormOrInventoryObj& a_inventoryObject)
			-> BSScript::ObjectHandle;
		[[nodiscard]]
		static auto GetHandleForRefOrInventoryObject(const RefrOrInventoryObj& a_inventoryObject)
			-> BSScript::ObjectHandle;
		[[nodiscard]]
		static auto GetHandleForActiveEffect(const ActiveEffect* a_activeEffect) -> BSScript::ObjectHandle;
		[[nodiscard]]
		static auto GetHandleForInputEnableLayer(const BSInputEnableLayer* a_inputEnableLayer)
			-> BSScript::ObjectHandle;

		template <class T>
		[[nodiscard]]
		static auto GetHandleForTemplateObject(const T& a_object) -> BSScript::ObjectHandle
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
		mutable BSSpinLock persistLock;									   // 0x08
		BSTHashMap<BSScript::ObjectHandle, std::uint32_t> persistRefCount; // 0x10
		BSTHashMap<BSScript::ObjectHandle, bool> queuedPromotes;		   // 0x40
		mutable BSSpinLock remapLock;									   // 0x70
		BSTHashMap<TESFormID, TESFormID> changedFormIDs;				   // 0x78
	};

	static_assert(sizeof(HandlePolicy) == 0xA8);
}
