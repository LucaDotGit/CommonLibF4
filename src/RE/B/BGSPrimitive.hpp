#pragma once

#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BGSPrimitiveLine;
	class BSMultiBoundShape;
	class BSFadeNode;
	class NiColorA;

	class __declspec(novtable) BGSPrimitive
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSPrimitive;
		inline static constexpr const auto& VTABLE = VTABLE::BGSPrimitive;

		enum class PRIMITIVE_TYPE : std::int32_t
		{
			None = 0,
			Box = 1,
			Sphere = 2,
			Plane = 3,
			Line = 4,
			Ellipsoid = 5
		};

		virtual ~BGSPrimitive(); // 0x00

		// add
		virtual void SetColor(const NiColorA& a_color) = 0;				  // 0x01
		virtual void SetRadii(const NiPoint3& a_radii) = 0;				  // 0x02
		virtual auto IsInside(const NiPoint3& a_point) const -> bool = 0; // 0x03
		virtual auto MakeMultiBoundShape(const NiPoint3& a_angle) const
			-> BSMultiBoundShape*; // 0x04 - { return nullptr; }

		[[nodiscard]]
		static auto CreateAbstract(PRIMITIVE_TYPE a_type, const NiPoint3& a_point, const NiColorA& a_color)
			-> BGSPrimitiveLine*
		{
			using FuncType = decltype(&BGSPrimitive::CreateAbstract);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSPrimitive::CreateAbstract);
			return std::invoke(FUNC, a_type, a_point, a_color);
		}

		// members
		REX::Enum<PRIMITIVE_TYPE, std::int32_t> type; // 0x08
		NiPoint3 radii;								  // 0x0C
		NiPointer<BSFadeNode> node;					  // 0x18
	};

	static_assert(sizeof(BGSPrimitive) == 0x20);
}
