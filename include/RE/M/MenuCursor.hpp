#pragma once

#include "RE/B/BSInputEventSingleUser.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/S/Setting.hpp"

namespace RE
{
	class __declspec(novtable) MenuCursor
		: public BSInputEventSingleUser,	 // 00
		  public BSTSingletonSDM<MenuCursor> // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::MenuCursor };
		inline static constexpr auto VTABLE{ VTABLE::MenuCursor };

		~MenuCursor() override; // 00

		GAME_HEAP_REDEFINE_NEW(MenuCursor);

		[[nodiscard]] static MenuCursor* GetSingleton();

		[[nodiscard]] static Setting& GetPipboyConstraintTLX();
		[[nodiscard]] static Setting& GetPipboyConstraintTLY();
		[[nodiscard]] static Setting& GetPipboyConstraintWidth();
		[[nodiscard]] static Setting& GetPipboyConstraintHeight();
		[[nodiscard]] static Setting& GetPipboyConstraintTLX_PowerArmor();
		[[nodiscard]] static Setting& GetPipboyConstraintTLY_PowerArmor();
		[[nodiscard]] static Setting& GetPipboyConstraintWidth_PowerArmor();
		[[nodiscard]] static Setting& GetPipboyConstraintHeight_PowerArmor();

		void CenterCursor();
		void ClearConstraints() noexcept;
		void ConstrainForPipboy();
		void ConstrainForPipboyPA();
		void RegisterCursor();
		void SetCursorConstraintsRaw(std::uint32_t a_tlx, std::uint32_t a_tly, std::uint32_t a_width, std::uint32_t a_height);
		void UnregisterCursor();

		// members
		std::int32_t cursorPosX;		  // 24
		std::int32_t cursorPosY;		  // 28
		std::int32_t minCursorX;		  // 2C
		std::int32_t minCursorY;		  // 30
		std::int32_t maxCursorX;		  // 34
		std::int32_t maxCursorY;		  // 38
		REX::Float32 leftConstraintPct;	  // 3C
		REX::Float32 rightConstraintPct;  // 40
		REX::Float32 topConstraintPct;	  // 44
		REX::Float32 bottomConstraintPct; // 48
		REX::Float32 gamepadCursorSpeed;  // 4C
		std::uint32_t registeredCursors;  // 50
		bool forceOSCursorPos;			  // 54
		bool allowGamepadCursorOverride;  // 55
	};
	static_assert(sizeof(MenuCursor) == 0x58);
}
