#pragma once

#include "RE/Bethesda/BSResource/AsyncStream.hpp"
#include "RE/Bethesda/BSResource/BSResourceEnums.hpp"
#include "RE/Bethesda/BSResource/Entry.hpp"
#include "RE/Bethesda/BSResource/GlobalLocations.hpp"
#include "RE/Bethesda/BSResource/GlobalPaths.hpp"
#include "RE/Bethesda/BSResource/Location.hpp"
#include "RE/Bethesda/BSResource/LooseFileStreamBase.hpp"
#include "RE/Bethesda/BSResource/Stream.hpp"
#include "RE/Bethesda/BSResource/StreamBase.hpp"

namespace RE::BSResource
{
	[[nodiscard]] ErrorCode GetOrCreateStream(const char* a_fileName, BSTSmartPointer<Stream>& a_result, bool a_writable = false, Location* a_optionalStart = nullptr);

	inline void RegisterLocation(Location* a_location, std::uint32_t a_priority)
	{
		using func_t = decltype(&RegisterLocation);
		static REL::Relocation<func_t> func{ REL::ID(918408) };
		return func(a_location, a_priority);
	}
}
