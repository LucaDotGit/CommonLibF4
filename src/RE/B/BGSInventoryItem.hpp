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
		class __declspec(novtable) Stack : public BSIntrusiveRefCounted // 0x08
		{
		public:
			inline static constexpr const auto& RTTI = RTTI::BGSInventoryItem__Stack;
			inline static constexpr const auto& VTABLE = VTABLE::BGSInventoryItem__Stack;

			enum class Flags : std::uint16_t
			{
				None = 0,
				SlotIndex1 = 1 << 0,
				SlotIndex2 = 1 << 1,
				SlotIndex3 = 1 << 2,
				EquipStateLocked = 1 << 3,
				InvShouldEquip = 1 << 4,
				Temporary = 1 << 5,
				SlotMask = SlotIndex1 | SlotIndex2 | SlotIndex3
			};

			virtual ~Stack(); // 0x00

			// members
			BSTSmartPointer<Stack> nextStack;		  // 0x10
			BSTSmartPointer<ExtraDataList> extra;	  // 0x18
			std::uint32_t count;					  // 0x20
			REX::EnumSet<Flags, std::uint16_t> flags; // 0x24
		};

		static_assert(sizeof(Stack) == 0x28);

#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'265)
#endif

		// NOLINTBEGIN(cppcoreguidelines-virtual-class-destructor)

		class __declspec(novtable) StackDataCompareFunctor
		{
		public:
			inline static constexpr const auto& RTTI = RTTI::BGSInventoryItem__StackDataCompareFunctor;
			inline static constexpr const auto& VTABLE = VTABLE::BGSInventoryItem__StackDataCompareFunctor;

			// add
			virtual auto CompareData(const BGSInventoryItem::Stack& a_stack) -> bool = 0; // 0x00
			virtual auto UseDefaultStackIfNoMatch() const -> bool;						  // 0x01 - { return false; }
		};

		static_assert(sizeof(StackDataCompareFunctor) == 0x08);

		class __declspec(novtable) CheckStackIDFunctor : public StackDataCompareFunctor // 0x00
		{
		public:
			inline static constexpr const auto& RTTI = RTTI::BGSInventoryItem__CheckStackIDFunctor;
			inline static constexpr const auto& VTABLE = VTABLE::BGSInventoryItem__CheckStackIDFunctor;

			explicit CheckStackIDFunctor(std::uint32_t a_targetIndex) noexcept :
				targetIndex(a_targetIndex)
			{
				REL::EmplaceVtable(this);
			}

			// override (StackDataCompareFunctor)
			auto CompareData(const BGSInventoryItem::Stack& a_stack) -> bool override; // 0x00

			// members
			std::uint32_t targetIndex; // 0x08
		};

		static_assert(sizeof(CheckStackIDFunctor) == 0x10);

		class __declspec(novtable) CheckExtraDataFunctor : public StackDataCompareFunctor // 0x00
		{
		public:
			inline static constexpr const auto& RTTI = RTTI::BGSInventoryItem__CheckExtraDataFunctor;
			inline static constexpr const auto& VTABLE = VTABLE::BGSInventoryItem__CheckExtraDataFunctor;

			explicit CheckExtraDataFunctor(const BGSInventoryItem::Stack* a_stack) noexcept :
				extra(a_stack ? a_stack->extra.get() : nullptr)
			{
				REL::EmplaceVtable(this);
			}

			// override (StackDataCompareFunctor)
			auto CompareData(const BGSInventoryItem::Stack& a_stack) -> bool override; // 0x00

			// members
			ExtraDataList* extra; // 0x08
		};

		static_assert(sizeof(CheckExtraDataFunctor) == 0x10);

		class __declspec(novtable) FindEquippedStackFunctor : public StackDataCompareFunctor // 0x00
		{
		public:
			static constexpr const auto& RTTI = RTTI::BGSInventoryItem__FindEquippedStackFunctor;
			static constexpr const auto& VTABLE = VTABLE::BGSInventoryItem__FindEquippedStackFunctor;

			FindEquippedStackFunctor() noexcept
			{
				REL::EmplaceVtable(this);
			}

			// override (StackDataCompareFunctor)
			auto CompareData(const BGSInventoryItem::Stack& a_stack) -> bool override; // 0x00
		};

		static_assert(sizeof(FindEquippedStackFunctor) == 0x08);

		class __declspec(novtable) HasExtraDataFunctor : public StackDataCompareFunctor // 0x00
		{
		public:
			static constexpr const auto& RTTI = RTTI::BGSInventoryItem__HasExtraDataFunctor;
			static constexpr const auto& VTABLE = VTABLE::BGSInventoryItem__HasExtraDataFunctor;

			explicit HasExtraDataFunctor(EXTRA_DATA_TYPE a_type) noexcept :
				type(a_type)
			{
				REL::EmplaceVtable(this);
			}

			// override (StackDataCompareFunctor)
			auto CompareData(const BGSInventoryItem::Stack& a_stack) -> bool override; // 0x00

			// members
			REX::Enum<EXTRA_DATA_TYPE, std::uint8_t> type; // 0x08
		};

		static_assert(sizeof(HasExtraDataFunctor) == 0x10);

		class __declspec(novtable) IsUIEquivalentStackFunctor : public StackDataCompareFunctor // 0x00
		{
		public:
			static constexpr const auto& RTTI = RTTI::BGSInventoryItem__IsUIEquivalentStackFunctor;
			static constexpr const auto& VTABLE = VTABLE::BGSInventoryItem__IsUIEquivalentStackFunctor;

			explicit IsUIEquivalentStackFunctor(BGSInventoryItem::Stack* a_stack) noexcept :
				stack(a_stack)
			{
				REL::EmplaceVtable(this);
			}

			// override (StackDataCompareFunctor)
			auto CompareData(const BGSInventoryItem::Stack& a_stack) -> bool override; // 0x00

			// members
			BSTSmartPointer<BGSInventoryItem::Stack> stack; // 0x08
		};

		static_assert(sizeof(IsUIEquivalentStackFunctor) == 0x10);

		class __declspec(novtable) StackDataWriteFunctor
		{
		public:
			inline static constexpr const auto& RTTI = RTTI::BGSInventoryItem__StackDataWriteFunctor;
			inline static constexpr const auto& VTABLE = VTABLE::BGSInventoryItem__StackDataWriteFunctor;

			StackDataWriteFunctor() noexcept
			{
				REL::EmplaceVtable(this);
			}

			// add
			virtual void WriteDataImpl(TESBoundObject& a_baseObj, BGSInventoryItem::Stack& a_stack) = 0; // 0x01

			// members
			bool shouldSplitStacks{true};			  // 0x08
			bool transferEquippedToSplitStack{false}; // 0x09
		};

		static_assert(sizeof(StackDataWriteFunctor) == 0x10);

		class __declspec(novtable) ModifyModDataFunctor : public StackDataWriteFunctor // 0x00
		{
		public:
			inline static constexpr const auto& RTTI = RTTI::BGSInventoryItem__ModifyModDataFunctor;
			inline static constexpr const auto& VTABLE = VTABLE::BGSInventoryItem__ModifyModDataFunctor;

			ModifyModDataFunctor(
				BGSMod::Attachment::Mod* a_mod,
				std::int8_t a_slotIndex,
				bool a_attach,
				bool* a_success) noexcept :
				mod(a_mod),
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
			void WriteDataImpl(TESBoundObject& a_baseObj, BGSInventoryItem::Stack& a_stack) override; // 0x01

			// members
			BGSMod::Attachment::Mod* mod;	   // 0x10
			TESBoundObject* foundObj{nullptr}; // 0x18
			bool* success;					   // 0x20
			std::int8_t slotIndex;			   // 0x28
			bool attach;					   // 0x29
			bool equipLocked{false};		   // 0x2A
		};

		static_assert(sizeof(ModifyModDataFunctor) == 0x30);

		class __declspec(novtable) SetHealthFunctor : public StackDataWriteFunctor // 0x00
		{
		public:
			inline static constexpr const auto& RTTI = RTTI::BGSInventoryItem__SetHealthFunctor;
			inline static constexpr const auto& VTABLE = VTABLE::BGSInventoryItem__SetHealthFunctor;

			explicit SetHealthFunctor(REX::Float32 a_health) noexcept :
				health(a_health)
			{
				REL::EmplaceVtable(this);
			}

			// override (StackDataWriteFunctor)
			void WriteDataImpl(TESBoundObject& a_baseObj, BGSInventoryItem::Stack& a_stack) override; // 0x01

			// members
			REX::Float32 health; // 0x10
		};

		static_assert(sizeof(SetHealthFunctor) == 0x18);

		class __declspec(novtable) ClearEquipFlagsFunctor : public StackDataWriteFunctor // 0x00
		{
		public:
			static constexpr const auto& RTTI = RTTI::BGSInventoryItem__ClearEquipFlagsFunctor;
			static constexpr const auto& VTABLE = VTABLE::BGSInventoryItem__ClearEquipFlagsFunctor;

			ClearEquipFlagsFunctor() noexcept
			{
				REL::EmplaceVtable(this);
			}

			// override (StackDataWriteFunctor)
			void WriteDataImpl(TESBoundObject& a_baseObj, BGSInventoryItem::Stack& a_stack) override; // 0x00
		};

		static_assert(sizeof(ClearEquipFlagsFunctor) == 0x10);

		class __declspec(novtable) ModCountFunctor : public StackDataWriteFunctor // 0x00
		{
		public:
			static constexpr const auto& RTTI = RTTI::BGSInventoryItem__ModCountFunctor;
			static constexpr const auto& VTABLE = VTABLE::BGSInventoryItem__ModCountFunctor;

			explicit ModCountFunctor(std::int32_t a_count) noexcept :
				count(a_count)
			{
				REL::EmplaceVtable(this);
			}

			// override (StackDataWriteFunctor)
			void WriteDataImpl(TESBoundObject& a_baseObj, BGSInventoryItem::Stack& a_stack) override; // 0x00

			// members
			std::int32_t count; // 0x10
		};

		static_assert(sizeof(ModCountFunctor) == 0x18);

		class __declspec(novtable) SetFlagFunctor : public StackDataWriteFunctor // 0x00
		{
		public:
			static constexpr const auto& RTTI = RTTI::BGSInventoryItem__SetFlagFunctor;
			static constexpr const auto& VTABLE = VTABLE::BGSInventoryItem__SetFlagFunctor;

			SetFlagFunctor(std::uint32_t a_flagIndex, bool a_setFlag) noexcept :
				flagIndex(a_flagIndex),
				setFlag(a_setFlag)
			{
				REL::EmplaceVtable(this);
			}

			// override (StackDataWriteFunctor)
			void WriteDataImpl(TESBoundObject& a_baseObj, BGSInventoryItem::Stack& a_stack) override; // 0x00

			// members
			std::uint32_t flagIndex; // 0x10
			bool setFlag;			 // 0x14
		};

		static_assert(sizeof(SetFlagFunctor) == 0x18);

		// NOLINTEND(cppcoreguidelines-virtual-class-destructor)

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif

		[[nodiscard]]
		auto IsEquipped(std::uint32_t a_stackID) const -> bool;
		auto FindAndWriteStackData(
			StackDataCompareFunctor& a_compareFunc,
			StackDataWriteFunctor& a_writeFunc,
			bool a_manualMerge,
			ObjectRefHandle a_owner) -> bool;
		[[nodiscard]]
		auto GetCount() const noexcept -> std::uint32_t;
		[[nodiscard]]
		auto GetStackByID(std::uint32_t a_stackID) const -> Stack*;
		[[nodiscard]]
		auto GetDisplayFullName(std::uint32_t a_stackID) const -> const char*;
		[[nodiscard]]
		auto GetDisplayFullName(const ExtraDataList* a_extra) const -> const char*;
		[[nodiscard]]
		auto GetInstanceData(std::uint32_t a_stackID) const -> TBO_InstanceData*;
		[[nodiscard]]
		auto GetInventoryValue(std::uint32_t a_stackID, bool a_scale) const -> std::int32_t;
		[[nodiscard]]
		auto GetExtraDataAt(std::uint32_t a_index) const -> ExtraDataList*;
		[[nodiscard]]
		auto GetStackCount() const -> std::uint64_t;
		[[nodiscard]]
		auto GetTotalWeight() const -> REX::Float32;
		[[nodiscard]]
		auto IsQuestObject(std::int32_t a_stackIterations) const -> bool;
		void MergeStacks();

		// members
		TESBoundObject* object;			  // 0x00
		BSTSmartPointer<Stack> stackData; // 0x08
	};

	static_assert(sizeof(BGSInventoryItem) == 0x10);
}
