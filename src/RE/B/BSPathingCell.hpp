#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class bhkWorld;
	class BSPathingNumericIDVisitor;
	class BSPathingSpace;
	class BSPathingStreamRead;
	class BSPathingStreamWrite;

	class __declspec(novtable) BSPathingCell : public BSIntrusiveRefCounted // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSPathingCell;
		inline static constexpr const auto& VTABLE = VTABLE::BSPathingCell;

		virtual ~BSPathingCell(); // 0x00

		virtual auto GetType() -> std::uint32_t;										   // 0x01
		virtual void Write(BSPathingStreamWrite& a_target);								   // 0x02
		virtual void Read(BSPathingStreamRead& a_source);								   // 0x03
		virtual void FixupNumericID(BSPathingNumericIDVisitor& a_visitor);				   // 0x04
		virtual auto IsEqual(const BSTSmartPointer<BSPathingCell>& a_other) -> bool;	   // 0x05
		virtual void GetSpace(BSTSmartPointer<BSPathingSpace>& a_outSpace);				   // 0x06
		virtual auto GetBhkWorld() -> bhkWorld*;										   // 0x07
		virtual auto QValid() -> bool;													   // 0x08
		virtual auto QAttached() -> bool;												   // 0x09
		virtual auto QLoaded() -> bool;													   // 0x0A
		virtual auto IsInSameSpace(const BSTSmartPointer<BSPathingCell>& a_other) -> bool; // 0x0B
	};

	static_assert(sizeof(BSPathingCell) == 0x10);
}
