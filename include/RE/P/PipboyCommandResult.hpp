#pragma once

namespace RE::Json
{
	class Value;
}

namespace RE
{
	class __declspec(novtable) PipboyCommandResult
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyCommandResult };
		inline static constexpr auto VTABLE{ VTABLE::PipboyCommandResult };

		virtual ~PipboyCommandResult(); // 00

		// add
		virtual void Serialize(Json::Value* a_json) = 0; // 01

		// members
		std::uint32_t commandID{ 0 }; // 08
		bool succeeded{ false };	  // 0C
		bool shouldReply{ false };	  // 0D
	};
	static_assert(sizeof(PipboyCommandResult) == 0x10);
}
