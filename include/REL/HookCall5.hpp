#pragma once

#include "REL/Asm.hpp"
#include "REL/IHookFn.hpp"
#include "REL/Trampoline.hpp"

namespace REL
{
	template <class T>
	class HookCall5 final
		: public IHookFn<T>
	{
	public:
		using value_type = std::decay_t<T>;

		static_assert(std::is_function_v<std::remove_pointer_t<T>>);

		HookCall5() = default;

		HookCall5(const REL::IId& a_id, std::ptrdiff_t a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookCall5(const REL::IId& a_id, const REL::IOffset& a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookCall5(HookStep a_step, const REL::IId& a_id, std::ptrdiff_t a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_step, a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookCall5(HookStep a_step, const REL::IId& a_id, const REL::IOffset& a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_step, a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookCall5(std::string a_name, const REL::IId& a_id, std::ptrdiff_t a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_name, a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookCall5(std::string a_name, const REL::IId& a_id, const REL::IOffset& a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_name, a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookCall5(std::string a_name, HookStep a_step, const REL::IId& a_id, std::ptrdiff_t a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_name, a_step, a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookCall5(std::string a_name, HookStep a_step, const REL::IId& a_id, const REL::IOffset& a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_name, a_step, a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		~HookCall5() noexcept override = default;

		HookCall5(const HookCall5&) = delete;
		HookCall5(HookCall5&&) noexcept = default;

		HookCall5& operator=(const HookCall5&) = delete;
		HookCall5& operator=(HookCall5&&) noexcept = default;

		[[nodiscard]] std::string_view GetTypeName() const noexcept override { return "Call5"sv; }

	protected:
		void InitNewBytes() override
		{
			const auto assembly = REL::Asm::Call5(this->_address, REL::GetTrampoline()->AllocateBranch5(this->_newFunc.GetAddress()));
			REL::WriteData(std::span(this->_newBytes), assembly);
		}

		void InitData()
		{
			this->_size = sizeof(Asm::Call5);
			this->_trampolineSize = sizeof(Asm::Jump14);
			this->_oldFunc = REL::Asm::Call5::TARGET(this->_address);
		}
	};

	template <class T>
	HookCall5(const REL::IId&, std::ptrdiff_t, const T&) -> HookCall5<std::decay_t<T>>;

	template <class T>
	HookCall5(const REL::IId&, const REL::IOffset&, const T&) -> HookCall5<std::decay_t<T>>;

	template <class T>
	HookCall5(HookStep, const REL::IId&, std::ptrdiff_t, const T&) -> HookCall5<std::decay_t<T>>;

	template <class T>
	HookCall5(HookStep, const REL::IId&, const REL::IOffset&, const T&) -> HookCall5<std::decay_t<T>>;

	template <class T>
	HookCall5(std::string, const REL::IId&, std::ptrdiff_t, const T&) -> HookCall5<std::decay_t<T>>;

	template <class T>
	HookCall5(std::string, const REL::IId&, const REL::IOffset&, const T&) -> HookCall5<std::decay_t<T>>;

	template <class T>
	HookCall5(std::string, HookStep, const REL::IId&, std::ptrdiff_t, const T&) -> HookCall5<std::decay_t<T>>;

	template <class T>
	HookCall5(std::string, HookStep, const REL::IId&, const REL::IOffset&, const T&) -> HookCall5<std::decay_t<T>>;
}
