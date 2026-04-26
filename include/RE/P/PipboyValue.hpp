#pragma once

namespace RE::Json
{
	class Value;
}

namespace RE
{
	class BSBinarySerializer;

	class __declspec(novtable) PipboyValue
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyValue };
		inline static constexpr auto VTABLE{ VTABLE::PipboyValue };

		enum class SERIALIZATION_DATA_TYPE : std::int32_t
		{
			kBool = 0,
			kInt8 = 1,
			kUint8 = 2,
			kInt32 = 3,
			kUint32 = 4,
			kFloat = 5,
			kString = 6,
			kArray = 7,
			kObject = 8
		};

		PipboyValue(PipboyValue* a_parentValue)
			: parentValue(a_parentValue)
		{
			REL::EmplaceVtable(this);
		}

		virtual ~PipboyValue() = default; // 00

		// add
		virtual void CleanDirtyToGame();													   // 01
		virtual void Serialize(Json::Value* a_json) = 0;									   // 02
		virtual void SerializeChanges(BSBinarySerializer& a_serializer, bool a_fullSerialize); // 03
		virtual SERIALIZATION_DATA_TYPE GetType() = 0;										   // 04

		// members
		std::uint32_t id{ 0 };				 // 08
		bool isDirtyGame{ false };			 // 0C
		bool isDirtyToCompanion{ false };	 // 0D
		PipboyValue* parentValue{ nullptr }; // 10
	};
	static_assert(sizeof(PipboyValue) == 0x18);
}
