#pragma once

#include "F4SE/Core.hpp"
#include "RE/B/BSScript_StackID.hpp"
#include "REX/NotNull.hpp"
#include "REX/Ownership.hpp"

namespace F4SE
{
	class IObject;

#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'265)
#endif

	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class PersistentObjectStorage // final
	{
	public:
		PersistentObjectStorage() = delete;
		~PersistentObjectStorage() = delete;

		PersistentObjectStorage(const PersistentObjectStorage&) = delete;
		PersistentObjectStorage(PersistentObjectStorage&&) = delete;

		auto operator=(const PersistentObjectStorage&) -> PersistentObjectStorage& = delete;
		auto operator=(PersistentObjectStorage&&) -> PersistentObjectStorage& = delete;

		// add
		virtual auto Store(
			[[maybe_unused]] REX::NotNull<REX::Owner<IObject*>> a_object,
			[[maybe_unused]] RE::BSScript::StackID a_stackID) const -> F4SE::ObjectHandle // 0x00
		{
			return static_cast<F4SE::ObjectHandle>(0);
		}

		[[nodiscard]]
		virtual auto Access([[maybe_unused]] F4SE::ObjectHandle a_objectHandle) const -> REX::Observer<IObject*> // 0x01
		{
			return nullptr;
		}

		[[nodiscard]]
		virtual auto Take([[maybe_unused]] F4SE::ObjectHandle a_objectHandle) const -> REX::Owner<IObject*> // 0x02
		{
			return nullptr;
		}
	};

	static_assert(sizeof(PersistentObjectStorage) == 0x08);

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif
}
