#pragma once

namespace RE
{
	class NiBinaryStream;

	class __declspec(novtable) BSStreamParserData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSStreamParserData };
		inline static constexpr auto VTABLE{ VTABLE::BSStreamParserData };

		BSStreamParserData();

		virtual ~BSStreamParserData() = default; // 00

		// add
		virtual bool Begin() = 0;				 // 01
		virtual void End() = 0;					 // 02
		virtual NiBinaryStream* GetStream() = 0; // 03
	};
}
