#pragma once

#include "RE/B/BSTSmartPointer.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BSStorage;
}

namespace RE::BSScript::Internal
{
	class CodeTasklet;
	class ReadableStringTable;
	class ReadableTypeTable;
	class WritableStringTable;
	class WritableTypeTable;
}

namespace RE::BSScript
{
	class Array;
	class IHandleReaderWriter;
	class Object;
	class Stack;
	class Struct;
	class TypeInfo;

	class __declspec(novtable) IVMSaveLoadInterface
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__IVMSaveLoadInterface;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__IVMSaveLoadInterface;

		virtual ~IVMSaveLoadInterface() = default; // 0x00

		// add
		virtual auto SaveGame(
			BSStorage& a_storage,
			const IHandleReaderWriter& a_handleReaderWriter,
			bool a_calculatingSize) -> bool = 0; // 0x01
		virtual auto LoadGame(
			const BSStorage& a_storage,
			const IHandleReaderWriter& a_handleReaderWriter,
			bool& a_unk01,
			bool& a_unk02) -> bool = 0;															  // 0x02
		virtual void MarkSaveInvalid(BSStorage& a_storage) = 0;									  // 0x03
		virtual auto GetSaveGameVersion() const -> std::uint16_t = 0;							  // 0x04
		virtual void CleanupSave() = 0;															  // 0x05
		virtual void CleanupLoad() = 0;															  // 0x06
		virtual void DropAllRunningData() = 0;													  // 0x07
		virtual auto GetSaveHandleForObject(const Object* a_object) const -> SaveHandle = 0;	  // 0x08
		virtual void SetSaveHandleForObject(const Object* a_object, SaveHandle a_saveHandle) = 0; // 0x09
		virtual auto GetObjectBySaveHandle(SaveHandle a_saveHandle, BSTSmartPointer<Object>& a_object) const
			-> bool = 0; // 0x0A
		virtual auto GetObjectBySaveHandle(
			SaveHandle a_saveHandle,
			const TypeInfo& a_typeInfo,
			BSTSmartPointer<Object>& a_object) const -> bool = 0;								  // 0x0B
		virtual auto GetSaveHandleForStruct(const Struct* a_struct) const -> SaveHandle = 0;	  // 0x0C
		virtual void SetSaveHandleForStruct(const Struct* a_struct, SaveHandle a_saveHandle) = 0; // 0x0D
		virtual auto GetStructBySaveHandle(SaveHandle a_saveHandle, BSTSmartPointer<Struct>& a_struct) const
			-> bool = 0;																	   // 0x0E
		virtual auto GetSaveHandleForArray(const Array* a_array) const -> SaveHandle = 0;	   // 0x0F
		virtual void SetSaveHandleForArray(const Array* a_array, SaveHandle a_saveHandle) = 0; // 0x10
		virtual auto GetArrayBySaveHandle(SaveHandle a_saveHandle, BSTSmartPointer<Array>& a_array) const
			-> bool = 0;																				 // 0x11
		virtual auto GetStackByID(StackID a_stackID, BSTSmartPointer<Stack>& a_stack) const -> bool = 0; // 0x12
		virtual auto GetWritableStringTable() -> Internal::WritableStringTable& = 0;					 // 0x13
		virtual auto GetWritableStringTable() const -> const Internal::WritableStringTable& = 0;		 // 0x14
		virtual auto GetReadableStringTable() const -> Internal::ReadableStringTable& = 0;				 // 0x15
		virtual auto GetWritableTypeTable() -> Internal::WritableTypeTable& = 0;						 // 0x16
		virtual auto GetWritableTypeTable() const -> const Internal::WritableTypeTable& = 0;			 // 0x17
		virtual auto GetReadableTypeTable() const -> Internal::ReadableTypeTable& = 0;					 // 0x18
		virtual auto CreateEmptyTasklet(Stack* a_stack, BSTSmartPointer<Internal::CodeTasklet>& a_tasklet)
			-> bool = 0; // 0x19

		GAME_HEAP_REDEFINE_NEW(IVMSaveLoadInterface);
	};

	static_assert(sizeof(IVMSaveLoadInterface) == 0x08);
}
