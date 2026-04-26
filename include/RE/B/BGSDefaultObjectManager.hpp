#pragma once

#include "RE/B/BSTSingleton.hpp"
#include "RE/D/DEFAULT_OBJECT.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSDefaultObjectManager
		: public TESForm,									   // 00
		  public BSTSingletonImplicit<BGSDefaultObjectManager> // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSDefaultObjectManager };
		inline static constexpr auto VTABLE{ VTABLE::BGSDefaultObjectManager };
		inline static constexpr auto FORM_TYPE{ FormType::kDefaultObjectManager };

		~BGSDefaultObjectManager() override; // 00

		GAME_HEAP_REDEFINE_NEW(BGSDefaultObjectManager);

		[[nodiscard]] static BGSDefaultObjectManager* GetSingleton()
		{
			using FuncType = decltype(&BGSDefaultObjectManager::GetSingleton);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSDefaultObjectManager::Singleton };
			return std::invoke(FUNC);
		}

		[[nodiscard]] TESForm* GetDefaultObject(DEFAULT_OBJECT a_objectType) const noexcept
		{
			REX::Assert(a_objectType < DEFAULT_OBJECT::kTotal);
			return objectInitArray[std::to_underlying(a_objectType)] ? objectArray[std::to_underlying(a_objectType)] : nullptr;
		}

		template <class T>
		[[nodiscard]] T* GetDefaultObject(DEFAULT_OBJECT a_obj) const noexcept
			requires(std::derived_from<T, TESForm> &&
					 !std::is_pointer_v<T> &&
					 !std::is_reference_v<T>)
		{
			const auto* object = GetDefaultObject(a_obj);
			return object ? object->As<T>() : nullptr;
		}

		// members
		std::array<TESForm*, std::to_underlying(DEFAULT_OBJECT::kTotal)> objectArray; // 020
		std::array<bool, std::to_underlying(DEFAULT_OBJECT::kTotal)> objectInitArray; // C70
	};
	static_assert(sizeof(BGSDefaultObjectManager) == 0xE00);
}
