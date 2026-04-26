#pragma once

#include "RE/B/BSISoundDescriptor.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class BGSSoundDescriptor;

	class __declspec(novtable) BGSSoundDescriptorForm
		: public TESForm,			// 00
		  public BSISoundDescriptor // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSoundDescriptorForm };
		inline static constexpr auto VTABLE{ VTABLE::BGSSoundDescriptorForm };
		inline static constexpr auto FORM_TYPE{ FormType::kSoundDescriptor };

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
		BGSSoundDescriptor* impl; // 28
	};
	static_assert(sizeof(BGSSoundDescriptorForm) == 0x30);
}
