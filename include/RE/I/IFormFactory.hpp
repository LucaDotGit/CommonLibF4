#pragma once

#include "RE/F/FormType.hpp"

namespace RE::BGSMod::Property
{
	class BridgeI;
}

namespace RE
{
	enum class OBJECT_CATEGORY_TYPE : std::int32_t;
	enum class OBJECT_TYPE : std::int32_t;

	class __declspec(novtable) IFormFactory
	{
	public:
		inline static constexpr auto RTTI{ RTTI::IFormFactory };
		inline static constexpr auto VTABLE{ VTABLE::IFormFactory };

		virtual ~IFormFactory(); // 00

		// add
		virtual TESForm* DoCreate() = 0;							  // 01
		virtual const char* GetFormName() const = 0;				  // 02
		virtual FormType GetFormID() const = 0;						  // 03
		virtual const char* GetObjectName() const;					  // 04 - { return nullptr; }
		virtual OBJECT_TYPE GetObjectType() const;					  // 05
		virtual OBJECT_CATEGORY_TYPE GetObjectCategory() const;		  // 06
		virtual BGSMod::Property::BridgeI* GetPropertyBridge() const; // 07 - { return nullptr; }

		[[nodiscard]] static auto GetFormFactories()
			-> std::span<IFormFactory*, std::to_underlying(FormType::kTotal)>;
	};
	static_assert(sizeof(IFormFactory) == 0x08);
}
