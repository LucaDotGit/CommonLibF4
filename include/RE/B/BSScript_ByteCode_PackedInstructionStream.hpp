#pragma once

namespace RE::BSScript::ByteCode
{
	enum class Opcode : std::int32_t;

	class PackedInstructionStream
	{
	public:
		class InstructionInfo
		{
		public:
			// members
			REX::Enum<Opcode, std::int32_t> opcode; // 00
			std::uint16_t numArguments;				// 04
			std::uint32_t bitStart;					// 08
		};
		static_assert(sizeof(InstructionInfo) == 0x0C);

		[[nodiscard]] std::uint32_t GetInstructionByteSize() const noexcept;
		[[nodiscard]] PackedInstructionStream CopyInstructionStream() const noexcept;

		// members
		std::uint32_t numInstructionBits;	 // 00
		std::uint16_t jumpTargetBitCount;	 // 04
		std::uint8_t localVariableBitCount;	 // 06
		std::uint8_t memberVariableBitCount; // 07
		std::byte* instructions;			 // 08
	};
	static_assert(sizeof(PackedInstructionStream) == 0x10);
}
