#include "REX/Logging/Sinks/FileSink.hpp"

namespace REX::Logging::Sinks
{
	FileSink::FileSink(std::filesystem::path a_filePath) :
		IFileSink(std::move(a_filePath))
	{
	}

	FileSink::~FileSink() noexcept = default;

	void FileSink::Log([[maybe_unused]] const REX::Logging::Context& a_context, std::string_view a_formattedMessage)
	{
		WriteStream(a_formattedMessage);
	}
}
