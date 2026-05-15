#pragma once

#include "REX/NotNull.hpp"

namespace REX
{
	template <class T>
	class Singleton
	{
	public:
		using value_type = T;

	protected:
		Singleton() noexcept = default;
		~Singleton() noexcept = default;

	public:
		Singleton(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;

		Singleton& operator=(const Singleton&) = delete;
		Singleton& operator=(Singleton&&) = delete;

		[[nodiscard]] static auto GetSingleton()
			-> const REX::NotNull<std::unique_ptr<T>>&
		{
			static const auto INSTANCE = REX::NotNull(std::make_unique<T>());
			return INSTANCE;
		}
	};
	static_assert(std::is_empty_v<Singleton<std::any>>);
}
