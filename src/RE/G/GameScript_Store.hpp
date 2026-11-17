#pragma once

#include "RE/B/BSScript_IStore.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSResource
{
	class Stream;
}

namespace RE::GameScript
{
	class __declspec(novtable) Store : public BSScript::IStore // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__Store;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__Store;

		~Store() override; // 0x00

		// override (BSScript::IStore)
		auto GetSize() const -> std::size_t override;	  // 0x01
		auto GetPosition() const -> std::size_t override; // 0x02 - { return currentPosition; }
		auto Seek(std::size_t a_offset, BSStorageDefs::SeekMode a_seekMode) const
			-> BSStorageDefs::ErrorCode override;														   // 0x03
		auto Read(std::size_t a_numBytes, std::byte* a_bytes) const -> BSStorageDefs::ErrorCode override;  // 0x04
		auto Write(std::size_t a_numBytes, const std::byte* a_bytes) -> BSStorageDefs::ErrorCode override; // 0x05
		auto Open(const char* a_path) -> bool override;													   // 0x06
		void Close() override;																			   // 0x07
		auto GetStoreName() const -> const BSFixedString& override; // 0x08 - { return ressourceName; }
		auto GetIsOpen() const -> bool override;					// 0x09 - { return open; }
		auto GetIsGood() const -> bool override;					// 0x0A - { return good; }
		auto GetIsEOF() const -> bool override;						// 0x0B

		// members
		std::size_t currentPosition;				// 0x20
		BSTSmartPointer<BSResource::Stream> stream; // 0x28
		BSFixedString ressourceName;				// 0x30
		bool open;									// 0x38
		bool good;									// 0x39
	};

	static_assert(sizeof(Store) == 0x40);
}
