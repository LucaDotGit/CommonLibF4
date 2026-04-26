#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiProperty;

	class __declspec(novtable) BSMaterialObject
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSMaterialObject };
		inline static constexpr auto VTABLE{ VTABLE::BSMaterialObject };

		class DIRECTIONAL_DATA
		{
		public:
			// members
			REX::Float32 falloffScale;	  // 00
			REX::Float32 falloffBias;	  // 04
			REX::Float32 noiseUVScale;	  // 08
			REX::Float32 materialUVScale; // 0C
			NiPoint3 projectionDir;		  // 10
			REX::Float32 normalDampener;  // 1C
			REX::Float32 red;			  // 20
			REX::Float32 green;			  // 24
			REX::Float32 blue;			  // 28
			std::int32_t singlePass;	  // 2C
		};
		static_assert(sizeof(DIRECTIONAL_DATA) == 0x30);

		virtual ~BSMaterialObject(); // 00

		// add
		virtual void EnsureLoaded(); // 01 - { return; }

		// members
		DIRECTIONAL_DATA directionalData;		  // 08
		BSTArray<NiPointer<NiProperty>> property; // 38
	};
	static_assert(sizeof(BSMaterialObject) == 0x50);
}
