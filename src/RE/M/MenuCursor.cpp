#include "RE/M/MenuCursor.hpp"

#include "RE/S/SettingUtil.hpp"

namespace RE
{
	MenuCursor* MenuCursor::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<MenuCursor**>{ ID::MenuCursor::Singleton };
		return *SINGLETON;
	}

	Setting& MenuCursor::GetPipboyConstraintTLX()
	{
		static auto* PipboyConstraintTLX = GetINISetting("uPipboyConstraintTLX:Pipboy"sv);
		return *PipboyConstraintTLX;
	}

	Setting& MenuCursor::GetPipboyConstraintTLY()
	{
		static auto* PipboyConstraintTLY = GetINISetting("uPipboyConstraintTLY:Pipboy"sv);
		return *PipboyConstraintTLY;
	}

	Setting& MenuCursor::GetPipboyConstraintWidth()
	{
		static auto* PipboyConstraintWidth = GetINISetting("uPipboyConstraintWidth:Pipboy"sv);
		return *PipboyConstraintWidth;
	}

	Setting& MenuCursor::GetPipboyConstraintHeight()
	{
		static auto* PipboyConstraintHeight = GetINISetting("uPipboyConstraintHeight:Pipboy"sv);
		return *PipboyConstraintHeight;
	}

	Setting& MenuCursor::GetPipboyConstraintTLX_PowerArmor()
	{
		static auto* PipboyConstraintTLX_PowerArmor = GetINISetting("uPipboyConstraintTLX_PowerArmor:Pipboy"sv);
		return *PipboyConstraintTLX_PowerArmor;
	}

	Setting& MenuCursor::GetPipboyConstraintTLY_PowerArmor()
	{
		static auto* PipboyConstraintTLY_PowerArmor = GetINISetting("uPipboyConstraintTLY_PowerArmor:Pipboy"sv);
		return *PipboyConstraintTLY_PowerArmor;
	}

	Setting& MenuCursor::GetPipboyConstraintWidth_PowerArmor()
	{
		static auto* PipboyConstraintWidth_PowerArmor = GetINISetting("uPipboyConstraintWidth_PowerArmor:Pipboy"sv);
		return *PipboyConstraintWidth_PowerArmor;
	}

	Setting& MenuCursor::GetPipboyConstraintHeight_PowerArmor()
	{
		static auto* PipboyConstraintHeight_PowerArmor = GetINISetting("uPipboyConstraintHeight_PowerArmor:Pipboy"sv);
		return *PipboyConstraintHeight_PowerArmor;
	}

	void MenuCursor::CenterCursor()
	{
		using FuncType = decltype(&MenuCursor::CenterCursor);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::MenuCursor::CenterCursor };
		FUNC(this);
	}

	void MenuCursor::ClearConstraints() noexcept
	{
		leftConstraintPct = 0.0_f32;
		rightConstraintPct = 0.0_f32;
		topConstraintPct = 0.0_f32;
		bottomConstraintPct = 0.0_f32;
	}

	void MenuCursor::ConstrainForPipboy()
	{
		SetCursorConstraintsRaw(
			GetPipboyConstraintTLX().GetUInt(),
			GetPipboyConstraintTLY().GetUInt(),
			GetPipboyConstraintWidth().GetUInt(),
			GetPipboyConstraintHeight().GetUInt());
	}

	void MenuCursor::ConstrainForPipboyPA()
	{
		SetCursorConstraintsRaw(
			GetPipboyConstraintTLX_PowerArmor().GetUInt(),
			GetPipboyConstraintTLY_PowerArmor().GetUInt(),
			GetPipboyConstraintWidth_PowerArmor().GetUInt(),
			GetPipboyConstraintHeight_PowerArmor().GetUInt());
	}

	void MenuCursor::RegisterCursor()
	{
		using FuncType = decltype(&MenuCursor::RegisterCursor);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::MenuCursor::RegisterCursor };
		FUNC(this);
	}

	void MenuCursor::SetCursorConstraintsRaw(std::uint32_t a_tlx, std::uint32_t a_tly, std::uint32_t a_width, std::uint32_t a_height)
	{
		using FuncType = decltype(&MenuCursor::SetCursorConstraintsRaw);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::MenuCursor::SetCursorConstraintsRaw };
		FUNC(this, a_tlx, a_tly, a_width, a_height);
	}

	void MenuCursor::UnregisterCursor()
	{
		using FuncType = decltype(&MenuCursor::UnregisterCursor);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::MenuCursor::UnregisterCursor };
		FUNC(this);
	}
}
