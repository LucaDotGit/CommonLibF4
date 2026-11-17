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
		inline static constexpr const auto& RTTI = RTTI::PipboyCommandResult;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyCommandResult;

		virtual ~PipboyCommandResult(); // 0x00

		// add
		virtual void Serialize(Json::Value* a_json) = 0; // 0x01

		// members
		std::uint32_t commandID{0}; // 0x08
		bool succeeded{false};		// 0x0C
		bool shouldReply{false};	// 0x0D
	};

	static_assert(sizeof(PipboyCommandResult) == 0x10);
}
