#pragma once

#include "RE/B/BGSKeywordForm.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/T/TESBoundObject.hpp"

namespace RE
{
	class __declspec(novtable) BGSArtObject
		: public TESBoundObject,	  // 00
		  public BGSKeywordForm,	  // 68
		  public BGSModelMaterialSwap // 88
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSArtObject };
		inline static constexpr auto VTABLE{ VTABLE::BGSArtObject };
		inline static constexpr auto FORM_TYPE{ FormType::kArtObject };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class ArtType : std::int32_t
		{
			kMagicCastingArt = 0,
			kMagicHitEffect = 1,
			kMagicEnchantEffect = 2,

			kTotal = 3
		};

		class Data
		{
		public:
			// members
			REX::Enum<ArtType, std::int32_t> artType; // 00
		};
		static_assert(sizeof(Data) == 0x04);

		// members
		Data data; // C8
	};
	static_assert(sizeof(BGSArtObject) == 0xD0);
}
