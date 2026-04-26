#pragma once

#include "RE/B/BSSimpleList.hpp"
#include "RE/P/PATH_DATA.hpp"
#include "RE/T/TESCondition.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class NiFormArray;

	class __declspec(novtable) BGSCameraPath
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSCameraPath };
		inline static constexpr auto VTABLE{ VTABLE::BGSCameraPath };
		inline static constexpr auto FORM_TYPE{ FormType::kCameraPath };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		TESCondition conditions;			// 20
		BSSimpleList<BGSCameraShot*> shots; // 28
		PATH_DATA data;						// 38
		NiFormArray* childPaths;			// 40
		BGSCameraPath* parentPath;			// 48
		BGSCameraPath* prevPath;			// 50
	};
	static_assert(sizeof(BGSCameraPath) == 0x58);
}
