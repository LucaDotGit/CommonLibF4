#pragma once

#include "Scaleform/A/Array.hpp"
#include "Scaleform/A/Atomic.hpp"
#include "Scaleform/N/NewOverrideBase.hpp"
#include "Scaleform/R/RefCountBase.hpp"

namespace Scaleform
{
	class __declspec(novtable) Waitable
		: public RefCountBase<Waitable, 2> // 00
	{
	public:
		using WaitHandler = void(void*);

		class HandlerStruct
		{
		public:
			// members
			WaitHandler* handler; // 00
			void* userData;		  // 08
		};
		static_assert(sizeof(HandlerStruct) == 0x10);

		class HandlerArray
			: public NewOverrideBase<2> // 00
		{
		public:
			using SizePolicyType = ArrayConstPolicy<0, 16, true>;
			using HandlerArrayType = Array<HandlerStruct, 2, SizePolicyType>;

			void AddRef()
			{
				refCount++;
			}

			void Release()
			{
				if (--refCount == 0) {
					delete this;
				}
			}

			// members
			mutable AtomicInt<std::int32_t> refCount; // 00
			HandlerArrayType handlers;				  // 08
			Lock handlersLock;						  // 20
		};
		static_assert(sizeof(HandlerArray) == 0x48);

		// members
		HandlerArray* handlers; // 10
	};
	static_assert(sizeof(Waitable) == 0x18);
}
