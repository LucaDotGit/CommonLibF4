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
			REX::Enum<Opcode, std::int32_t> opcode; // 0x00
			std::uint16_t numArguments;				// 0x04
			std::uint32_t bitStart;					// 0x08
		};

		static_assert(sizeof(InstructionInfo) == 0x0C);

		[[nodiscard]]
		auto GetInstructionByteSize() const noexcept -> std::uint32_t;
		[[nodiscard]]
		auto Clone() const -> PackedInstructionStream;

		// members
		std::uint32_t numInstructionBits;	 // 0x00
		std::uint16_t jumpTargetBitCount;	 // 0x04
		std::uint8_t localVariableBitCount;	 // 0x06
		std::uint8_t memberVariableBitCount; // 0x07
		std::byte* instructions;			 // 0x08
	};

	static_assert(sizeof(PackedInstructionStream) == 0x10);
}
