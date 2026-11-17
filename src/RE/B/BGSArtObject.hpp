#pragma once

#include "RE/B/BGSKeywordForm.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/T/TESBoundObject.hpp"

namespace RE
{
	class __declspec(novtable) BGSArtObject :
		public TESBoundObject,		// 0x00
		public BGSKeywordForm,		// 0x68
		public BGSModelMaterialSwap // 0x88
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSArtObject;
		inline static constexpr const auto& VTABLE = VTABLE::BGSArtObject;
		inline static constexpr auto FORM_TYPE = FormType::ArtObject;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class ArtType : std::int32_t
		{
			MagicCastingArt = 0,
			MagicHitEffect = 1,
			MagicEnchantEffect = 2,

			_Count = 3
		};

		class Data
		{
		public:
			// members
			REX::Enum<ArtType, std::int32_t> artType; // 0x00
		};

		static_assert(sizeof(Data) == 0x04);

		~BGSArtObject() override; // 0x00

		// members
		Data data; // 0xC8
	};

	static_assert(sizeof(BGSArtObject) == 0xD0);
}
