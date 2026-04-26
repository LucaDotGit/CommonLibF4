#pragma once

#include "REL/Asm.hpp"
#include "REL/IHookFn.hpp"
#include "REL/Trampoline.hpp"

namespace REL
{
	template <class T>
	class HookJump6 final
		: public IHookFn<T>
	{
	public:
		using value_type = std::decay_t<T>;

		static_assert(std::is_function_v<std::remove_pointer_t<T>>);

		HookJump6() = default;

		HookJump6(const REL::IId& a_id, std::ptrdiff_t a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookJump6(const REL::IId& a_id, const REL::IOffset& a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookJump6(HookStep a_step, const REL::IId& a_id, std::ptrdiff_t a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_step, a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookJump6(HookStep a_step, const REL::IId& a_id, const REL::IOffset& a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_step, a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookJump6(std::string a_name, const REL::IId& a_id, std::ptrdiff_t a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_name, a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookJump6(std::string a_name, const REL::IId& a_id, const REL::IOffset& a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_name, a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookJump6(std::string a_name, HookStep a_step, const REL::IId& a_id, std::ptrdiff_t a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_name, a_step, a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		HookJump6(std::string a_name, HookStep a_step, const REL::IId& a_id, const REL::IOffset& a_offset, const value_type& a_newFunc)
			: IHookFn<T>(a_name, a_step, a_id, a_offset, a_newFunc)
		{
			InitData();
		}

		~HookJump6() noexcept override = default;

		HookJump6(const HookJump6&) = delete;
		HookJump6(HookJump6&&) noexcept = default;

		HookJump6& operator=(const HookJump6&) = delete;
		HookJump6& operator=(HookJump6&&) noexcept = default;

		[[nodiscard]] std::string_view GetTypeName() const noexcept override { return "Jump6"sv; }

	protected:
		void InitNewBytes() override
		{
			const auto assembly = REL::Asm::Jump6(this->_address, REL::GetTrampoline()->AllocateBranch6(this->_newFunc.GetAddress()));
			REL::WriteData(std::span(this->_newBytes), assembly);
		}

		void InitData()
		{
			this->_size = sizeof(Asm::Jump6);
			this->_trampolineSize = sizeof(std::uintptr_t);
			this->_oldFunc = REL::Asm::Jump6::TARGET(this->_address);
		}
	};

	template <class T>
	HookJump6(const REL::IId&, std::ptrdiff_t, const T&) -> HookJump6<std::decay_t<T>>;

	template <class T>
	HookJump6(const REL::IId&, const REL::IOffset&, const T&) -> HookJump6<std::decay_t<T>>;

	template <class T>
	HookJump6(HookStep, const REL::IId&, std::ptrdiff_t, const T&) -> HookJump6<std::decay_t<T>>;

	template <class T>
	HookJump6(HookStep, const REL::IId&, const REL::IOffset&, const T&) -> HookJump6<std::decay_t<T>>;

	template <class T>
	HookJump6(std::string, const REL::IId&, std::ptrdiff_t, const T&) -> HookJump6<std::decay_t<T>>;

	template <class T>
	HookJump6(std::string, const REL::IId&, const REL::IOffset&, const T&) -> HookJump6<std::decay_t<T>>;

	template <class T>
	HookJump6(std::string, HookStep, const REL::IId&, std::ptrdiff_t, const T&) -> HookJump6<std::decay_t<T>>;

	template <class T>
	HookJump6(std::string, HookStep, const REL::IId&, const REL::IOffset&, const T&) -> HookJump6<std::decay_t<T>>;
}
