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
	class HookNop final
		: public IHook
	{
	public:
		HookNop() = default;

		HookNop(const REL::IId& a_id, std::ptrdiff_t a_offset, std::size_t a_size)
			: IHook(a_id.GetAddress() + a_offset)
		{
			_size = a_size;
		}

		HookNop(const REL::IId& a_id, const REL::IOffset& a_offset, std::size_t a_size)
			: IHook(a_id.GetAddress() + a_offset.GetOffset())
		{
			_size = a_size;
		}

		HookNop(const REL::IId& a_id, std::ptrdiff_t a_offset, const REL::ISize& a_size)
			: IHook(a_id.GetAddress() + a_offset)
		{
			_size = a_size.GetSize();
		}

		HookNop(const REL::IId& a_id, const REL::IOffset& a_offset, const REL::ISize& a_size)
			: IHook(a_id.GetAddress() + a_offset.GetOffset())
		{
			_size = a_size.GetSize();
		}

		HookNop(HookStep a_step, const REL::IId& a_id, std::ptrdiff_t a_offset, std::size_t a_size)
			: IHook(a_id.GetAddress() + a_offset, a_step)
		{
			_size = a_size;
		}

		HookNop(HookStep a_step, const REL::IId& a_id, const REL::IOffset& a_offset, std::size_t a_size)
			: IHook(a_id.GetAddress() + a_offset.GetOffset(), a_step)
		{
			_size = a_size;
		}

		HookNop(HookStep a_step, const REL::IId& a_id, std::ptrdiff_t a_offset, const REL::ISize& a_size)
			: IHook(a_id.GetAddress() + a_offset, a_step)
		{
			_size = a_size.GetSize();
		}

		HookNop(HookStep a_step, const REL::IId& a_id, const REL::IOffset& a_offset, const REL::ISize& a_size)
			: IHook(a_id.GetAddress() + a_offset.GetOffset(), a_step)
		{
			_size = a_size.GetSize();
		}

		HookNop(std::string a_name, const REL::IId& a_id, std::ptrdiff_t a_offset, std::size_t a_size)
			: IHook(a_id.GetAddress() + a_offset, std::move(a_name))
		{
			_size = a_size;
		}

		HookNop(std::string a_name, const REL::IId& a_id, const REL::IOffset& a_offset, std::size_t a_size)
			: IHook(a_id.GetAddress() + a_offset.GetOffset(), std::move(a_name))
		{
			_size = a_size;
		}

		HookNop(std::string a_name, const REL::IId& a_id, std::ptrdiff_t a_offset, const REL::ISize& a_size)
			: IHook(a_id.GetAddress() + a_offset, std::move(a_name))
		{
			_size = a_size.GetSize();
		}

		HookNop(std::string a_name, const REL::IId& a_id, const REL::IOffset& a_offset, const REL::ISize& a_size)
			: IHook(a_id.GetAddress() + a_offset.GetOffset(), std::move(a_name))
		{
			_size = a_size.GetSize();
		}

		HookNop(std::string a_name, HookStep a_step, const REL::IId& a_id, std::ptrdiff_t a_offset, std::size_t a_size)
			: IHook(a_id.GetAddress() + a_offset, std::move(a_name), a_step)
		{
			_size = a_size;
		}

		HookNop(std::string a_name, HookStep a_step, const REL::IId& a_id, const REL::IOffset& a_offset, std::size_t a_size)
			: IHook(a_id.GetAddress() + a_offset.GetOffset(), std::move(a_name), a_step)
		{
			_size = a_size;
		}

		HookNop(std::string a_name, HookStep a_step, const REL::IId& a_id, std::ptrdiff_t a_offset, const REL::ISize& a_size)
			: IHook(a_id.GetAddress() + a_offset, std::move(a_name), a_step)
		{
			_size = a_size.GetSize();
		}

		HookNop(std::string a_name, HookStep a_step, const REL::IId& a_id, const REL::IOffset& a_offset, const REL::ISize& a_size)
			: IHook(a_id.GetAddress() + a_offset.GetOffset(), std::move(a_name), a_step)
		{
			_size = a_size.GetSize();
		}

		~HookNop() noexcept override = default;

		HookNop(const HookNop&) = delete;
		HookNop(HookNop&&) noexcept = default;

		HookNop& operator=(const HookNop&) = delete;
		HookNop& operator=(HookNop&&) noexcept = default;

		[[nodiscard]] std::string_view GetTypeName() const noexcept override { return "Nop"sv; }

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

			const auto writeError = REL::WriteSafeFill(_address, REL::NOP, _size);
			if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				REX::Fail(
					"{}: Failed to write NOP bytes.\n"
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
	};
}
