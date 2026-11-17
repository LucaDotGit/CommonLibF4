#pragma once

#include "RE/M/MemoryManager.hpp"
#include "RE/S/SETTING_VALUE.hpp"

namespace RE
{
	class /*__declspec(novtable)*/ Setting
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::Setting;
		inline static constexpr const auto& VTABLE = VTABLE::Setting;

		enum class SETTING_TYPE : std::int32_t
		{
			Binary = 0,
			Char = 1,
			UChar = 2,
			Int = 3,
			UInt = 4,
			Float = 5,
			String = 6,
			RGB = 7,
			RGBA = 8,
			None = 9
		};

		Setting() noexcept;
		virtual ~Setting() noexcept; // 0x00

		Setting(std::nullptr_t) = delete;

		explicit Setting(const char* a_key) noexcept;
		Setting(const char* a_key, bool a_value) noexcept;
		Setting(const char* a_key, std::int8_t a_value) noexcept;
		Setting(const char* a_key, std::uint8_t a_value) noexcept;
		Setting(const char* a_key, std::int32_t a_value) noexcept;
		Setting(const char* a_key, std::uint32_t a_value) noexcept;
		Setting(const char* a_key, REX::Float32 a_value) noexcept;
		Setting(const char* a_key, char* a_value) noexcept;
		Setting(const char* a_key, const char* a_value);
		Setting(const char* a_key, REX::ZStringView a_value);
		Setting(const char* a_key, std::span<const std::uint8_t, 3> a_value) noexcept;
		Setting(const char* a_key, std::span<const std::uint8_t, 4> a_value) noexcept;

		Setting(const Setting& a_rhs);
		Setting(Setting&& a_rhs) noexcept;

		auto operator=(const Setting& a_rhs) -> Setting&;
		auto operator=(Setting&& a_rhs) noexcept -> Setting&;

		auto operator=(std::nullptr_t) -> Setting& = delete;

		auto operator=(bool a_value) noexcept -> Setting&;
		auto operator=(std::int8_t a_value) noexcept -> Setting&;
		auto operator=(std::uint8_t a_value) noexcept -> Setting&;
		auto operator=(std::int32_t a_value) noexcept -> Setting&;
		auto operator=(std::uint32_t a_value) noexcept -> Setting&;
		auto operator=(REX::Float32 a_value) noexcept -> Setting&;
		auto operator=(char* a_value) noexcept -> Setting&;
		auto operator=(const char* a_value) -> Setting&;
		auto operator=(REX::ZStringView a_value) -> Setting&;
		auto operator=(std::span<const std::uint8_t, 3> a_value) noexcept -> Setting&;
		auto operator=(std::span<const std::uint8_t, 4> a_value) noexcept -> Setting&;

		// add
		[[nodiscard]]
		virtual auto IsPrefSetting() const -> bool; // 0x01

		GAME_HEAP_REDEFINE_NEW(Setting);

		[[nodiscard]]
		auto operator==(const Setting& a_rhs) const noexcept -> bool;
		[[nodiscard]]
		auto operator<=>(const Setting& a_rhs) const noexcept -> std::partial_ordering;

		[[nodiscard]]
		auto Equals(const Setting& a_rhs) const noexcept -> bool;
		[[nodiscard]]
		auto Compare(const Setting& a_rhs) const noexcept -> std::partial_ordering;

		[[nodiscard]]
		auto GetType() const noexcept -> SETTING_TYPE;

		[[nodiscard]]
		auto GetKey() const noexcept -> const char*;
		[[nodiscard]]
		auto GetKeyView() const noexcept -> REX::ZStringView;

		[[nodiscard]]
		auto IsNone() const noexcept -> bool;
		[[nodiscard]]
		auto IsBinary() const noexcept -> bool;
		[[nodiscard]]
		auto IsChar() const noexcept -> bool;
		[[nodiscard]]
		auto IsUChar() const noexcept -> bool;
		[[nodiscard]]
		auto IsInt() const noexcept -> bool;
		[[nodiscard]]
		auto IsUInt() const noexcept -> bool;
		[[nodiscard]]
		auto IsFloat() const noexcept -> bool;
		[[nodiscard]]
		auto IsString() const noexcept -> bool;
		[[nodiscard]]
		auto IsRGB() const noexcept -> bool;
		[[nodiscard]]
		auto IsRGBA() const noexcept -> bool;

		[[nodiscard]]
		auto GetNone() const noexcept -> std::nullptr_t;
		[[nodiscard]]
		auto GetBinary() const noexcept -> bool;
		[[nodiscard]]
		auto GetChar() const noexcept -> std::int8_t;
		[[nodiscard]]
		auto GetUChar() const noexcept -> std::uint8_t;
		[[nodiscard]]
		auto GetInt() const noexcept -> std::int32_t;
		[[nodiscard]]
		auto GetUInt() const noexcept -> std::uint32_t;
		[[nodiscard]]
		auto GetFloat() const noexcept -> REX::Float32;
		[[nodiscard]]
		auto GetString() const noexcept -> const char*;
		[[nodiscard]]
		auto GetStringView() const noexcept -> REX::ZStringView;
		[[nodiscard]]
		auto GetRGB() const noexcept -> std::span<const std::uint8_t, 3>;
		[[nodiscard]]
		auto GetRGBA() const noexcept -> std::span<const std::uint8_t, 4>;

		void SetKey(char* a_key) noexcept;
		void SetKey(const char* a_key);
		void SetKeyView(REX::ZStringView a_key);

		void SetNone() noexcept;
		void SetBinary(bool a_value) noexcept;
		void SetChar(std::int8_t a_value) noexcept;
		void SetUChar(std::uint8_t a_value) noexcept;
		void SetInt(std::int32_t a_value) noexcept;
		void SetUInt(std::uint32_t a_value) noexcept;
		void SetFloat(REX::Float32 a_value) noexcept;
		void SetString(char* a_value) noexcept;
		void SetString(const char* a_value);
		void SetStringView(REX::ZStringView a_value);
		void SetRGB(std::span<const std::uint8_t, 3> a_value) noexcept;
		void SetRGBA(std::span<const std::uint8_t, 4> a_value) noexcept;

		[[nodiscard]]
		auto ToString() const -> std::string;

		void swap(Setting& a_other) noexcept;

	private:
		void Assign(const Setting& a_other);

		// members
		SETTING_VALUE _value; // 0x08
		char* _key{nullptr};  // 0x10
	};

	static_assert(sizeof(Setting) == 0x18);
}

namespace std
{
	template <>
	struct hash<RE::Setting>
	{
	public:
		[[nodiscard]]
		auto operator()(const RE::Setting& a_key) const noexcept -> std::size_t;
	};
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<RE::Setting> : public formatter<std::string>
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
		constexpr auto format(const RE::Setting& a_value, FormatContext& a_context) const
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
	struct formatter<RE::Setting> : public formatter<std::string>
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
		constexpr auto format(const RE::Setting& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif
