#pragma once

#include "RE/B/BSFixedString.hpp"
#include "REX/Error.hpp"
#include "REX/NotNull.hpp"
#include "Scaleform/P/Ptr.hpp"

namespace RE
{
	class BSScaleformTranslator;
}

namespace F4SE
{
	class Translator final
	{
	public:
		Translator(
			RE::BSFixedString a_languageCode,
			REX::NotNull<Scaleform::Ptr<RE::BSScaleformTranslator>> a_scaleformTranslator) noexcept;

		~Translator() noexcept;

		Translator(const Translator&) noexcept = default;
		Translator(Translator&&) noexcept = default;

		auto operator=(const Translator&) noexcept -> Translator& = default;
		auto operator=(Translator&&) noexcept -> Translator& = default;

		[[nodiscard]]
		auto GetLocale() const noexcept -> std::locale;
		[[nodiscard]]
		auto GetLanguageCode() const noexcept -> RE::BSFixedString;
		[[nodiscard]]
		auto GetScaleformTranslator() const noexcept -> REX::NotNull<Scaleform::Ptr<RE::BSScaleformTranslator>>;

		auto LoadFromFile(std::string_view a_rawName) const -> REX::SystemError;

	private:
		std::locale _locale;
		RE::BSFixedString _languageCode;
		REX::NotNull<Scaleform::Ptr<RE::BSScaleformTranslator>> _scaleformTranslator;
	};
}
