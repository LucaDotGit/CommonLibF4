#pragma once

#include "F4SE/Core.hpp"
#include "F4SE/QueryInterface.hpp"
#include "REX/Concepts.hpp"
#include "REX/Contract.hpp"
#include "REX/Enum.hpp"
#include "REX/NotNull.hpp"
#include "REX/Ownership.hpp"

namespace F4SE
{
	class MessagingInterface final
	{
	public:
		inline static constexpr auto INTERFACE_ID = QueryInterface::InterfaceID::Messaging;
		inline static constexpr auto INTERFACE_VERSION = static_cast<std::uint32_t>(1);

		using value_type = std::byte;
		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;

		enum class MessageType : std::uint32_t
		{
			PostLoad = 0,
			PostPostLoad,
			PreLoadGame,
			PostLoadGame,
			PreSaveGame,
			PostSaveGame,
			DeleteGame,
			InputLoaded,
			NewGame,
			GameLoaded,
			GameDataReady,

			_Min = PostLoad,
			_Max = GameDataReady,

			_Count = _Max + 1
		};

		class Message;

		using EventCallback = void F4SE_API(const Message* a_message);

		MessagingInterface() = delete;
		~MessagingInterface() = delete;

		MessagingInterface(const MessagingInterface&) = delete;
		MessagingInterface(MessagingInterface&&) = delete;

		auto operator=(const MessagingInterface&) -> MessagingInterface& = delete;
		auto operator=(MessagingInterface&&) -> MessagingInterface& = delete;

		[[nodiscard]]
		auto GetVersion() const noexcept -> F4SE::InterfaceVersion;

		void RegisterListener(REX::NotNull<REX::Observer<EventCallback*>> a_handler) const;
		auto RegisterListener(REX::NotNull<REX::Observer<EventCallback*>> a_handler, const char* a_sender) const
			-> bool;
		auto Dispatch(MessageType a_messageType, pointer a_data, size_type a_dataSize, const char* a_receiver) const
			-> bool;
		[[nodiscard]]
		auto GetEventDispatcher(std::uint32_t a_dispatcherID) const -> REX::Observer<void*>;

		template <REX::trivially_writable T>
		auto Dispatch(MessageType a_messageType, T* a_data, size_type a_size, const char* a_receiver) const -> bool
		{
			return Dispatch(a_messageType, reinterpret_cast<pointer>(a_data), a_size * sizeof(T), a_receiver);
		}

		template <REX::trivially_writable T>
		auto Dispatch(MessageType a_messageType, T* a_data, const char* a_receiver) const -> bool
		{
			return Dispatch(a_messageType, reinterpret_cast<pointer>(a_data), sizeof(std::uintptr_t), a_receiver);
		}

		template <REX::trivially_writable T>
		auto Dispatch(MessageType a_messageType, T& a_data, const char* a_receiver) const -> bool
			requires(sizeof(T) <= sizeof(std::uintptr_t))
		{
			return Dispatch(a_messageType, reinterpret_cast<pointer>(std::addressof(a_data)), sizeof(T), a_receiver);
		}

		template <REX::trivially_writable T, std::size_t N>
		auto Dispatch(MessageType a_messageType, std::span<T, N> a_span, const char* a_receiver) const -> bool
		{
			return Dispatch(
				a_messageType,
				reinterpret_cast<pointer>(a_span.data()),
				static_cast<size_type>(a_span.size_bytes()),
				a_receiver);
		}
	};

	static_assert(std::is_empty_v<MessagingInterface>);

	class MessagingInterface::Message final
	{
	public:
		using value_type = MessagingInterface::value_type;
		using size_type = MessagingInterface::size_type;
		using difference_type = MessagingInterface::difference_type;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = value_type*;
		using const_iterator = const value_type*;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		Message(const char* a_sender, MessageType a_type) noexcept :
			_sender(a_sender),
			_type(a_type)
		{
		}

		~Message() noexcept = default;

		Message(const Message&) = delete;
		Message(Message&&) noexcept = default;

		auto operator=(const Message&) -> Message& = delete;
		auto operator=(Message&&) noexcept -> Message& = default;

		[[nodiscard]]
		constexpr auto operator[](size_type a_index) noexcept -> reference
		{
			return at(a_index);
		}

		[[nodiscard]]
		constexpr auto operator[](size_type a_index) const noexcept -> const_reference
		{
			return at(a_index);
		}

		[[nodiscard]]
		constexpr auto at(size_type a_index) noexcept -> reference
		{
			REX::Assert(a_index < size());
			return _data[a_index];
		}

		[[nodiscard]]
		constexpr auto at(size_type a_index) const noexcept -> const_reference
		{
			REX::Assert(a_index < size());
			return _data[a_index];
		}

		[[nodiscard]]
		constexpr auto front() noexcept -> reference
		{
			return at(0);
		}

		[[nodiscard]]
		constexpr auto front() const noexcept -> const_reference
		{
			return at(0);
		}

		[[nodiscard]]
		constexpr auto back() noexcept -> reference
		{
			return at(size() - 1);
		}

		[[nodiscard]]
		constexpr auto back() const noexcept -> const_reference
		{
			return at(size() - 1);
		}

		[[nodiscard]]
		constexpr auto data() noexcept -> pointer
		{
			return _data;
		}

		[[nodiscard]]
		constexpr auto data() const noexcept -> const_pointer
		{
			return _data;
		}

		[[nodiscard]]
		constexpr auto begin() noexcept -> iterator
		{
			return data();
		}

		[[nodiscard]]
		constexpr auto begin() const noexcept -> const_iterator
		{
			return data();
		}

		[[nodiscard]]
		constexpr auto cbegin() const noexcept -> const_iterator
		{
			return data();
		}

		[[nodiscard]]
		constexpr auto end() noexcept -> iterator
		{
			return data() + size();
		}

		[[nodiscard]]
		constexpr auto end() const noexcept -> const_iterator
		{
			return data() + size();
		}

		[[nodiscard]]
		constexpr auto cend() const noexcept -> const_iterator
		{
			return data() + size();
		}

		[[nodiscard]]
		constexpr auto rbegin() noexcept -> reverse_iterator
		{
			return reverse_iterator(end());
		}

		[[nodiscard]]
		constexpr auto rbegin() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(end());
		}

		[[nodiscard]]
		constexpr auto crbegin() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(cend());
		}

		[[nodiscard]]
		constexpr auto rend() noexcept -> reverse_iterator
		{
			return reverse_iterator(begin());
		}

		[[nodiscard]]
		constexpr auto rend() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(begin());
		}

		[[nodiscard]]
		constexpr auto crend() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(cbegin());
		}

		[[nodiscard]]
		constexpr auto size() const noexcept -> size_type
		{
			return _dataSize;
		}

		[[nodiscard]]
		// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
		constexpr auto max_size() const noexcept -> size_type
		{
			return std::numeric_limits<size_type>::max();
		}

		[[nodiscard]]
		auto empty() const noexcept -> bool
		{
			return _dataSize == 0;
		}

		[[nodiscard]]
		auto GetSender() const noexcept -> const char*
		{
			return _sender;
		}

		[[nodiscard]]
		auto GetType() const noexcept -> MessageType
		{
			return _type.get();
		}

		[[nodiscard]]
		auto GetDataSize() const noexcept -> size_type
		{
			return _dataSize;
		}

		[[nodiscard]]
		auto GetData() const noexcept -> const_pointer
		{
			return _data;
		}

		template <REX::trivially_readable T>
		[[nodiscard]]
		auto GetRawValue() const noexcept -> std::optional<T>
			requires(sizeof(T) <= sizeof(std::uintptr_t))
		{
			if (_dataSize != sizeof(T)) {
				return std::nullopt;
			}

			auto result = T();
			std::copy_n(
				reinterpret_cast<const_pointer>(std::addressof(_data)),
				sizeof(T),
				reinterpret_cast<pointer>(std::addressof(result)));
			return result;
		}

		template <class T>
		[[nodiscard]]
		auto GetPointer() const noexcept -> std::optional<T*>
		{
			if (_dataSize != sizeof(std::uintptr_t)) {
				return std::nullopt;
			}

			return reinterpret_cast<T*>(_data);
		}

		template <REX::trivially_readable T>
		[[nodiscard]]
		auto GetSpan() const noexcept -> std::optional<std::span<T>>
		{
			if ((_dataSize % sizeof(T)) != 0) {
				return std::nullopt;
			}

			return std::span{reinterpret_cast<T*>(_data), _dataSize / sizeof(T)};
		}

		template <REX::character CharT>
		[[nodiscard]]
		auto GetStringView() const noexcept -> std::optional<std::basic_string_view<CharT>>
		{
			if ((_dataSize % sizeof(CharT)) != 0) {
				return std::nullopt;
			}

			return std::basic_string_view{reinterpret_cast<const CharT*>(_data), _dataSize / sizeof(CharT)};
		}

	private:
		// members
		const char* _sender{nullptr}; // 0x00
		REX::Enum<MessageType> _type; // 0x08
		size_type _dataSize{0};		  // 0x0C
		pointer _data{nullptr};		  // 0x10
	};

	static_assert(sizeof(MessagingInterface::Message) == 0x18);
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<F4SE::MessagingInterface::MessageType> final : public formatter<std::string_view>
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
		constexpr auto format(const F4SE::MessagingInterface::MessageType& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			switch (a_value) {
				case F4SE::MessagingInterface::MessageType::PostLoad: {
					return format_to(a_context.out(), "{}"sv, "PostLoad"sv);
				}
				case F4SE::MessagingInterface::MessageType::PostPostLoad: {
					return format_to(a_context.out(), "{}"sv, "PostPostLoad"sv);
				}
				case F4SE::MessagingInterface::MessageType::PreLoadGame: {
					return format_to(a_context.out(), "{}"sv, "PreLoadGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::PostLoadGame: {
					return format_to(a_context.out(), "{}"sv, "PostLoadGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::PreSaveGame: {
					return format_to(a_context.out(), "{}"sv, "PreSaveGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::PostSaveGame: {
					return format_to(a_context.out(), "{}"sv, "PostSaveGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::DeleteGame: {
					return format_to(a_context.out(), "{}"sv, "DeleteGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::InputLoaded: {
					return format_to(a_context.out(), "{}"sv, "InputLoaded"sv);
				}
				case F4SE::MessagingInterface::MessageType::NewGame: {
					return format_to(a_context.out(), "{}"sv, "NewGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::GameLoaded: {
					return format_to(a_context.out(), "{}"sv, "GameLoaded"sv);
				}
				case F4SE::MessagingInterface::MessageType::GameDataReady: {
					return format_to(a_context.out(), "{}"sv, "GameDataReady"sv);
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
	struct formatter<F4SE::MessagingInterface::MessageType> final : public formatter<std::string_view>
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
		constexpr auto format(const F4SE::MessagingInterface::MessageType& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			switch (a_value) {
				case F4SE::MessagingInterface::MessageType::PostLoad: {
					return format_to(a_context.out(), "{}"sv, "PostLoad"sv);
				}
				case F4SE::MessagingInterface::MessageType::PostPostLoad: {
					return format_to(a_context.out(), "{}"sv, "PostPostLoad"sv);
				}
				case F4SE::MessagingInterface::MessageType::PreLoadGame: {
					return format_to(a_context.out(), "{}"sv, "PreLoadGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::PostLoadGame: {
					return format_to(a_context.out(), "{}"sv, "PostLoadGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::PreSaveGame: {
					return format_to(a_context.out(), "{}"sv, "PreSaveGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::PostSaveGame: {
					return format_to(a_context.out(), "{}"sv, "PostSaveGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::DeleteGame: {
					return format_to(a_context.out(), "{}"sv, "DeleteGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::InputLoaded: {
					return format_to(a_context.out(), "{}"sv, "InputLoaded"sv);
				}
				case F4SE::MessagingInterface::MessageType::NewGame: {
					return format_to(a_context.out(), "{}"sv, "NewGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::GameLoaded: {
					return format_to(a_context.out(), "{}"sv, "GameLoaded"sv);
				}
				case F4SE::MessagingInterface::MessageType::GameDataReady: {
					return format_to(a_context.out(), "{}"sv, "GameDataReady"sv);
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
