#pragma once

namespace REX::Logging
{
	class Context;

	class IFormatter
	{
	public:
		IFormatter() noexcept = default;
		virtual ~IFormatter() noexcept = default;

		IFormatter(const IFormatter&) = delete;
		IFormatter(IFormatter&&) = delete;

		auto operator=(const IFormatter&) -> IFormatter& = delete;
		auto operator=(IFormatter&&) -> IFormatter& = delete;

		virtual void Format(const REX::Logging::Context& a_context, std::pmr::string& a_buffer) const = 0;
	};
}
