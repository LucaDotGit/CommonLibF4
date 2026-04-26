#pragma once

#include "RE/N/NiColor.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BGSPrimitiveLine;
	class BSMultiBoundShape;
	class BSFadeNode;

	class __declspec(novtable) BGSPrimitive
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSPrimitive };
		inline static constexpr auto VTABLE{ VTABLE::BGSPrimitive };

		enum class PRIMITIVE_TYPE : std::int32_t
		{
			kNone = 0,
			kBox = 1,
			kSphere = 2,
			kPlane = 3,
			kLine = 4,
			kEllipsoid = 5
		};

		virtual ~BGSPrimitive(); // 00

		// add
		virtual void SetColor(const NiColorA& a_color) = 0;							   // 01
		virtual void SetRadii(const NiPoint3& a_radii) = 0;							   // 02
		virtual bool IsInside(const NiPoint3& a_point) const = 0;					   // 03
		virtual BSMultiBoundShape* MakeMultiBoundShape(const NiPoint3& a_angle) const; // 04 - { return nullptr; }

		[[nodiscard]] static BGSPrimitiveLine* CreateAbstract(PRIMITIVE_TYPE a_type, const NiPoint3& a_point, const NiColorA& a_color)
		{
			using FuncType = decltype(&BGSPrimitive::CreateAbstract);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSPrimitive::CreateAbstract };
			return std::invoke(FUNC, a_type, a_point, a_color);
		}

		// members
		REX::Enum<PRIMITIVE_TYPE, std::int32_t> type; // 08
		NiPoint3 radii;								  // 0C
		NiPointer<BSFadeNode> node;					  // 18
	};
	static_assert(sizeof(BGSPrimitive) == 0x20);
}
