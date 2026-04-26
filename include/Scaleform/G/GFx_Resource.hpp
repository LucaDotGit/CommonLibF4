#pragma once

#include "Scaleform/A/Atomic.hpp"
#include "Scaleform/G/GFx_ResourceLibBase.hpp"
#include "Scaleform/N/NewOverrideBase.hpp"

namespace Scaleform::GFx
{
	class ResourceKey;
	class ResourceReport;

	class __declspec(novtable) Resource
		: public NewOverrideBase<2> // 00
	{
	public:
		virtual ~Resource() = default; // 00

		// add
		virtual ResourceKey GetKey();					   // 01
		virtual std::uint32_t GetResourceTypeCode() const; // 02
		virtual ResourceReport* GetResourceReport();	   // 03

		void AddRef() noexcept;
		void Release() noexcept;

		// members
		AtomicInt<std::uint32_t> refCount; // 08
		ResourceLibBase* lib;			   // 10
	};
	static_assert(sizeof(Resource) == 0x18);
}
