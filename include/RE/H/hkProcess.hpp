#pragma once

namespace RE
{
	class hkDebugDisplayHandler;
	class hkDisplaySerializeIStream;
	class hkDisplaySerializeOStream;
	class hkProcessHandler;

	class __declspec(novtable) hkProcess
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hkProcess };
		inline static constexpr auto VTABLE{ VTABLE::hkProcess };

		virtual ~hkProcess(); // 00

		// add
		virtual void Unk01() = 0;																	// 01
		virtual std::int64_t GetType();																// 02 - { return 0; }
		virtual void GetConsumableCommands(std::uint8_t** a_commands, std::int32_t* a_numCommands); // 03 - { return; }
		virtual void ConsumeCommand(std::uint8_t a_command);										// 04 - { return; }
		virtual bool IsOk();																		// 05 - { return false; }
		virtual void Init();																		// 06 - { return; }
		virtual void Step(REX::Float32 a_frameTimeInMs);											// 07 - { return; }

		// members
		bool selectable{ false };						  // 08
		hkDisplaySerializeIStream* inStream{ nullptr };	  // 10
		hkDisplaySerializeOStream* outStream{ nullptr };  // 18
		hkDebugDisplayHandler* displayHandler{ nullptr }; // 20
		hkProcessHandler* processHandler{ nullptr };	  // 28
	};
	static_assert(sizeof(hkProcess) == 0x30);
}
