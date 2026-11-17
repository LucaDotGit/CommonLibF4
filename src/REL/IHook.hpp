#pragma once

#include "REX/Enum.hpp"
#include "REX/Hashing.hpp"

namespace REX::Logging
{
	class ILogger;
}

namespace REL
{
	class Trampoline;

	using HookHandle = std::uint64_t;

	inline constexpr auto INVALID_HOOK_HANDLE = std::numeric_limits<HookHandle>::min();

	enum class HookStep : std::int32_t
	{
		PreLoad = 1,
		Load,

		_Min = PreLoad,
		_Max = Load,

		_Count = _Max
	};

	class IHook : public std::enable_shared_from_this<IHook>
	{
	public:
		explicit IHook() noexcept;

		explicit IHook(std::uintptr_t a_address, std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept;

		explicit IHook(std::uintptr_t a_address, HookStep a_step, std::shared_ptr<REX::Logging::ILogger> a_logger = {})
			noexcept;

		explicit IHook(
			std::uintptr_t a_address,
			std::string a_name,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept;

		explicit IHook(
			std::uintptr_t a_address,
			std::string a_name,
			HookStep a_step,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept;

		virtual ~IHook() noexcept;

		IHook(const IHook&) = delete;
		IHook(IHook&&) noexcept = default;

		auto operator=(const IHook&) -> IHook& = delete;
		auto operator=(IHook&&) noexcept -> IHook& = default;

		[[nodiscard]]
		auto operator==(const IHook& a_rhs) const noexcept -> bool;
		[[nodiscard]]
		auto operator<=>(const IHook& a_rhs) const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		auto GetHandle() const noexcept -> HookHandle
		{
			return _handle;
		}

		[[nodiscard]]
		auto GetAddress() const noexcept -> std::uintptr_t
		{
			return _address;
		}

		[[nodiscard]]
		auto GetName() const noexcept -> std::string_view
		{
			return _name;
		}

		[[nodiscard]]
		auto GetStep() const noexcept -> HookStep
		{
			return _step.get();
		}

		[[nodiscard]]
		auto GetIsSetup() const noexcept -> bool
		{
			return _isSetup;
		}

		[[nodiscard]]
		auto GetIsEnabled() const noexcept -> bool
		{
			return _isEnabled;
		}

		[[nodiscard]]
		auto CanBeEnabled() const noexcept -> bool
		{
			return _isSetup && !_isEnabled;
		}

		[[nodiscard]]
		auto CanBeDisabled() const noexcept -> bool
		{
			return _isSetup && _isEnabled;
		}

	protected:
		[[nodiscard]]
		auto GetLogger() const noexcept -> const std::shared_ptr<REX::Logging::ILogger>&
		{
			return _logger;
		}

		void SetIsEnabled(bool a_isEnabled) noexcept
		{
			_isEnabled = a_isEnabled;
		}

		void SetIsSetup(bool a_isSetup) noexcept
		{
			_isSetup = a_isSetup;
		}

	public:
		[[nodiscard]]
		virtual auto GetTypeName() const noexcept -> std::string_view = 0;

		[[nodiscard]]
		virtual auto GetSize() const noexcept -> std::size_t = 0;

		[[nodiscard]]
		virtual auto GetTrampolineSize() const noexcept -> std::size_t = 0;

		virtual auto Setup(REL::Trampoline& a_trampoline) -> bool = 0;
		virtual auto Enable() -> bool = 0;
		virtual auto Disable() -> bool = 0;

		[[nodiscard]]
		auto ToString() const -> std::string;

	private:
		HookHandle _handle;
		std::uintptr_t _address;
		std::string _name;
		REX::Enum<HookStep> _step{HookStep::Load};
		bool _isSetup{false};
		bool _isEnabled{false};
		std::shared_ptr<REX::Logging::ILogger> _logger;
	};
}

namespace std
{
	template <class T>
		requires(std::derived_from<T, REL::IHook>)
	struct hash<T>
	{
	public:
		[[nodiscard]]
		auto operator()(const T& a_key) const noexcept -> std::size_t
		{
			return REX::Hash(a_key.GetHandle());
		}
	};
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<REL::HookStep> : public formatter<std::string_view>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const REL::HookStep& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			switch (a_value) {
				case REL::HookStep::PreLoad: {
					return format_to(a_context.out(), "{}"sv, "PreLoad"sv);
				}
				case REL::HookStep::Load: {
					return format_to(a_context.out(), "{}"sv, "Load"sv);
				}
				[[unlikely]]
				default: {
					return format_to(a_context.out(), "{}"sv, "[Unknown]"sv);
				}
			}
		}
	};

	template <class T>
		requires(std::derived_from<T, REL::IHook>)
	struct formatter<T> : public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const T& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <>
	struct formatter<REL::HookStep> : public formatter<std::string_view>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const REL::HookStep& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			switch (a_value) {
				case REL::HookStep::PreLoad: {
					return format_to(a_context.out(), "{}"sv, "PreLoad"sv);
				}
				case REL::HookStep::Load: {
					return format_to(a_context.out(), "{}"sv, "Load"sv);
				}
				[[unlikely]]
				default: {
					return format_to(a_context.out(), "{}"sv, "[Unknown]"sv);
				}
			}
		}
	};

	template <class T>
		requires(std::derived_from<T, REL::IHook>)
	struct formatter<T> : public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const T& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif
