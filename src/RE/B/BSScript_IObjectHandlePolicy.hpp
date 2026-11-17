#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	enum class FormType : std::int32_t;
}

namespace RE::BSScript
{
	class __declspec(novtable) IObjectHandlePolicy
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__IObjectHandlePolicy;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__IObjectHandlePolicy;

		virtual ~IObjectHandlePolicy() = default; // 0x00

		// add
		virtual auto HandleIsType(FormType a_type, ObjectHandle a_objectHandle) const -> bool = 0;			// 0x01
		virtual auto GetHandleType(ObjectHandle a_objectHandle, FormType& a_typeID) const -> bool = 0;		// 0x02
		virtual auto IsHandleLoaded(ObjectHandle a_objectHandle) const -> bool = 0;							// 0x03
		virtual auto IsHandleObjectAvailable(ObjectHandle a_objectHandle) const -> bool = 0;				// 0x04
		virtual auto ShouldAttemptToCleanHandle(ObjectHandle a_objectHandle) const -> bool = 0;				// 0x05
		virtual auto EmptyHandle() const -> ObjectHandle = 0;												// 0x06
		virtual auto GetHandleForObject(FormType a_type, const void* a_object) const -> ObjectHandle = 0;	// 0x07
		virtual auto HasParent(ObjectHandle a_childHandle) const -> bool = 0;								// 0x08
		virtual auto GetParentHandle(ObjectHandle a_childHandle) const -> ObjectHandle = 0;					// 0x09
		virtual auto GetHandleScriptsMovedFrom(ObjectHandle a_newHandle) const -> ObjectHandle = 0;			// 0x0A
		virtual auto GetSaveRemappedHandle(ObjectHandle a_saveHandle) const -> ObjectHandle = 0;			// 0x0B
		virtual auto GetObjectForHandle(FormType a_type, ObjectHandle a_objectHandle) const -> void* = 0;	// 0x0C
		virtual void PersistHandle(ObjectHandle a_objectHandle) = 0;										// 0x0D
		virtual void ReleaseHandle(ObjectHandle a_objectHandle) = 0;										// 0x0E
		virtual void ConvertHandleToString(ObjectHandle a_objectHandle, BSFixedString& a_string) const = 0; // 0x0F

		GAME_HEAP_REDEFINE_NEW(IObjectHandlePolicy);
	};

	static_assert(sizeof(IObjectHandlePolicy) == 0x08);
}
