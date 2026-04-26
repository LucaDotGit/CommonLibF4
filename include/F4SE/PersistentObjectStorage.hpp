#pragma once

#include "F4SE/Core.hpp"

#include "REX/NotNull.hpp"
#include "REX/Own.hpp"

namespace F4SE
{
	class IObject;

#if _MSC_VER > 0l
#pragma warning(push)
#pragma warning(disable : 4265) // 'class': class has virtual functions, but destructor is not virtual
#endif

	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class PersistentObjectStorage // final
	{
	public:
		PersistentObjectStorage() = delete;
		~PersistentObjectStorage() = delete;

		PersistentObjectStorage(const PersistentObjectStorage&) = delete;
		PersistentObjectStorage(PersistentObjectStorage&&) = delete;

		PersistentObjectStorage& operator=(const PersistentObjectStorage&) = delete;
		PersistentObjectStorage& operator=(PersistentObjectStorage&&) = delete;

		// add
		virtual ObjectHandle Store([[maybe_unused]] REX::NotNull<REX::Owner<IObject*>> a_object, [[maybe_unused]] RE::BSScript::StackID a_stackID) const { return ObjectHandle(); } // 00
		[[nodiscard]] virtual REX::Observer<IObject*> Access([[maybe_unused]] ObjectHandle a_objectHandle) const { return nullptr; }												// 01
		[[nodiscard]] virtual REX::Owner<IObject*> Take([[maybe_unused]] ObjectHandle a_objectHandle) const { return nullptr; }														// 02
	};
	static_assert(sizeof(PersistentObjectStorage) == 0x08);

#if _MSC_VER > 0l
#pragma warning(pop)
#endif
}
