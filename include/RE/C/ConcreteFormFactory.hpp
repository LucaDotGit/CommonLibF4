#pragma once

#include "RE/I/IFormFactory.hpp"

namespace RE
{
	template <class T, FormType ID = T::FORM_TYPE>
	class __declspec(novtable) ConcreteFormFactory
		: public IFormFactory // 00
	{
	public:
		static_assert(std::derived_from<T, TESForm>);

		[[nodiscard]] static ConcreteFormFactory* GetFormFactory()
		{
			const auto factories = GetFormFactories();
			return static_cast<ConcreteFormFactory*>(factories[std::to_underlying(ID)]);
		}

		[[nodiscard]] T* Create()
		{
			return static_cast<T*>(DoCreate());
		}

		// members
		const char* name{ nullptr };
	};
}
