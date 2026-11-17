#include "REX/Logging/Sinks/RotatingFileSink.hpp"

#include "REX/Error.hpp"
#include "REX/Exception.hpp"
#include "REX/IO.hpp"

namespace REX::Logging::Sinks
{
	RotatingFileSink::RotatingFileSink(
		std::filesystem::path a_filePath,
		std::size_t a_fileRotationCount,
		std::size_t a_fileRotationByteSize) :
		_fileRotationCount(a_fileRotationCount),
		_fileRotationByteSize(a_fileRotationByteSize)
	{
		RotateFiles(a_filePath);
		OpenStream(std::move(a_filePath));
	}

	RotatingFileSink::~RotatingFileSink() noexcept = default;

	void RotatingFileSink::Log(
		[[maybe_unused]] const REX::Logging::Context& a_context,
		std::string_view a_formattedMessage)
	{
		WriteStream(a_formattedMessage);

		_currentFileByteSize += a_formattedMessage.size();
		if (_fileRotationByteSize == 0 || _currentFileByteSize < _fileRotationByteSize) {
			return;
		}

		CloseStream();
		RotateFiles(_fileStream.GetPath());
		OpenStream(_fileStream.GetPath());

		_currentFileByteSize = 0;
	}

	void RotatingFileSink::RotateFiles(const std::filesystem::path& a_filePath) const
	{
		const auto rotateError = REX::RotateFile(a_filePath, _fileRotationCount);
		if (rotateError.value() != REX::ERROR_NUMBER_SUCCESS &&
			rotateError != REX::PosixErrorCode::no_such_file_or_directory) [[unlikely]] {
			REX::Throw<std::filesystem::filesystem_error>(rotateError.message(), rotateError);
		}
	}
}
