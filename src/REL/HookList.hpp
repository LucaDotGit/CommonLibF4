#pragma once

#include "REL/IHook.hpp"
#include "REX/NotNull.hpp"

namespace REX::Logging
{
	class ILogger;
}

namespace REL
{
	class HookList final
	{
	public:
		HookList() noexcept;
		explicit HookList(std::shared_ptr<REX::Logging::ILogger> a_logger) noexcept;

		~HookList() noexcept;

		HookList(const HookList&) = delete;
		HookList(HookList&&) = delete;

		auto operator=(const HookList&) -> HookList& = delete;
		auto operator=(HookList&&) -> HookList& = delete;

		[[nodiscard]]
		auto Contains(const REX::NotNull<std::shared_ptr<REL::IHook>>& a_key) const noexcept -> bool;
		[[nodiscard]]
		auto GetValue(const REX::NotNull<std::shared_ptr<REL::IHook>>& a_key) const noexcept
			-> std::shared_ptr<REL::IHook>;
		auto Add(REX::NotNull<std::shared_ptr<REL::IHook>> a_key) -> bool;
		auto Remove(const REX::NotNull<std::shared_ptr<REL::IHook>>& a_key) noexcept -> bool;
		void Clear() noexcept;

		void Setup(REL::Trampoline& a_trampoline);

		void Enable();
		auto Enable(HookStep a_step) -> bool;

		void Disable();
		auto Disable(HookStep a_step) -> bool;

		[[nodiscard]]
		auto GetTrampolineSize() const noexcept -> std::size_t;

	private:
		std::shared_ptr<REX::Logging::ILogger> _logger;
		mutable std::shared_mutex _hookMutex;
		std::map<REL::HookHandle, REX::NotNull<std::shared_ptr<REL::IHook>>> _hookMap;
	};
}
