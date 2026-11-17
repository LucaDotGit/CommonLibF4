#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class BSPathingDoor;
	class BSPathingStreamRead;
	class BSPathingStreamWrite;

	class __declspec(novtable) BSPathingLockData : public BSIntrusiveRefCounted // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSPathingLockData;
		inline static constexpr const auto& VTABLE = VTABLE::BSPathingLockData;

		virtual ~BSPathingLockData(); // 0x00

		virtual auto GetType() -> std::uint32_t; // 0x01
		virtual auto CanTraverse(
			const BSTSmartPointer<BSPathingDoor>& a_door,
			REX::Float32& a_outCost,
			bool& a_outCommandMode) -> bool;																	 // 0x02
		virtual auto CanTraverse(const BSTSmartPointer<BSPathingDoor>& a_door, REX::Float32& a_outCost) -> bool; // 0x03
		virtual auto CanTraverse(const BSTSmartPointer<BSPathingDoor>& a_door) -> bool;							 // 0x04
		virtual void Write(BSPathingStreamWrite& a_target);														 // 0x05
		virtual void Read(BSPathingStreamRead& a_source);														 // 0x06
	};

	static_assert(sizeof(BSPathingLockData) == 0x10);
}
