#pragma once

#include "F4SE/Core.hpp"
#include "REX/Concepts.hpp"
#include "REX/Message.hpp"
#include "REX/NotNull.hpp"
#include "REX/Ownership.hpp"

namespace REX
{
	class Version;
}

namespace F4SE::Impl
{
	template <class T>
	concept QueryInterfaceConstraint = !REX::pointer<T> &&
									   !REX::reference<T> &&
									   REX::enumeration<std::remove_cv_t<decltype(T::INTERFACE_ID)>> &&
									   REX::unsigned_integer<std::remove_cv_t<decltype(T::INTERFACE_VERSION)>>;
}

namespace F4SE
{
	class PluginInfo;

	class QueryInterface
	{
	public:
		enum class InterfaceID : std::uint32_t
		{
			Invalid = 0,
			Messaging,
			Scaleform,
			Papyrus,
			Serialization,
			Task,
			Object,
			Trampoline,

			_Min = Invalid,
			_Max = Trampoline,

			_Count = _Max + 1
		};

		using PluginInfoFunctor = REX::Observer<const PluginInfo*>(F4SE_API*)(const char* a_name);

		QueryInterface() = delete;
		~QueryInterface() = delete;

		QueryInterface(const QueryInterface&) = delete;
		QueryInterface(QueryInterface&&) = delete;

		auto operator=(const QueryInterface&) -> QueryInterface& = delete;
		auto operator=(QueryInterface&&) -> QueryInterface& = delete;

		[[nodiscard]]
		auto GetXseVersion() const noexcept -> REX::Version;
		[[nodiscard]]
		auto GetRuntimeVersion() const noexcept -> REX::Version;
		[[nodiscard]]
		auto GetEditorVersion() const noexcept -> REX::Version;
		[[nodiscard]]
		auto IsEditor() const noexcept -> bool;
		[[nodiscard]]
		auto Query(InterfaceID a_id) const -> REX::Observer<void*>;
		[[nodiscard]]
		auto GetPluginHandle() const -> F4SE::PluginHandle;
		[[nodiscard]]
		auto GetReleaseIndex() const -> std::uint32_t;
		[[nodiscard]]
		auto GetPluginInfo(const char* a_name) const -> REX::Observer<const PluginInfo*>;
		[[nodiscard]]
		auto GetPluginInfoFunctor() const -> PluginInfoFunctor;
		[[nodiscard]]
		auto GetSaveFolderName() const -> std::string_view;

		template <Impl::QueryInterfaceConstraint T>
		[[nodiscard]]
		auto QueryOrFail() const -> REX::NotNull<REX::Observer<const T*>>
		{
			constexpr auto INTERFACE_ID = T::INTERFACE_ID;
			constexpr auto INTERFACE_VERSION = T::INTERFACE_VERSION;

			auto* interface = static_cast<const T*>(Query(INTERFACE_ID));
			if (!interface || interface->GetVersion() > INTERFACE_VERSION) [[unlikely]] {
				REX::Fail(
					"Failed to query xSE {} interface v{}.\n"
					"The interface is either not available or the version is outdated."sv,
					INTERFACE_ID,
					INTERFACE_VERSION);
			}

			return interface;
		}
	};

	static_assert(std::is_empty_v<QueryInterface>);
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<F4SE::QueryInterface::InterfaceID> final : public formatter<std::string_view>
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
		constexpr auto format(const F4SE::QueryInterface::InterfaceID& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			switch (a_value) {
				case F4SE::QueryInterface::InterfaceID::Messaging: {
					return format_to(a_context.out(), "{}"sv, "Messaging"sv);
				}
				case F4SE::QueryInterface::InterfaceID::Scaleform: {
					return format_to(a_context.out(), "{}"sv, "Scaleform"sv);
				}
				case F4SE::QueryInterface::InterfaceID::Papyrus: {
					return format_to(a_context.out(), "{}"sv, "Papyrus"sv);
				}
				case F4SE::QueryInterface::InterfaceID::Serialization: {
					return format_to(a_context.out(), "{}"sv, "Serialization"sv);
				}
				case F4SE::QueryInterface::InterfaceID::Task: {
					return format_to(a_context.out(), "{}"sv, "Task"sv);
				}
				case F4SE::QueryInterface::InterfaceID::Object: {
					return format_to(a_context.out(), "{}"sv, "Object"sv);
				}
				case F4SE::QueryInterface::InterfaceID::Trampoline: {
					return format_to(a_context.out(), "{}"sv, "Trampoline"sv);
				}
				[[unlikely]]
				default: {
					return format_to(a_context.out(), "{}"sv, "[Unknown]"sv);
				}
			}
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <>
	struct formatter<F4SE::QueryInterface::InterfaceID> final : public formatter<std::string_view>
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
		constexpr auto format(const F4SE::QueryInterface::InterfaceID& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			switch (a_value) {
				case F4SE::QueryInterface::InterfaceID::Messaging: {
					return format_to(a_context.out(), "{}"sv, "Messaging"sv);
				}
				case F4SE::QueryInterface::InterfaceID::Scaleform: {
					return format_to(a_context.out(), "{}"sv, "Scaleform"sv);
				}
				case F4SE::QueryInterface::InterfaceID::Papyrus: {
					return format_to(a_context.out(), "{}"sv, "Papyrus"sv);
				}
				case F4SE::QueryInterface::InterfaceID::Serialization: {
					return format_to(a_context.out(), "{}"sv, "Serialization"sv);
				}
				case F4SE::QueryInterface::InterfaceID::Task: {
					return format_to(a_context.out(), "{}"sv, "Task"sv);
				}
				case F4SE::QueryInterface::InterfaceID::Object: {
					return format_to(a_context.out(), "{}"sv, "Object"sv);
				}
				case F4SE::QueryInterface::InterfaceID::Trampoline: {
					return format_to(a_context.out(), "{}"sv, "Trampoline"sv);
				}
				[[unlikely]]
				default: {
					return format_to(a_context.out(), "{}"sv, "[Unknown]"sv);
				}
			}
		}
	};
}
#endif
