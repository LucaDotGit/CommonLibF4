#pragma once

#include "RE/E/EXTRA_DATA_TYPE.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class __declspec(novtable) BSExtraData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSExtraData };
		inline static constexpr auto VTABLE{ VTABLE::BSExtraData };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kNone };

		BSExtraData()
		{
			REL::EmplaceVtable(this);
		}

		explicit BSExtraData(EXTRA_DATA_TYPE a_type)
			: type(a_type)
		{
			REL::EmplaceVtable(this);
		}

		BSExtraData(const BSExtraData&) = delete;
		BSExtraData(BSExtraData&&) = delete;

		BSExtraData& operator=(const BSExtraData&) = delete;
		BSExtraData& operator=(BSExtraData&&) = delete;

		virtual ~BSExtraData() = default; // 00

		// add
		virtual bool CompareImpl(const BSExtraData& a_compare) const;  // 01 - { return false; }
		virtual bool CompareForUI(const BSExtraData* a_compare) const; // 02

		GAME_HEAP_REDEFINE_NEW(BSExtraData);

		[[nodiscard]] EXTRA_DATA_TYPE GetExtraType() const noexcept { return *type; }

		// members
		BSExtraData* next{ nullptr };											 // 08
		std::uint16_t flags{ 0 };												 // 10
		REX::Enum<EXTRA_DATA_TYPE, std::uint8_t> type{ EXTRA_DATA_TYPE::kNone }; // 12
	};
	static_assert(sizeof(BSExtraData) == 0x18);
}
