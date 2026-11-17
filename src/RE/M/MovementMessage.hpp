#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"

namespace RE
{
	class BSPathingNumericIDVisitor;
	class BSPathingStreamRead;
	class BSPathingStreamWrite;
	class IPathFollowerAction;

	class __declspec(novtable) MovementMessage : public BSIntrusiveRefCounted // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::MovementMessage;
		inline static constexpr const auto& VTABLE = VTABLE::MovementMessage;

		virtual ~MovementMessage(); // 0x00

		virtual auto GetMessageType() -> std::uint32_t;						   // 0x01
		virtual auto GetType() -> std::uint32_t;							   // 0x02
		virtual void Write(BSPathingStreamWrite& a_target);					   // 0x03
		virtual void Read(BSPathingStreamRead& a_source);					   // 0x04
		virtual void FixupNumericID(BSPathingNumericIDVisitor& a_visitor);	   // 0x05
		virtual auto GetPathFollowerActionInterface() -> IPathFollowerAction*; // 0x06
	};

	static_assert(sizeof(MovementMessage) == 0x10);
}
