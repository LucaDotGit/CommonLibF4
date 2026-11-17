#pragma once

#include "REX/Logging/Sinks/IFileSink.hpp"

namespace REX
{
	class FileStream;
}

namespace REX::Logging
{
	class Context;
}

namespace REX::Logging::Sinks
{
	class FileSink final : public REX::Logging::Sinks::IFileSink
	{
	public:
		explicit FileSink(std::filesystem::path a_filePath);
		~FileSink() noexcept override;

		FileSink(const FileSink&) = delete;
		FileSink(FileSink&&) = delete;

		auto operator=(const FileSink&) -> FileSink& = delete;
		auto operator=(FileSink&&) -> FileSink& = delete;

		void Log(const REX::Logging::Context& a_context, std::string_view a_formattedMessage) override;
	};
}
