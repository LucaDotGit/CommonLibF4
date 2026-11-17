#pragma once

namespace RE
{
#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'265)
#endif

	class __declspec(novtable) BSIReverbType
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSIReverbType;
		inline static constexpr const auto& VTABLE = VTABLE::BSIReverbType;

		// add
		virtual auto DoGetRoomLevel() const -> std::int32_t = 0;	   // 0x00
		virtual auto DoGetRoomHFLevel() const -> std::int32_t = 0;	   // 0x01
		virtual auto DoGetDecayTime() const -> REX::Float32 = 0;	   // 0x02
		virtual auto DoGetDecayHFRatio() const -> REX::Float32 = 0;	   // 0x03
		virtual auto DoGetReflectionLevel() const -> std::int32_t = 0; // 0x04
		virtual auto DoGetReflectionDelay() const -> REX::Float32 = 0; // 0x05
		virtual auto DoGetReverbLevel() const -> std::int32_t = 0;	   // 0x06
		virtual auto DoGetReverbDelay() const -> REX::Float32 = 0;	   // 0x07
		virtual auto DoGetDiffusion() const -> REX::Float32 = 0;	   // 0x08
		virtual auto DoGetDensity() const -> REX::Float32 = 0;		   // 0x09
		virtual auto DoGetHFReference() const -> REX::Float32 = 0;	   // 0x0A
	};

	static_assert(sizeof(BSIReverbType) == 0x08);

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif
}
