#pragma once

#include "REL/IHook.hpp"
#include "REL/Id.hpp"
#include "REL/Memory.hpp"
#include "REL/Offset.hpp"
#include "REL/Size.hpp"
#include "REX/Logging/ILogger.hpp"
#include "REX/Message.hpp"

namespace REL::Hooks
{
	class Nop final : public REL::IHook
	{
	public:
		explicit Nop() noexcept = default;

		explicit Nop(
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			std::size_t a_size,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset), std::move(a_logger)),
			_size(a_size)
		{
		}

		explicit Nop(
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			std::size_t a_size,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset.GetOffset()), std::move(a_logger)),
			_size(a_size)
		{
		}

		explicit Nop(
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			const REL::ISize& a_size,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset), std::move(a_logger)),
			_size(a_size.GetSize())
		{
		}

		explicit Nop(
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			const REL::ISize& a_size,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset.GetOffset()), std::move(a_logger)),
			_size(a_size.GetSize())
		{
		}

		explicit Nop(
			HookStep a_step,
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			std::size_t a_size,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset), a_step, std::move(a_logger)),
			_size(a_size)
		{
		}

		explicit Nop(
			HookStep a_step,
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			std::size_t a_size,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset.GetOffset()), a_step, std::move(a_logger)),
			_size(a_size)
		{
		}

		explicit Nop(
			HookStep a_step,
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			const REL::ISize& a_size,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset), a_step, std::move(a_logger)),
			_size(a_size.GetSize())
		{
		}

		explicit Nop(
			HookStep a_step,
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			const REL::ISize& a_size,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset.GetOffset()), a_step, std::move(a_logger)),
			_size(a_size.GetSize())
		{
		}

		explicit Nop(
			std::string a_name,
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			std::size_t a_size,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset), std::move(a_name), std::move(a_logger)),
			_size(a_size)
		{
		}

		explicit Nop(
			std::string a_name,
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			std::size_t a_size,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(
				a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset.GetOffset()),
				std::move(a_name),
				std::move(a_logger)),
			_size(a_size)
		{
		}

		explicit Nop(
			std::string a_name,
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			const REL::ISize& a_size,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset), std::move(a_name), std::move(a_logger)),
			_size(a_size.GetSize())
		{
		}

		explicit Nop(
			std::string a_name,
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			const REL::ISize& a_size,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(
				a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset.GetOffset()),
				std::move(a_name),
				std::move(a_logger)),
			_size(a_size.GetSize())
		{
		}

		explicit Nop(
			std::string a_name,
			HookStep a_step,
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			std::size_t a_size,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(
				a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset),
				std::move(a_name),
				a_step,
				std::move(a_logger)),
			_size(a_size)
		{
		}

		explicit Nop(
			std::string a_name,
			HookStep a_step,
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			std::size_t a_size,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(
				a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset.GetOffset()),
				std::move(a_name),
				a_step,
				std::move(a_logger)),
			_size(a_size)
		{
		}

		explicit Nop(
			std::string a_name,
			HookStep a_step,
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			const REL::ISize& a_size,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(
				a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset),
				std::move(a_name),
				a_step,
				std::move(a_logger)),
			_size(a_size.GetSize())
		{
		}

		explicit Nop(
			std::string a_name,
			HookStep a_step,
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			const REL::ISize& a_size,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) noexcept :
			IHook(
				a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset.GetOffset()),
				std::move(a_name),
				a_step,
				std::move(a_logger)),
			_size(a_size.GetSize())
		{
		}

		~Nop() noexcept override = default;

		Nop(const Nop&) = delete;
		Nop(Nop&&) noexcept = default;

		auto operator=(const Nop&) -> Nop& = delete;
		auto operator=(Nop&&) noexcept -> Nop& = default;

		[[nodiscard]]
		auto GetTypeName() const noexcept -> std::string_view override
		{
			return "Nop"sv;
		}

		[[nodiscard]]
		auto GetSize() const noexcept -> std::size_t override
		{
			return _size;
		}

		[[nodiscard]]
		auto GetTrampolineSize() const noexcept -> std::size_t override
		{
			return 0;
		}

		auto Setup([[maybe_unused]] REL::Trampoline& a_trampoline) -> bool override
		{
			if (GetIsSetup()) {
				return false;
			}

			if (GetAddress() == REL::INVALID_ADDRESS) [[unlikely]] {
				REX::Fail("{}: Address is null."sv, *this);
			}

			if (GetSize() == 0) [[unlikely]] {
				REX::Fail("{}: Size is empty."sv, *this);
			}

			if (!_oldBytes) {
				// NOLINTNEXTLINE(modernize-avoid-c-arrays)
				_oldBytes = std::make_unique_for_overwrite<std::uint8_t[]>(GetSize());
			}

			REL::Write(std::span{_oldBytes.get(), GetSize()}, GetAddress());

			SetIsSetup(true);

			if (GetLogger()) {
				GetLogger()->LogTrace("{}: Setup"sv, *this);
			}

			return true;
		}

		auto Enable() -> bool override
		{
			if (!CanBeEnabled()) {
				return false;
			}

			const auto writeResult = REL::WriteSafeFill(GetAddress(), REL::OP_CODE_NOP, GetSize());
			if (!writeResult.has_value()) [[unlikely]] {
				REX::Fail(
					"{}: Failed to write NOP bytes.\n"
					"System Error (0x{:08X}): {}"sv,
					*this,
					writeResult.error().value(),
					writeResult.error().message());
			}

			SetIsEnabled(true);

			if (GetLogger()) {
				GetLogger()->LogTrace("{}: Enabled"sv, *this);
			}

			return true;
		}

		auto Disable() -> bool override
		{
			if (!CanBeDisabled()) {
				return false;
			}

			const auto writeResult = REL::WriteSafe(GetAddress(), std::span{_oldBytes.get(), GetSize()});
			if (!writeResult.has_value()) [[unlikely]] {
				REX::Fail(
					"{}: Failed to write old bytes.\n"
					"System Error (0x{:08X}): {}"sv,
					*this,
					writeResult.error().value(),
					writeResult.error().message());
			}

			SetIsEnabled(false);

			if (GetLogger()) {
				GetLogger()->LogTrace("{}: Disabled"sv, *this);
			}

			return false;
		}

	private:
		std::size_t _size{0};
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<std::uint8_t[]> _oldBytes;
	};
}
