#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTranslator.hpp"
#include "Scaleform/G/GFx_Translator.hpp"

namespace RE
{
	class Setting;

	template <class T>
	class BSStreamParser;

	class __declspec(novtable) BSScaleformTranslator : public Scaleform::GFx::Translator // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScaleformTranslator;
		inline static constexpr const auto& VTABLE = VTABLE::BSScaleformTranslator;

		template <REX::character CharT>
		inline static constexpr auto TRANSLATION_LANGUAGE_SEPARATOR = static_cast<CharT>('_');

		template <REX::character CharT>
		inline static constexpr auto TRANSLATION_KEY_PREFIX = static_cast<CharT>('$');

		inline static constexpr auto TRANSLATION_DIRECTORY_PATH = "Data/Interface/Translations"sv;
		inline static constexpr auto TRANSLATION_RELATIVE_DIRECTORY_PATH = "Interface/Translations"sv;
		inline static constexpr auto TRANSLATION_FILE_EXTENSION = ".txt"sv;

		inline static constexpr auto DEFAULT_LANGUAGE = "en"sv;

		template <REX::character CharT>
		[[nodiscard]]
		static constexpr auto IsKeyValid(std::basic_string_view<CharT> a_key) noexcept -> bool
		{
			return !a_key.empty() && a_key.front() == TRANSLATION_KEY_PREFIX<CharT>;
		}

		[[nodiscard]]
		static auto GetLanguageSetting() -> Setting&;

		[[nodiscard]]
		static auto GetLanguage() -> BSFixedString;

		[[nodiscard]]
		static auto GetTranslationFilePath(std::string_view a_rawName, std::string_view a_language)
			-> std::filesystem::path;
		[[nodiscard]]
		static auto GetRelativeTranslationFilePath(std::string_view a_rawName, std::string_view a_language)
			-> std::filesystem::path;

		[[nodiscard]]
		auto GetTranslator() noexcept -> auto&
		{
			return translator;
		}

		[[nodiscard]]
		auto GetTranslator() const noexcept -> const auto&
		{
			return translator;
		}

		void AddTranslations(BSStreamParser<wchar_t>& a_parser);
		void AddTranslationsFromFile(const char* a_filePath);
		void AddTranslationsByName(std::string_view a_rawName);

		// members
		BSTranslator translator; // 0x20
	};

	static_assert(sizeof(BSScaleformTranslator) == 0x50);
}
