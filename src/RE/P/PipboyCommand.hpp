#pragma once

namespace RE::Json
{
	class Value;
}

namespace RE
{
	class PipboyCommandResult;

	class __declspec(novtable) PipboyCommand
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyCommand;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyCommand;

		virtual ~PipboyCommand(); // 0x00

		// add
		virtual void Init(Json::Value* a_json) = 0;				 // 0x01
		virtual auto DoValidate() -> const PipboyCommandResult*; // 0x02 - { return validationResult; }
		virtual auto DoExecute() -> const PipboyCommandResult*;	 // 0x03 - { return executionResult; }

		// members
		std::uint32_t id{0};							// 0x08
		PipboyCommandResult* validationResult{nullptr}; // 0x10
		PipboyCommandResult* executionResult{nullptr};	// 0x18
		bool isReadOnly{false};							// 0x20
	};

	static_assert(sizeof(PipboyCommand) == 0x28);
}
