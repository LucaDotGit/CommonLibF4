#pragma once

#include "RE/B/BSMaterialObject.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) BGSMaterialObject :
		public TESForm,			// 0x00
		public TESModel,		// 0x20
		public BSMaterialObject // 0x50
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSMaterialObject;
		inline static constexpr const auto& VTABLE = VTABLE::BGSMaterialObject;
		inline static constexpr auto FORM_TYPE = FormType::MaterialObject;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class FILE_DATA
		{
		public:
			// members
			std::byte* buffer;		  // 0x00
			std::uint32_t bufferSize; // 0x08
		};

		static_assert(sizeof(FILE_DATA) == 0x10);

		// members
		BSTArray<FILE_DATA> fileDataArray; // 0xA0
	};

	static_assert(sizeof(BGSMaterialObject) == 0xB8);
}
