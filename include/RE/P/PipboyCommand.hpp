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
		inline static constexpr auto RTTI{ RTTI::PipboyCommand };
		inline static constexpr auto VTABLE{ VTABLE::PipboyCommand };

		virtual ~PipboyCommand(); // 00

		// add
		virtual void Init(Json::Value* a_json) = 0;		 // 01
		virtual const PipboyCommandResult* DoValidate(); // 02
		virtual const PipboyCommandResult* DoExecute();	 // 03

		// members
		std::uint32_t id{ 0 };							  // 08
		PipboyCommandResult* validationResult{ nullptr }; // 10
		PipboyCommandResult* executionResult{ nullptr };  // 18
		bool isReadonly{ false };						  // 20
	};
	static_assert(sizeof(PipboyCommand) == 0x28);
}