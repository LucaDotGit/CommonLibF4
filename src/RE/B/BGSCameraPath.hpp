#pragma once

#include "RE/B/BSSimpleList.hpp"
#include "RE/P/PATH_DATA.hpp"
#include "RE/T/TESCondition.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class NiFormArray;

	class __declspec(novtable) BGSCameraPath : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSCameraPath;
		inline static constexpr const auto& VTABLE = VTABLE::BGSCameraPath;
		inline static constexpr auto FORM_TYPE = FormType::CameraPath;

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
		TESCondition conditions;			// 0x20
		BSSimpleList<BGSCameraShot*> shots; // 0x28
		PATH_DATA data;						// 0x38
		NiFormArray* childPaths;			// 0x40
		BGSCameraPath* parentPath;			// 0x48
		BGSCameraPath* prevPath;			// 0x50
	};

	static_assert(sizeof(BGSCameraPath) == 0x58);
}
