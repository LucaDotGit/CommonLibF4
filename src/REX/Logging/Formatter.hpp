#pragma once

#include "REX/Logging/IFormatter.hpp"

namespace REX::Logging
{
	class Context;

	class Formatter final : public REX::Logging::IFormatter
	{
	public:
		Formatter() noexcept = default;
		~Formatter() noexcept override = default;

		Formatter(const Formatter&) = delete;
		Formatter(Formatter&&) = delete;

		auto operator=(const Formatter&) -> Formatter& = delete;
		auto operator=(Formatter&&) -> Formatter& = delete;

		void Format(const REX::Logging::Context& a_context, std::pmr::string& a_buffer) const override;
	};
}
