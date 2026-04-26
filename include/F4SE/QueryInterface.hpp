#pragma once

#include "F4SE/Core.hpp"

#include "REX/Own.hpp"

namespace F4SE::Impl
{
	template <class T>
	concept QueryInterfaceConstraint =
		!std::is_pointer_v<T> &&
		!std::is_reference_v<T> &&
		(requires { T::INTERFACE_ID; }) &&
		(requires { T::INTERFACE_VERSION; });
}

namespace F4SE
{
	class PluginInfo;

	class QueryInterface
	{
	public:
		enum class InterfaceID : std::int32_t
		{
			kInvalid = 0,
			kMessaging = 1,
			kScaleform = 2,
			kPapyrus = 3,
			kSerialization = 4,
			kTask = 5,
			kObject = 6,
			kTrampoline = 7,

			kTotal = 8
		};

		using PluginInfoAccessor = REX::Observer<const PluginInfo*>(F4SE_API*)(const char* a_name);

		QueryInterface() = delete;
		~QueryInterface() = delete;

		QueryInterface(const QueryInterface&) = delete;
		QueryInterface(QueryInterface&&) = delete;

		QueryInterface& operator=(const QueryInterface&) = delete;
		QueryInterface& operator=(QueryInterface&&) = delete;

		[[nodiscard]] REX::Version GetF4SEVersion() const noexcept;
		[[nodiscard]] REX::Version GetRuntimeVersion() const noexcept;
		[[nodiscard]] REX::Version GetEditorVersion() const noexcept;
		[[nodiscard]] bool IsEditor() const noexcept;
		[[nodiscard]] REX::Observer<void*> DoQueryInterface(InterfaceID a_id) const;
		[[nodiscard]] PluginHandle GetPluginHandle() const;
		[[nodiscard]] std::uint32_t GetReleaseIndex() const;
		[[nodiscard]] REX::Observer<const PluginInfo*> GetPluginInfo(const char* a_name) const;
		[[nodiscard]] PluginInfoAccessor GetPluginInfoAccessor() const;
		[[nodiscard]] std::string_view GetSaveFolderName() const;

		template <Impl::QueryInterfaceConstraint T>
		[[nodiscard]] REX::Observer<T*> DoQueryInterface() const
		{
			constexpr auto INTERFACE_ID = T::INTERFACE_ID;
			constexpr auto INTERFACE_VERSION = T::INTERFACE_VERSION;

			auto* interface = reinterpret_cast<T*>(DoQueryInterface(INTERFACE_ID));
			if (!interface || interface->GetVersion() > INTERFACE_VERSION) [[unlikely]] {
				FailDoQueryInterfaceImpl(INTERFACE_ID, INTERFACE_VERSION);
			}

			return interface;
		}

	private:
		[[noreturn]] static void FailDoQueryInterfaceImpl(InterfaceID a_id, std::uint32_t a_version);
	};
	static_assert(std::is_empty_v<QueryInterface>);
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<F4SE::QueryInterface::InterfaceID> final
		: public formatter<std::string_view>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const F4SE::QueryInterface::InterfaceID& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			switch (a_value) {
				case F4SE::QueryInterface::InterfaceID::kMessaging: {
					return format_to(a_ctx.out(), "{}"sv, "Messaging"sv);
				}
				case F4SE::QueryInterface::InterfaceID::kScaleform: {
					return format_to(a_ctx.out(), "{}"sv, "Scaleform"sv);
				}
				case F4SE::QueryInterface::InterfaceID::kPapyrus: {
					return format_to(a_ctx.out(), "{}"sv, "Papyrus"sv);
				}
				case F4SE::QueryInterface::InterfaceID::kSerialization: {
					return format_to(a_ctx.out(), "{}"sv, "Serialization"sv);
				}
				case F4SE::QueryInterface::InterfaceID::kTask: {
					return format_to(a_ctx.out(), "{}"sv, "Task"sv);
				}
				case F4SE::QueryInterface::InterfaceID::kObject: {
					return format_to(a_ctx.out(), "{}"sv, "Object"sv);
				}
				case F4SE::QueryInterface::InterfaceID::kTrampoline: {
					return format_to(a_ctx.out(), "{}"sv, "Trampoline"sv);
				}
				[[unlikely]] default: {
					return format_to(a_ctx.out(), "{}"sv, "Unknown"sv);
				}
			}
		}
	};
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <>
	struct formatter<F4SE::QueryInterface::InterfaceID> final
		: public formatter<std::string_view>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const F4SE::QueryInterface::InterfaceID& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			switch (a_value) {
				case F4SE::QueryInterface::InterfaceID::kMessaging: {
					return format_to(a_ctx.out(), "{}"sv, "Messaging"sv);
				}
				case F4SE::QueryInterface::InterfaceID::kScaleform: {
					return format_to(a_ctx.out(), "{}"sv, "Scaleform"sv);
				}
				case F4SE::QueryInterface::InterfaceID::kPapyrus: {
					return format_to(a_ctx.out(), "{}"sv, "Papyrus"sv);
				}
				case F4SE::QueryInterface::InterfaceID::kSerialization: {
					return format_to(a_ctx.out(), "{}"sv, "Serialization"sv);
				}
				case F4SE::QueryInterface::InterfaceID::kTask: {
					return format_to(a_ctx.out(), "{}"sv, "Task"sv);
				}
				case F4SE::QueryInterface::InterfaceID::kObject: {
					return format_to(a_ctx.out(), "{}"sv, "Object"sv);
				}
				case F4SE::QueryInterface::InterfaceID::kTrampoline: {
					return format_to(a_ctx.out(), "{}"sv, "Trampoline"sv);
				}
				[[unlikely]] default: {
					return format_to(a_ctx.out(), "{}"sv, "Unknown"sv);
				}
			}
		}
	};
}
#endif
