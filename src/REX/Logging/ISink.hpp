#pragma once

namespace REX::Logging
{
	class Context;

	class ISink : public std::enable_shared_from_this<ISink>
	{
	public:
		ISink() noexcept = default;
		virtual ~ISink() noexcept = default;

		ISink(const ISink&) = delete;
		ISink(ISink&&) = delete;

		auto operator=(const ISink&) -> ISink& = delete;
		auto operator=(ISink&&) -> ISink& = delete;

		virtual void Log(const REX::Logging::Context& a_context, std::string_view a_formattedMessage) = 0;
		virtual void Flush() = 0;
	};
}
