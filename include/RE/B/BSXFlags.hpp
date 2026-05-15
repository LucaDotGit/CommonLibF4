#pragma once

#include "RE/N/NiIntegerExtraData.hpp"
#include "RE/N/NiObjectNET.hpp"

namespace RE
{
	class __declspec(novtable) BSXFlags
		: public NiIntegerExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSXFlags };
		inline static constexpr auto VTABLE{ VTABLE::BSXFlags };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::BSXFlags };

		enum class Flag : std::int32_t
		{
			kNone = 0,
			kAnimated = 1 << 0,
			kHavok = 1 << 1,
			kRagdoll = 1 << 2,
			kComplex = 1 << 3,
			kAddon = 1 << 4,
			kEditorMarker = 1 << 5,
			kDynamic = 1 << 6,
			kArticulated = 1 << 7,
			kNeedsTransformUpdate = 1 << 8,
			kExternalEmit = 1 << 9,
			kMagicShaderParticles = 1 << 10,
			kLights = 1 << 11,
			kBreakable = 1 << 12,
			kSearchedBreakable = 1 << 13
		};

		BSXFlags()
			: NiIntegerExtraData(GetExtraName(), 0)
		{
			REL::EmplaceVtable(this);
		}

		explicit BSXFlags(Flag a_value)
			: NiIntegerExtraData(GetExtraName(), static_cast<std::int32_t>(a_value))
		{
			REL::EmplaceVtable(this);
		}

		[[nodiscard]] Flag GetFlags() const noexcept { return static_cast<Flag>(value); }
		void SetFlags(Flag a_value) noexcept { value = static_cast<std::int32_t>(a_value); }

		[[nodiscard]] static NiPointer<BSXFlags> Find(NiObjectNET* a_object) noexcept
		{
			if (!a_object) {
				return nullptr;
			}

			return dynamic_ni_pointer_cast<BSXFlags>(a_object->GetExtraData(BSFixedString("BSX"sv)));
		}

		[[nodiscard]] static const BSFixedString& GetExtraName()
		{
			static const auto EXTRA_NAME = BSFixedString("BSX"sv);
			return EXTRA_NAME;
		}
	};
	static_assert(sizeof(BSXFlags) == 0x20);
}
