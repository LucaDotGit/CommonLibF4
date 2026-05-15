#pragma once

#include "RE/H/hkBlockStreamBase.hpp"

namespace RE
{
	template <class T>
	class hkBlockStream
		: public hkBlockStreamBase::Stream
	{
	public:
		class Consumer;
		class Modifier;
		class Reader;
		class Writer;
	};
	static_assert(sizeof(hkBlockStream<std::any>) == 0x100);
}
