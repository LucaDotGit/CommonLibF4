#pragma once

#include "RE/N/NiPoint.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSTransform
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSTransform };
		inline static constexpr auto VTABLE{ VTABLE::BGSTransform };
		inline static constexpr auto FORM_TYPE{ FormType::kTransform };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kAroundOrigin = 1 << 16
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class TransformData
		{
		public:
			// members
			NiPoint3 position;	  // 00
			NiPoint3 rotation;	  // 0C
			REX::Float32 scale;	  // 18
			REX::Float32 minZoom; // 1C
			REX::Float32 maxZoom; // 20
		};
		static_assert(sizeof(TransformData) == 0x24);

		// members
		TransformData data; // 20
	};
	static_assert(sizeof(BGSTransform) == 0x48);
}
