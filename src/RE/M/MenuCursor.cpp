#include "RE/M/MenuCursor.hpp"

#include "RE/S/SettingUtil.hpp"

namespace RE
{
	auto MenuCursor::GetSingleton() noexcept -> MenuCursor*
	{
		static const auto SINGLETON = REL::Relocation<MenuCursor**>(ID::MenuCursor::Singleton);
		return *SINGLETON;
	}

	auto MenuCursor::GetPipboyConstraintTLXSetting() -> Setting&
	{
		static auto* PipboyConstraintTLX = GetINISetting("uPipboyConstraintTLX:Pipboy"sv);
		REX::Assert(PipboyConstraintTLX != nullptr);
		return *PipboyConstraintTLX;
	}

	auto MenuCursor::GetPipboyConstraintTLYSetting() -> Setting&
	{
		static auto* PipboyConstraintTLY = GetINISetting("uPipboyConstraintTLY:Pipboy"sv);
		REX::Assert(PipboyConstraintTLY != nullptr);
		return *PipboyConstraintTLY;
	}

	auto MenuCursor::GetPipboyConstraintWidthSetting() -> Setting&
	{
		static auto* PipboyConstraintWidth = GetINISetting("uPipboyConstraintWidth:Pipboy"sv);
		REX::Assert(PipboyConstraintWidth != nullptr);
		return *PipboyConstraintWidth;
	}

	auto MenuCursor::GetPipboyConstraintHeightSetting() -> Setting&
	{
		static auto* PipboyConstraintHeight = GetINISetting("uPipboyConstraintHeight:Pipboy"sv);
		REX::Assert(PipboyConstraintHeight != nullptr);
		return *PipboyConstraintHeight;
	}

	auto MenuCursor::GetPipboyConstraintTLX_PowerArmorSetting() -> Setting&
	{
		static auto* PipboyConstraintTLX_PowerArmor = GetINISetting("uPipboyConstraintTLX_PowerArmor:Pipboy"sv);
		REX::Assert(PipboyConstraintTLX_PowerArmor != nullptr);
		return *PipboyConstraintTLX_PowerArmor;
	}

	auto MenuCursor::GetPipboyConstraintTLY_PowerArmorSetting() -> Setting&
	{
		static auto* PipboyConstraintTLY_PowerArmor = GetINISetting("uPipboyConstraintTLY_PowerArmor:Pipboy"sv);
		REX::Assert(PipboyConstraintTLY_PowerArmor != nullptr);
		return *PipboyConstraintTLY_PowerArmor;
	}

	auto MenuCursor::GetPipboyConstraintWidth_PowerArmorSetting() -> Setting&
	{
		static auto* PipboyConstraintWidth_PowerArmor = GetINISetting("uPipboyConstraintWidth_PowerArmor:Pipboy"sv);
		REX::Assert(PipboyConstraintWidth_PowerArmor != nullptr);
		return *PipboyConstraintWidth_PowerArmor;
	}

	auto MenuCursor::GetPipboyConstraintHeight_PowerArmorSetting() -> Setting&
	{
		static auto* PipboyConstraintHeight_PowerArmor = GetINISetting("uPipboyConstraintHeight_PowerArmor:Pipboy"sv);
		REX::Assert(PipboyConstraintHeight_PowerArmor != nullptr);
		return *PipboyConstraintHeight_PowerArmor;
	}

	auto MenuCursor::GetPipboyConstraintTLX() -> std::uint32_t
	{
		const auto& setting = GetPipboyConstraintTLXSetting();
		if (!setting.IsUInt()) [[unlikely]] {
			REX::Assert(false);
			return 0;
		}

		return setting.GetUInt();
	}

	auto MenuCursor::GetPipboyConstraintTLY() -> std::uint32_t
	{
		const auto& setting = GetPipboyConstraintTLYSetting();
		if (!setting.IsUInt()) [[unlikely]] {
			REX::Assert(false);
			return 0;
		}

		return setting.GetUInt();
	}

	auto MenuCursor::GetPipboyConstraintWidth() -> std::uint32_t
	{
		const auto& setting = GetPipboyConstraintWidthSetting();
		if (!setting.IsUInt()) [[unlikely]] {
			REX::Assert(false);
			return 0;
		}

		return setting.GetUInt();
	}

	auto MenuCursor::GetPipboyConstraintHeight() -> std::uint32_t
	{
		const auto& setting = GetPipboyConstraintHeightSetting();
		if (!setting.IsUInt()) [[unlikely]] {
			REX::Assert(false);
			return 0;
		}

		return setting.GetUInt();
	}

	auto MenuCursor::GetPipboyConstraintTLX_PowerArmor() -> std::uint32_t
	{
		const auto& setting = GetPipboyConstraintTLX_PowerArmorSetting();
		if (!setting.IsUInt()) [[unlikely]] {
			REX::Assert(false);
			return 0;
		}

		return setting.GetUInt();
	}

	auto MenuCursor::GetPipboyConstraintTLY_PowerArmor() -> std::uint32_t
	{
		const auto& setting = GetPipboyConstraintTLY_PowerArmorSetting();
		if (!setting.IsUInt()) [[unlikely]] {
			REX::Assert(false);
			return 0;
		}

		return setting.GetUInt();
	}

	auto MenuCursor::GetPipboyConstraintWidth_PowerArmor() -> std::uint32_t
	{
		const auto& setting = GetPipboyConstraintWidth_PowerArmorSetting();
		if (!setting.IsUInt()) [[unlikely]] {
			REX::Assert(false);
			return 0;
		}

		return setting.GetUInt();
	}

	auto MenuCursor::GetPipboyConstraintHeight_PowerArmor() -> std::uint32_t
	{
		const auto& setting = GetPipboyConstraintHeight_PowerArmorSetting();
		if (!setting.IsUInt()) [[unlikely]] {
			REX::Assert(false);
			return 0;
		}

		return setting.GetUInt();
	}

	void MenuCursor::SetPipboyConstraintTLX(std::uint32_t a_value)
	{
		auto& setting = GetPipboyConstraintTLXSetting();
		if (!setting.IsUInt()) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		setting.SetUInt(a_value);
	}

	void MenuCursor::SetPipboyConstraintTLY(std::uint32_t a_value)
	{
		auto& setting = GetPipboyConstraintTLYSetting();
		if (!setting.IsUInt()) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		setting.SetUInt(a_value);
	}

	void MenuCursor::SetPipboyConstraintWidth(std::uint32_t a_value)
	{
		auto& setting = GetPipboyConstraintWidthSetting();
		if (!setting.IsUInt()) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		setting.SetUInt(a_value);
	}

	void MenuCursor::SetPipboyConstraintHeight(std::uint32_t a_value)
	{
		auto& setting = GetPipboyConstraintHeightSetting();
		if (!setting.IsUInt()) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		setting.SetUInt(a_value);
	}

	void MenuCursor::SetPipboyConstraintTLX_PowerArmor(std::uint32_t a_value)
	{
		auto& setting = GetPipboyConstraintTLX_PowerArmorSetting();
		if (!setting.IsUInt()) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		setting.SetUInt(a_value);
	}

	void MenuCursor::SetPipboyConstraintTLY_PowerArmor(std::uint32_t a_value)
	{
		auto& setting = GetPipboyConstraintTLY_PowerArmorSetting();
		if (!setting.IsUInt()) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		setting.SetUInt(a_value);
	}

	void MenuCursor::SetPipboyConstraintWidth_PowerArmor(std::uint32_t a_value)
	{
		auto& setting = GetPipboyConstraintWidth_PowerArmorSetting();
		if (!setting.IsUInt()) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		setting.SetUInt(a_value);
	}

	void MenuCursor::SetPipboyConstraintHeight_PowerArmor(std::uint32_t a_value)
	{
		auto& setting = GetPipboyConstraintHeight_PowerArmorSetting();
		if (!setting.IsUInt()) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		setting.SetUInt(a_value);
	}

	void MenuCursor::CenterCursor()
	{
		using FuncType = decltype(&MenuCursor::CenterCursor);
		static const auto FUNC = REL::Relocation<FuncType>(ID::MenuCursor::CenterCursor);
		std::invoke(FUNC, this);
	}

	void MenuCursor::ClearConstraints() noexcept
	{
		leftConstraintPct = static_cast<REX::Float32>(0.0);
		rightConstraintPct = static_cast<REX::Float32>(0.0);
		topConstraintPct = static_cast<REX::Float32>(0.0);
		bottomConstraintPct = static_cast<REX::Float32>(0.0);
	}

	void MenuCursor::ConstrainForPipboy()
	{
		SetCursorConstraintsRaw(
			GetPipboyConstraintTLX(),
			GetPipboyConstraintTLY(),
			GetPipboyConstraintWidth(),
			GetPipboyConstraintHeight());
	}

	void MenuCursor::ConstrainForPipboyPA()
	{
		SetCursorConstraintsRaw(
			GetPipboyConstraintTLX_PowerArmor(),
			GetPipboyConstraintTLY_PowerArmor(),
			GetPipboyConstraintWidth_PowerArmor(),
			GetPipboyConstraintHeight_PowerArmor());
	}

	void MenuCursor::RegisterCursor()
	{
		using FuncType = decltype(&MenuCursor::RegisterCursor);
		static const auto FUNC = REL::Relocation<FuncType>(ID::MenuCursor::RegisterCursor);
		std::invoke(FUNC, this);
	}

	void MenuCursor::SetCursorConstraintsRaw(
		std::uint32_t a_tlx,
		std::uint32_t a_tly,
		std::uint32_t a_width,
		std::uint32_t a_height)
	{
		using FuncType = decltype(&MenuCursor::SetCursorConstraintsRaw);
		static const auto FUNC = REL::Relocation<FuncType>(ID::MenuCursor::SetCursorConstraintsRaw);
		std::invoke(FUNC, this, a_tlx, a_tly, a_width, a_height);
	}

	void MenuCursor::UnregisterCursor()
	{
		using FuncType = decltype(&MenuCursor::UnregisterCursor);
		static const auto FUNC = REL::Relocation<FuncType>(ID::MenuCursor::UnregisterCursor);
		std::invoke(FUNC, this);
	}
}
