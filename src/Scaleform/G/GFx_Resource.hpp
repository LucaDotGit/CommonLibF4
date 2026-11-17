#pragma once

#include "Scaleform/A/AtomicValue.hpp"
#include "Scaleform/G/GFx_ResourceLibBase.hpp"
#include "Scaleform/N/NewOverrideBase.hpp"

namespace Scaleform::GFx
{
	class ResourceKey;
	class ResourceReport;

	class __declspec(novtable) Resource : public NewOverrideBase<2> // 0x00
	{
	public:
		virtual ~Resource() = default; // 0x00

		// add
		virtual auto GetKey() -> ResourceKey;					   // 0x01
		virtual auto GetResourceTypeCode() const -> std::uint32_t; // 0x02
		virtual auto GetResourceReport() -> ResourceReport*;	   // 0x03

		void AddRef() const noexcept;
		void Release() const noexcept;

		// members
		mutable AtomicValue<std::uint32_t> refCount; // 0x08
		ResourceLibBase* lib;						 // 0x10
	};

	static_assert(sizeof(Resource) == 0x18);
}
