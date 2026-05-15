#pragma once

#include "REL/IHook.hpp"

#include "REX/NotNull.hpp"

namespace REL
{
	class HookStore final
	{
	public:
		HookStore() = default;
		~HookStore() noexcept = default;

		HookStore(const HookStore&) = delete;
		HookStore(HookStore&&) = delete;

		HookStore& operator=(const HookStore&) = delete;
		HookStore& operator=(HookStore&&) = delete;

		[[nodiscard]] bool Contains(const REX::NotNull<std::shared_ptr<REL::IHook>>& a_hook) const noexcept;
		bool Add(REX::NotNull<std::shared_ptr<REL::IHook>> a_hook);
		bool Remove(const REX::NotNull<std::shared_ptr<REL::IHook>>& a_hook) noexcept;
		void Clear() noexcept;

		void Init();
		void Init(HookStep a_step);

		void Enable() noexcept;
		bool Enable(HookStep a_step) noexcept;

		void Disable() noexcept;
		bool Disable(HookStep a_step) noexcept;

		[[nodiscard]] std::size_t GetTrampolineSize() const noexcept;

	private:
		mutable std::shared_mutex _mapMutex;
		std::map<REL::HookHandle, REX::NotNull<std::shared_ptr<REL::IHook>>> _hookMap;
	};

	[[nodiscard]] auto GetHookStore()
		-> const REX::NotNull<std::unique_ptr<HookStore>>&;
}
