#pragma once

#include "REX/Enum.hpp"
#include "REX/Hash.hpp"

namespace REL
{
	using HookHandle = std::uint64_t;

	inline constexpr auto INVALID_HOOK_HANDLE = std::numeric_limits<HookHandle>::min();

	enum class HookStep : std::int32_t
	{
		kNone = 0,
		kPreLoad,
		kLoad
	};

	class IHook
		: public std::enable_shared_from_this<IHook>
	{
	public:
		explicit IHook();
		explicit IHook(std::uintptr_t a_address);
		explicit IHook(std::uintptr_t a_address, std::string a_name);
		explicit IHook(std::uintptr_t a_address, HookStep a_step);
		explicit IHook(std::uintptr_t a_address, std::string a_name, HookStep a_step);

		virtual ~IHook() noexcept;

		IHook(const IHook&) = delete;
		IHook(IHook&& a_rhs) noexcept = default;

		IHook& operator=(const IHook&) = delete;
		IHook& operator=(IHook&& a_rhs) noexcept = default;

		[[nodiscard]] bool operator==(const IHook& a_rhs) const noexcept;
		[[nodiscard]] bool operator!=(const IHook& a_rhs) const noexcept;
		[[nodiscard]] auto operator<=>(const IHook& a_rhs) const noexcept;

		[[nodiscard]] explicit operator bool() const noexcept;

		[[nodiscard]] HookHandle GetHandle() const noexcept { return _handle; }
		[[nodiscard]] std::uintptr_t GetAddress() const noexcept { return _address; }
		[[nodiscard]] std::string_view GetName() const noexcept { return _name; }
		[[nodiscard]] HookStep GetStep() const noexcept { return _step.get(); }
		[[nodiscard]] std::size_t GetSize() const noexcept { return _size; }
		[[nodiscard]] std::size_t GetTrampolineSize() const noexcept { return _trampolineSize; }
		[[nodiscard]] bool IsInitialized() const noexcept { return _initialized; }
		[[nodiscard]] bool IsEnabled() const noexcept { return _enabled; }
		[[nodiscard]] bool CanBeEnabled() const noexcept { return _initialized && !_enabled; }
		[[nodiscard]] bool CanBeDisabled() const noexcept { return _initialized && _enabled; }

		[[nodiscard]] virtual std::string_view GetTypeName() const noexcept = 0;

		virtual bool Init();
		virtual bool Enable() = 0;
		virtual bool Disable() = 0;

		[[nodiscard]] std::string ToString() const;

	protected:
		inline static constexpr auto DEFAULT_HOOK_NAME = "Hook"sv;
		inline static constexpr auto INVALID_HOOK_NAME = "<Invalid Hook>"sv;

		inline static constinit auto HookHandleCount = std::atomic<HookHandle>(0);

		[[nodiscard]] static HookHandle CreateHookHandle() noexcept;

		HookHandle _handle;
		std::uintptr_t _address;
		std::string _name;
		REX::Enum<HookStep> _step{ HookStep::kLoad };
		std::size_t _size{ sizeof(std::uintptr_t) };
		std::size_t _trampolineSize{ 0 };
		bool _initialized{ false };
		bool _enabled{ false };
	};
}

namespace std
{
	template <class T>
		requires(std::derived_from<T, REL::IHook>)
	struct hash<T>
	{
	public:
		[[nodiscard]] std::size_t operator()(const T& a_key) const noexcept
		{
			return REX::Hash(a_key.GetHandle());
		}
	};
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<REL::HookStep>
		: public formatter<std::string_view>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const REL::HookStep& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			switch (a_value) {
				case REL::HookStep::kNone: {
					return format_to(a_context.out(), "{}"sv, "None"sv);
				}
				case REL::HookStep::kPreLoad: {
					return format_to(a_context.out(), "{}"sv, "PreLoad"sv);
				}
				case REL::HookStep::kLoad: {
					return format_to(a_context.out(), "{}"sv, "Load"sv);
				}
				[[unlikely]] default: {
					return format_to(a_context.out(), "{}"sv, "Unknown"sv);
				}
			}
		}
	};

	template <class T>
		requires(std::derived_from<T, REL::IHook>)
	struct formatter<T>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const T& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <>
	struct formatter<REL::HookStep>
		: public formatter<std::string_view>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const REL::HookStep& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			switch (a_value) {
				case REL::HookStep::kNone: {
					return format_to(a_context.out(), "{}"sv, "None"sv);
				}
				case REL::HookStep::kPreLoad: {
					return format_to(a_context.out(), "{}"sv, "PreLoad"sv);
				}
				case REL::HookStep::kLoad: {
					return format_to(a_context.out(), "{}"sv, "Load"sv);
				}
				[[unlikely]] default: {
					return format_to(a_context.out(), "{}"sv, "Unknown"sv);
				}
			}
		}
	};

	template <class T>
		requires(std::derived_from<T, REL::IHook>)
	struct formatter<T>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const T& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif
