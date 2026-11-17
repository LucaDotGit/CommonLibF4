#pragma once

#include "RE/B/BSResource_ErrorCode.hpp"
#include "RE/B/BSResource_Stream.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiBinaryStream.hpp"

namespace RE::BSResource
{
	class Location;
}

namespace RE
{
	class __declspec(novtable) BSResourceNiBinaryStream : public NiBinaryStream // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSResourceNiBinaryStream;
		inline static constexpr const auto& VTABLE = VTABLE::BSResourceNiBinaryStream;

		class BufferType;

		BSResourceNiBinaryStream();

		explicit BSResourceNiBinaryStream(
			const char* a_name,
			bool a_writeable = false,
			BSResource::Location* a_optionalStart = nullptr,
			bool a_fullReadHint = false);

		BSResourceNiBinaryStream(const BSResourceNiBinaryStream&) = delete;
		BSResourceNiBinaryStream(BSResourceNiBinaryStream&&) noexcept = default;

		auto operator=(const BSResourceNiBinaryStream&) -> BSResourceNiBinaryStream& = delete;
		auto operator=(BSResourceNiBinaryStream&&) noexcept -> BSResourceNiBinaryStream& = default;

		~BSResourceNiBinaryStream() override; // 0x00

		// override (NiBinaryStream)
		explicit operator bool() const noexcept override // 0x01
		{
			return good();
		}

		void Seek(std::ptrdiff_t a_numBytes) override; // 0x02

		auto GetPosition() const noexcept -> std::size_t override // 0x03
		{
			return streamPosition;
		}

		void GetBufferInfo(BufferInfo& a_buffer) override;								   // 0x04
		auto DoRead(void* a_buffer, std::size_t a_toRead) -> std::size_t override;		   // 0x05
		auto DoWrite(const void* a_buffer, std::size_t a_toWrite) -> std::size_t override; // 0x05

		[[nodiscard]]
		auto good() const -> bool
		{
			return static_cast<bool>(stream);
		}

		// members
		BSTSmartPointer<BSResource::Stream> stream;					  // 0x10
		BufferType* buffer{nullptr};								  // 0x18
		std::size_t streamPosition{0};								  // 0x20
		BSResource::ErrorCode lastError{BSResource::ErrorCode::None}; // 0x28
	};

	static_assert(sizeof(BSResourceNiBinaryStream) == 0x30);

	[[nodiscard]]
	auto BinaryStreamWithRescan(const char* a_fileName) -> BSResourceNiBinaryStream*;
}
