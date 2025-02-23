#pragma once

#include "RE/msvc/functional.hpp"

namespace RE
{
	template <class>
	class BSTThreadScrapFunction;

	template <class R, class... Args>
	class BSTThreadScrapFunction<R(Args...)>
	{
	public:
		using result_type = R;

		BSTThreadScrapFunction() noexcept
		{
			if (IsOldGen()) {
				_oldGenFunc = nullptr;
			}
			else {
				_nextGenFunc = nullptr;
			}
		}

		BSTThreadScrapFunction(const BSTThreadScrapFunction& a_other) :
			BSTThreadScrapFunction()
		{
			*this = a_other;
		}

		BSTThreadScrapFunction(BSTThreadScrapFunction&& a_other) noexcept :
			BSTThreadScrapFunction()
		{
			*this = std::move(a_other);
		}

		explicit BSTThreadScrapFunction(msvc::function<R(Args...)> a_oldGenFunc) :
			_oldGenFunc(a_oldGenFunc)
		{
			assert(IsOldGen());
		}

		explicit BSTThreadScrapFunction(std::function<R(Args...)> a_nextGenFunc) :
			_nextGenFunc(a_nextGenFunc)
		{
			assert(IsNextGen());
		}

		~BSTThreadScrapFunction() noexcept
		{
			if (IsOldGen()) {
				_oldGenFunc.~function();
			}
			else {
				_nextGenFunc.~function();
			}
		}

		BSTThreadScrapFunction& operator=(const BSTThreadScrapFunction& a_other)
		{
			if (this == std::addressof(a_other)) {
				return *this;
			}

			if (a_other.IsOldGen()) {
				_oldGenFunc = a_other._oldGenFunc;
				return *this;
			}

			_nextGenFunc = a_other._nextGenFunc;
			return *this;
		}

		BSTThreadScrapFunction& operator=(BSTThreadScrapFunction&& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return *this;
			}

			if (a_other.IsOldGen()) {
				_oldGenFunc = std::move(a_other._oldGenFunc);
				return *this;
			}

			_nextGenFunc = std::move(a_other._nextGenFunc);
			return *this;
		}

		BSTThreadScrapFunction& operator=(msvc::function<R(Args...)> a_oldGenFunc)
		{
			assert(IsOldGen());
			_oldGenFunc = a_oldGenFunc;
			return *this;
		}

		BSTThreadScrapFunction& operator=(std::function<R(Args...)> a_nextGenFunc)
		{
			assert(IsNextGen());
			_nextGenFunc = a_nextGenFunc;
			return *this;
		}

		result_type operator()(Args&&... a_args) const
		{
			if (IsOldGen()) {
				return _oldGenFunc(std::forward<Args>(a_args)...);
			}

			return _nextGenFunc(std::forward<Args>(a_args)...);
		}

		[[nodiscard]] explicit operator bool() const noexcept
		{
			if (IsOldGen()) {
				return static_cast<bool>(_oldGenFunc);
			}

			return static_cast<bool>(_nextGenFunc);
		}

		[[nodiscard]] bool operator==(const BSTThreadScrapFunction& a_other) const noexcept
		{
			if (IsOldGen()) {
				return _oldGenFunc == a_other._oldGenFunc;
			}

			return _nextGenFunc == a_other._nextGenFunc;
		}

		[[nodiscard]] bool operator!=(const BSTThreadScrapFunction& a_other) const noexcept
		{
			return !(*this == a_other);
		}

	private:
		static bool IsOldGen() noexcept
		{
			return !IsNextGen();
		}

		static bool IsNextGen() noexcept
		{
			return REL::Module::IsNG();
		}

	private:
		union
		{
			msvc::function<R(Args...)> _oldGenFunc;
			std::function<R(Args...)> _nextGenFunc;
		};
	};
}