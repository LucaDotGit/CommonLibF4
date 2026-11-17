#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSString.hpp"
#include "RE/P/PipboyValue.hpp"

namespace RE
{
	template <class T>
	class PipboyPrimitiveValue;

	template <>
	class __declspec(novtable) PipboyPrimitiveValue<bool> : public PipboyValue // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyPrimitiveValue_bool_;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyPrimitiveValue_bool_;

		explicit PipboyPrimitiveValue(PipboyValue* a_parentValue, bool a_value = false) :
			PipboyValue(a_parentValue),
			value(a_value)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPrimitiveValue() override; // 0x00

		// override (PipboyValue)
		void CleanDirtyToGame() override;															// 0x00
		void Serialize(Json::Value& a_json) override;												// 0x01
		void SerializeChanges(BSBinarySerializer& a_serializer, bool a_fullSerialization) override; // 0x03
		auto GetType() -> SERIALIZATION_DATA_TYPE override; // 0x04 - { return SERIALIZATION_DATA_TYPE::Bool; }

		// members
		bool value; // 0x18
	};

	static_assert(sizeof(PipboyPrimitiveValue<bool>) == 0x20);

	template <>
	class __declspec(novtable) PipboyPrimitiveValue<std::int8_t> : public PipboyValue // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyPrimitiveValue_char_;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyPrimitiveValue_char_;

		explicit PipboyPrimitiveValue(PipboyValue* a_parentValue, std::int8_t a_value = 0) :
			PipboyValue(a_parentValue),
			value(a_value)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPrimitiveValue() override; // 0x00

		// override (PipboyValue)
		void CleanDirtyToGame() override;															// 0x00
		void Serialize(Json::Value& a_json) override;												// 0x01
		void SerializeChanges(BSBinarySerializer& a_serializer, bool a_fullSerialization) override; // 0x03
		auto GetType() -> SERIALIZATION_DATA_TYPE override; // 0x04 - { return SERIALIZATION_DATA_TYPE::Int8; }

		// members
		std::int8_t value; // 0x18
	};

	static_assert(sizeof(PipboyPrimitiveValue<std::int8_t>) == 0x20);

	template <>
	class __declspec(novtable) PipboyPrimitiveValue<std::uint8_t> : public PipboyValue // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyPrimitiveValue_unsignedchar_;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyPrimitiveValue_unsignedchar_;

		explicit PipboyPrimitiveValue(PipboyValue* a_parentValue, std::uint8_t a_value = 0) :
			PipboyValue(a_parentValue),
			value(a_value)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPrimitiveValue() override; // 0x00

		// override (PipboyValue)
		void CleanDirtyToGame() override;															// 0x00
		void Serialize(Json::Value& a_json) override;												// 0x01
		void SerializeChanges(BSBinarySerializer& a_serializer, bool a_fullSerialization) override; // 0x03
		auto GetType() -> SERIALIZATION_DATA_TYPE override; // 0x04 - { return SERIALIZATION_DATA_TYPE::Uint8; }

		// members
		std::uint8_t value; // 0x18
	};

	static_assert(sizeof(PipboyPrimitiveValue<std::uint8_t>) == 0x20);

	template <>
	class __declspec(novtable) PipboyPrimitiveValue<std::int32_t> : public PipboyValue // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyPrimitiveValue_int_;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyPrimitiveValue_int_;

		explicit PipboyPrimitiveValue(PipboyValue* a_parentValue, std::int32_t a_value = 0) :
			PipboyValue(a_parentValue),
			value(a_value)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPrimitiveValue() override; // 0x00

		// override (PipboyValue)
		void CleanDirtyToGame() override;															// 0x00
		void Serialize(Json::Value& a_json) override;												// 0x01
		void SerializeChanges(BSBinarySerializer& a_serializer, bool a_fullSerialization) override; // 0x03
		auto GetType() -> SERIALIZATION_DATA_TYPE override; // 0x04 - { return SERIALIZATION_DATA_TYPE::Int32; }

		// members
		std::int32_t value; // 0x18
	};

	static_assert(sizeof(PipboyPrimitiveValue<std::int32_t>) == 0x20);

	template <>
	class __declspec(novtable) PipboyPrimitiveValue<std::uint32_t> : public PipboyValue // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyPrimitiveValue_unsignedint_;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyPrimitiveValue_unsignedint_;

		explicit PipboyPrimitiveValue(PipboyValue* a_parentValue, std::uint32_t a_value = 0) :
			PipboyValue(a_parentValue),
			value(a_value)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPrimitiveValue() override; // 0x00

		// override (PipboyValue)
		void CleanDirtyToGame() override;															// 0x00
		void Serialize(Json::Value& a_json) override;												// 0x01
		void SerializeChanges(BSBinarySerializer& a_serializer, bool a_fullSerialization) override; // 0x03
		auto GetType() -> SERIALIZATION_DATA_TYPE override; // 0x04 - { return SERIALIZATION_DATA_TYPE::Uint32; }

		// members
		std::uint32_t value; // 0x18
	};

	static_assert(sizeof(PipboyPrimitiveValue<std::uint32_t>) == 0x20);

	template <>
	class __declspec(novtable) PipboyPrimitiveValue<REX::Float32> : public PipboyValue // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyPrimitiveValue_float_;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyPrimitiveValue_float_;

		explicit PipboyPrimitiveValue(
			PipboyValue* a_parentValue,
			REX::Float32 a_value = static_cast<REX::Float32>(0.0)) :
			PipboyValue(a_parentValue),
			value(a_value)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPrimitiveValue() override; // 0x00

		// override (PipboyValue)
		void CleanDirtyToGame() override;															// 0x00
		void Serialize(Json::Value& a_json) override;												// 0x01
		void SerializeChanges(BSBinarySerializer& a_serializer, bool a_fullSerialization) override; // 0x03
		auto GetType() -> SERIALIZATION_DATA_TYPE override; // 0x04 - { return SERIALIZATION_DATA_TYPE::Float; }

		// members
		REX::Float32 value; // 0x18
	};

	static_assert(sizeof(PipboyPrimitiveValue<REX::Float32>) == 0x20);

	template <>
	class __declspec(novtable) PipboyPrimitiveValue<BSString> : public PipboyValue // 0x00
	{
	public:
		inline static constexpr const auto& RTTI =
			RTTI::PipboyPrimitiveValue_BSStringT_char_1_DynamicMemoryManagementPol__;
		inline static constexpr const auto& VTABLE =
			VTABLE::PipboyPrimitiveValue_BSStringT_char_1_DynamicMemoryManagementPol__;

		explicit PipboyPrimitiveValue(PipboyValue* a_parentValue, BSString a_value = {}) :
			PipboyValue(a_parentValue),
			value(std::move(a_value))
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPrimitiveValue() override; // 0x00

		// override (PipboyValue)
		void CleanDirtyToGame() override;															// 0x00
		void Serialize(Json::Value& a_json) override;												// 0x01
		void SerializeChanges(BSBinarySerializer& a_serializer, bool a_fullSerialization) override; // 0x03
		auto GetType() -> SERIALIZATION_DATA_TYPE override; // 0x04 - { return SERIALIZATION_DATA_TYPE::String; }

		// members
		BSString value; // 0x18
	};

	static_assert(sizeof(PipboyPrimitiveValue<BSString>) == 0x28);

	template <>
	class __declspec(novtable) PipboyPrimitiveValue<BSFixedStringCS> : public PipboyValue // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyPrimitiveValue_BSFixedStringCS_;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyPrimitiveValue_BSFixedStringCS_;

		explicit PipboyPrimitiveValue(PipboyValue* a_parentValue, BSFixedStringCS a_value = {}) :
			PipboyValue(a_parentValue),
			value(std::move(a_value))
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPrimitiveValue() override; // 0x00

		// override (PipboyValue)
		void CleanDirtyToGame() override;															// 0x00
		void Serialize(Json::Value& a_json) override;												// 0x01
		void SerializeChanges(BSBinarySerializer& a_serializer, bool a_fullSerialization) override; // 0x03
		auto GetType() -> SERIALIZATION_DATA_TYPE override; // 0x04 - { return SERIALIZATION_DATA_TYPE::String; }

		// members
		BSFixedStringCS value; // 0x18
	};

	static_assert(sizeof(PipboyPrimitiveValue<BSFixedStringCS>) == 0x20);

	template <>
	class __declspec(novtable) PipboyPrimitiveValue<BGSLocalizedString> : public PipboyValue // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyPrimitiveValue_BGSLocalizedString_;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyPrimitiveValue_BGSLocalizedString_;

		explicit PipboyPrimitiveValue(PipboyValue* a_parentValue, BGSLocalizedString a_value = {}) :
			PipboyValue(a_parentValue),
			value(std::move(a_value))
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPrimitiveValue() override; // 0x00

		// override (PipboyValue)
		void CleanDirtyToGame() override;															// 0x00
		void Serialize(Json::Value& a_json) override;												// 0x01
		void SerializeChanges(BSBinarySerializer& a_serializer, bool a_fullSerialization) override; // 0x03
		auto GetType() -> SERIALIZATION_DATA_TYPE override; // 0x04 - { return SERIALIZATION_DATA_TYPE::String; }

		// members
		BGSLocalizedString value; // 0x18
	};

	static_assert(sizeof(PipboyPrimitiveValue<BSFixedStringCS>) == 0x20);
}
