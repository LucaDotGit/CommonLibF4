#pragma once

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

		auto operator=(const Singleton&) -> Singleton& = delete;
		auto operator=(Singleton&&) -> Singleton& = delete;

		[[nodiscard]]
		static auto GetSingleton() noexcept(std::is_nothrow_default_constructible_v<value_type>) -> value_type&
		{
			static auto Instance = value_type();
			return Instance;
		}
	};

	static_assert(std::is_empty_v<Singleton<std::any>>);
}
