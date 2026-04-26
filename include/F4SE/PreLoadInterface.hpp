#pragma once

#include "F4SE/QueryInterface.hpp"

namespace F4SE
{
	class PreLoadInterface final
		: public QueryInterface
	{
	public:
		PreLoadInterface() = delete;
		~PreLoadInterface() = delete;

		PreLoadInterface(const PreLoadInterface&) = delete;
		PreLoadInterface(PreLoadInterface&&) = delete;

		PreLoadInterface& operator=(const PreLoadInterface&) = delete;
		PreLoadInterface& operator=(PreLoadInterface&&) = delete;
	};
	static_assert(std::is_empty_v<PreLoadInterface>);
}
