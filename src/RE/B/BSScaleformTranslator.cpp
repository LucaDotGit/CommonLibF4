#include "RE/B/BSScaleformTranslator.hpp"

#include "RE/B/BSResourceStreamParser.hpp"
#include "RE/B/BSStreamParser.hpp"
#include "RE/S/Setting.hpp"
#include "RE/S/SettingUtil.hpp"

namespace RE
{
	auto BSScaleformTranslator::GetLanguageSetting() -> Setting&
	{
		static auto* Language = GetINISetting("sLanguage:General"sv);
		REX::Assert(Language != nullptr);
		return *Language;
	}

	auto BSScaleformTranslator::GetLanguage() -> BSFixedString
	{
		const auto& languageSetting = GetLanguageSetting();
		if (!languageSetting.IsString()) [[unlikely]] {
			REX::Assert(false);
			return BSFixedString(DEFAULT_LANGUAGE);
		}

		return {languageSetting.GetString()};
	}

	auto BSScaleformTranslator::GetTranslationFilePath(std::string_view a_rawName, std::string_view a_language)
		-> std::filesystem::path
	{
		return std::filesystem::path{
			REX::Format(
				"{}/{}{}{}{}"sv,
				TRANSLATION_DIRECTORY_PATH,
				a_rawName,
				TRANSLATION_LANGUAGE_SEPARATOR<char>,
				a_language,
				TRANSLATION_FILE_EXTENSION),
			std::filesystem::path::generic_format
		};
	}

	auto BSScaleformTranslator::GetRelativeTranslationFilePath(std::string_view a_rawName, std::string_view a_language)
		-> std::filesystem::path
	{
		return std::filesystem::path{
			REX::Format(
				"{}/{}{}{}{}"sv,
				TRANSLATION_RELATIVE_DIRECTORY_PATH,
				a_rawName,
				TRANSLATION_LANGUAGE_SEPARATOR<char>,
				a_language,
				TRANSLATION_FILE_EXTENSION),
			std::filesystem::path::generic_format
		};
	}

	void BSScaleformTranslator::AddTranslations(BSStreamParser<wchar_t>& a_parser)
	{
		using FuncType = decltype(&BSScaleformTranslator::AddTranslations);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSScaleformTranslator::AddTranslations);
		std::invoke(FUNC, this, a_parser);
	}

	void BSScaleformTranslator::AddTranslationsFromFile(const char* a_filePath)
	{
		auto resourceParser = BSResourceStreamParser(a_filePath);
		auto parser = BSStreamParser<wchar_t>(resourceParser);
		AddTranslations(parser);
	}

	void BSScaleformTranslator::AddTranslationsByName(std::string_view a_rawName)
	{
		const auto currentLanguage = GetLanguage();
		const auto filePath = GetRelativeTranslationFilePath(a_rawName, currentLanguage);
		AddTranslationsFromFile(filePath.generic_string().data());
	}
}
