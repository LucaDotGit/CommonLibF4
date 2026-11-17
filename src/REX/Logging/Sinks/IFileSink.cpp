#include "REX/Logging/Sinks/IFileSink.hpp"

#include "REX/Contract.hpp"
#include "REX/Error.hpp"
#include "REX/Exception.hpp"
#include "REX/FileStream.hpp"

namespace REX::Logging::Sinks
{
	IFileSink::IFileSink() noexcept = default;

	IFileSink::IFileSink(std::filesystem::path a_filePath)
	{
		OpenStream(std::move(a_filePath));
	}

	IFileSink::~IFileSink() noexcept = default;

	void IFileSink::Flush()
	{
		FlushStream();
	}

	void IFileSink::OpenStream(std::filesystem::path a_filePath)
	{
		REX::Assert(!_fileStream.IsOpen());

		auto newFileStream = REX::FileStream::Open(
			std::move(a_filePath),
			FileMode::Create,
			FileAccess::Write,
			FileShare::Read,
			FileOptions::SequentialScan,
			REX::SMALL_FILE_BUFFER_OPTIONS);
		if (!newFileStream.has_value()) [[unlikely]] {
			REX::Throw<std::filesystem::filesystem_error>(newFileStream.error().message(), newFileStream.error());
		}

		_fileStream = std::move(newFileStream).value();
	}

	void IFileSink::FlushStream()
	{
		const auto flushError = _fileStream.Flush();
		if (flushError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			REX::Throw<std::filesystem::filesystem_error>(flushError.message(), flushError);
		}
	}

	void IFileSink::CloseStream()
	{
		const auto closeError = _fileStream.Close();
		if (closeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			REX::Throw<std::filesystem::filesystem_error>(closeError.message(), closeError);
		}
	}

	void IFileSink::WriteStream(std::string_view a_message)
	{
		const auto writeError = _fileStream.WriteText(a_message);
		if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			REX::Throw<std::filesystem::filesystem_error>(writeError.message(), writeError);
		}
	}
}
