#pragma once

#include "RE/B/BSStreamParserData.hpp"
#include "RE/N/NiBinaryStream.hpp"

namespace RE
{
	class BSStreamParserData;

	template <class T>
	class BSStreamParser
	{
	public:
		using value_type = T;

		static_assert(REX::win32_character<value_type>);

		explicit BSStreamParser(BSStreamParserData& a_data) :
			data(std::addressof(a_data))
		{
			auto* stream = a_data.GetStream();
			if (!stream) {
				return;
			}

			auto bufferInfo = NiBinaryStream::BufferInfo();
			stream->GetBufferInfo(bufferInfo);

			streamSizeInBytes = bufferInfo.fileSize;
		}

		~BSStreamParser() noexcept = default;

		BSStreamParser(BSStreamParser&&) = delete;
		BSStreamParser(const BSStreamParser&) = delete;

		auto operator=(BSStreamParser&&) -> BSStreamParser& = delete;
		auto operator=(const BSStreamParser&) -> BSStreamParser& = delete;

		// members
		std::array<value_type, REX::W32::MAX_FNAME> readBuffer; // 0x000
		value_type* readPosition{nullptr};						// 0x100
		BSStreamParserData* data;								// 0x108
		std::size_t streamSizeInBytes{0};						// 0x110
	};
}
