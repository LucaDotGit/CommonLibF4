#pragma once

#include "F4SE/QueryInterface.hpp"

namespace F4SE
{
	class LoadInterface final
		: public QueryInterface
	{
	public:
		LoadInterface() = delete;
		~LoadInterface() = delete;

		LoadInterface(const LoadInterface&) = delete;
		LoadInterface(LoadInterface&&) = delete;

		LoadInterface& operator=(const LoadInterface&) = delete;
		LoadInterface& operator=(LoadInterface&&) = delete;
	};
	static_assert(std::is_empty_v<LoadInterface>);
}
