#pragma once

#include "RE/B/BSTSingleton.hpp"
#include "RE/D/DEFAULT_OBJECT.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSDefaultObjectManager :
		public TESForm,										 // 0x00
		public BSTSingletonImplicit<BGSDefaultObjectManager> // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSDefaultObjectManager;
		inline static constexpr const auto& VTABLE = VTABLE::BGSDefaultObjectManager;
		inline static constexpr auto FORM_TYPE = FormType::DefaultObjectManager;

		~BGSDefaultObjectManager() override; // 0x00

		GAME_HEAP_REDEFINE_NEW(BGSDefaultObjectManager);

		[[nodiscard]]
		static auto GetSingleton() -> BGSDefaultObjectManager*
		{
			using FuncType = decltype(&BGSDefaultObjectManager::GetSingleton);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSDefaultObjectManager::Singleton);
			return std::invoke(FUNC);
		}

		[[nodiscard]]
		auto GetDefaultObjects() noexcept -> std::span<TESForm*>;

		[[nodiscard]]
		auto GetDefaultObjects() const noexcept -> std::span<TESForm* const>;

		[[nodiscard]]
		auto GetDefaultObject(DEFAULT_OBJECT a_objectType) const noexcept -> TESForm*;

		template <class T>
		[[nodiscard]]
		auto GetDefaultObject(DEFAULT_OBJECT a_obj) const noexcept -> T*
			requires(std::derived_from<T, TESForm> && !REX::pointer<T> && !REX::reference<T>)
		{
			// NOLINTNEXTLINE(misc-const-correctness)
			auto* object = GetDefaultObject(a_obj);
			return object ? object->As<T>() : nullptr;
		}

		// members
		std::array<TESForm*, std::to_underlying(DEFAULT_OBJECT::_Count)> objectArray; // 0x020
		std::array<bool, std::to_underlying(DEFAULT_OBJECT::_Count)> objectInitArray; // 0xC70
	};

	static_assert(sizeof(BGSDefaultObjectManager) == 0xE10);
}
