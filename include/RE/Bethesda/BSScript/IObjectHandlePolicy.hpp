#pragma once

namespace RE::BSScript
{
	struct __declspec(novtable) IObjectHandlePolicy
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__IObjectHandlePolicy };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__IObjectHandlePolicy };

		virtual ~IObjectHandlePolicy() = default; // 00

		// add
		virtual bool HandleIsType(VMTypeID a_type, VMHandle a_handle) const = 0;				  // 01
		virtual bool GetHandleType(VMHandle a_handle, VMTypeID& a_typeID) const = 0;			  // 02
		virtual bool IsHandleLoaded(VMHandle a_handle) const = 0;								  // 03
		virtual bool IsHandleObjectAvailable(VMHandle a_handle) const = 0;						  // 04
		virtual bool ShouldAttemptToCleanHandle(VMHandle a_handle) const = 0;					  // 05
		virtual VMHandle EmptyHandle() const = 0;												  // 06
		virtual VMHandle GetHandleForObject(VMTypeID a_type, const void* a_object) const = 0;	  // 07
		virtual bool HasParent(VMHandle a_childHandle) const = 0;								  // 08
		virtual VMHandle GetParentHandle(VMHandle a_childHandle) const = 0;						  // 09
		virtual VMHandle GetHandleScriptsMovedFrom(VMHandle a_newHandle) const = 0;				  // 0A
		virtual VMHandle GetSaveRemappedHandle(VMHandle a_saveHandle) const = 0;				  // 0B
		virtual void* GetObjectForHandle(VMTypeID a_type, VMHandle a_handle) const = 0;			  // 0C
		virtual void PersistHandle(VMHandle a_handle) = 0;										  // 0D
		virtual void ReleaseHandle(VMHandle a_handle) = 0;										  // 0E
		virtual void ConvertHandleToString(VMHandle a_handle, BSFixedString& a_string) const = 0; // 0F
	};
	static_assert(sizeof(IObjectHandlePolicy) == 0x8);
}
