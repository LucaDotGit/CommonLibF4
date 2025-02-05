#pragma once

#include "RE/NetImmerse/NiPoint.hpp"
#include "RE/NetImmerse/NiSmartPointer.hpp"

namespace RE
{
	class BSFadeNode;
	class BSMultiBoundShape;
	class NiColorA;

	class __declspec(novtable) BGSPrimitive
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSPrimitive };
		inline static constexpr auto VTABLE{ VTABLE::BGSPrimitive };

		enum class PRIMITIVE_TYPE
		{
			kNone,
			kBox,
			kSphere,
			kPlane,
			kLine,
			kEllipsoid
		};

		virtual ~BGSPrimitive(); // 00

		// add
		virtual void SetColor(const NiColorA& a_color) = 0;																   // 01
		virtual void SetRadii(const NiPoint3& a_radii) = 0;																   // 02
		virtual bool IsInside(const NiPoint3& a_point) const = 0;														   // 03
		virtual BSMultiBoundShape* MakeMultiBoundShape([[maybe_unused]] const NiPoint3& a_angle) const { return nullptr; } // 04

		// members
		REX::Enum<PRIMITIVE_TYPE, std::uint32_t> type; // 08
		NiPoint3 radii;								   // 0C
		NiPointer<BSFadeNode> node;					   // 18
	};
	static_assert(sizeof(BGSPrimitive) == 0x20);
}
