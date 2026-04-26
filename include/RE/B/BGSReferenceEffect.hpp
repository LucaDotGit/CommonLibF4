#pragma once

#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSReferenceEffect
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSReferenceEffect };
		inline static constexpr auto VTABLE{ VTABLE::BGSReferenceEffect };
		inline static constexpr auto FORM_TYPE{ FormType::kVisualEffect };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kFaceTarget = 1 << 0,
			kAttachToCamera = 1 << 1,
			kInheritRotation = 1 << 2
		};

		class Data
		{
		public:
			// members
			BGSArtObject* artObject;				  // 00
			TESEffectShader* effectShader;			  // 08
			REX::EnumSet<Flags, std::uint32_t> flags; // 10
		};
		static_assert(sizeof(Data) == 0x18);

		// members
		Data data; // 20
	};
	static_assert(sizeof(BGSReferenceEffect) == 0x38);
}
