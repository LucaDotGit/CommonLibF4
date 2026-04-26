#pragma once

#include "RE/B/BSMaterialObject.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) BGSMaterialObject
		: public TESForm,		  // 00
		  public TESModel,		  // 20
		  public BSMaterialObject // 50
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMaterialObject };
		inline static constexpr auto VTABLE{ VTABLE::BGSMaterialObject };
		inline static constexpr auto FORM_TYPE{ FormType::kMaterialObject };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class FILE_DATA
		{
		public:
			// members
			std::byte* buffer;		  // 00
			std::uint32_t bufferSize; // 08
		};
		static_assert(sizeof(FILE_DATA) == 0x10);

		// members
		BSTArray<FILE_DATA> fileDataArray; // A0
	};
	static_assert(sizeof(BGSMaterialObject) == 0xB8);
}
