#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiProperty;

	class __declspec(novtable) BSMaterialObject
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSMaterialObject;
		inline static constexpr const auto& VTABLE = VTABLE::BSMaterialObject;

		class DIRECTIONAL_DATA
		{
		public:
			// members
			REX::Float32 falloffScale;	  // 0x00
			REX::Float32 falloffBias;	  // 0x04
			REX::Float32 noiseUVScale;	  // 0x08
			REX::Float32 materialUVScale; // 0x0C
			NiPoint3 projectionDir;		  // 0x10
			REX::Float32 normalDampener;  // 0x1C
			REX::Float32 red;			  // 0x20
			REX::Float32 green;			  // 0x24
			REX::Float32 blue;			  // 0x28
			std::int32_t singlePass;	  // 0x2C
		};

		static_assert(sizeof(DIRECTIONAL_DATA) == 0x30);

		virtual ~BSMaterialObject(); // 0x00

		// add
		virtual void EnsureLoaded(); // 0x01 - { return; }

		// members
		DIRECTIONAL_DATA directionalData;		  // 0x08
		BSTArray<NiPointer<NiProperty>> property; // 0x38
	};

	static_assert(sizeof(BSMaterialObject) == 0x50);
}
