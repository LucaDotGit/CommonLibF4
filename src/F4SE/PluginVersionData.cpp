#include "F4SE/PluginVersionData.hpp"

#include "REX/Error.hpp"
#include "REX/Message.hpp"
#include "REX/NotNull.hpp"
#include "REX/W32/KERNEL32.hpp"

namespace F4SE
{
	auto PluginVersionData::GetSingleton() noexcept -> const PluginVersionData&
	{
		static const auto INSTANCE = []() noexcept -> REX::NotNull<const PluginVersionData*> {
			const auto* result = static_cast<const PluginVersionData*>(
				REX::W32::GetProcAddress(REX::W32::GetCurrentModule(), "F4SEPlugin_Version"));
			if (!result) [[unlikely]] {
				const auto currentError = REX::GetCurrentSystemError();
				REX::Fail(
					"Failed to get the plugin version data instance.\n"
					"System Error (0x{:08X}): {}"sv,
					currentError.value(),
					currentError.message());
			}

			return result;
		}();

		return *(INSTANCE.get());
	}
}
