#pragma once

#include "RE/B/BSTSmartPointer.hpp"

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
		inline static constexpr auto RTTI{ RTTI::BSScript__IVMSaveLoadInterface };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__IVMSaveLoadInterface };

		virtual ~IVMSaveLoadInterface() = default; // 00

		// add
		virtual bool SaveGame(BSStorage& a_storage, const IHandleReaderWriter& a_handleReaderWriter, bool a_calculatingSize) = 0;				  // 01
		virtual bool LoadGame(const BSStorage& a_storage, const IHandleReaderWriter& a_handleReaderWriter, bool& a_unk01, bool& a_unk02) = 0;	  // 02
		virtual void MarkSaveInvalid(BSStorage& a_storage) = 0;																					  // 03
		virtual std::uint16_t GetSaveGameVersion() const = 0;																					  // 04
		virtual void CleanupSave() = 0;																											  // 05
		virtual void CleanupLoad() = 0;																											  // 06
		virtual void DropAllRunningData() = 0;																									  // 07
		virtual ObjectHandle GetSaveHandleForObject(const Object* a_object) const = 0;															  // 08
		virtual void SetSaveHandleForObject(const Object* a_object, ObjectHandle a_objectHandle) = 0;											  // 09
		virtual bool GetObjectBySaveHandle(ObjectHandle a_objectHandle, BSTSmartPointer<Object>& a_object) const = 0;							  // 0A
		virtual bool GetObjectBySaveHandle(ObjectHandle a_objectHandle, const TypeInfo& a_typeInfo, BSTSmartPointer<Object>& a_object) const = 0; // 0B
		virtual ObjectHandle GetSaveHandleForStruct(const Struct* a_struct) const = 0;															  // 0C
		virtual void SetSaveHandleForStruct(const Struct* a_struct, ObjectHandle a_objectHandle) = 0;											  // 0D
		virtual bool GetStructBySaveHandle(ObjectHandle a_objectHandle, BSTSmartPointer<Struct>& a_struct) const = 0;							  // 0E
		virtual ObjectHandle GetSaveHandleForArray(const Array* a_array) const = 0;																  // 0F
		virtual void SetSaveHandleForArray(const Array* a_array, ObjectHandle a_objectHandle) = 0;												  // 10
		virtual bool GetArrayBySaveHandle(ObjectHandle a_objectHandle, BSTSmartPointer<Array>& a_array) const = 0;								  // 11
		virtual bool GetStackByID(StackID a_stackID, BSTSmartPointer<Stack>& a_stack) const = 0;												  // 12
		virtual Internal::WritableStringTable& GetWritableStringTable() = 0;																	  // 13
		virtual const Internal::WritableStringTable& GetWritableStringTable() const = 0;														  // 14
		virtual Internal::ReadableStringTable& GetReadableStringTable() const = 0;																  // 15
		virtual Internal::WritableTypeTable& GetWritableTypeTable() = 0;																		  // 16
		virtual const Internal::WritableTypeTable& GetWritableTypeTable() const = 0;															  // 17
		virtual Internal::ReadableTypeTable& GetReadableTypeTable() const = 0;																	  // 18
		virtual bool CreateEmptyTasklet(Stack* a_stack, BSTSmartPointer<Internal::CodeTasklet>& a_tasklet) = 0;									  // 19
	};
	static_assert(sizeof(IVMSaveLoadInterface) == 0x08);
}
