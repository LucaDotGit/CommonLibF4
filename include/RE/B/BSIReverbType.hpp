#pragma once

namespace RE
{
	class __declspec(novtable) BSIReverbType
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSIReverbType };
		inline static constexpr auto VTABLE{ VTABLE::BSIReverbType };

		// add
		virtual std::int32_t DoGetRoomLevel() const = 0;	   // 00
		virtual std::int32_t DoGetRoomHFLevel() const = 0;	   // 01
		virtual REX::Float32 DoGetDecayTime() const = 0;	   // 02
		virtual REX::Float32 DoGetDecayHFRatio() const = 0;	   // 03
		virtual std::int32_t DoGetReflectionLevel() const = 0; // 04
		virtual REX::Float32 DoGetReflectionDelay() const = 0; // 05
		virtual std::int32_t DoGetReverbLevel() const = 0;	   // 06
		virtual REX::Float32 DoGetReverbDelay() const = 0;	   // 07
		virtual REX::Float32 DoGetDiffusion() const = 0;	   // 08
		virtual REX::Float32 DoGetDensity() const = 0;		   // 09
		virtual REX::Float32 DoGetHFReference() const = 0;	   // 0A
	};
	static_assert(sizeof(BSIReverbType) == 0x08);
}
