#include "F4SE/PluginVersionData.hpp"

#include "REX/Message.hpp"
#include "REX/W32/KERNEL32.hpp"

namespace F4SE
{
	auto PluginVersionData::GetSingleton() noexcept -> REX::NotNull<REX::Observer<const PluginVersionData*>>
	{
		static const auto* INSTANCE = []() noexcept {
			const auto* result = reinterpret_cast<const PluginVersionData*>(REX::W32::GetProcAddress(REX::W32::GetCurrentModule(), "F4SEPlugin_Version"));
			if (!result) [[unlikely]] {
				const auto currentError = REX::GetCurrentSystemError();
				REX::Fail(
					"Failed to get plugin version data singleton.\n"
					"System Error (0x{:08X}): {}"sv,
					currentError.value(), currentError.message());
			}

			return result;
		}();

		return INSTANCE;
	}
}
