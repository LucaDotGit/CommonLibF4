#pragma once

namespace RE::BSScript::ByteCode
{
	struct PackedInstructionStream
	{
	public:
		PackedInstructionStream();
		PackedInstructionStream(
			void* a_instructions,
			std::uint32_t a_numInstrBits,
			std::uint16_t a_jumpTargetBitCount,
			std::int8_t a_localVariableBitCount,
			std::int8_t a_memberVariableBitCount);

		// members
		std::uint32_t numInstructionBits;	// 00
		std::uint16_t jumpTargetBitCount;	// 04
		std::int8_t localVariableBitCount;	// 06
		std::int8_t memberVariableBitCount; // 07
		void* instructions;					// 08
	};
	static_assert(sizeof(PackedInstructionStream) == 0x10);
}
