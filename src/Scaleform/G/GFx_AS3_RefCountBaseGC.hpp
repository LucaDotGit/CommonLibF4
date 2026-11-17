#pragma once

#include "Scaleform/N/NewOverrideBase.hpp"

namespace Scaleform::GFx::AS3
{
	template <std::int32_t STAT>
	class __declspec(novtable) RefCountBaseGC : public NewOverrideBase<STAT> // 0x00
	{
	public:
		virtual ~RefCountBaseGC(); // 0x00

		// members
		union
		{
		public:
			void* rcc{nullptr};
			std::uint64_t rccRaw;
		}; // 0x08

		union
		{
		public:
			const RefCountBaseGC<STAT>* next{nullptr};
			const RefCountBaseGC<STAT>* nextRoot;
		}; // 0x10

		union
		{
		public:
			const RefCountBaseGC<STAT>* prev{nullptr};
			const RefCountBaseGC<STAT>* prevRoot;
		}; // 0x18

		std::uint32_t refCount{0}; // 0x20
	};

	static_assert(sizeof(RefCountBaseGC<328>) == 0x28);
}
