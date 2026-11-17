#pragma once

#include "RE/I/ImageSpaceBaseData.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESTexture.hpp"

namespace RE
{
	class NiTexture;

	class __declspec(novtable) TESImageSpace : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESImageSpace;
		inline static constexpr const auto& VTABLE = VTABLE::TESImageSpace;
		inline static constexpr auto FORM_TYPE = FormType::ImageSpace;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		// members
		ImageSpaceBaseData data;		   // 0x20
		TESTexture lutTexture;			   // 0x78
		NiPointer<NiTexture> niLutTexture; // 0x88
	};

	static_assert(sizeof(TESImageSpace) == 0x90);
}
