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

	Setting::Setting(const char* a_key, char a_value) noexcept
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

	Setting::Setting(const char* a_key, const char* a_value) noexcept
	{
		SetKey(a_key);
		SetString(a_value);
	}

	Setting::Setting(const char* a_key, REX::zstring_view a_value) noexcept
	{
		SetKey(a_key);
		SetString(a_value);
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

	Setting::Setting(const Setting& a_rhs) noexcept
	{
		Assign(a_rhs);
	}

	Setting::Setting(Setting&& a_rhs) noexcept
		: _value(a_rhs._value),
		  _key(std::exchange(a_rhs._key, nullptr))
	{
	}

	Setting& Setting::operator=(const Setting& a_rhs) noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		Assign(a_rhs);
		return *this;
	}

	Setting& Setting::operator=(Setting&& a_rhs) noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		_key = std::exchange(a_rhs._key, nullptr);
		_value = a_rhs._value;
		return *this;
	}

	Setting& Setting::operator=(bool a_value) noexcept
	{
		SetBinary(a_value);
		return *this;
	}

	Setting& Setting::operator=(char a_value) noexcept
	{
		SetChar(a_value);
		return *this;
	}

	Setting& Setting::operator=(std::uint8_t a_value) noexcept
	{
		SetUChar(a_value);
		return *this;
	}

	Setting& Setting::operator=(std::int32_t a_value) noexcept
	{
		SetInt(a_value);
		return *this;
	}

	Setting& Setting::operator=(std::uint32_t a_value) noexcept
	{
		SetUInt(a_value);
		return *this;
	}

	Setting& Setting::operator=(REX::Float32 a_value) noexcept
	{
		SetFloat(a_value);
		return *this;
	}

	Setting& Setting::operator=(char* a_value) noexcept
	{
		SetString(a_value);
		return *this;
	}

	Setting& Setting::operator=(REX::zstring_view a_value) noexcept
	{
		SetString(a_value);
		return *this;
	}

	Setting& Setting::operator=(std::span<const std::uint8_t, 3> a_value) noexcept
	{
		SetRGB(a_value);
		return *this;
	}

	Setting& Setting::operator=(std::span<const std::uint8_t, 4> a_value) noexcept
	{
		SetRGBA(a_value);
		return *this;
	}

	bool Setting::IsPrefSetting() const
	{
		return false;
	}

	bool Setting::operator==(const Setting& a_rhs) const noexcept
	{
		return Equals(a_rhs);
	}

	bool Setting::operator!=(const Setting& a_rhs) const noexcept
	{
		return !(*this == a_rhs);
	}

	std::partial_ordering Setting::operator<=>(const Setting& a_rhs) const noexcept
	{
		return Compare(a_rhs);
	}

	bool Setting::Equals(const Setting& a_rhs) const noexcept
	{
		if (GetType() != a_rhs.GetType()) {
			return false;
		}

		if (!REX::EqualsIgnoreCase(GetKeyView(), a_rhs.GetKeyView())) {
			return false;
		}

		switch (GetType()) {
			case SETTING_TYPE::kBinary: {
				return GetBinary() == a_rhs.GetBinary();
			}
			case SETTING_TYPE::kChar: {
				return GetChar() == a_rhs.GetChar();
			}
			case SETTING_TYPE::kUChar: {
				return GetUChar() == a_rhs.GetUChar();
			}
			case SETTING_TYPE::kInt: {
				return GetInt() == a_rhs.GetInt();
			}
			case SETTING_TYPE::kUInt: {
				return GetUInt() == a_rhs.GetUInt();
			}
			case SETTING_TYPE::kFloat: {
				return GetFloat() == a_rhs.GetFloat();
			}
			case SETTING_TYPE::kString: {
				return REX::EqualsIgnoreCase(GetStringView(), a_rhs.GetStringView());
			}
			case SETTING_TYPE::kRGB: {
				return std::ranges::equal(GetRGB(), a_rhs.GetRGB());
			}
			case SETTING_TYPE::kRGBA: {
				return std::ranges::equal(GetRGBA(), a_rhs.GetRGBA());
			}
			case SETTING_TYPE::kNone: {
				return true;
			}
			[[unlikely]] default: {
				REX::Assert(false);
				return false;
			}
		}
	}

	std::partial_ordering Setting::Compare(const Setting& a_rhs) const noexcept
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
			case SETTING_TYPE::kBinary: {
				return GetBinary() <=> a_rhs.GetBinary();
			}
			case SETTING_TYPE::kChar: {
				return GetChar() <=> a_rhs.GetChar();
			}
			case SETTING_TYPE::kUChar: {
				return GetUChar() <=> a_rhs.GetUChar();
			}
			case SETTING_TYPE::kInt: {
				return GetInt() <=> a_rhs.GetInt();
			}
			case SETTING_TYPE::kUInt: {
				return GetUInt() <=> a_rhs.GetUInt();
			}
			case SETTING_TYPE::kFloat: {
				return GetFloat() <=> a_rhs.GetFloat();
			}
			case SETTING_TYPE::kString: {
				return REX::CompareIgnoreCase(GetStringView(), a_rhs.GetStringView());
			}
			case SETTING_TYPE::kRGB: {
				const auto leftRGB = GetRGB();
				const auto rightRGB = a_rhs.GetRGB();
				return std::lexicographical_compare_three_way(
					leftRGB.begin(), leftRGB.end(), rightRGB.begin(), rightRGB.end());
			}
			case SETTING_TYPE::kRGBA: {
				const auto leftRGBA = GetRGBA();
				const auto rightRGBA = a_rhs.GetRGBA();
				return std::lexicographical_compare_three_way(
					leftRGBA.begin(), leftRGBA.end(), rightRGBA.begin(), rightRGBA.end());
			}
			case SETTING_TYPE::kNone: {
				return std::partial_ordering::equivalent;
			}
			[[unlikely]] default: {
				REX::Assert(false);
				return std::partial_ordering::unordered;
			}
		}
	}

	Setting::SETTING_TYPE Setting::GetType() const noexcept
	{
		if (REX::IsNullOrEmpty(_key)) {
			return SETTING_TYPE::kNone;
		}

		switch (_key[0]) {
			case 'b':
			case 'B': {
				return SETTING_TYPE::kBinary;
			}
			case 'c':
			case 'C': {
				return SETTING_TYPE::kChar;
			}
			case 'h':
			case 'H': {
				return SETTING_TYPE::kUChar;
			}
			case 'i':
			case 'I': {
				return SETTING_TYPE::kInt;
			}
			case 'u':
			case 'U': {
				return SETTING_TYPE::kUInt;
			}
			case 'f':
			case 'F': {
				return SETTING_TYPE::kFloat;
			}
			case 's':
			case 'S': {
				return SETTING_TYPE::kString;
			}
			case 'r':
			case 'R': {
				return SETTING_TYPE::kRGB;
			}
			case 'a':
			case 'A': {
				return SETTING_TYPE::kRGBA;
			}
			default: {
				return SETTING_TYPE::kNone;
			}
		}
	}

	const char* Setting::GetKey() const noexcept
	{
		return _key;
	}

	REX::zstring_view Setting::GetKeyView() const noexcept
	{
		return _key;
	}

	bool Setting::IsNone() const noexcept
	{
		return GetType() == SETTING_TYPE::kNone;
	}

	bool Setting::IsBinary() const noexcept
	{
		return GetType() == SETTING_TYPE::kBinary;
	}

	bool Setting::IsChar() const noexcept
	{
		return GetType() == SETTING_TYPE::kChar;
	}

	bool Setting::IsUChar() const noexcept
	{
		return GetType() == SETTING_TYPE::kUChar;
	}

	bool Setting::IsInt() const noexcept
	{
		return GetType() == SETTING_TYPE::kInt;
	}

	bool Setting::IsUInt() const noexcept
	{
		return GetType() == SETTING_TYPE::kUInt;
	}

	bool Setting::IsFloat() const noexcept
	{
		return GetType() == SETTING_TYPE::kFloat;
	}

	bool Setting::IsString() const noexcept
	{
		return GetType() == SETTING_TYPE::kString;
	}

	bool Setting::IsRGB() const noexcept
	{
		return GetType() == SETTING_TYPE::kRGB;
	}

	bool Setting::IsRGBA() const noexcept
	{
		return GetType() == SETTING_TYPE::kRGBA;
	}

	std::nullptr_t Setting::GetNone() const noexcept
	{
		REX::Assert(this->IsNone());
		REX::Assert(_value.none == nullptr);
		return nullptr;
	}

	bool Setting::GetBinary() const noexcept
	{
		REX::Assert(this->IsBinary());
		return _value.boolean;
	}

	char Setting::GetChar() const noexcept
	{
		REX::Assert(this->IsChar());
		return _value.int8;
	}

	std::uint8_t Setting::GetUChar() const noexcept
	{
		REX::Assert(this->IsUChar());
		return _value.uint8;
	}

	std::int32_t Setting::GetInt() const noexcept
	{
		REX::Assert(this->IsInt());
		return _value.int32;
	}

	std::uint32_t Setting::GetUInt() const noexcept
	{
		REX::Assert(this->IsUInt());
		return _value.uint32;
	}

	REX::Float32 Setting::GetFloat() const noexcept
	{
		REX::Assert(this->IsFloat());
		return _value.float32;
	}

	const char* Setting::GetString() const noexcept
	{
		REX::Assert(this->IsString());
		return _value.string;
	}

	REX::zstring_view Setting::GetStringView() const noexcept
	{
		REX::Assert(this->IsString());
		return _value.string;
	}

	std::span<const std::uint8_t, 3> Setting::GetRGB() const noexcept
	{
		REX::Assert(this->IsRGB());
		return _value.rgb.array;
	}

	std::span<const std::uint8_t, 4> Setting::GetRGBA() const noexcept
	{
		REX::Assert(this->IsRGBA());
		return _value.rgba.array;
	}

	void Setting::SetKey(const char* a_key) noexcept
	{
		SetKeyView(a_key);
	}

	void Setting::SetKeyView(REX::zstring_view a_key) noexcept
	{
		if (_key) {
			free(_key);
		}

		if (a_key.empty()) {
			_key = nullptr;
			return;
		}

		auto* newKey = calloc<char>(a_key.size() + sizeof(char));
		std::ranges::copy(a_key, newKey);
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

	void Setting::SetChar(char a_value) noexcept
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

	void Setting::SetString(REX::zstring_view a_value) noexcept
	{
		REX::Assert(this->IsString());

		if (_value.string) {
			free(_value.string);
		}

		auto* newString = calloc<char>(a_value.size() + sizeof(char));
		if (!newString) [[unlikely]] {
			REX::AllocationFail();
		}

		std::ranges::copy(a_value, newString);
		_value.string = newString;
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

	std::string Setting::ToString() const
	{
		constexpr auto FORMAT_STRING = "[{} = {}]"sv;

		switch (GetType()) {
			case SETTING_TYPE::kBinary: {
				return REX::Format(FORMAT_STRING, GetKeyView(), GetBinary());
			}
			case SETTING_TYPE::kChar: {
				return REX::Format(FORMAT_STRING, GetKeyView(), GetChar());
			}
			case SETTING_TYPE::kUChar: {
				return REX::Format(FORMAT_STRING, GetKeyView(), GetUChar());
			}
			case SETTING_TYPE::kInt: {
				return REX::Format(FORMAT_STRING, GetKeyView(), GetInt());
			}
			case SETTING_TYPE::kUInt: {
				return REX::Format(FORMAT_STRING, GetKeyView(), GetUInt());
			}
			case SETTING_TYPE::kFloat: {
				return REX::Format(FORMAT_STRING, GetKeyView(), GetFloat());
			}
			case SETTING_TYPE::kString: {
				return REX::Format(FORMAT_STRING, GetKeyView(), GetStringView());
			}
			case SETTING_TYPE::kRGB: {
				const auto rgb = GetRGB();
				return REX::Format(FORMAT_STRING, GetKeyView(), rgb);
			}
			case SETTING_TYPE::kRGBA: {
				const auto rgba = GetRGBA();
				return REX::Format(FORMAT_STRING, GetKeyView(), rgba);
			}
			case SETTING_TYPE::kNone: {
				return REX::Format(FORMAT_STRING, GetKeyView(), GetNone());
			}
			[[unlikely]] default: {
				REX::Assert(false);
				return "[Invalid Setting]"s;
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

	void Setting::Assign(const Setting& a_other) noexcept
	{
		SetKey(a_other._key);

		switch (a_other.GetType()) {
			case SETTING_TYPE::kBinary: {
				SetBinary(a_other.GetBinary());
				break;
			}
			case SETTING_TYPE::kChar: {
				SetChar(a_other.GetChar());
				break;
			}
			case SETTING_TYPE::kUChar: {
				SetUChar(a_other.GetUChar());
				break;
			}
			case SETTING_TYPE::kInt: {
				SetInt(a_other.GetInt());
				break;
			}
			case SETTING_TYPE::kUInt: {
				SetUInt(a_other.GetUInt());
				break;
			}
			case SETTING_TYPE::kFloat: {
				SetFloat(a_other.GetFloat());
				break;
			}
			case SETTING_TYPE::kString: {
				SetString(a_other.GetString());
				break;
			}
			case SETTING_TYPE::kRGB: {
				SetRGB(a_other.GetRGB());
				break;
			}
			case SETTING_TYPE::kRGBA: {
				SetRGBA(a_other.GetRGBA());
				break;
			}
			case SETTING_TYPE::kNone: {
				SetNone();
				break;
			}
			[[unlikely]] default: {
				REX::Assert(false);
			}
		}
	}

	void swap(Setting& a_lhs, Setting& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}

namespace std
{
	std::size_t hash<RE::Setting>::operator()(const RE::Setting& a_key) const noexcept
	{
		using SettingType = RE::Setting::SETTING_TYPE;

		const auto type = a_key.GetType();
		switch (type) {
			case SettingType::kBinary: {
				return REX::HashCombine(type, a_key.GetBinary());
			}
			case SettingType::kChar: {
				return REX::HashCombine(type, a_key.GetChar());
			}
			case SettingType::kUChar: {
				return REX::HashCombine(type, a_key.GetUChar());
			}
			case SettingType::kInt: {
				return REX::HashCombine(type, a_key.GetInt());
			}
			case SettingType::kUInt: {
				return REX::HashCombine(type, a_key.GetUInt());
			}
			case SettingType::kFloat: {
				return REX::HashCombine(type, a_key.GetFloat());
			}
			case SettingType::kString: {
				return REX::HashCombine(type, static_cast<REX::zstring_view>(a_key.GetString()));
			}
			case SettingType::kRGB: {
				const auto rgb = a_key.GetRGB();
				return REX::HashCombine(type, rgb[0], rgb[1], rgb[2]);
			}
			case SettingType::kRGBA: {
				const auto rgba = a_key.GetRGBA();
				return REX::HashCombine(type, rgba[0], rgba[1], rgba[2], rgba[3]);
			}
			case SettingType::kNone: {
				return REX::HashCombine(type, a_key.GetNone());
			}
			[[unlikely]] default: {
				REX::Assert(false);
				return 0;
			}
		}
	}
}
