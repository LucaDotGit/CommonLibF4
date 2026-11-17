#include "REX/Contract.hpp"

#include "REX/Logging/Level.hpp"
#include "REX/Message.hpp"
#include "REX/SourceLocation.hpp"
#include "REX/System.hpp"

#if (NDEBUG == 0)
#include "REX/EnumSet.hpp"
#include "REX/W32/KERNEL32.hpp"
#include "REX/W32/USER32.hpp"
#endif

namespace REX::Impl
{
	namespace
	{
#if (NDEBUG == 0)
		constexpr auto ASSERT_MESSAGE_BOX_FLAGS = REX::EnumSet(
			MessageBoxFlags::MB_SYSTEMMODAL,
			MessageBoxFlags::MB_SETFOREGROUND,
			MessageBoxFlags::MB_TOPMOST,
			MessageBoxFlags::MB_ABORTRETRYIGNORE);

		void Terminate(REX::MessageBoxResult a_messageBoxResult) noexcept
		{
			switch (a_messageBoxResult) {
				case REX::W32::IDABORT: {
					REX::W32::TerminateCurrentProcess(EXIT_FAILURE);
				}
				case REX::W32::IDRETRY: {
					REX::W32::DebugBreak();
					break;
				}
				case REX::W32::IDIGNORE: {
					break;
				}
				[[unlikely]]
				default: {
					REX::W32::TerminateCurrentProcess(EXIT_FAILURE);
				}
			}
		}
#endif
	}

	void EnsureFail(std::string_view a_format, REX::SourceLocation a_location) noexcept
	{
		REX::ShowSourceMessage(REX::Logging::Level::Critical, a_format, a_location);
		REX::Terminate(EXIT_FAILURE);
	}

	void EnsureFail(std::wstring_view a_format, REX::SourceLocation a_location) noexcept
	{
		REX::ShowSourceMessage(REX::Logging::Level::Critical, a_format, a_location);
		REX::Terminate(EXIT_FAILURE);
	}

#if (NDEBUG == 0)
	void AssumeFail(std::string_view a_format, REX::SourceLocation a_location) noexcept
	{
		REX::ShowSourceMessage(REX::Logging::Level::Critical, a_format, a_location);
		REX::Terminate(EXIT_FAILURE);
	}

	void AssumeFail(std::wstring_view a_format, REX::SourceLocation a_location) noexcept
	{
		REX::ShowSourceMessage(REX::Logging::Level::Critical, a_format, a_location);
		REX::Terminate(EXIT_FAILURE);
	}

	void AssertFail(std::string_view a_format, REX::SourceLocation a_location) noexcept
	{
		const auto messageBoxResult = REX::ShowSourceMessage(
			REX::Logging::Level::Error,
			a_format,
			Impl::ASSERT_MESSAGE_BOX_FLAGS.get(),
			a_location);

		Impl::Terminate(messageBoxResult);
	}

	void AssertFail(std::wstring_view a_format, REX::SourceLocation a_location) noexcept
	{
		const auto messageBoxResult = REX::ShowSourceMessage(
			REX::Logging::Level::Error,
			a_format,
			Impl::ASSERT_MESSAGE_BOX_FLAGS.get(),
			a_location);

		Impl::Terminate(messageBoxResult);
	}
#endif
}
