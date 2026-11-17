#pragma once

#include "RE/N/NiPoint3.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSTransform : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSTransform;
		inline static constexpr const auto& VTABLE = VTABLE::BGSTransform;
		inline static constexpr auto FORM_TYPE = FormType::Transform;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12,
				AroundOrigin = 1 << 16
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class TransformData
		{
		public:
			// members
			NiPoint3 position;	  // 0x00
			NiPoint3 rotation;	  // 0x0C
			REX::Float32 scale;	  // 0x18
			REX::Float32 minZoom; // 0x1C
			REX::Float32 maxZoom; // 0x20
		};

		static_assert(sizeof(TransformData) == 0x24);

		// members
		TransformData data; // 0x20
	};

	static_assert(sizeof(BGSTransform) == 0x48);
}
