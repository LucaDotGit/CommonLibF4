#pragma once

namespace Scaleform::Render
{
	class LinearHeap;
}

namespace Scaleform::Render::ContextImpl
{
	class EntryData;

	template <class C, class B>
	class __declspec(novtable) ContextData_ImplMixin : public B // 0x00
	{
	public:
		virtual auto ConstructCopy(LinearHeap& heap) const -> EntryData*;
		virtual void CopyTo(void* pdest) const;
		virtual void Destroy();
	};
}
