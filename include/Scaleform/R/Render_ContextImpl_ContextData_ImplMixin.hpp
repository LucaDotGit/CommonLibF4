#pragma once

namespace Scaleform::Render
{
	class LinearHeap;
}

namespace Scaleform::Render::ContextImpl
{
	class EntryData;

	template <class C, class B>
	class __declspec(novtable) ContextData_ImplMixin
		: public B // 00
	{
	public:
		virtual EntryData* ConstructCopy(LinearHeap& heap) const;
		virtual void CopyTo(void* pdest) const;
		virtual void Destroy();
	};
}
