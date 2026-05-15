#include "RE/B/BSScaleformTranslator.hpp"

#include "RE/B/BSResourceStreamParser.hpp"
#include "RE/B/BSStreamParser.hpp"
#include "RE/S/Setting.hpp"
#include "RE/S/SettingUtil.hpp"

namespace RE
{
	Setting& BSScaleformTranslator::GetLanguageSetting()
	{
		static auto* Language = GetINISetting(LANGUAGE_SETTING_KEY);
		return *Language;
	}

	std::string_view BSScaleformTranslator::GetLanguage()
	{
		auto& languageSetting = GetLanguageSetting();
		if (!languageSetting.IsString()) [[unlikely]] {
			REX::Assert(false);
			return DEFAULT_LANGUAGE;
		}

		return languageSetting.GetString();
	}

	std::filesystem::path BSScaleformTranslator::GetTranslationFilePath(std::string_view a_rawName, std::string_view a_language)
	{
		return std::filesystem::path{
			REX::Format("{}/{}{}{}{}"sv,
				TRANSLATION_DIRECTORY_PATH,
				a_rawName,
				TRANSLATION_LANGUAGE_SEPARATOR<char>,
				a_language,
				TRANSLATION_FILE_EXTENSION),
			std::filesystem::path::generic_format
		};
	}

	std::filesystem::path BSScaleformTranslator::GetRelativeTranslationFilePath(std::string_view a_rawName, std::string_view a_language)
	{
		return std::filesystem::path{
			REX::Format("{}/{}{}{}{}"sv,
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
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSScaleformTranslator::AddTranslations };
		std::invoke(FUNC, this, a_parser);
	}

	void BSScaleformTranslator::AddTranslationsFromFile(const char* a_filePath)
	{
		auto resourceParser = BSResourceStreamParser(a_filePath);
		auto parser = BSStreamParser<wchar_t>(std::addressof(resourceParser));
		AddTranslations(parser);
	}

	void BSScaleformTranslator::AddTranslationsByName(std::string_view a_rawName)
	{
		const auto currentLanguage = GetLanguage();
		const auto filePath = GetRelativeTranslationFilePath(a_rawName, currentLanguage);
		AddTranslationsFromFile(filePath.generic_string().data());
	}

	template bool BSScaleformTranslator::IsKeyValid(std::string_view) noexcept;
	template bool BSScaleformTranslator::IsKeyValid(std::wstring_view) noexcept;
}
