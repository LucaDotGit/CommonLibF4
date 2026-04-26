#include "RE/B/BSScript_ByteCode_PackedInstructionStream.hpp"

#include "RE/M/MemoryManager.hpp"

namespace RE::BSScript::ByteCode
{
	std::uint32_t PackedInstructionStream::GetInstructionByteSize() const noexcept
	{
		return (numInstructionBits + 7) / 8;
	}

	PackedInstructionStream PackedInstructionStream::CopyInstructionStream() const noexcept
	{
		auto result = PackedInstructionStream();
		result.numInstructionBits = numInstructionBits;
		result.jumpTargetBitCount = jumpTargetBitCount;
		result.localVariableBitCount = localVariableBitCount;
		result.memberVariableBitCount = memberVariableBitCount;
		result.instructions = nullptr;

		const auto byteSize = GetInstructionByteSize();
		if (byteSize == 0 || !instructions) {
			return result;
		}

		auto* newInstructions = calloc<std::byte>(byteSize);
		if (!newInstructions) [[unlikely]] {
			REX::AllocationFail();
		}

		std::copy_n(instructions, byteSize, newInstructions);
		result.instructions = newInstructions;

		return result;
	}
}
