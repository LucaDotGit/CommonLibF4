#pragma once

namespace REX
{
	template <class T>
	class Singleton
	{
	public:
		static T* GetSingleton()
		{
			static auto singleton = T();
			return std::addressof(singleton);
		}

	protected:
		Singleton() noexcept = default;
		virtual ~Singleton() noexcept = default;

		Singleton(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;

		Singleton& operator=(const Singleton&) = delete;
		Singleton& operator=(Singleton&&) = delete;
	};
}
