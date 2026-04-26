#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSStringT.hpp"
#include "RE/P/PipboyValue.hpp"

namespace RE
{
	template <class T>
	class PipboyPrimitiveValue;

	template <>
	class __declspec(novtable) PipboyPrimitiveValue<bool>
		: public PipboyValue // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyPrimitiveValue_bool_ };
		inline static constexpr auto VTABLE{ VTABLE::PipboyPrimitiveValue_bool_ };

		PipboyPrimitiveValue(bool a_value, PipboyValue* a_parentValue)
			: PipboyValue(a_parentValue),
			  value(a_value)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPrimitiveValue() override = default; // 00

		// override (PipboyValue)
		void CleanDirtyToGame() override { return; }																							 // 00
		void Serialize([[maybe_unused]] Json::Value* a_json) override { return; }																 // 01
		void SerializeChanges([[maybe_unused]] BSBinarySerializer& a_serializer, [[maybe_unused]] bool a_fullSerialization) override { return; } // 03
		SERIALIZATION_DATA_TYPE GetType() override { return SERIALIZATION_DATA_TYPE::kBool; }													 // 04

		// members
		bool value; // 18
	};
	static_assert(sizeof(PipboyPrimitiveValue<bool>) == 0x20);

	template <>
	class __declspec(novtable) PipboyPrimitiveValue<std::int8_t>
		: public PipboyValue // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyPrimitiveValue_char_ };
		inline static constexpr auto VTABLE{ VTABLE::PipboyPrimitiveValue_char_ };

		PipboyPrimitiveValue(std::int8_t a_value, PipboyValue* a_parentValue)
			: PipboyValue(a_parentValue),
			  value(a_value)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPrimitiveValue() override = default; // 00

		// override (PipboyValue)
		void CleanDirtyToGame() override { return; }																							 // 00
		void Serialize([[maybe_unused]] Json::Value* a_json) override { return; }																 // 01
		void SerializeChanges([[maybe_unused]] BSBinarySerializer& a_serializer, [[maybe_unused]] bool a_fullSerialization) override { return; } // 03
		SERIALIZATION_DATA_TYPE GetType() override { return SERIALIZATION_DATA_TYPE::kInt8; }													 // 04

		// members
		std::int8_t value; // 18
	};
	static_assert(sizeof(PipboyPrimitiveValue<std::int8_t>) == 0x20);

	template <>
	class __declspec(novtable) PipboyPrimitiveValue<std::uint8_t>
		: public PipboyValue // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyPrimitiveValue_unsignedchar_ };
		inline static constexpr auto VTABLE{ VTABLE::PipboyPrimitiveValue_unsignedchar_ };

		PipboyPrimitiveValue(std::uint8_t a_value, PipboyValue* a_parentValue)
			: PipboyValue(a_parentValue),
			  value(a_value)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPrimitiveValue() override = default; // 00

		// override (PipboyValue)
		void CleanDirtyToGame() override { return; }																							 // 00
		void Serialize([[maybe_unused]] Json::Value* a_json) override { return; }																 // 01
		void SerializeChanges([[maybe_unused]] BSBinarySerializer& a_serializer, [[maybe_unused]] bool a_fullSerialization) override { return; } // 03
		SERIALIZATION_DATA_TYPE GetType() override { return SERIALIZATION_DATA_TYPE::kUint8; }													 // 04

		// members
		std::uint8_t value; // 18
	};
	static_assert(sizeof(PipboyPrimitiveValue<std::uint8_t>) == 0x20);

	template <>
	class __declspec(novtable) PipboyPrimitiveValue<std::int32_t>
		: public PipboyValue // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyPrimitiveValue_int_ };
		inline static constexpr auto VTABLE{ VTABLE::PipboyPrimitiveValue_int_ };

		PipboyPrimitiveValue(std::int32_t a_value, PipboyValue* a_parentValue)
			: PipboyValue(a_parentValue),
			  value(a_value)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPrimitiveValue() override = default; // 00

		// override (PipboyValue)
		void CleanDirtyToGame() override { return; }																							 // 00
		void Serialize([[maybe_unused]] Json::Value* a_json) override { return; }																 // 01
		void SerializeChanges([[maybe_unused]] BSBinarySerializer& a_serializer, [[maybe_unused]] bool a_fullSerialization) override { return; } // 03
		SERIALIZATION_DATA_TYPE GetType() override { return SERIALIZATION_DATA_TYPE::kInt32; }													 // 04

		// members
		std::int32_t value; // 18
	};
	static_assert(sizeof(PipboyPrimitiveValue<std::int32_t>) == 0x20);

	template <>
	class __declspec(novtable) PipboyPrimitiveValue<std::uint32_t>
		: public PipboyValue // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyPrimitiveValue_unsignedint_ };
		inline static constexpr auto VTABLE{ VTABLE::PipboyPrimitiveValue_unsignedint_ };

		PipboyPrimitiveValue(std::uint32_t a_value, PipboyValue* a_parentValue)
			: PipboyValue(a_parentValue),
			  value(a_value)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPrimitiveValue() override = default; // 00

		// override (PipboyValue)
		void CleanDirtyToGame() override { return; }																							 // 00
		void Serialize([[maybe_unused]] Json::Value* a_json) override { return; }																 // 01
		void SerializeChanges([[maybe_unused]] BSBinarySerializer& a_serializer, [[maybe_unused]] bool a_fullSerialization) override { return; } // 03
		SERIALIZATION_DATA_TYPE GetType() override { return SERIALIZATION_DATA_TYPE::kUint32; }													 // 04

		// members
		std::uint32_t value; // 18
	};
	static_assert(sizeof(PipboyPrimitiveValue<std::uint32_t>) == 0x20);

	template <>
	class __declspec(novtable) PipboyPrimitiveValue<REX::Float32>
		: public PipboyValue // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyPrimitiveValue_float_ };
		inline static constexpr auto VTABLE{ VTABLE::PipboyPrimitiveValue_float_ };

		PipboyPrimitiveValue(REX::Float32 a_value, PipboyValue* a_parentValue)
			: PipboyValue(a_parentValue),
			  value(a_value)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPrimitiveValue() override = default; // 00

		// override (PipboyValue)
		void CleanDirtyToGame() override { return; }																							 // 00
		void Serialize([[maybe_unused]] Json::Value* a_json) override { return; }																 // 01
		void SerializeChanges([[maybe_unused]] BSBinarySerializer& a_serializer, [[maybe_unused]] bool a_fullSerialization) override { return; } // 03
		SERIALIZATION_DATA_TYPE GetType() override { return SERIALIZATION_DATA_TYPE::kFloat; }													 // 04

		// members
		REX::Float32 value; // 18
	};
	static_assert(sizeof(PipboyPrimitiveValue<REX::Float32>) == 0x20);

	template <>
	class __declspec(novtable) PipboyPrimitiveValue<BSString>
		: public PipboyValue // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyPrimitiveValue_BSStringT_char_1_DynamicMemoryManagementPol__ };
		inline static constexpr auto VTABLE{ VTABLE::PipboyPrimitiveValue_BSStringT_char_1_DynamicMemoryManagementPol__ };

		PipboyPrimitiveValue(BSString a_value, PipboyValue* a_parentValue)
			: PipboyValue(a_parentValue),
			  value(std::move(a_value))
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPrimitiveValue() override = default; // 00

		// override (PipboyValue)
		void CleanDirtyToGame() override { return; }																							 // 00
		void Serialize([[maybe_unused]] Json::Value* a_json) override { return; }																 // 01
		void SerializeChanges([[maybe_unused]] BSBinarySerializer& a_serializer, [[maybe_unused]] bool a_fullSerialization) override { return; } // 03
		SERIALIZATION_DATA_TYPE GetType() override { return SERIALIZATION_DATA_TYPE::kString; }													 // 04

		// members
		BSString value; // 18
	};
	static_assert(sizeof(PipboyPrimitiveValue<BSString>) == 0x28);

	template <>
	class __declspec(novtable) PipboyPrimitiveValue<BSFixedStringCS>
		: public PipboyValue // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyPrimitiveValue_BSFixedStringCS_ };
		inline static constexpr auto VTABLE{ VTABLE::PipboyPrimitiveValue_BSFixedStringCS_ };

		PipboyPrimitiveValue(BSFixedStringCS a_value, PipboyValue* a_parentValue)
			: PipboyValue(a_parentValue),
			  value(std::move(a_value))
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPrimitiveValue() override = default; // 00

		// override (PipboyValue)
		void CleanDirtyToGame() override { return; }																							 // 00
		void Serialize([[maybe_unused]] Json::Value* a_json) override { return; }																 // 01
		void SerializeChanges([[maybe_unused]] BSBinarySerializer& a_serializer, [[maybe_unused]] bool a_fullSerialization) override { return; } // 03
		SERIALIZATION_DATA_TYPE GetType() override { return SERIALIZATION_DATA_TYPE::kString; }													 // 04

		// members
		BSFixedStringCS value; // 18
	};
	static_assert(sizeof(PipboyPrimitiveValue<BSFixedStringCS>) == 0x20);

	template <>
	class __declspec(novtable) PipboyPrimitiveValue<BGSLocalizedString>
		: public PipboyValue // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyPrimitiveValue_BGSLocalizedString_ };
		inline static constexpr auto VTABLE{ VTABLE::PipboyPrimitiveValue_BGSLocalizedString_ };

		PipboyPrimitiveValue(BGSLocalizedString a_value, PipboyValue* a_parentValue)
			: PipboyValue(a_parentValue),
			  value(std::move(a_value))
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPrimitiveValue() override = default; // 00

		// override (PipboyValue)
		void CleanDirtyToGame() override { return; }																							 // 00
		void Serialize([[maybe_unused]] Json::Value* a_json) override { return; }																 // 01
		void SerializeChanges([[maybe_unused]] BSBinarySerializer& a_serializer, [[maybe_unused]] bool a_fullSerialization) override { return; } // 03
		SERIALIZATION_DATA_TYPE GetType() override { return SERIALIZATION_DATA_TYPE::kString; }													 // 04

		// members
		BGSLocalizedString value; // 18
	};
	static_assert(sizeof(PipboyPrimitiveValue<BSFixedStringCS>) == 0x20);
}
