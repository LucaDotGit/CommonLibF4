#pragma once

#include "REX/Logging/Sinks/IFileSink.hpp"

namespace REX::Logging
{
	class Context;
}

namespace REX::Logging::Sinks
{
	class RotatingFileSink final : public REX::Logging::Sinks::IFileSink
	{
	public:
		RotatingFileSink(
			std::filesystem::path a_filePath,
			std::size_t a_fileRotationCount,
			std::size_t a_fileRotationByteSize);
		~RotatingFileSink() noexcept override;

		RotatingFileSink(const RotatingFileSink&) = delete;
		RotatingFileSink(RotatingFileSink&&) = delete;

		auto operator=(const RotatingFileSink&) -> RotatingFileSink& = delete;
		auto operator=(RotatingFileSink&&) -> RotatingFileSink& = delete;

		[[nodiscard]]
		auto GetFileRotationCount() const noexcept
		{
			return _fileRotationCount;
		}

		[[nodiscard]]
		auto GetFileRotationByteSize() const noexcept
		{
			return _fileRotationByteSize;
		}

		void Log(const REX::Logging::Context& a_context, std::string_view a_formattedMessage) override;

	private:
		void RotateFiles(const std::filesystem::path& a_filePath) const;

		std::size_t _fileRotationCount;
		std::size_t _fileRotationByteSize;
		std::size_t _currentFileByteSize{0};
	};
}
