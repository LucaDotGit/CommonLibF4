#pragma once

#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSReferenceEffect : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSReferenceEffect;
		inline static constexpr const auto& VTABLE = VTABLE::BGSReferenceEffect;
		inline static constexpr auto FORM_TYPE = FormType::VisualEffect;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			None = 0,
			FaceTarget = 1 << 0,
			AttachToCamera = 1 << 1,
			InheritRotation = 1 << 2
		};

		class Data
		{
		public:
			// members
			BGSArtObject* artObject;				  // 0x00
			TESEffectShader* effectShader;			  // 0x08
			REX::EnumSet<Flags, std::uint32_t> flags; // 0x10
		};

		static_assert(sizeof(Data) == 0x18);

		// members
		Data data; // 0x20
	};

	static_assert(sizeof(BGSReferenceEffect) == 0x38);
}
