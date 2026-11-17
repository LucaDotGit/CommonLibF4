#pragma once

#include "RE/I/IFormFactory.hpp"

namespace RE::Impl
{
	template <class T>
	concept ConcreteFormFactoryConstraint = std::derived_from<T, TESForm> &&
											!REX::pointer<T> &&
											!REX::reference<T> &&
											std::same_as<std::remove_cv_t<decltype(T::FORM_TYPE)>, FormType>;
}

namespace RE
{
	template <Impl::ConcreteFormFactoryConstraint T>
	class __declspec(novtable) ConcreteFormFactory : public IFormFactory // 0x00
	{
	public:
		~ConcreteFormFactory() override; // 0x00

		[[nodiscard]]
		static auto GetFormFactory() -> ConcreteFormFactory*
		{
			const auto factories = GetFormFactories();
			return static_cast<ConcreteFormFactory*>(factories[REX::ToUnsigned(std::to_underlying(T::FORM_TYPE))]);
		}

		[[nodiscard]]
		auto Create() -> T*
		{
			return static_cast<T*>(DoCreate());
		}

		// members
		const char* name{nullptr}; // 0x08
	};
}
