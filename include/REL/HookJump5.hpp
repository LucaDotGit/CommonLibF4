#pragma once

#include "REL/Asm.hpp"
#include "REL/IHookFn.hpp"
#include "REL/Trampoline.hpp"

namespace REL
{
	template <class T>
	class HookJump5 final
		: public IHookFn<T>
	{
	public:
		using value_type = std::decay_t<T>;

		static_assert(std::is_function_v<std::remove_pointer_t<T>>);

		HookJump5() = default;

		HookJump5(const REL::IId& a_id, std::ptrdiff_t a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookJump5(const REL::IId& a_id, const REL::IOffset& a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookJump5(HookStep a_step, const REL::IId& a_id, std::ptrdiff_t a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_step, a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookJump5(HookStep a_step, const REL::IId& a_id, const REL::IOffset& a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_step, a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookJump5(std::string a_name, const REL::IId& a_id, std::ptrdiff_t a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_name, a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookJump5(std::string a_name, const REL::IId& a_id, const REL::IOffset& a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_name, a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookJump5(std::string a_name, HookStep a_step, const REL::IId& a_id, std::ptrdiff_t a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_name, a_step, a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookJump5(std::string a_name, HookStep a_step, const REL::IId& a_id, const REL::IOffset& a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_name, a_step, a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		~HookJump5() noexcept override = default;

		HookJump5(const HookJump5&) = delete;
		HookJump5(HookJump5&&) noexcept = default;

		HookJump5& operator=(const HookJump5&) = delete;
		HookJump5& operator=(HookJump5&&) noexcept = default;

		[[nodiscard]] std::string_view GetTypeName() const noexcept override { return "Jump5"sv; }

	protected:
		void InitNewBytes() override
		{
			const auto assembly = REL::Asm::Jump5(this->_address, REL::GetTrampoline()->AllocateBranch5(this->_newFunc.GetAddress()));
			REL::WriteData(std::span(this->_newBytes), assembly);
		}

		void InitData()
		{
			this->_size = sizeof(Asm::Jump5);
			this->_trampolineSize = sizeof(Asm::Jump14);
			this->_oldFunc = REL::Asm::Jump5::TARGET(this->_address);
		}
	};

	template <class T>
	HookJump5(const REL::IId&, std::ptrdiff_t, const T&) -> HookJump5<std::decay_t<T>>;

	template <class T>
	HookJump5(const REL::IId&, const REL::IOffset&, const T&) -> HookJump5<std::decay_t<T>>;

	template <class T>
	HookJump5(HookStep, const REL::IId&, std::ptrdiff_t, const T&) -> HookJump5<std::decay_t<T>>;

	template <class T>
	HookJump5(HookStep, const REL::IId&, const REL::IOffset&, const T&) -> HookJump5<std::decay_t<T>>;

	template <class T>
	HookJump5(std::string, const REL::IId&, std::ptrdiff_t, const T&) -> HookJump5<std::decay_t<T>>;

	template <class T>
	HookJump5(std::string, const REL::IId&, const REL::IOffset&, const T&) -> HookJump5<std::decay_t<T>>;

	template <class T>
	HookJump5(std::string, HookStep, const REL::IId&, std::ptrdiff_t, const T&) -> HookJump5<std::decay_t<T>>;

	template <class T>
	HookJump5(std::string, HookStep, const REL::IId&, const REL::IOffset&, const T&) -> HookJump5<std::decay_t<T>>;
}
