#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/N/NiObject.hpp"

namespace RE
{
	class __declspec(novtable) NiExtraData : public NiObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiExtraData;
		inline static constexpr const auto& VTABLE = VTABLE::NiExtraData;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiExtraData;

		NiExtraData()
		{
			REL::EmplaceVtable(this);
		}

		explicit NiExtraData(BSFixedString a_name) :
			name(std::move(a_name))
		{
			REL::EmplaceVtable(this);
		}

		~NiExtraData() override = default; // 0x00

		// add
		virtual auto KeepForExport() const -> bool;		  // 0x28 - { return false; }
		virtual auto KeepForExporterOnly() const -> bool; // 0x29 - { return false; }
		virtual auto IsStreamable() const -> bool;		  // 0x2A - { return true; }
		virtual auto IsCloneable() const -> bool;		  // 0x2B - { return true; }

		[[nodiscard]]
		auto GetName() const noexcept -> BSFixedString
		{
			return name;
		}

		void SetName(BSFixedString a_name) noexcept
		{
			name = std::move(a_name);
		}

		// members
		BSFixedString name; // 0x10
	};

	static_assert(sizeof(NiExtraData) == 0x18);
}
