#pragma once

#include "REX/FileStream.hpp"
#include "REX/Logging/ISink.hpp"

namespace REX::Logging::Sinks
{
	class IFileSink : public REX::Logging::ISink
	{
	public:
		IFileSink() noexcept;
		explicit IFileSink(std::filesystem::path a_filePath);

		~IFileSink() noexcept override;

		IFileSink(const IFileSink&) = delete;
		IFileSink(IFileSink&&) = delete;

		auto operator=(const IFileSink&) -> IFileSink& = delete;
		auto operator=(IFileSink&&) -> IFileSink& = delete;

		void Flush() override;

	protected:
		void OpenStream(std::filesystem::path a_filePath);
		void FlushStream();
		void CloseStream();
		void WriteStream(std::string_view a_message);

		REX::FileStream _fileStream;
	};
}
