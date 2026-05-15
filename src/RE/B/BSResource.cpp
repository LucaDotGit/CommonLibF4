#include "RE/B/BSResource.hpp"

namespace RE::BSResource
{
	ErrorCode GetOrCreateStream(const char* a_fileName, BSTSmartPointer<Stream>& a_result, bool a_writable, Location* a_optionalStart)
	{
		using FuncType = decltype(&BSResource::GetOrCreateStream);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSResource::GetOrCreateStream };
		return std::invoke(FUNC, a_fileName, a_result, a_writable, a_optionalStart);
	}

	void RegisterLocation(Location* a_location, std::uint32_t a_priority)
	{
		using FuncType = decltype(&BSResource::RegisterLocation);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSResource::RegisterLocation };
		std::invoke(FUNC, a_location, a_priority);
	}
}
