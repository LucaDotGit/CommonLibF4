#pragma once

#include "REL/Cast.hpp"
#include "REL/IHook.hpp"
#include "REL/Id.hpp"
#include "REL/Memory.hpp"
#include "REL/Offset.hpp"
#include "REL/Size.hpp"

#include "REX/Error.hpp"
#include "REX/Log.hpp"
#include "REX/Message.hpp"

namespace REL
{
	class HookRepl final
		: public IHook
	{
	public:
		HookRepl() = default;

		HookRepl(const REL::IId& a_id, std::ptrdiff_t a_offset, std::span<const std::uint8_t> a_newBytes)
			: IHook(a_id.GetAddress() + a_offset),
			  _newBytes{ a_newBytes.begin(), a_newBytes.end() }
		{
			_size = _newBytes.size();
		}

		HookRepl(const REL::IId& a_id, const REL::IOffset& a_offset, std::span<const std::uint8_t> a_newBytes)
			: IHook(a_id.GetAddress() + a_offset.GetOffset()),
			  _newBytes{ a_newBytes.begin(), a_newBytes.end() }
		{
			_size = _newBytes.size();
		}

		HookRepl(HookStep a_step, const REL::IId& a_id, std::ptrdiff_t a_offset, std::span<const std::uint8_t> a_newBytes)
			: IHook(a_id.GetAddress() + a_offset, a_step),
			  _newBytes{ a_newBytes.begin(), a_newBytes.end() }
		{
			_size = _newBytes.size();
		}

		HookRepl(HookStep a_step, const REL::IId& a_id, const REL::IOffset& a_offset, std::span<const std::uint8_t> a_newBytes)
			: IHook(a_id.GetAddress() + a_offset.GetOffset(), a_step),
			  _newBytes{ a_newBytes.begin(), a_newBytes.end() }
		{
			_size = _newBytes.size();
		}

		HookRepl(std::string a_name, const REL::IId& a_id, std::ptrdiff_t a_offset, std::span<const std::uint8_t> a_newBytes)
			: IHook(a_id.GetAddress() + a_offset, std::move(a_name)),
			  _newBytes{ a_newBytes.begin(), a_newBytes.end() }
		{
			_size = _newBytes.size();
		}

		HookRepl(std::string a_name, const REL::IId& a_id, const REL::IOffset& a_offset, std::span<const std::uint8_t> a_newBytes)
			: IHook(a_id.GetAddress() + a_offset.GetOffset(), std::move(a_name)),
			  _newBytes{ a_newBytes.begin(), a_newBytes.end() }
		{
			_size = _newBytes.size();
		}

		HookRepl(std::string a_name, HookStep a_step, const REL::IId& a_id, std::ptrdiff_t a_offset, std::span<const std::uint8_t> a_newBytes)
			: IHook(a_id.GetAddress() + a_offset, std::move(a_name), a_step),
			  _newBytes{ a_newBytes.begin(), a_newBytes.end() }
		{
			_size = _newBytes.size();
		}

		HookRepl(std::string a_name, HookStep a_step, const REL::IId& a_id, const REL::IOffset& a_offset, std::span<const std::uint8_t> a_newBytes)
			: IHook(a_id.GetAddress() + a_offset.GetOffset(), std::move(a_name), a_step),
			  _newBytes{ a_newBytes.begin(), a_newBytes.end() }
		{
			_size = _newBytes.size();
		}

		~HookRepl() noexcept override = default;

		HookRepl(const HookRepl&) = delete;
		HookRepl(HookRepl&&) noexcept = default;

		HookRepl& operator=(const HookRepl&) = delete;
		HookRepl& operator=(HookRepl&&) noexcept = default;

		[[nodiscard]] std::string_view GetTypeName() const noexcept override { return "Repl"sv; }

		bool Init() override
		{
			if (IsInitialized()) {
				return false;
			}

			if (_address == REL::INVALID_ADDRESS) [[unlikely]] {
				REX::Fail("{}: Address is null."sv,
					*this);
			}

			if (_size == REL::INVALID_SIZE) [[unlikely]] {
				REX::Fail("{}: Size is empty."sv,
					*this);
			}

			_oldBytes.resize(_size);

			REL::Write(std::span(_oldBytes), _address);

			_initialized = true;

			REX::LogTrace("{}: Init"sv,
				*this);

			return true;
		}

		bool Enable() override
		{
			if (!CanBeEnabled()) {
				return false;
			}

			const auto writeError = REL::WriteSafe(_address, std::span(_newBytes));
			if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				REX::Fail(
					"{}: Failed to write new bytes.\n"
					"System Error (0x{:08X}): {}"sv,
					*this, writeError.value(), writeError.message());
			}

			_enabled = true;

			REX::LogTrace("{}: Enabled"sv,
				*this);

			return true;
		}

		bool Disable() override
		{
			if (!CanBeDisabled()) {
				return false;
			}

			const auto writeError = REL::WriteSafe(_address, std::span(_oldBytes));
			if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				REX::Fail(
					"{}: Failed to write old bytes.\n"
					"System Error (0x{:08X}): {}"sv,
					*this, writeError.value(), writeError.message());
			}

			_enabled = false;

			REX::LogTrace("{}: Disabled"sv,
				*this);

			return false;
		}

	private:
		std::vector<std::uint8_t> _oldBytes;
		std::vector<std::uint8_t> _newBytes;
	};
}
