#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSStorage.hpp"

namespace RE::BSScript
{
	class __declspec(novtable) IStore : public BSStorage // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__IStore;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__IStore;

		~IStore() override = default; // 0x00

		// add
		virtual auto Open(const char* a_path) -> bool = 0;			   // 0x06
		virtual void Close() = 0;									   // 0x07
		virtual auto GetStoreName() const -> const BSFixedString& = 0; // 0x08
		virtual auto GetIsOpen() const -> bool = 0;					   // 0x09
		virtual auto GetIsGood() const -> bool = 0;					   // 0x0A
		virtual auto GetIsEOF() const -> bool = 0;					   // 0x0B
	};

	static_assert(sizeof(IStore) == 0x20);
}
