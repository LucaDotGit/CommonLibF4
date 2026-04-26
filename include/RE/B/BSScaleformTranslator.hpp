#pragma once

#include "RE/B/BSTranslator.hpp"
#include "Scaleform/G/GFx_Translator.hpp"

namespace RE
{
	class Setting;

	template <class T>
	class BSStreamParser;

	class __declspec(novtable) BSScaleformTranslator
		: public ::Scaleform::GFx::Translator // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScaleformTranslator };
		inline static constexpr auto VTABLE{ VTABLE::BSScaleformTranslator };

		inline static constexpr auto TRANSLATION_DIRECTORY_PATH = "Data/Interface/Translations"sv;
		inline static constexpr auto TRANSLATION_RELATIVE_DIRECTORY_PATH = "Interface/Translations"sv;
		inline static constexpr auto TRANSLATION_FILE_EXTENSION = ".txt"sv;

		template <class T>
		inline static constexpr auto TRANSLATION_LANGUAGE_SEPARATOR = static_cast<T>('_');

		template <class T>
		inline static constexpr auto TRANSLATION_KEY_PREFIX = static_cast<T>('$');

		inline static constexpr auto LANGUAGE_SETTING_KEY = "sLanguage:General"sv;
		inline static constexpr auto LANGUAGE_ENGLISH = "en"sv;
		inline static constexpr auto DEFAULT_LANGUAGE = LANGUAGE_ENGLISH;

		template <class T>
		[[nodiscard]] static constexpr bool IsKeyValid(std::basic_string_view<T> a_key) noexcept
		{
			return !a_key.empty() && a_key.front() == TRANSLATION_KEY_PREFIX<T>;
		}

		[[nodiscard]] static Setting& GetLanguageSetting();

		[[nodiscard]] static std::string_view GetLanguage();

		[[nodiscard]] static std::filesystem::path GetTranslationFilePath(std::string_view a_rawName, std::string_view a_language);
		[[nodiscard]] static std::filesystem::path GetRelativeTranslationFilePath(std::string_view a_rawName, std::string_view a_language);

		void AddTranslations(BSStreamParser<wchar_t>& a_parser);
		void AddTranslationsFromFile(const char* a_filePath);
		void AddTranslationsByName(std::string_view a_rawName);

		// members
		BSTranslator translator; // 20
	};
	static_assert(sizeof(BSScaleformTranslator) == 0x50);

	extern template bool BSScaleformTranslator::IsKeyValid(std::string_view) noexcept;
	extern template bool BSScaleformTranslator::IsKeyValid(std::wstring_view) noexcept;
}
