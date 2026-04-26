#include "RE/N/NiMatrix3.hpp"

namespace RE
{
	bool NiMatrix3::ToEulerAnglesXYZ(NiPoint3& a_point) const noexcept
	{
		return ToEulerAnglesXYZ(a_point.x, a_point.y, a_point.z);
	}

	bool NiMatrix3::ToEulerAnglesXYZ(REX::Float32& a_x, REX::Float32& a_y, REX::Float32& a_z) const noexcept
	{
		using FuncType = bool (*)(const NiMatrix3*, REX::Float32&, REX::Float32&, REX::Float32&) noexcept;
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiMatrix3::ToEulerAnglesXYZ };
		return std::invoke(FUNC, this, a_x, a_y, a_z);
	}

	bool NiMatrix3::ToEulerAnglesXZY(REX::Float32& a_x, REX::Float32& a_z, REX::Float32& a_y) const noexcept
	{
		using FuncType = decltype(&NiMatrix3::ToEulerAnglesXZY);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiMatrix3::ToEulerAnglesXZY };
		return std::invoke(FUNC, this, a_x, a_z, a_y);
	}

	bool NiMatrix3::ToEulerAnglesYXZ(REX::Float32& a_y, REX::Float32& a_x, REX::Float32& a_z) const noexcept
	{
		using FuncType = decltype(&NiMatrix3::ToEulerAnglesYXZ);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiMatrix3::ToEulerAnglesYXZ };
		return std::invoke(FUNC, this, a_y, a_x, a_z);
	}

	bool NiMatrix3::ToEulerAnglesYZX(REX::Float32& a_y, REX::Float32& a_z, REX::Float32& a_x) const noexcept
	{
		using FuncType = decltype(&NiMatrix3::ToEulerAnglesYZX);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiMatrix3::ToEulerAnglesYZX };
		return std::invoke(FUNC, this, a_y, a_z, a_x);
	}

	bool NiMatrix3::ToEulerAnglesZYX(REX::Float32& a_z, REX::Float32& a_y, REX::Float32& a_x) const noexcept
	{
		using FuncType = decltype(&NiMatrix3::ToEulerAnglesZYX);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiMatrix3::ToEulerAnglesZYX };
		return std::invoke(FUNC, this, a_z, a_y, a_x);
	}

	bool NiMatrix3::ToEulerAnglesZXY(REX::Float32& a_z, REX::Float32& a_x, REX::Float32& a_y) const noexcept
	{
		using FuncType = decltype(&NiMatrix3::ToEulerAnglesZXY);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiMatrix3::ToEulerAnglesZXY };
		return std::invoke(FUNC, this, a_z, a_x, a_y);
	}

	void NiMatrix3::FromEulerAnglesXYZ(const NiPoint3& a_point) noexcept
	{
		FromEulerAnglesXYZ(a_point.x, a_point.y, a_point.z);
	}

	void NiMatrix3::FromEulerAnglesXYZ(REX::Float32 a_x, REX::Float32 a_y, REX::Float32 a_z) noexcept
	{
		using FuncType = void (*)(NiMatrix3*, REX::Float32, REX::Float32, REX::Float32) noexcept;
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiMatrix3::FromEulerAnglesXYZ };
		FUNC(this, a_x, a_y, a_z);
	}

	void NiMatrix3::FromEulerAnglesXZY(REX::Float32 a_x, REX::Float32 a_z, REX::Float32 a_y) noexcept
	{
		using FuncType = decltype(&NiMatrix3::FromEulerAnglesXZY);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiMatrix3::FromEulerAnglesXZY };
		FUNC(this, a_x, a_z, a_y);
	}

	void NiMatrix3::FromEulerAnglesYXZ(REX::Float32 a_y, REX::Float32 a_x, REX::Float32 a_z) noexcept
	{
		using FuncType = decltype(&NiMatrix3::FromEulerAnglesYXZ);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiMatrix3::FromEulerAnglesYXZ };
		FUNC(this, a_y, a_x, a_z);
	}

	void NiMatrix3::FromEulerAnglesYZX(REX::Float32 a_y, REX::Float32 a_z, REX::Float32 a_x) noexcept
	{
		using FuncType = decltype(&NiMatrix3::FromEulerAnglesYZX);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiMatrix3::FromEulerAnglesYZX };
		FUNC(this, a_y, a_z, a_x);
	}

	void NiMatrix3::FromEulerAnglesZYX(REX::Float32 a_z, REX::Float32 a_y, REX::Float32 a_x) noexcept
	{
		using FuncType = decltype(&NiMatrix3::FromEulerAnglesZYX);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiMatrix3::FromEulerAnglesZYX };
		FUNC(this, a_z, a_y, a_x);
	}

	void NiMatrix3::FromEulerAnglesZXY(REX::Float32 a_z, REX::Float32 a_x, REX::Float32 a_y) noexcept
	{
		using FuncType = decltype(&NiMatrix3::FromEulerAnglesZXY);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiMatrix3::FromEulerAnglesZXY };
		FUNC(this, a_z, a_x, a_y);
	}
}
