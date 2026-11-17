#pragma once

#include "REL/IHook.hpp"
#include "REL/Id.hpp"
#include "REL/Memory.hpp"
#include "REL/Offset.hpp"
#include "REX/Logging/ILogger.hpp"
#include "REX/Message.hpp"

namespace REL::Hooks
{
	class Repl final : public REL::IHook
	{
	public:
		explicit Repl() noexcept = default;

		explicit Repl(
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			std::span<const std::uint8_t> a_newBytes,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) :
			IHook(a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset), std::move(a_logger)),
			_size(a_newBytes.size())
		{
			AllocateNewBytes(a_newBytes);
		}

		explicit Repl(
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			std::span<const std::uint8_t> a_newBytes,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) :
			IHook(a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset.GetOffset()), std::move(a_logger)),
			_size(a_newBytes.size())
		{
			AllocateNewBytes(a_newBytes);
		}

		explicit Repl(
			HookStep a_step,
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			std::span<const std::uint8_t> a_newBytes,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) :
			IHook(a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset), a_step, std::move(a_logger)),
			_size(a_newBytes.size())
		{
			AllocateNewBytes(a_newBytes);
		}

		explicit Repl(
			HookStep a_step,
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			std::span<const std::uint8_t> a_newBytes,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) :
			IHook(a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset.GetOffset()), a_step, std::move(a_logger)),
			_size(a_newBytes.size())
		{
			AllocateNewBytes(a_newBytes);
		}

		explicit Repl(
			std::string a_name,
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			std::span<const std::uint8_t> a_newBytes,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) :
			IHook(a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset), std::move(a_name), std::move(a_logger)),
			_size(a_newBytes.size())
		{
			AllocateNewBytes(a_newBytes);
		}

		explicit Repl(
			std::string a_name,
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			std::span<const std::uint8_t> a_newBytes,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) :
			IHook(
				a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset.GetOffset()),
				std::move(a_name),
				std::move(a_logger)),
			_size(a_newBytes.size())
		{
			AllocateNewBytes(a_newBytes);
		}

		explicit Repl(
			std::string a_name,
			HookStep a_step,
			const REL::IId& a_id,
			std::ptrdiff_t a_offset,
			std::span<const std::uint8_t> a_newBytes,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) :
			IHook(
				a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset),
				std::move(a_name),
				a_step,
				std::move(a_logger)),
			_size(a_newBytes.size())
		{
			AllocateNewBytes(a_newBytes);
		}

		explicit Repl(
			std::string a_name,
			HookStep a_step,
			const REL::IId& a_id,
			const REL::IOffset& a_offset,
			std::span<const std::uint8_t> a_newBytes,
			std::shared_ptr<REX::Logging::ILogger> a_logger = {}) :
			IHook(
				a_id.GetAddress() + static_cast<std::uintptr_t>(a_offset.GetOffset()),
				std::move(a_name),
				a_step,
				std::move(a_logger)),
			_size(a_newBytes.size())
		{
			AllocateNewBytes(a_newBytes);
		}

		~Repl() noexcept override = default;

		Repl(const Repl&) = delete;
		Repl(Repl&&) noexcept = default;

		auto operator=(const Repl&) -> Repl& = delete;
		auto operator=(Repl&&) noexcept -> Repl& = default;

		[[nodiscard]]
		auto GetTypeName() const noexcept -> std::string_view override
		{
			return "Repl"sv;
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

			const auto writeResult = REL::WriteSafe(GetAddress(), std::span{_newBytes.get(), GetSize()});
			if (!writeResult.has_value()) [[unlikely]] {
				REX::Fail(
					"{}: Failed to write new bytes.\n"
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
		void AllocateNewBytes(std::span<const std::uint8_t> a_newBytes)
		{
			if (!_newBytes) {
				// NOLINTNEXTLINE(modernize-avoid-c-arrays)
				_newBytes = std::make_unique_for_overwrite<std::uint8_t[]>(a_newBytes.size());
			}

			std::ranges::copy(a_newBytes, _newBytes.get());
		}

		std::size_t _size{0};
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<std::uint8_t[]> _oldBytes;
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<std::uint8_t[]> _newBytes;
	};
}
