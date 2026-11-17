#pragma once

#include "RE/B/BSStorage.hpp"

namespace RE::BSStorageDefs
{
	enum class ErrorCode : std::int32_t;
	enum class SeekMode : std::int32_t;
}

namespace RE
{
	class __declspec(novtable) BSMemStorage : public BSStorage // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSMemStorage;
		inline static constexpr const auto& VTABLE = VTABLE::BSMemStorage;

		using BSStorage::value_type;
		using BSStorage::size_type;
		using BSStorage::difference_type;
		using BSStorage::pointer;
		using BSStorage::const_pointer;

		~BSMemStorage() override; // 0x00

		// override BSStorage
		auto GetSize() const -> size_type override;		// 0x01 - { return bufferSize; }
		auto GetPosition() const -> size_type override; // 0x02 - { return currentPosition; }
		auto Seek(size_type a_offset, BSStorageDefs::SeekMode a_seekMode) const
			-> BSStorageDefs::ErrorCode override;												   // 0x03
		auto Read(size_type a_size, pointer a_buffer) const -> BSStorageDefs::ErrorCode override;  // 0x04
		auto Write(size_type a_size, const_pointer a_buffer) -> BSStorageDefs::ErrorCode override; // 0x05

		// members
		size_type bufferSize;	   // 0x20
		size_type currentPosition; // 0x28
		const_pointer buffer;	   // 0x30
	};

	static_assert(sizeof(BSMemStorage) == 0x38);
}
