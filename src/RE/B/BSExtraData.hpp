#pragma once

#include "RE/E/EXTRA_DATA_TYPE.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class __declspec(novtable) BSExtraData
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSExtraData;
		inline static constexpr const auto& VTABLE = VTABLE::BSExtraData;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::None;

		BSExtraData()
		{
			REL::EmplaceVtable(this);
		}

		explicit BSExtraData(EXTRA_DATA_TYPE a_type) :
			type(a_type)
		{
			REL::EmplaceVtable(this);
		}

		BSExtraData(const BSExtraData&) = delete;
		BSExtraData(BSExtraData&&) = delete;

		auto operator=(const BSExtraData&) -> BSExtraData& = delete;
		auto operator=(BSExtraData&&) -> BSExtraData& = delete;

		virtual ~BSExtraData() = default; // 0x00

		// add
		virtual auto CompareImpl(const BSExtraData& a_compare) const -> bool;  // 0x01 - { return false; }
		virtual auto CompareForUI(const BSExtraData* a_compare) const -> bool; // 0x02

		GAME_HEAP_REDEFINE_NEW(BSExtraData);

		[[nodiscard]]
		auto GetExtraType() const noexcept -> EXTRA_DATA_TYPE
		{
			return type.get();
		}

		[[nodiscard]]
		auto Compare(const BSExtraData& a_compare) const -> bool
		{
			if (type != a_compare.type) {
				return false;
			}

			return CompareImpl(a_compare);
		}

		// members
		BSExtraData* next{nullptr};											  // 0x08
		std::uint16_t flags{0};												  // 0x10
		REX::Enum<EXTRA_DATA_TYPE, std::uint8_t> type{EXTRA_DATA_TYPE::None}; // 0x12
	};

	static_assert(sizeof(BSExtraData) == 0x18);
}
