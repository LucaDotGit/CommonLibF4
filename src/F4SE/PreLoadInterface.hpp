#pragma once

#include "F4SE/QueryInterface.hpp"

namespace F4SE
{
	class PreLoadInterface final : public QueryInterface
	{
	public:
		PreLoadInterface() = delete;
		~PreLoadInterface() = delete;

		PreLoadInterface(const PreLoadInterface&) = delete;
		PreLoadInterface(PreLoadInterface&&) = delete;

		auto operator=(const PreLoadInterface&) -> PreLoadInterface& = delete;
		auto operator=(PreLoadInterface&&) -> PreLoadInterface& = delete;
	};

	static_assert(std::is_empty_v<PreLoadInterface>);
}
