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
		inline static constexpr const auto& RTTI = RTTI::IFormFactory;
		inline static constexpr const auto& VTABLE = VTABLE::IFormFactory;

		virtual ~IFormFactory(); // 0x00

		// add
		virtual auto DoCreate() -> TESForm* = 0;							  // 0x01
		virtual auto GetFormName() const -> const char* = 0;				  // 0x02
		virtual auto GetFormID() const -> FormType = 0;						  // 0x03
		virtual auto GetObjectName() const -> const char*;					  // 0x04 - { return nullptr; }
		virtual auto GetObjectType() const -> OBJECT_TYPE;					  // 0x05
		virtual auto GetObjectCategory() const -> OBJECT_CATEGORY_TYPE;		  // 0x06
		virtual auto GetPropertyBridge() const -> BGSMod::Property::BridgeI*; // 0x07 - { return nullptr; }

		[[nodiscard]]
		static auto GetFormFactories() -> std::span<IFormFactory*, std::to_underlying(FormType::_Count)>;
	};

	static_assert(sizeof(IFormFactory) == 0x08);
}
