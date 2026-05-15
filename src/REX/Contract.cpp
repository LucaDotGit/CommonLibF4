#include "REX/Contract.hpp"

#include "REX/Log.hpp"
#include "REX/Message.hpp"
#include "REX/W32/KERNEL32.hpp"

#if NDEBUG == 0
#include "REX/EnumSet.hpp"
#include "REX/W32/USER32.hpp"
#endif

namespace REX::Impl
{
#if NDEBUG == 0
	static constexpr auto ASSERT_MESSAGE_BOX_FLAGS = REX::EnumSet(
		MessageBoxFlags::MB_SYSTEMMODAL,
		MessageBoxFlags::MB_SETFOREGROUND,
		MessageBoxFlags::MB_TOPMOST,
		MessageBoxFlags::MB_ABORTRETRYIGNORE);
#endif

	void Ensure(REX::SourceLocation a_location, std::string_view a_format) noexcept
	{
		REX::ShowSourceMessage(REX::LogLevel::kCritical, a_location, a_format);

		if (REX::W32::IsDebuggerPresent()) {
			REX::W32::DebugBreak();
		}

		REX::W32::TerminateCurrentProcess(EXIT_FAILURE);
	}

	void Ensure(REX::SourceLocation a_location, std::wstring_view a_format) noexcept
	{
		REX::ShowSourceMessage(REX::LogLevel::kCritical, a_location, a_format);

		if (REX::W32::IsDebuggerPresent()) {
			REX::W32::DebugBreak();
		}

		REX::W32::TerminateCurrentProcess(EXIT_FAILURE);
	}

#if NDEBUG == 0
	void Assume(REX::SourceLocation a_location, std::string_view a_format) noexcept
	{
		REX::ShowSourceMessage(REX::LogLevel::kCritical, a_location, a_format);

		if (REX::W32::IsDebuggerPresent()) {
			REX::W32::DebugBreak();
		}

		REX::W32::TerminateCurrentProcess(EXIT_FAILURE);
	}

	void Assume(REX::SourceLocation a_location, std::wstring_view a_format) noexcept
	{
		REX::ShowSourceMessage(REX::LogLevel::kCritical, a_location, a_format);

		if (REX::W32::IsDebuggerPresent()) {
			REX::W32::DebugBreak();
		}

		REX::W32::TerminateCurrentProcess(EXIT_FAILURE);
	}
#endif

#if NDEBUG == 0
	void Assert(REX::SourceLocation a_location, std::string_view a_format) noexcept
	{
		const auto messageBoxResult = REX::Impl::ShowSourceMessage(REX::LogLevel::kError, a_location, a_format, ASSERT_MESSAGE_BOX_FLAGS.get());
		switch (messageBoxResult) {
			case REX::W32::IDABORT: {
				REX::W32::TerminateCurrentProcess(EXIT_FAILURE);
				break;
			}
			case REX::W32::IDRETRY: {
				REX::W32::DebugBreak();
				break;
			}
			case REX::W32::IDIGNORE: {
				break;
			}
			[[unlikely]] default: {
				REX::W32::TerminateCurrentProcess(EXIT_FAILURE);
			}
		}
	}

	void Assert(REX::SourceLocation a_location, std::wstring_view a_format) noexcept
	{
		const auto messageBoxResult = REX::Impl::ShowSourceMessage(REX::LogLevel::kError, a_location, a_format, ASSERT_MESSAGE_BOX_FLAGS.get());
		switch (messageBoxResult) {
			case REX::W32::IDABORT: {
				REX::W32::TerminateCurrentProcess(EXIT_FAILURE);
				break;
			}
			case REX::W32::IDRETRY: {
				REX::W32::DebugBreak();
				break;
			}
			case REX::W32::IDIGNORE: {
				break;
			}
			[[unlikely]] default: {
				REX::W32::TerminateCurrentProcess(EXIT_FAILURE);
			}
		}
	}
#endif
}
