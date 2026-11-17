#include "RE/B/BSScript_ByteCode_PackedInstructionStream.hpp"

#include "RE/M/MemoryManager.hpp"

namespace RE::BSScript::ByteCode
{
	auto PackedInstructionStream::GetInstructionByteSize() const noexcept -> std::uint32_t
	{
		return (numInstructionBits + 7) / 8;
	}

	auto PackedInstructionStream::Clone() const -> PackedInstructionStream
	{
		auto result = PackedInstructionStream{
			.numInstructionBits = numInstructionBits,
			.jumpTargetBitCount = jumpTargetBitCount,
			.localVariableBitCount = localVariableBitCount,
			.memberVariableBitCount = memberVariableBitCount,
			.instructions = nullptr
		};

		if (!instructions) {
			return result;
		}

		const auto byteSize = GetInstructionByteSize();
		if (byteSize == 0) {
			return result;
		}

		auto* newInstructions = malloc<std::byte>(byteSize);
		if (!newInstructions) [[unlikely]] {
			REX::Throw<std::bad_alloc>();
		}

		std::copy_n(instructions, byteSize, newInstructions);
		result.instructions = newInstructions;

		return result;
	}
}
