#pragma once

#include "Scaleform/A/Array.hpp"
#include "Scaleform/A/AtomicValue.hpp"
#include "Scaleform/N/NewOverrideBase.hpp"
#include "Scaleform/R/RefCountBase.hpp"

namespace Scaleform
{
	class __declspec(novtable) Waitable : public RefCountBase<Waitable, 2> // 0x00
	{
	public:
		using WaitHandler = void(void*);

		class HandlerStruct
		{
		public:
			// members
			WaitHandler* handler; // 0x00
			void* userData;		  // 0x08
		};

		static_assert(sizeof(HandlerStruct) == 0x10);

		class HandlerArray : public NewOverrideBase<2> // 0x00
		{
		public:
			using SizePolicyType = ArrayConstPolicy<0, 16, true>;
			using HandlerArrayType = Array<HandlerStruct, 2, SizePolicyType>;

			void AddRef() const noexcept;
			void Release() const noexcept;

			// members
			mutable AtomicValue<std::int32_t> refCount; // 0x00
			HandlerArrayType handlers;					// 0x08
			mutable Lock handlersLock;					// 0x20
		};

		static_assert(sizeof(HandlerArray) == 0x48);

		// members
		HandlerArray* handlers; // 0x10
	};

	static_assert(sizeof(Waitable) == 0x18);
}
