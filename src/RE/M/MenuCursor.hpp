#pragma once

#include "RE/B/BSInputEventSingleUser.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/S/Setting.hpp"

namespace RE
{
	class __declspec(novtable) MenuCursor :
		public BSInputEventSingleUser,	   // 0x00
		public BSTSingletonSDM<MenuCursor> // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::MenuCursor;
		inline static constexpr const auto& VTABLE = VTABLE::MenuCursor;

		~MenuCursor() override; // 0x00

		GAME_HEAP_REDEFINE_NEW(MenuCursor);

		[[nodiscard]]
		static auto GetSingleton() noexcept -> MenuCursor*;

		[[nodiscard]]
		static auto GetPipboyConstraintTLXSetting() -> Setting&;
		[[nodiscard]]
		static auto GetPipboyConstraintTLYSetting() -> Setting&;
		[[nodiscard]]
		static auto GetPipboyConstraintWidthSetting() -> Setting&;
		[[nodiscard]]
		static auto GetPipboyConstraintHeightSetting() -> Setting&;
		[[nodiscard]]
		static auto GetPipboyConstraintTLX_PowerArmorSetting() -> Setting&;
		[[nodiscard]]
		static auto GetPipboyConstraintTLY_PowerArmorSetting() -> Setting&;
		[[nodiscard]]
		static auto GetPipboyConstraintWidth_PowerArmorSetting() -> Setting&;
		[[nodiscard]]
		static auto GetPipboyConstraintHeight_PowerArmorSetting() -> Setting&;

		[[nodiscard]]
		static auto GetPipboyConstraintTLX() -> std::uint32_t;
		[[nodiscard]]
		static auto GetPipboyConstraintTLY() -> std::uint32_t;
		[[nodiscard]]
		static auto GetPipboyConstraintWidth() -> std::uint32_t;
		[[nodiscard]]
		static auto GetPipboyConstraintHeight() -> std::uint32_t;
		[[nodiscard]]
		static auto GetPipboyConstraintTLX_PowerArmor() -> std::uint32_t;
		[[nodiscard]]
		static auto GetPipboyConstraintTLY_PowerArmor() -> std::uint32_t;
		[[nodiscard]]
		static auto GetPipboyConstraintWidth_PowerArmor() -> std::uint32_t;
		[[nodiscard]]
		static auto GetPipboyConstraintHeight_PowerArmor() -> std::uint32_t;

		static void SetPipboyConstraintTLX(std::uint32_t a_value);
		static void SetPipboyConstraintTLY(std::uint32_t a_value);
		static void SetPipboyConstraintWidth(std::uint32_t a_value);
		static void SetPipboyConstraintHeight(std::uint32_t a_value);
		static void SetPipboyConstraintTLX_PowerArmor(std::uint32_t a_value);
		static void SetPipboyConstraintTLY_PowerArmor(std::uint32_t a_value);
		static void SetPipboyConstraintWidth_PowerArmor(std::uint32_t a_value);
		static void SetPipboyConstraintHeight_PowerArmor(std::uint32_t a_value);

		void CenterCursor();
		void ClearConstraints() noexcept;
		void ConstrainForPipboy();
		void ConstrainForPipboyPA();
		void RegisterCursor();
		void SetCursorConstraintsRaw(
			std::uint32_t a_tlx,
			std::uint32_t a_tly,
			std::uint32_t a_width,
			std::uint32_t a_height);
		void UnregisterCursor();

		// members
		std::int32_t cursorPosX;		  // 0x24
		std::int32_t cursorPosY;		  // 0x28
		std::int32_t minCursorX;		  // 0x2C
		std::int32_t minCursorY;		  // 0x30
		std::int32_t maxCursorX;		  // 0x34
		std::int32_t maxCursorY;		  // 0x38
		REX::Float32 leftConstraintPct;	  // 0x3C
		REX::Float32 rightConstraintPct;  // 0x40
		REX::Float32 topConstraintPct;	  // 0x44
		REX::Float32 bottomConstraintPct; // 0x48
		REX::Float32 gamepadCursorSpeed;  // 0x4C
		std::uint32_t registeredCursors;  // 0x50
		bool forceOSCursorPos;			  // 0x54
		bool allowGamepadCursorOverride;  // 0x55
	};

	static_assert(sizeof(MenuCursor) == 0x58);
}
