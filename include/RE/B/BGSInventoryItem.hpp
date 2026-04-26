#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/E/ExtraDataList.hpp"

namespace RE
{
	class TBO_InstanceData;

	class BGSInventoryItem
	{
	public:
		class __declspec(novtable) Stack
			: public BSIntrusiveRefCounted // 08
		{
		public:
			inline static constexpr auto RTTI{ RTTI::BGSInventoryItem__Stack };
			inline static constexpr auto VTABLE{ VTABLE::BGSInventoryItem__Stack };

			enum class Flags : std::uint16_t
			{
				kNone = 0,
				kSlotIndex1 = 1 << 0,
				kSlotIndex2 = 1 << 1,
				kSlotIndex3 = 1 << 2,
				kEquipStateLocked = 1 << 3,
				kInvShouldEquip = 1 << 4,
				kTemporary = 1 << 5,
				kSlotMask = kSlotIndex1 | kSlotIndex2 | kSlotIndex3
			};

			virtual ~Stack(); // 00

			// members
			BSTSmartPointer<Stack> nextStack;		  // 10
			BSTSmartPointer<ExtraDataList> extra;	  // 18
			std::uint32_t count;					  // 20
			REX::EnumSet<Flags, std::uint16_t> flags; // 24
		};
		static_assert(sizeof(Stack) == 0x28);

		// NOLINTBEGIN(cppcoreguidelines-virtual-class-destructor)

		class __declspec(novtable) StackDataCompareFunctor
		{
		public:
			inline static constexpr auto RTTI{ RTTI::BGSInventoryItem__StackDataCompareFunctor };
			inline static constexpr auto VTABLE{ VTABLE::BGSInventoryItem__StackDataCompareFunctor };

			// add
			virtual bool CompareData(const BGSInventoryItem::Stack& a_stack) = 0; // 00
			virtual bool UseDefaultStackIfNoMatch() const;						  // 01 - { return false; }
		};
		static_assert(sizeof(StackDataCompareFunctor) == 0x08);

		class __declspec(novtable) CheckStackIDFunctor
			: public StackDataCompareFunctor // 00
		{
		public:
			inline static constexpr auto RTTI{ RTTI::BGSInventoryItem__CheckStackIDFunctor };
			inline static constexpr auto VTABLE{ VTABLE::BGSInventoryItem__CheckStackIDFunctor };

			CheckStackIDFunctor(std::uint32_t a_targetIndex) noexcept
				: targetIndex(a_targetIndex)
			{
				REL::EmplaceVtable(this);
			}

			// override (StackDataCompareFunctor)
			bool CompareData(const BGSInventoryItem::Stack& a_stack) override; // 00 - { return targetIndex-- == 0; }

			// members
			std::uint32_t targetIndex; // 08
		};
		static_assert(sizeof(CheckStackIDFunctor) == 0x10);

		class __declspec(novtable) CheckExtraDataFunctor
			: public StackDataCompareFunctor // 00
		{
		public:
			inline static constexpr auto RTTI{ RTTI::BGSInventoryItem__CheckExtraDataFunctor };
			inline static constexpr auto VTABLE{ VTABLE::BGSInventoryItem__CheckExtraDataFunctor };

			CheckExtraDataFunctor(const BGSInventoryItem::Stack* a_stack) noexcept
				: extra(a_stack ? a_stack->extra.get() : nullptr)
			{
				REL::EmplaceVtable(this);
			}

			// override (StackDataCompareFunctor)
			bool CompareData(const BGSInventoryItem::Stack& a_stack) override; // 00 - { return a_stack.extra.get() == extra; }

			// members
			ExtraDataList* extra; // 08
		};
		static_assert(sizeof(CheckExtraDataFunctor) == 0x10);

		class __declspec(novtable) StackDataWriteFunctor
		{
		public:
			inline static constexpr auto RTTI{ RTTI::BGSInventoryItem__StackDataWriteFunctor };
			inline static constexpr auto VTABLE{ VTABLE::BGSInventoryItem__StackDataWriteFunctor };

			// add
			virtual void WriteDataImpl(TESBoundObject& a_baseObj, BGSInventoryItem::Stack& a_stack) = 0; // 01

			// members
			bool shouldSplitStacks{ true };				// 08
			bool transferEquippedToSplitStack{ false }; // 09
		};
		static_assert(sizeof(StackDataWriteFunctor) == 0x10);

		class __declspec(novtable) ModifyModDataFunctor
			: public StackDataWriteFunctor // 00
		{
		public:
			inline static constexpr auto RTTI{ RTTI::BGSInventoryItem__ModifyModDataFunctor };
			inline static constexpr auto VTABLE{ VTABLE::BGSInventoryItem__ModifyModDataFunctor };

			ModifyModDataFunctor(BGSMod::Attachment::Mod* a_mod, std::int8_t a_slotIndex, bool a_attach, bool* a_success)
				: mod(a_mod),
				  success(a_success),
				  slotIndex(a_slotIndex),
				  attach(a_attach)
			{
				REL::EmplaceVtable(this);

				if (success) {
					*success = true;
				}
			}

			// override (StackDataWriteFunctor)
			void WriteDataImpl(TESBoundObject& a_baseObj, BGSInventoryItem::Stack& a_stack) override; // 01

			// members
			BGSMod::Attachment::Mod* mod;		 // 10
			TESBoundObject* foundObj{ nullptr }; // 18
			bool* success;						 // 20
			std::int8_t slotIndex;				 // 28
			bool attach;						 // 29
			bool equipLocked{ false };			 // 2A
		};
		static_assert(sizeof(ModifyModDataFunctor) == 0x30);

		class __declspec(novtable) SetHealthFunctor
			: public StackDataWriteFunctor // 00
		{
		public:
			inline static constexpr auto RTTI{ RTTI::BGSInventoryItem__SetHealthFunctor };
			inline static constexpr auto VTABLE{ VTABLE::BGSInventoryItem__SetHealthFunctor };

			SetHealthFunctor(REX::Float32 a_health)
				: health(a_health)
			{
				REL::EmplaceVtable(this);
			}

			// override (StackDataWriteFunctor)
			void WriteDataImpl(TESBoundObject& a_baseObj, BGSInventoryItem::Stack& a_stack) override; // 01

			// members
			REX::Float32 health; // 10
		};
		static_assert(sizeof(SetHealthFunctor) == 0x18);

		// NOLINTEND(cppcoreguidelines-virtual-class-destructor)

		[[nodiscard]] bool IsEquipped(std::uint32_t a_stackID) const;
		bool FindAndWriteStackData(StackDataCompareFunctor& a_compareFunc, StackDataWriteFunctor& a_writeFunc, bool a_manualMerge, ObjectRefHandle a_owner);
		[[nodiscard]] std::uint32_t GetCount() const noexcept;
		[[nodiscard]] Stack* GetStackByID(std::uint32_t a_stackID) const;
		[[nodiscard]] const char* GetDisplayFullName(std::uint32_t a_stackID) const;
		[[nodiscard]] const char* GetDisplayFullName(const ExtraDataList* a_extra) const;
		[[nodiscard]] TBO_InstanceData* GetInstanceData(std::uint32_t a_stackID) const;
		[[nodiscard]] std::int32_t GetInventoryValue(std::uint32_t a_stackID, bool a_scale) const;
		[[nodiscard]] ExtraDataList* GetExtraDataAt(std::uint32_t a_index) const;
		[[nodiscard]] std::uint64_t GetStackCount() const;
		[[nodiscard]] REX::Float32 GetTotalWeight() const;
		[[nodiscard]] bool IsQuestObject(std::int32_t a_stackIterations) const;
		void MergeStacks();

		// members
		TESBoundObject* object;			  // 00
		BSTSmartPointer<Stack> stackData; // 08
	};
	static_assert(sizeof(BGSInventoryItem) == 0x10);
}
