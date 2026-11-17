#pragma once

#include "RE/E/EquippedItem.hpp"
#include "RE/N/NiRefObject.hpp"

namespace RE
{
	class BGSLoadFormBuffer;
	class BGSSaveFormBuffer;

	class __declspec(novtable) EquippedItemData : public NiRefObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::EquippedItemData;
		inline static constexpr const auto& VTABLE = VTABLE::EquippedItemData;

		// add
		virtual void SaveGame(BGSSaveFormBuffer* a_saveGameBuffer, const EquippedItem& a_equippedItem)
			const = 0;																						// 0x02
		virtual void LoadGame(BGSLoadFormBuffer* a_loadGameBuffer, const EquippedItem& a_equippedItem) = 0; // 0x03
		virtual auto GetObjectType() const -> std::uint32_t = 0;											// 0x04
	};

	static_assert(sizeof(EquippedItemData) == 0x10);
}
