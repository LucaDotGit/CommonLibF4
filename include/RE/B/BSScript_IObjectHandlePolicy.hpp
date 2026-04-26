#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	enum class FormType : std::int32_t;
}

namespace RE::BSScript
{
	class __declspec(novtable) IObjectHandlePolicy
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__IObjectHandlePolicy };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__IObjectHandlePolicy };

		virtual ~IObjectHandlePolicy() = default; // 00

		// add
		virtual bool HandleIsType(FormType a_type, ObjectHandle a_objectHandle) const = 0;					// 01
		virtual bool GetHandleType(ObjectHandle a_objectHandle, FormType& a_typeID) const = 0;				// 02
		virtual bool IsHandleLoaded(ObjectHandle a_objectHandle) const = 0;									// 03
		virtual bool IsHandleObjectAvailable(ObjectHandle a_objectHandle) const = 0;						// 04
		virtual bool ShouldAttemptToCleanHandle(ObjectHandle a_objectHandle) const = 0;						// 05
		virtual ObjectHandle EmptyHandle() const = 0;														// 06
		virtual ObjectHandle GetHandleForObject(FormType a_type, const void* a_object) const = 0;			// 07
		virtual bool HasParent(ObjectHandle a_childHandle) const = 0;										// 08
		virtual ObjectHandle GetParentHandle(ObjectHandle a_childHandle) const = 0;							// 09
		virtual ObjectHandle GetHandleScriptsMovedFrom(ObjectHandle a_newHandle) const = 0;					// 0A
		virtual ObjectHandle GetSaveRemappedHandle(ObjectHandle a_saveHandle) const = 0;					// 0B
		virtual void* GetObjectForHandle(FormType a_type, ObjectHandle a_objectHandle) const = 0;			// 0C
		virtual void PersistHandle(ObjectHandle a_objectHandle) = 0;										// 0D
		virtual void ReleaseHandle(ObjectHandle a_objectHandle) = 0;										// 0E
		virtual void ConvertHandleToString(ObjectHandle a_objectHandle, BSFixedString& a_string) const = 0; // 0F
	};
	static_assert(sizeof(IObjectHandlePolicy) == 0x08);
}
