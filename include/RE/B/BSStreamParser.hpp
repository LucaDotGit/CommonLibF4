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
		BSStreamParser(BSStreamParserData* a_data)
			: data(a_data)
		{
			if (!a_data) {
				return;
			}

			auto* stream = a_data->GetStream();
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

		BSStreamParser& operator=(BSStreamParser&&) = delete;
		BSStreamParser& operator=(const BSStreamParser&) = delete;

		// members
		std::array<T, REX::W32::MAX_FNAME> readBuffer; // 000
		T* readPosition{ 0 };						   // 100
		BSStreamParserData* data;					   // 108
		std::size_t streamSizeInBytes{ 0 };			   // 110
	};
	static_assert(sizeof(BSStreamParser<char>) == 0x118);
	static_assert(sizeof(BSStreamParser<wchar_t>) == 0x218);

	extern template class BSStreamParser<char>;
	extern template class BSStreamParser<wchar_t>;
}
