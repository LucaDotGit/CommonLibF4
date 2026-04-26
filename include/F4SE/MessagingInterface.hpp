#pragma once

#include "F4SE/Core.hpp"
#include "F4SE/QueryInterface.hpp"

#include "REX/NotNull.hpp"
#include "REX/Own.hpp"

namespace F4SE
{
	class MessagingInterface final
	{
	public:
		inline static constexpr auto INTERFACE_ID{ QueryInterface::InterfaceID::kMessaging };
		inline static constexpr auto INTERFACE_VERSION{ 1ui32 };

		enum class MessageType : std::int32_t
		{
			kPostLoad = 0,
			kPostPostLoad = 1,
			kPreLoadGame = 2,
			kPostLoadGame = 3,
			kPreSaveGame = 4,
			kPostSaveGame = 5,
			kDeleteGame = 6,
			kInputLoaded = 7,
			kNewGame = 8,
			kGameLoaded = 9,
			kGameDataReady = 10,

			kTotal = 11
		};

		class Message;

		using EventCallback = void F4SE_API(Message* a_msg);

		MessagingInterface() = delete;
		~MessagingInterface() = delete;

		MessagingInterface(const MessagingInterface&) = delete;
		MessagingInterface(MessagingInterface&&) = delete;

		MessagingInterface& operator=(const MessagingInterface&) = delete;
		MessagingInterface& operator=(MessagingInterface&&) = delete;

		[[nodiscard]] std::uint32_t GetVersion() const noexcept;

		bool RegisterListener(REX::NotNull<REX::Observer<EventCallback*>> a_handler) const;
		bool RegisterListener(REX::NotNull<REX::Observer<EventCallback*>> a_handler, const char* a_sender) const;
		bool Dispatch(MessageType a_messageType, std::byte* a_data, std::uint32_t a_dataSize, const char* a_receiver) const;
		[[nodiscard]] void* GetEventDispatcher(std::uint32_t a_dispatcherID) const;
	};
	static_assert(std::is_empty_v<MessagingInterface>);

	class MessagingInterface::Message final
	{
	public:
		using value_type = std::byte;
		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using pointer = std::byte*;
		using const_pointer = const std::byte*;
		using reference = std::byte&;
		using const_reference = const std::byte&;
		using iterator = std::byte*;
		using const_iterator = const std::byte*;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		Message(const char* a_sender, MessageType a_type) noexcept
			: _sender(a_sender),
			  _type(a_type)
		{
		}

		Message(const char* a_sender, MessageType a_type, pointer a_data, size_type a_dataSize) noexcept
			: _sender(a_sender),
			  _type(a_type),
			  _dataSize(a_dataSize),
			  _data(a_data)
		{
		}

		template <REX::trivially_writable T>
		Message(const char* a_sender, MessageType a_type, const T& a_data) noexcept
			: Message(a_sender, a_type)
		{
			_dataSize = sizeof(T);
			_data = reinterpret_cast<pointer>(std::addressof(a_data));
		}

		template <class T>
		Message(const char* a_sender, MessageType a_type, T* a_data) noexcept
			: Message(a_sender, a_type)
		{
			if (!a_data) {
				_dataSize = 0;
				_data = nullptr;
				return;
			}

			_dataSize = sizeof(std::uintptr_t);
			_data = reinterpret_cast<pointer>(a_data);
		}

		template <class T>
		Message(const char* a_sender, MessageType a_type, std::span<T> a_data) noexcept
			: Message(a_sender, a_type)
		{
			_dataSize = static_cast<size_type>(a_data.size_bytes());
			_data = reinterpret_cast<pointer>(a_data.data());
		}

		template <REX::character T>
		Message(const char* a_sender, MessageType a_type, std::basic_string_view<T> a_data) noexcept
			: Message(a_sender, a_type)
		{
			_dataSize = static_cast<size_type>(a_data.size() * sizeof(T));
			_data = reinterpret_cast<pointer>(const_cast<T*>(a_data.data()));
		}

		~Message() noexcept = default;

		Message(const Message&) = delete;
		Message(Message&&) noexcept = default;

		Message& operator=(const Message&) = delete;
		Message& operator=(Message&&) noexcept = default;

		[[nodiscard]] reference operator[](size_type a_index) noexcept { return at(a_index); }
		[[nodiscard]] const_reference operator[](size_type a_index) const noexcept { return at(a_index); }

		[[nodiscard]] reference at(size_type a_index) noexcept
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]] const_reference at(size_type a_index) const noexcept
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]] reference front() noexcept { return at(0); }
		[[nodiscard]] const_reference front() const noexcept { return at(0); }

		[[nodiscard]] reference back() noexcept { return at(size() - 1); }
		[[nodiscard]] const_reference back() const noexcept { return at(size() - 1); }

		[[nodiscard]] pointer data() noexcept { return _data; }
		[[nodiscard]] const_pointer data() const noexcept { return _data; }

		[[nodiscard]] iterator begin() noexcept { return _data; }
		[[nodiscard]] const_iterator begin() const noexcept { return _data; }
		[[nodiscard]] const_iterator cbegin() const noexcept { return _data; }

		[[nodiscard]] iterator end() noexcept { return _data + _dataSize; }
		[[nodiscard]] const_iterator end() const noexcept { return _data + _dataSize; }
		[[nodiscard]] const_iterator cend() const noexcept { return _data + _dataSize; }

		[[nodiscard]] reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
		[[nodiscard]] const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
		[[nodiscard]] const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

		[[nodiscard]] reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
		[[nodiscard]] const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
		[[nodiscard]] const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

		[[nodiscard]] size_type size() const noexcept { return _dataSize; }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); } // NOLINT(readability-convert-member-functions-to-static)

		[[nodiscard]] bool empty() const noexcept { return _dataSize == 0; }

		[[nodiscard]] const char* GetSender() const noexcept { return _sender; }
		[[nodiscard]] MessageType GetType() const noexcept { return _type.get(); }
		[[nodiscard]] size_type GetDataSize() const noexcept { return _dataSize; }
		[[nodiscard]] pointer GetData() noexcept { return _data; }
		[[nodiscard]] const_pointer GetData() const noexcept { return _data; }

		template <REX::trivially_writable T>
		[[nodiscard]] auto GetAsRawValue() const noexcept -> std::optional<T>
		{
			if (_dataSize != sizeof(T)) {
				return std::nullopt;
			}

			auto result = T();
			std::copy_n(reinterpret_cast<const_pointer>(std::addressof(_data)), sizeof(T), reinterpret_cast<pointer>(std::addressof(result)));
			return result;
		}

		template <class T>
		[[nodiscard]] auto GetAsPointer() const noexcept -> std::optional<T*>
		{
			if (_dataSize != sizeof(std::uintptr_t)) {
				return std::nullopt;
			}

			return reinterpret_cast<T*>(_data);
		}

		template <class T>
		[[nodiscard]] auto GetAsSpan() noexcept -> std::optional<std::span<T>>
		{
			if ((_dataSize % sizeof(T)) != 0) {
				return std::nullopt;
			}

			return std::span{ reinterpret_cast<T*>(_data), _dataSize / sizeof(T) };
		}

		template <REX::character T>
		[[nodiscard]] auto GetAsStringView() const noexcept -> std::optional<std::basic_string_view<T>>
		{
			if ((_dataSize % sizeof(T)) != 0) {
				return std::nullopt;
			}

			return std::basic_string_view{ reinterpret_cast<const T*>(_data), _dataSize / sizeof(T) };
		}

	private:
		// members
		const char* _sender{ nullptr }; // 00
		REX::Enum<MessageType> _type;	// 08
		size_type _dataSize{ 0 };		// 0C
		pointer _data{ nullptr };		// 10
	};
	static_assert(sizeof(MessagingInterface::Message) == 0x18);
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<F4SE::MessagingInterface::MessageType> final
		: public formatter<std::string_view>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const F4SE::MessagingInterface::MessageType& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			switch (a_value) {
				case F4SE::MessagingInterface::MessageType::kPostLoad: {
					return format_to(a_ctx.out(), "{}"sv, "PostLoad"sv);
				}
				case F4SE::MessagingInterface::MessageType::kPostPostLoad: {
					return format_to(a_ctx.out(), "{}"sv, "PostPostLoad"sv);
				}
				case F4SE::MessagingInterface::MessageType::kPreLoadGame: {
					return format_to(a_ctx.out(), "{}"sv, "PreLoadGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::kPostLoadGame: {
					return format_to(a_ctx.out(), "{}"sv, "PostLoadGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::kPreSaveGame: {
					return format_to(a_ctx.out(), "{}"sv, "PreSaveGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::kPostSaveGame: {
					return format_to(a_ctx.out(), "{}"sv, "PostSaveGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::kDeleteGame: {
					return format_to(a_ctx.out(), "{}"sv, "DeleteGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::kInputLoaded: {
					return format_to(a_ctx.out(), "{}"sv, "InputLoaded"sv);
				}
				case F4SE::MessagingInterface::MessageType::kNewGame: {
					return format_to(a_ctx.out(), "{}"sv, "NewGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::kGameLoaded: {
					return format_to(a_ctx.out(), "{}"sv, "GameLoaded"sv);
				}
				case F4SE::MessagingInterface::MessageType::kGameDataReady: {
					return format_to(a_ctx.out(), "{}"sv, "GameDataReady"sv);
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
	struct formatter<F4SE::MessagingInterface::MessageType> final
		: public formatter<std::string_view>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const F4SE::MessagingInterface::MessageType& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			switch (a_value) {
				case F4SE::MessagingInterface::MessageType::kPostLoad: {
					return format_to(a_ctx.out(), "{}"sv, "PostLoad"sv);
				}
				case F4SE::MessagingInterface::MessageType::kPostPostLoad: {
					return format_to(a_ctx.out(), "{}"sv, "PostPostLoad"sv);
				}
				case F4SE::MessagingInterface::MessageType::kPreLoadGame: {
					return format_to(a_ctx.out(), "{}"sv, "PreLoadGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::kPostLoadGame: {
					return format_to(a_ctx.out(), "{}"sv, "PostLoadGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::kPreSaveGame: {
					return format_to(a_ctx.out(), "{}"sv, "PreSaveGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::kPostSaveGame: {
					return format_to(a_ctx.out(), "{}"sv, "PostSaveGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::kDeleteGame: {
					return format_to(a_ctx.out(), "{}"sv, "DeleteGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::kInputLoaded: {
					return format_to(a_ctx.out(), "{}"sv, "InputLoaded"sv);
				}
				case F4SE::MessagingInterface::MessageType::kNewGame: {
					return format_to(a_ctx.out(), "{}"sv, "NewGame"sv);
				}
				case F4SE::MessagingInterface::MessageType::kGameLoaded: {
					return format_to(a_ctx.out(), "{}"sv, "GameLoaded"sv);
				}
				case F4SE::MessagingInterface::MessageType::kGameDataReady: {
					return format_to(a_ctx.out(), "{}"sv, "GameDataReady"sv);
				}
				[[unlikely]] default: {
					return format_to(a_ctx.out(), "{}"sv, "Unknown"sv);
				}
			}
		}
	};
}
#endif
