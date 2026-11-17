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
		inline static constexpr const auto& RTTI = RTTI::hkProcess;
		inline static constexpr const auto& VTABLE = VTABLE::hkProcess;

		virtual ~hkProcess(); // 0x00

		// add
		virtual void Unk01() = 0;				// 0x01
		virtual auto GetType() -> std::int64_t; // 0x02 - { return 0; }
		virtual void GetConsumableCommands(
			std::uint8_t** a_commands,
			std::int32_t* a_numCommands);					 // 0x03 - { return; }
		virtual void ConsumeCommand(std::uint8_t a_command); // 0x04 - { return; }
		virtual auto IsOk() -> bool;						 // 0x05 - { return false; }
		virtual void Init();								 // 0x06 - { return; }
		virtual void Step(REX::Float32 a_frameTimeInMs);	 // 0x07 - { return; }

		// members
		bool selectable{false};							// 0x08
		hkDisplaySerializeIStream* inStream{nullptr};	// 0x10
		hkDisplaySerializeOStream* outStream{nullptr};	// 0x18
		hkDebugDisplayHandler* displayHandler{nullptr}; // 0x20
		hkProcessHandler* processHandler{nullptr};		// 0x28
	};

	static_assert(sizeof(hkProcess) == 0x30);
}
