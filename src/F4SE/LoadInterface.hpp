#pragma once

#include "F4SE/QueryInterface.hpp"

namespace F4SE
{
	class LoadInterface final : public QueryInterface
	{
	public:
		LoadInterface() = delete;
		~LoadInterface() = delete;

		LoadInterface(const LoadInterface&) = delete;
		LoadInterface(LoadInterface&&) = delete;

		auto operator=(const LoadInterface&) -> LoadInterface& = delete;
		auto operator=(LoadInterface&&) -> LoadInterface& = delete;
	};

	static_assert(std::is_empty_v<LoadInterface>);
}
