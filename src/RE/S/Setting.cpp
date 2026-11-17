#include "RE/S/Setting.hpp"

namespace RE
{
	Setting::Setting() noexcept = default;

	Setting::~Setting() noexcept
	{
		if (IsString()) {
			free(_value.string);
			_value.string = nullptr;
		}

		if (_key) {
			free(_key);
			_key = nullptr;
		}
	}

	Setting::Setting(const char* a_key) noexcept
	{
		SetKey(a_key);
		SetNone();
	}

	Setting::Setting(const char* a_key, bool a_value) noexcept
	{
		SetKey(a_key);
		SetBinary(a_value);
	}

	Setting::Setting(const char* a_key, std::int8_t a_value) noexcept
	{
		SetKey(a_key);
		SetChar(a_value);
	}

	Setting::Setting(const char* a_key, std::uint8_t a_value) noexcept
	{
		SetKey(a_key);
		SetUChar(a_value);
	}

	Setting::Setting(const char* a_key, std::int32_t a_value) noexcept
	{
		SetKey(a_key);
		SetInt(a_value);
	}

	Setting::Setting(const char* a_key, std::uint32_t a_value) noexcept
	{
		SetKey(a_key);
		SetUInt(a_value);
	}

	Setting::Setting(const char* a_key, REX::Float32 a_value) noexcept
	{
		SetKey(a_key);
		SetFloat(a_value);
	}

	Setting::Setting(const char* a_key, char* a_value) noexcept
	{
		SetKey(a_key);
		SetString(a_value);
	}

	Setting::Setting(const char* a_key, const char* a_value)
	{
		SetKey(a_key);
		SetString(a_value);
	}

	Setting::Setting(const char* a_key, REX::ZStringView a_value)
	{
		SetKey(a_key);
		SetStringView(a_value);
	}

	Setting::Setting(const char* a_key, std::span<const std::uint8_t, 3> a_value) noexcept
	{
		SetKey(a_key);
		SetRGB(a_value);
	}

	Setting::Setting(const char* a_key, std::span<const std::uint8_t, 4> a_value) noexcept
	{
		SetKey(a_key);
		SetRGBA(a_value);
	}

	Setting::Setting(const Setting& a_rhs)
	{
		Assign(a_rhs);
	}

	Setting::Setting(Setting&& a_rhs) noexcept :
		_value(a_rhs._value),
		_key(std::exchange(a_rhs._key, nullptr))
	{
	}

	auto Setting::operator=(const Setting& a_rhs) -> Setting&
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		Assign(a_rhs);
		return *this;
	}

	auto Setting::operator=(Setting&& a_rhs) noexcept -> Setting&
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		_key = std::exchange(a_rhs._key, nullptr);
		_value = a_rhs._value;
		return *this;
	}

	auto Setting::operator=(bool a_value) noexcept -> Setting&
	{
		SetBinary(a_value);
		return *this;
	}

	auto Setting::operator=(std::int8_t a_value) noexcept -> Setting&
	{
		SetChar(a_value);
		return *this;
	}

	auto Setting::operator=(std::uint8_t a_value) noexcept -> Setting&
	{
		SetUChar(a_value);
		return *this;
	}

	auto Setting::operator=(std::int32_t a_value) noexcept -> Setting&
	{
		SetInt(a_value);
		return *this;
	}

	auto Setting::operator=(std::uint32_t a_value) noexcept -> Setting&
	{
		SetUInt(a_value);
		return *this;
	}

	auto Setting::operator=(REX::Float32 a_value) noexcept -> Setting&
	{
		SetFloat(a_value);
		return *this;
	}

	auto Setting::operator=(char* a_value) noexcept -> Setting&
	{
		SetString(a_value);
		return *this;
	}

	auto Setting::operator=(const char* a_value) -> Setting&
	{
		SetString(a_value);
		return *this;
	}

	auto Setting::operator=(REX::ZStringView a_value) -> Setting&
	{
		SetStringView(a_value);
		return *this;
	}

	auto Setting::operator=(std::span<const std::uint8_t, 3> a_value) noexcept -> Setting&
	{
		SetRGB(a_value);
		return *this;
	}

	auto Setting::operator=(std::span<const std::uint8_t, 4> a_value) noexcept -> Setting&
	{
		SetRGBA(a_value);
		return *this;
	}

	auto Setting::IsPrefSetting() const -> bool
	{
		return false;
	}

	auto Setting::operator==(const Setting& a_rhs) const noexcept -> bool
	{
		return Equals(a_rhs);
	}

	auto Setting::operator<=>(const Setting& a_rhs) const noexcept -> std::partial_ordering
	{
		return Compare(a_rhs);
	}

	auto Setting::Equals(const Setting& a_rhs) const noexcept -> bool
	{
		if (GetType() != a_rhs.GetType()) {
			return false;
		}

		if (!REX::EqualsIgnoreCase(GetKeyView(), a_rhs.GetKeyView())) {
			return false;
		}

		switch (GetType()) {
			case SETTING_TYPE::Binary: {
				return GetBinary() == a_rhs.GetBinary();
			}
			case SETTING_TYPE::Char: {
				return GetChar() == a_rhs.GetChar();
			}
			case SETTING_TYPE::UChar: {
				return GetUChar() == a_rhs.GetUChar();
			}
			case SETTING_TYPE::Int: {
				return GetInt() == a_rhs.GetInt();
			}
			case SETTING_TYPE::UInt: {
				return GetUInt() == a_rhs.GetUInt();
			}
			case SETTING_TYPE::Float: {
				return GetFloat() == a_rhs.GetFloat();
			}
			case SETTING_TYPE::String: {
				return REX::EqualsIgnoreCase(GetStringView(), a_rhs.GetStringView());
			}
			case SETTING_TYPE::RGB: {
				return std::ranges::equal(GetRGB(), a_rhs.GetRGB());
			}
			case SETTING_TYPE::RGBA: {
				return std::ranges::equal(GetRGBA(), a_rhs.GetRGBA());
			}
			case SETTING_TYPE::None: {
				return true;
			}
			default: {
				std::unreachable();
			}
		}
	}

	auto Setting::Compare(const Setting& a_rhs) const noexcept -> std::partial_ordering
	{
		const auto keyComparison = REX::CompareIgnoreCase(GetKeyView(), a_rhs.GetKeyView());
		if (keyComparison != std::partial_ordering::equivalent) {
			return keyComparison;
		}

		const auto typeComparison = GetType() <=> a_rhs.GetType();
		if (typeComparison != std::partial_ordering::equivalent) {
			return typeComparison;
		}

		switch (GetType()) {
			case SETTING_TYPE::Binary: {
				return GetBinary() <=> a_rhs.GetBinary();
			}
			case SETTING_TYPE::Char: {
				return GetChar() <=> a_rhs.GetChar();
			}
			case SETTING_TYPE::UChar: {
				return GetUChar() <=> a_rhs.GetUChar();
			}
			case SETTING_TYPE::Int: {
				return GetInt() <=> a_rhs.GetInt();
			}
			case SETTING_TYPE::UInt: {
				return GetUInt() <=> a_rhs.GetUInt();
			}
			case SETTING_TYPE::Float: {
				return GetFloat() <=> a_rhs.GetFloat();
			}
			case SETTING_TYPE::String: {
				return REX::CompareIgnoreCase(GetStringView(), a_rhs.GetStringView());
			}
			case SETTING_TYPE::RGB: {
				const auto leftRGB = GetRGB();
				const auto rightRGB = a_rhs.GetRGB();
				return std::lexicographical_compare_three_way(
					leftRGB.begin(),
					leftRGB.end(),
					rightRGB.begin(),
					rightRGB.end());
			}
			case SETTING_TYPE::RGBA: {
				const auto leftRGBA = GetRGBA();
				const auto rightRGBA = a_rhs.GetRGBA();
				return std::lexicographical_compare_three_way(
					leftRGBA.begin(),
					leftRGBA.end(),
					rightRGBA.begin(),
					rightRGBA.end());
			}
			case SETTING_TYPE::None: {
				return std::partial_ordering::equivalent;
			}
			default: {
				std::unreachable();
			}
		}
	}

	auto Setting::GetType() const noexcept -> Setting::SETTING_TYPE
	{
		if (REX::IsNullOrEmpty(_key)) {
			return SETTING_TYPE::None;
		}

		switch (_key[0]) {
			case 'b':
			case 'B': {
				return SETTING_TYPE::Binary;
			}
			case 'c':
			case 'C': {
				return SETTING_TYPE::Char;
			}
			case 'h':
			case 'H': {
				return SETTING_TYPE::UChar;
			}
			case 'i':
			case 'I': {
				return SETTING_TYPE::Int;
			}
			case 'u':
			case 'U': {
				return SETTING_TYPE::UInt;
			}
			case 'f':
			case 'F': {
				return SETTING_TYPE::Float;
			}
			case 's':
			case 'S': {
				return SETTING_TYPE::String;
			}
			case 'r':
			case 'R': {
				return SETTING_TYPE::RGB;
			}
			case 'a':
			case 'A': {
				return SETTING_TYPE::RGBA;
			}
			[[unlikely]]
			default: {
				REX::Assert(false);
				return SETTING_TYPE::None;
			}
		}
	}

	auto Setting::GetKey() const noexcept -> const char*
	{
		return _key;
	}

	auto Setting::GetKeyView() const noexcept -> REX::ZStringView
	{
		return _key;
	}

	auto Setting::IsNone() const noexcept -> bool
	{
		return GetType() == SETTING_TYPE::None;
	}

	auto Setting::IsBinary() const noexcept -> bool
	{
		return GetType() == SETTING_TYPE::Binary;
	}

	auto Setting::IsChar() const noexcept -> bool
	{
		return GetType() == SETTING_TYPE::Char;
	}

	auto Setting::IsUChar() const noexcept -> bool
	{
		return GetType() == SETTING_TYPE::UChar;
	}

	auto Setting::IsInt() const noexcept -> bool
	{
		return GetType() == SETTING_TYPE::Int;
	}

	auto Setting::IsUInt() const noexcept -> bool
	{
		return GetType() == SETTING_TYPE::UInt;
	}

	auto Setting::IsFloat() const noexcept -> bool
	{
		return GetType() == SETTING_TYPE::Float;
	}

	auto Setting::IsString() const noexcept -> bool
	{
		return GetType() == SETTING_TYPE::String;
	}

	auto Setting::IsRGB() const noexcept -> bool
	{
		return GetType() == SETTING_TYPE::RGB;
	}

	auto Setting::IsRGBA() const noexcept -> bool
	{
		return GetType() == SETTING_TYPE::RGBA;
	}

	auto Setting::GetNone() const noexcept -> std::nullptr_t
	{
		REX::Assert(this->IsNone());
		return nullptr;
	}

	auto Setting::GetBinary() const noexcept -> bool
	{
		REX::Assert(this->IsBinary());
		return _value.boolean;
	}

	auto Setting::GetChar() const noexcept -> std::int8_t
	{
		REX::Assert(this->IsChar());
		return _value.int8;
	}

	auto Setting::GetUChar() const noexcept -> std::uint8_t
	{
		REX::Assert(this->IsUChar());
		return _value.uint8;
	}

	auto Setting::GetInt() const noexcept -> std::int32_t
	{
		REX::Assert(this->IsInt());
		return _value.int32;
	}

	auto Setting::GetUInt() const noexcept -> std::uint32_t
	{
		REX::Assert(this->IsUInt());
		return _value.uint32;
	}

	auto Setting::GetFloat() const noexcept -> REX::Float32
	{
		REX::Assert(this->IsFloat());
		return _value.float32;
	}

	auto Setting::GetString() const noexcept -> const char*
	{
		REX::Assert(this->IsString());
		return _value.string;
	}

	auto Setting::GetStringView() const noexcept -> REX::ZStringView
	{
		REX::Assert(this->IsString());
		return _value.string;
	}

	auto Setting::GetRGB() const noexcept -> std::span<const std::uint8_t, 3>
	{
		REX::Assert(this->IsRGB());
		return _value.rgb.array;
	}

	auto Setting::GetRGBA() const noexcept -> std::span<const std::uint8_t, 4>
	{
		REX::Assert(this->IsRGBA());
		return _value.rgba.array;
	}

	void Setting::SetKey(char* a_key) noexcept
	{
		_key = a_key;
	}

	void Setting::SetKey(const char* a_key)
	{
		SetKeyView(a_key);
	}

	void Setting::SetKeyView(REX::ZStringView a_key)
	{
		if (_key) {
			free(_key);
		}

		if (a_key.empty()) {
			_key = nullptr;
			return;
		}

		auto* newKey = malloc<char>(a_key.size() + 1);
		if (!newKey) [[unlikely]] {
			REX::Throw<std::bad_alloc>();
		}

		std::ranges::copy(a_key, newKey);
		newKey[a_key.size()] = REX::EMPTY_CHAR<char>;

		_key = newKey;
	}

	void Setting::SetNone() noexcept
	{
		REX::Assert(this->IsNone());
		_value.none = nullptr;
	}

	void Setting::SetBinary(bool a_value) noexcept
	{
		REX::Assert(this->IsBinary());
		_value.boolean = a_value;
	}

	void Setting::SetChar(std::int8_t a_value) noexcept
	{
		REX::Assert(this->IsChar());
		_value.int8 = a_value;
	}

	void Setting::SetUChar(std::uint8_t a_value) noexcept
	{
		REX::Assert(this->IsUChar());
		_value.uint8 = a_value;
	}

	void Setting::SetInt(std::int32_t a_value) noexcept
	{
		REX::Assert(this->IsInt());
		_value.int32 = a_value;
	}

	void Setting::SetUInt(std::uint32_t a_value) noexcept
	{
		REX::Assert(this->IsUInt());
		_value.uint32 = a_value;
	}

	void Setting::SetFloat(REX::Float32 a_value) noexcept
	{
		REX::Assert(this->IsFloat());
		_value.float32 = a_value;
	}

	void Setting::SetString(char* a_value) noexcept
	{
		REX::Assert(this->IsString());
		_value.string = a_value;
	}

	void Setting::SetString(const char* a_value)
	{
		SetStringView(a_value);
	}

	void Setting::SetStringView(REX::ZStringView a_value)
	{
		REX::Assert(this->IsString());

		if (_value.string) {
			free(_value.string);
		}

		auto* newValue = malloc<char>(a_value.size() + 1);
		if (!newValue) [[unlikely]] {
			REX::Throw<std::bad_alloc>();
		}

		std::ranges::copy(a_value, newValue);
		newValue[a_value.size()] = REX::EMPTY_CHAR<char>;

		_value.string = newValue;
	}

	void Setting::SetRGB(std::span<const std::uint8_t, 3> a_value) noexcept
	{
		REX::Assert(this->IsRGB());
		std::ranges::copy(a_value, _value.rgb.array.begin());
	}

	void Setting::SetRGBA(std::span<const std::uint8_t, 4> a_value) noexcept
	{
		REX::Assert(this->IsRGBA());
		std::ranges::copy(a_value, _value.rgba.array.begin());
	}

	auto Setting::ToString() const -> std::string
	{
		constexpr auto FORMAT_STRING = "[{} = {}]"sv;

		switch (GetType()) {
			case SETTING_TYPE::Binary: {
				return REX::Format(FORMAT_STRING, GetKeyView(), GetBinary());
			}
			case SETTING_TYPE::Char: {
				return REX::Format(FORMAT_STRING, GetKeyView(), GetChar());
			}
			case SETTING_TYPE::UChar: {
				return REX::Format(FORMAT_STRING, GetKeyView(), GetUChar());
			}
			case SETTING_TYPE::Int: {
				return REX::Format(FORMAT_STRING, GetKeyView(), GetInt());
			}
			case SETTING_TYPE::UInt: {
				return REX::Format(FORMAT_STRING, GetKeyView(), GetUInt());
			}
			case SETTING_TYPE::Float: {
				return REX::Format(FORMAT_STRING, GetKeyView(), GetFloat());
			}
			case SETTING_TYPE::String: {
				return REX::Format(FORMAT_STRING, GetKeyView(), GetStringView());
			}
			case SETTING_TYPE::RGB: {
				const auto rgb = GetRGB();
				return REX::Format(FORMAT_STRING, GetKeyView(), rgb);
			}
			case SETTING_TYPE::RGBA: {
				const auto rgba = GetRGBA();
				return REX::Format(FORMAT_STRING, GetKeyView(), rgba);
			}
			case SETTING_TYPE::None: {
				return REX::Format(FORMAT_STRING, GetKeyView(), GetNone());
			}
			default: {
				std::unreachable();
			}
		}
	}

	void Setting::swap(Setting& a_other) noexcept
	{
		if (this == std::addressof(a_other)) {
			return;
		}

		std::swap(_key, a_other._key);
		std::swap(_value, a_other._value);
	}

	void Setting::Assign(const Setting& a_other)
	{
		SetKey(a_other._key);

		switch (a_other.GetType()) {
			case SETTING_TYPE::Binary: {
				SetBinary(a_other.GetBinary());
				break;
			}
			case SETTING_TYPE::Char: {
				SetChar(a_other.GetChar());
				break;
			}
			case SETTING_TYPE::UChar: {
				SetUChar(a_other.GetUChar());
				break;
			}
			case SETTING_TYPE::Int: {
				SetInt(a_other.GetInt());
				break;
			}
			case SETTING_TYPE::UInt: {
				SetUInt(a_other.GetUInt());
				break;
			}
			case SETTING_TYPE::Float: {
				SetFloat(a_other.GetFloat());
				break;
			}
			case SETTING_TYPE::String: {
				SetStringView(a_other.GetStringView());
				break;
			}
			case SETTING_TYPE::RGB: {
				SetRGB(a_other.GetRGB());
				break;
			}
			case SETTING_TYPE::RGBA: {
				SetRGBA(a_other.GetRGBA());
				break;
			}
			case SETTING_TYPE::None: {
				SetNone();
				break;
			}
			default: {
				std::unreachable();
			}
		}
	}
}

namespace std
{
	auto hash<RE::Setting>::operator()(const RE::Setting& a_key) const noexcept -> std::size_t
	{
		using SettingType = RE::Setting::SETTING_TYPE;

		const auto type = a_key.GetType();
		switch (type) {
			case SettingType::Binary: {
				return REX::HashCombine(type, a_key.GetBinary());
			}
			case SettingType::Char: {
				return REX::HashCombine(type, a_key.GetChar());
			}
			case SettingType::UChar: {
				return REX::HashCombine(type, a_key.GetUChar());
			}
			case SettingType::Int: {
				return REX::HashCombine(type, a_key.GetInt());
			}
			case SettingType::UInt: {
				return REX::HashCombine(type, a_key.GetUInt());
			}
			case SettingType::Float: {
				return REX::HashCombine(type, a_key.GetFloat());
			}
			case SettingType::String: {
				return REX::HashCombine(type, REX::ZStringView(a_key.GetString()));
			}
			case SettingType::RGB: {
				const auto rgb = a_key.GetRGB();
				return REX::HashCombine(type, rgb[0], rgb[1], rgb[2]);
			}
			case SettingType::RGBA: {
				const auto rgba = a_key.GetRGBA();
				return REX::HashCombine(type, rgba[0], rgba[1], rgba[2], rgba[3]);
			}
			case SettingType::None: {
				return REX::HashCombine(type, a_key.GetNone());
			}
			default: {
				std::unreachable();
			}
		}
	}
}
