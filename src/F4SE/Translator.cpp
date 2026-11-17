#include "F4SE/Translator.hpp"

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScaleformTranslator.hpp"
#include "REX/Error.hpp"
#include "REX/Localization.hpp"
#include "REX/NotNull.hpp"
#include "Scaleform/P/Ptr.hpp"

namespace F4SE
{
	Translator::Translator(
		RE::BSFixedString a_languageCode,
		REX::NotNull<Scaleform::Ptr<RE::BSScaleformTranslator>> a_scaleformTranslator) noexcept :
		_locale(REX::GetLocaleForLanguageOrDefault(a_languageCode)),
		_languageCode(std::move(a_languageCode)),
		_scaleformTranslator(std::move(a_scaleformTranslator))
	{
	}

	Translator::~Translator() noexcept = default;

	auto Translator::GetLocale() const noexcept -> std::locale
	{
		return _locale;
	}

	auto Translator::GetLanguageCode() const noexcept -> RE::BSFixedString
	{
		return _languageCode;
	}

	auto Translator::GetScaleformTranslator() const noexcept -> REX::NotNull<Scaleform::Ptr<RE::BSScaleformTranslator>>
	{
		return _scaleformTranslator;
	}

	auto Translator::LoadFromFile(std::string_view a_rawName) const -> REX::SystemError
	{
		return _scaleformTranslator->translator.LoadFromFile(a_rawName, _languageCode);
	}
}
