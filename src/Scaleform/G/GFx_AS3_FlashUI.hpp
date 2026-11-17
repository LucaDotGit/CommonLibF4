#pragma once

namespace Scaleform::GFx::AS3
{
	class __declspec(novtable) FlashUI
	{
	public:
		enum class OutputMessageType : std::int32_t
		{
			Message = 0,
			Error = 1,
			Warning = 2,
			Action = 3
		};

		enum class StateType : std::int32_t
		{
			Error = 0,
			Breakpoint = 1,
			PreStep = 2,
			Step = 3
		};

		virtual ~FlashUI(); // 0x00

		// add
		virtual void Output(OutputMessageType a_type, const char* a_msg) = 0; // 0x01
		virtual auto OnOpCode(std::uint64_t a_opCode) -> bool = 0;			  // 0x02

		// members
		StateType state;  // 0x08
		bool needToCheck; // 0x0C
	};

	static_assert(sizeof(FlashUI) == 0x10);
}
