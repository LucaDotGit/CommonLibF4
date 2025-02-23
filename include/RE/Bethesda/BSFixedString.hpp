#pragma once

#include "RE/Bethesda/BSStringPool.hpp"
#include "RE/Bethesda/CRC.hpp"
#include "RE/Bethesda/MemoryManager.hpp"

namespace RE
{
	namespace detail
	{
		template <class CharT, bool CS>
		class BSFixedString
		{
		public:
			using value_type = CharT;
			using traits_type = std::char_traits<value_type>;
			using size_type = std::uint32_t;
			using reference = value_type&;
			using const_reference = const value_type&;
			using pointer = value_type*;
			using const_pointer = const value_type*;
			using iterator = pointer;
			using const_iterator = const_pointer;
			using reverse_iterator = std::reverse_iterator<iterator>;
			using const_reverse_iterator = std::reverse_iterator<const_iterator>;

			BSFixedString() noexcept = default;
			BSFixedString(const volatile BSFixedString&) = delete;
			BSFixedString& operator=(const volatile BSFixedString&) = delete;

			template <bool B>
			BSFixedString(const BSFixedString<value_type, B>& a_rhs) :
				_data(a_rhs._data)
			{
				try_acquire();
			}

			template <bool B>
			BSFixedString(BSFixedString<value_type, B>&& a_rhs) noexcept :
				_data(std::exchange(a_rhs._data, nullptr))
			{
			}

			BSFixedString(const_pointer a_string)
			{
				if (a_string) {
					GetEntry<value_type>(_data, a_string, CS);
				}
			}

			explicit BSFixedString(std::basic_string_view<value_type> a_string)
			{
				if (!a_string.empty()) {
					assert(a_string.data()[a_string.size()] == value_type{});
					GetEntry<value_type>(_data, a_string.data(), CS);
				}
			}

			BSFixedString(std::basic_string_view<value_type>::const_iterator a_first, std::basic_string_view<value_type>::const_iterator a_last)
			{
				const auto view = std::basic_string_view<value_type>{ a_first, a_last };
				if (!view.empty()) {
					assert(view.data()[view.size()] == value_type{});
					GetEntry<value_type>(_data, view.data(), CS);
				}
			}

			BSFixedString(std::initializer_list<value_type> a_ilist)
			{
				const auto view = std::basic_string_view<value_type>{ a_ilist.begin(), a_ilist.end() };
				if (!view.empty()) {
					assert(view.data()[view.size()] == value_type{});
					GetEntry<value_type>(_data, view.data(), CS);
				}
			}

			~BSFixedString() { try_release(); }

			template <bool B>
			BSFixedString& operator=(const BSFixedString<value_type, B>& a_rhs)
			{
				if (this != std::addressof(a_rhs)) {
					try_release();
					_data = a_rhs._data;
					try_acquire();
				}
				return *this;
			}

			template <bool B>
			BSFixedString& operator=(BSFixedString<value_type, B>&& a_rhs)
			{
				if (this != std::addressof(a_rhs)) {
					std::swap(_data, a_rhs._data);
				}
				return *this;
			}

			BSFixedString& operator=(const_pointer a_string)
			{
				try_release();
				if (a_string) {
					GetEntry<value_type>(_data, a_string, CS);
				}
				return *this;
			}

			BSFixedString& operator=(std::basic_string_view<value_type> a_string)
			{
				try_release();
				if (!a_string.empty()) {
					assert(a_string.data()[a_string.size()] == value_type{});
					GetEntry<value_type>(_data, a_string.data(), CS);
				}
				return *this;
			}

			BSFixedString& operator=(std::initializer_list<value_type> a_ilist)
			{
				const auto view = std::basic_string_view<value_type>{ a_ilist.begin(), a_ilist.end() };
				try_release();
				if (!view.empty()) {
					assert(view.data()[view.size()] == value_type{});
					GetEntry<value_type>(_data, view.data(), CS);
				}
				return *this;
			}

			[[nodiscard]] operator std::basic_string_view<value_type>() const noexcept { return { data(), size() }; }

			[[nodiscard]] const_reference operator[](size_type a_pos) const noexcept
			{
				return at(a_pos);
			}

			[[nodiscard]] const_reference at(size_type a_pos) const noexcept
			{
				assert(a_pos < size());
				return data()[a_pos];
			}

			[[nodiscard]] const_iterator begin() const noexcept { return data(); }
			[[nodiscard]] const_iterator cbegin() const noexcept { return begin(); }
			[[nodiscard]] const_iterator end() const noexcept { return data() + size(); }
			[[nodiscard]] const_iterator cend() const noexcept { return end(); }

			[[nodiscard]] const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
			[[nodiscard]] const_reverse_iterator crbegin() const noexcept { return rbegin(); }
			[[nodiscard]] const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
			[[nodiscard]] const_reverse_iterator crend() const noexcept { return rend(); }

			[[nodiscard]] const_reference front() const noexcept { return at(0); }
			[[nodiscard]] const_reference back() const noexcept { return at(size() - 1); }

			[[nodiscard]] const_pointer data() const noexcept
			{
				const auto cstr = _data ? _data->data<value_type>() : nullptr;
				return cstr ? cstr : EMPTY;
			}

			[[nodiscard]] const_pointer c_str() const noexcept { return data(); }

			[[nodiscard]] bool empty() const noexcept { return size() == 0; }

			[[nodiscard]] size_type size() const noexcept { return _data ? _data->size() : 0; }
			[[nodiscard]] size_type length() const noexcept { return _data ? _data->length() : 0; }

			[[nodiscard]] friend auto operator==(const BSFixedString& a_lhs, const BSFixedString& a_rhs) noexcept
			{
				return hash_equals(a_lhs, a_rhs) || strcmp(a_lhs, a_rhs) == std::strong_ordering::equal;
			}

			[[nodiscard]] friend auto operator==(const BSFixedString& a_lhs, std::basic_string_view<value_type> a_rhs) noexcept
			{
				return strcmp(a_lhs, a_rhs) == std::strong_ordering::equal;
			}

			[[nodiscard]] friend auto operator==(std::basic_string_view<value_type> a_lhs, const BSFixedString& a_rhs) noexcept
			{
				return strcmp(a_lhs, a_rhs) == std::strong_ordering::equal;
			}

			[[nodiscard]] friend auto operator==(const BSFixedString& a_lhs, const_pointer a_rhs) noexcept
			{
				return strncmp(a_lhs.data(), a_rhs, a_lhs.size()) == std::strong_ordering::equal;
			}

			[[nodiscard]] friend auto operator==(const_pointer a_lhs, const BSFixedString& a_rhs) noexcept
			{
				return strncmp(a_lhs, a_rhs.data(), a_rhs.size()) == std::strong_ordering::equal;
			}

			[[nodiscard]] friend auto operator<=>(const BSFixedString& a_lhs, const BSFixedString& a_rhs) noexcept
			{
				return strcmp(a_lhs, a_rhs);
			}

			[[nodiscard]] friend auto operator<=>(const BSFixedString& a_lhs, std::basic_string_view<value_type> a_rhs) noexcept
			{
				return strcmp(a_lhs, a_rhs);
			}

			[[nodiscard]] friend auto operator<=>(std::basic_string_view<value_type> a_lhs, const BSFixedString& a_rhs) noexcept
			{
				return strcmp(a_lhs, a_rhs);
			}

			[[nodiscard]] friend auto operator<=>(const BSFixedString& a_lhs, const_pointer a_rhs) noexcept
			{
				return strncmp(a_lhs.data(), a_rhs, a_lhs.size());
			}

			[[nodiscard]] friend auto operator<=>(const_pointer a_lhs, const BSFixedString& a_rhs) noexcept
			{
				return strncmp(a_lhs, a_rhs.data(), a_rhs.size());
			}

			[[nodiscard]] bool contains(std::basic_string_view<value_type> a_rhs) const noexcept
			{
				if (a_rhs.size() > size()) {
					return false;
				}

				for (auto i = static_cast<size_type>(0); i < size(); ++i) {
					if (strncmp(&data()[i], a_rhs.data(), a_rhs.size()) == std::strong_ordering::equal) {
						return true;
					}
				}

				return false;
			}

		protected:
			template <class>
			friend struct RE::BSCRC32;

			[[nodiscard]] const void* hash_accessor() const noexcept { return _data; }

		private:
			template <class, bool>
			friend class BSFixedString;

			[[nodiscard]] static std::strong_ordering strcmp(std::basic_string_view<value_type> a_lhs, std::basic_string_view<value_type> a_rhs) noexcept
			{
				const auto lsize = a_lhs.size();
				const auto rsize = a_rhs.size();

				if (lsize != rsize) {
					return lsize <=> rsize;
				}

				return strncmp(a_lhs.data(), a_rhs.data(), lsize);
			}

			[[nodiscard]] static std::strong_ordering strncmp(const_pointer a_lhs, const_pointer a_rhs, std::size_t a_length) noexcept
			{
				if (a_length == 0) {
					return std::strong_ordering::equal;
				}

				if constexpr (CS) {
					if constexpr (std::is_same_v<value_type, char>) {
						return std::strncmp(a_lhs, a_rhs, a_length) <=> 0;
					}
					else if constexpr (std::is_same_v<value_type, wchar_t>) {
						return std::wcsncmp(a_lhs, a_rhs, a_length) <=> 0;
					}
					else {
						static_assert(false, "unsupported value_type");
					}
				}
				else {
					if constexpr (std::is_same_v<value_type, char>) {
						return _strnicmp(a_lhs, a_rhs, a_length) <=> 0;
					}
					else if constexpr (std::is_same_v<value_type, wchar_t>) {
						return _wcsnicmp(a_lhs, a_rhs, a_length) <=> 0;
					}
					else {
						static_assert(false, "unsupported value_type");
					}
				}
			}

			[[nodiscard]] static bool hash_equals(const BSFixedString& a_lhs, const BSFixedString& a_rhs) noexcept
			{
				if (a_lhs.empty() && a_rhs.empty()) {
					return true;
				}

				const auto getLeaf = [](const BSFixedString& a_str) {
					return a_str._data ? a_str._data->leaf() : nullptr;
				};

				const auto* lLeaf = getLeaf(a_lhs);
				const auto* rLeaf = getLeaf(a_rhs);
				return lLeaf == rLeaf;
			}

			void try_acquire()
			{
				if (_data) {
					_data->acquire();
				}
			}

			void try_release() { BSStringPool::Entry::release(_data); }

			static constexpr const value_type EMPTY[]{ 0 };

			// members
			BSStringPool::Entry* _data{ nullptr }; // 00
		};

		extern template class BSFixedString<char, false>;
		extern template class BSFixedString<char, true>;
		extern template class BSFixedString<wchar_t, false>;
		extern template class BSFixedString<wchar_t, true>;
	}

	using BSFixedString = detail::BSFixedString<char, false>;
	using BSFixedStringCS = detail::BSFixedString<char, true>;
	using BSFixedStringW = detail::BSFixedString<wchar_t, false>;
	using BSFixedStringWCS = detail::BSFixedString<wchar_t, true>;

	namespace BSScript
	{
		template <class>
		struct script_traits;

		template <>
		struct script_traits<RE::BSFixedString> final
		{
			using is_string = std::true_type;
		};

		template <>
		struct script_traits<RE::BSFixedStringCS> final
		{
			using is_string = std::true_type;
		};
	}

	template <class CharT, bool CS>
	struct BSCRC32<detail::BSFixedString<CharT, CS>>
	{
	public:
		[[nodiscard]] std::uint32_t operator()(const detail::BSFixedString<CharT, CS>& a_key) const noexcept
		{
			return BSCRC32<const void*>()(a_key.hash_accessor());
		}
	};

	extern template struct BSCRC32<BSFixedString>;
	extern template struct BSCRC32<BSFixedStringCS>;
	extern template struct BSCRC32<BSFixedStringW>;
	extern template struct BSCRC32<BSFixedStringWCS>;

	class BGSLocalizedString
	{
	public:
		using size_type = typename BSFixedStringCS::size_type;
		using traits_type = typename BSFixedStringCS::traits_type;
		using value_type = typename BSFixedStringCS::value_type;
		using reference = typename BSFixedStringCS::reference;
		using const_reference = typename BSFixedStringCS::const_reference;
		using pointer = typename BSFixedStringCS::pointer;
		using const_pointer = typename BSFixedStringCS::const_pointer;
		using iterator = typename BSFixedStringCS::iterator;
		using const_iterator = typename BSFixedStringCS::const_iterator;
		using reverse_iterator = typename BSFixedStringCS::reverse_iterator;
		using const_reverse_iterator = typename BSFixedStringCS::const_reverse_iterator;

		BGSLocalizedString() noexcept = default;
		BGSLocalizedString(const volatile BGSLocalizedString&) = delete;
		BGSLocalizedString& operator=(const volatile BGSLocalizedString&) = delete;

		BGSLocalizedString(const BGSLocalizedString& a_rhs) :
			_data(a_rhs._data)
		{
		}

		BGSLocalizedString(BGSLocalizedString&& a_rhs) noexcept :
			_data(std::exchange(a_rhs._data, nullptr))
		{
		}

		BGSLocalizedString(const BSFixedStringCS& a_string) :
			_data(a_string)
		{
		}

		BGSLocalizedString(const_pointer a_string)
		{
			parse(a_string);
		}

		explicit BGSLocalizedString(std::basic_string_view<value_type> a_string)
		{
			parse(a_string);
		}

		BGSLocalizedString(std::basic_string_view<value_type>::const_iterator a_first, std::basic_string_view<value_type>::const_iterator a_last)
		{
			const auto view = std::basic_string_view<value_type>{ a_first, a_last };
			parse(view);
		}

		BGSLocalizedString(std::initializer_list<value_type> a_ilist)
		{
			const auto view = std::basic_string_view<value_type>{ a_ilist.begin(), a_ilist.end() };
			parse(view);
		}

		~BGSLocalizedString() = default;

		BGSLocalizedString& operator=(const BGSLocalizedString& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				_data = a_rhs._data;
			}
			return *this;
		}

		BGSLocalizedString& operator=(BGSLocalizedString&& a_rhs) noexcept
		{
			if (this != std::addressof(a_rhs)) {
				std::swap(_data, a_rhs._data);
			}
			return *this;
		}

		BGSLocalizedString& operator=(const BSFixedStringCS& a_rhs)
		{
			parse(a_rhs);
			return *this;
		}

		BGSLocalizedString& operator=(const_pointer a_rhs)
		{
			parse(a_rhs);
			return *this;
		}

		BGSLocalizedString& operator=(std::basic_string_view<value_type> a_rhs)
		{
			parse(a_rhs);
			return *this;
		}

		BGSLocalizedString& operator=(std::initializer_list<value_type> a_rhs)
		{
			const auto view = std::basic_string_view<value_type>{ a_rhs.begin(), a_rhs.end() };
			parse(view);
			return *this;
		}

		[[nodiscard]] operator std::basic_string_view<value_type>() const noexcept { return _data; }
		[[nodiscard]] explicit operator BSFixedStringCS() const noexcept { return _data; }

		[[nodiscard]] const_reference operator[](size_type a_pos) const noexcept
		{
			return _data[a_pos];
		}

		[[nodiscard]] const_reference at(size_type a_pos) const noexcept
		{
			return _data.at(a_pos);
		}

		[[nodiscard]] const_reference front() const noexcept { return _data.front(); }
		[[nodiscard]] const_reference back() const noexcept { return _data.back(); }

		[[nodiscard]] const_pointer data() const noexcept { return _data.data(); }
		[[nodiscard]] const_pointer c_str() const noexcept { return _data.c_str(); }

		[[nodiscard]] const_iterator begin() const noexcept { return _data.begin(); }
		[[nodiscard]] const_iterator cbegin() const noexcept { return _data.cbegin(); }
		[[nodiscard]] const_iterator end() const noexcept { return _data.end(); }
		[[nodiscard]] const_iterator cend() const noexcept { return _data.cend(); }

		[[nodiscard]] const_reverse_iterator rbegin() const noexcept { return _data.rbegin(); }
		[[nodiscard]] const_reverse_iterator crbegin() const noexcept { return _data.crbegin(); }
		[[nodiscard]] const_reverse_iterator rend() const noexcept { return _data.rend(); }
		[[nodiscard]] const_reverse_iterator crend() const noexcept { return _data.crend(); }

		[[nodiscard]] bool empty() const noexcept { return _data.empty(); }

		[[nodiscard]] size_type size() const noexcept { return _data.size(); }
		[[nodiscard]] size_type length() const noexcept { return _data.length(); }

		[[nodiscard]] friend auto operator==(const BGSLocalizedString& a_lhs, const BGSLocalizedString& a_rhs) noexcept
		{
			return a_lhs._data == a_rhs._data;
		}

		[[nodiscard]] friend auto operator==(const BGSLocalizedString& a_lhs, std::basic_string_view<value_type> a_rhs) noexcept
		{
			return a_lhs._data == a_rhs;
		}

		[[nodiscard]] friend auto operator==(std::basic_string_view<value_type> a_lhs, const BGSLocalizedString& a_rhs) noexcept
		{
			return a_lhs == a_rhs._data;
		}

		[[nodiscard]] friend auto operator==(const BGSLocalizedString& a_lhs, const_pointer a_rhs) noexcept
		{
			return a_lhs._data == a_rhs;
		}

		[[nodiscard]] friend auto operator==(const_pointer a_lhs, const BGSLocalizedString& a_rhs) noexcept
		{
			return a_lhs == a_rhs._data;
		}

		[[nodiscard]] friend auto operator<=>(const BGSLocalizedString& a_lhs, const BGSLocalizedString& a_rhs) noexcept
		{
			return a_lhs._data <=> a_rhs._data;
		}

		[[nodiscard]] friend auto operator<=>(const BGSLocalizedString& a_lhs, std::basic_string_view<value_type> a_rhs) noexcept
		{
			return a_lhs._data <=> a_rhs;
		}

		[[nodiscard]] friend auto operator<=>(std::basic_string_view<value_type> a_lhs, const BGSLocalizedString& a_rhs) noexcept
		{
			return a_lhs <=> a_rhs._data;
		}

		[[nodiscard]] friend auto operator<=>(const BGSLocalizedString& a_lhs, const_pointer a_rhs) noexcept
		{
			return a_lhs._data <=> a_rhs;
		}

		[[nodiscard]] friend auto operator<=>(const_pointer a_lhs, const BGSLocalizedString& a_rhs) noexcept
		{
			return a_lhs <=> a_rhs._data;
		}

		[[nodiscard]] bool contains(std::basic_string_view<value_type> a_rhs) const noexcept
		{
			return _data.contains(a_rhs);
		}

	protected:
		template <class>
		friend struct BSCRC32;

		[[nodiscard]] const BSFixedStringCS& hash_accessor() const noexcept { return _data; }

	private:
		void parse(std::basic_string_view<value_type> a_rhs)
		{
			const auto self = static_cast<std::basic_string_view<value_type>>(_data);
			if (self.starts_with("<ID=")) {
				assert(self.size() >= PREFIX_LENGTH);
				std::vector<char> buf(PREFIX_LENGTH + a_rhs.size() + 1, '\0');
				strncpy_s(buf.data(), buf.size(), self.data(), PREFIX_LENGTH);
				strcpy_s(buf.data() + PREFIX_LENGTH, buf.size() - PREFIX_LENGTH, (a_rhs.empty() ? "" : a_rhs.data()));
				_data = std::string_view{ buf.data(), buf.size() };
			}
			else {
				_data = a_rhs;
			}
		}

		static constexpr std::size_t PREFIX_LENGTH = 13;

		// members
		BSFixedStringCS _data; // 00
	};
	static_assert(sizeof(BGSLocalizedString) == 0x8);

	namespace BSScript
	{
		template <class>
		struct script_traits;

		template <>
		struct script_traits<RE::BGSLocalizedString> final
		{
			using is_string = std::true_type;
		};
	}

	template <>
	struct BSCRC32<BGSLocalizedString>
	{
	public:
		[[nodiscard]] std::uint32_t operator()(const BGSLocalizedString& a_key) const noexcept
		{
			return BSCRC32<BSFixedStringCS>()(a_key.hash_accessor());
		}
	};

	struct BGSLocalizedStrings
	{
		struct ScrapStringBuffer
		{
		public:
			[[nodiscard]] const char* GetString() const noexcept { return static_cast<const char*>(buffer.GetPtr()) + offset; }

			// members
			MemoryManager::AutoScrapBuffer buffer; // 00
			std::size_t offset;					   // 08
		};
		static_assert(sizeof(ScrapStringBuffer) == 0x10);
	};
	static_assert(std::is_empty_v<BGSLocalizedStrings>);
}

namespace std
{
	template <class CharT, bool CS>
	struct formatter<RE::detail::BSFixedString<CharT, CS>, CharT>
		: public formatter<std::basic_string_view<CharT>, CharT>
	{
		constexpr auto parse(basic_format_parse_context<CharT>& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		constexpr auto format(const RE::detail::BSFixedString<CharT, CS>& a_str, FormatContext& a_ctx) const
		{
			return formatter<basic_string_view<CharT>, CharT>::format(a_str, a_ctx);
		}
	};

	template <>
	struct formatter<RE::BGSLocalizedString, RE::BGSLocalizedString::value_type>
		: public formatter<std::basic_string_view<RE::BGSLocalizedString::value_type>, RE::BGSLocalizedString::value_type>
	{
		constexpr auto parse(basic_format_parse_context<RE::BGSLocalizedString::value_type>& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		constexpr auto format(const RE::BGSLocalizedString& a_str, FormatContext& a_ctx) const
		{
			return formatter<basic_string_view<RE::BGSLocalizedString::value_type>, RE::BGSLocalizedString::value_type>::format(a_str, a_ctx);
		}
	};
}

#ifdef FMT_VERSION
namespace fmt
{
	template <class CharT, bool CS>
	struct formatter<RE::detail::BSFixedString<CharT, CS>, CharT>
		: public fmt::formatter<std::basic_string_view<CharT>, CharT>
	{
		constexpr auto parse(fmt::basic_format_parse_context<CharT>& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		constexpr auto format(const RE::detail::BSFixedString<CharT, CS>& a_str, FormatContext& a_ctx) const
		{
			return formatter<std::basic_string_view<CharT>, CharT>::format(a_str, a_ctx);
		}
	};

	template <>
	struct formatter<RE::BGSLocalizedString, RE::BGSLocalizedString::value_type>
		: public fmt::formatter<std::basic_string_view<RE::BGSLocalizedString::value_type>, RE::BGSLocalizedString::value_type>
	{
		constexpr auto parse(fmt::basic_format_parse_context<RE::BGSLocalizedString::value_type>& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		constexpr auto format(const RE::BGSLocalizedString& a_str, FormatContext& a_ctx) const
		{
			return formatter<std::basic_string_view<RE::BGSLocalizedString::value_type>, RE::BGSLocalizedString::value_type>::format(a_str, a_ctx);
		}
	};
}
#endif
