#include "REX/Logging/Sinks/CallbackSink.hpp"

#include "REX/Logging/Context.hpp"

namespace REX::Logging::Sinks
{
	CallbackSink::CallbackSink(REX::NotNull<std::move_only_function<CallbackType>> a_callback) noexcept :
		_callback(std::move(a_callback))
	{
	}

	CallbackSink::~CallbackSink() noexcept = default;

	void CallbackSink::Log(const REX::Logging::Context& a_context, std::string_view a_formattedMessage)
	{
		std::invoke(_callback.get(), a_context, a_formattedMessage);
	}

	void CallbackSink::Flush()
	{
		return;
	}
}
