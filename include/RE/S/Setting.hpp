#pragma once

#include "RE/M/MemoryManager.hpp"
#include "RE/S/SETTING_VALUE.hpp"

namespace RE
{
	class __declspec(novtable) Setting
	{
	public:
		inline static constexpr auto RTTI{ RTTI::Setting };
		inline static constexpr auto VTABLE{ VTABLE::Setting };

		enum class SETTING_TYPE : std::int32_t
		{
			kBinary = 0,
			kChar = 1,
			kUChar = 2,
			kInt = 3,
			kUInt = 4,
			kFloat = 5,
			kString = 6,
			kRGB = 7,
			kRGBA = 8,
			kNone = 9
		};

		Setting() noexcept;
		virtual ~Setting() noexcept; // 00

		Setting(std::nullptr_t) = delete;

		explicit Setting(const char* a_key) noexcept;
		explicit Setting(const char* a_key, bool a_value) noexcept;
		explicit Setting(const char* a_key, char a_value) noexcept;
		explicit Setting(const char* a_key, std::uint8_t a_value) noexcept;
		explicit Setting(const char* a_key, std::int32_t a_value) noexcept;
		explicit Setting(const char* a_key, std::uint32_t a_value) noexcept;
		explicit Setting(const char* a_key, REX::Float32 a_value) noexcept;
		explicit Setting(const char* a_key, char* a_value) noexcept;
		explicit Setting(const char* a_key, REX::zstring_view a_value);
		explicit Setting(const char* a_key, std::span<const std::uint8_t, 3> a_value) noexcept;
		explicit Setting(const char* a_key, std::span<const std::uint8_t, 4> a_value) noexcept;

		Setting(const Setting& a_rhs) noexcept;
		Setting(Setting&& a_rhs) noexcept;

		Setting& operator=(const Setting& a_rhs) noexcept;
		Setting& operator=(Setting&& a_rhs) noexcept;

		Setting& operator=(std::nullptr_t) = delete;

		Setting& operator=(bool a_value) noexcept;
		Setting& operator=(char a_value) noexcept;
		Setting& operator=(std::uint8_t a_value) noexcept;
		Setting& operator=(std::int32_t a_value) noexcept;
		Setting& operator=(std::uint32_t a_value) noexcept;
		Setting& operator=(REX::Float32 a_value) noexcept;
		Setting& operator=(char* a_value) noexcept;
		Setting& operator=(REX::zstring_view a_value);
		Setting& operator=(std::span<const std::uint8_t, 3> a_value) noexcept;
		Setting& operator=(std::span<const std::uint8_t, 4> a_value) noexcept;

		// add
		[[nodiscard]] virtual bool IsPrefSetting() const; // 01

		GAME_HEAP_REDEFINE_NEW(Setting);

		[[nodiscard]] bool operator==(const Setting& a_rhs) const noexcept;
		[[nodiscard]] bool operator!=(const Setting& a_rhs) const noexcept;
		[[nodiscard]] std::partial_ordering operator<=>(const Setting& a_rhs) const noexcept;

		[[nodiscard]] bool Equals(const Setting& a_rhs) const noexcept;
		[[nodiscard]] std::partial_ordering Compare(const Setting& a_rhs) const noexcept;

		[[nodiscard]] SETTING_TYPE GetType() const noexcept;

		[[nodiscard]] const char* GetKey() const noexcept;
		[[nodiscard]] REX::zstring_view GetKeyView() const noexcept;

		[[nodiscard]] bool IsNone() const noexcept;
		[[nodiscard]] bool IsBinary() const noexcept;
		[[nodiscard]] bool IsChar() const noexcept;
		[[nodiscard]] bool IsUChar() const noexcept;
		[[nodiscard]] bool IsInt() const noexcept;
		[[nodiscard]] bool IsUInt() const noexcept;
		[[nodiscard]] bool IsFloat() const noexcept;
		[[nodiscard]] bool IsString() const noexcept;
		[[nodiscard]] bool IsRGB() const noexcept;
		[[nodiscard]] bool IsRGBA() const noexcept;

		[[nodiscard]] std::nullptr_t GetNone() const noexcept;
		[[nodiscard]] bool GetBinary() const noexcept;
		[[nodiscard]] char GetChar() const noexcept;
		[[nodiscard]] std::uint8_t GetUChar() const noexcept;
		[[nodiscard]] std::int32_t GetInt() const noexcept;
		[[nodiscard]] std::uint32_t GetUInt() const noexcept;
		[[nodiscard]] REX::Float32 GetFloat() const noexcept;
		[[nodiscard]] const char* GetString() const noexcept;
		[[nodiscard]] REX::zstring_view GetStringView() const noexcept;
		[[nodiscard]] std::span<const std::uint8_t, 3> GetRGB() const noexcept;
		[[nodiscard]] std::span<const std::uint8_t, 4> GetRGBA() const noexcept;

		void SetKey(const char* a_key) noexcept;
		void SetKeyView(REX::zstring_view a_key) noexcept;

		void SetNone() noexcept;
		void SetBinary(bool a_value) noexcept;
		void SetChar(char a_value) noexcept;
		void SetUChar(std::uint8_t a_value) noexcept;
		void SetInt(std::int32_t a_value) noexcept;
		void SetUInt(std::uint32_t a_value) noexcept;
		void SetFloat(REX::Float32 a_value) noexcept;
		void SetString(char* a_value) noexcept;
		void SetStringView(REX::zstring_view a_value);
		void SetRGB(std::span<const std::uint8_t, 3> a_value) noexcept;
		void SetRGBA(std::span<const std::uint8_t, 4> a_value) noexcept;

		[[nodiscard]] std::string ToString() const;

		void swap(Setting& a_other) noexcept;

	private:
		void Assign(const Setting& a_other) noexcept;

		// members
		SETTING_VALUE _value;  // 08
		char* _key{ nullptr }; // 10
	};
	static_assert(sizeof(Setting) == 0x18);

	void swap(Setting& a_lhs, Setting& a_rhs) noexcept;
}

namespace std
{
	template <>
	struct hash<RE::Setting>
	{
	public:
		[[nodiscard]] std::size_t operator()(const RE::Setting& a_key) const noexcept;
	};
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<RE::Setting>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::Setting& a_value, FormatContext& a_context) const
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
	struct formatter<RE::Setting>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::Setting& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif
