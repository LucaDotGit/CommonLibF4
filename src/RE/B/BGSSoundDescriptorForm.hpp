#pragma once

#include "RE/B/BSISoundDescriptor.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class BGSSoundDescriptor;

	class __declspec(novtable) BGSSoundDescriptorForm :
		public TESForm,			  // 0x00
		public BSISoundDescriptor // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSSoundDescriptorForm;
		inline static constexpr const auto& VTABLE = VTABLE::BGSSoundDescriptorForm;
		inline static constexpr auto FORM_TYPE = FormType::SoundDescriptor;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		~BGSSoundDescriptorForm() override; // 0x00

		// members
		BGSSoundDescriptor* impl; // 0x28
	};

	static_assert(sizeof(BGSSoundDescriptorForm) == 0x30);
}
