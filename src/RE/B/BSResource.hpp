#pragma once

#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSResource
{
	enum class ErrorCode : std::int32_t;

	class Location;
	class Stream;

	auto GetOrCreateStream(
		const char* a_fileName,
		BSTSmartPointer<Stream>& a_result,
		bool a_writable,
		Location* a_optionalStart) -> ErrorCode;
	void RegisterLocation(Location* a_location, std::uint32_t a_priority);
}
