#pragma once

#include "RE/B/BSCRC32.hpp"
#include "RE/B/BSUntypedPointerHandle.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class HandleManager;

	template <class, class = BSUntypedPointerHandle<>>
	class BSPointerHandle;

	template <class, class = HandleManager>
	class BSPointerHandleManagerInterface;

	template <class T, class Handle>
	class BSPointerHandle
	{
	public:
		using element_type = T;
		using handle_type = Handle;

		constexpr BSPointerHandle() noexcept = default;
		constexpr ~BSPointerHandle() noexcept = default;

		constexpr BSPointerHandle(std::nullptr_t) noexcept
			: _handle()
		{
		}

		template <class U>
		constexpr explicit BSPointerHandle(U* a_rhs) noexcept
			requires(std::is_convertible_v<U*, T*>)
			: _handle(get_ptr_handle(a_rhs).get_handle())
		{
		}

		template <class U>
		constexpr BSPointerHandle(const BSPointerHandle<U, Handle>& a_rhs) noexcept
			requires(std::is_convertible_v<U*, T*>)
			: _handle(a_rhs._handle)
		{
		}

		template <class U>
		constexpr BSPointerHandle(BSPointerHandle<U, Handle>&& a_rhs) noexcept // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
			requires(std::is_convertible_v<U*, T*>)
			: _handle(std::exchange(a_rhs._handle, static_cast<handle_type::value_type>(0)))
		{
		}

		constexpr BSPointerHandle(const BSPointerHandle&) noexcept = default;
		constexpr BSPointerHandle(BSPointerHandle&&) noexcept = default;

		constexpr BSPointerHandle& operator=(std::nullptr_t) noexcept
		{
			_handle.reset();
			return *this;
		}

		template <class U>
		constexpr BSPointerHandle& operator=(U* a_rhs) noexcept
			requires(std::is_convertible_v<U*, T*>)
		{
			_handle = get_ptr_handle(a_rhs).get_handle();
			return *this;
		}

		template <class U>
		constexpr BSPointerHandle& operator=(const BSPointerHandle<U, Handle>& a_rhs) noexcept
			requires(std::is_convertible_v<U*, T*>)
		{
			_handle = a_rhs._handle;
			return *this;
		}

		template <class U>
		constexpr BSPointerHandle& operator=(BSPointerHandle<U, Handle>&& a_rhs) noexcept // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
			requires(std::is_convertible_v<U*, T*>)
		{
			_handle = std::exchange(a_rhs._handle, static_cast<handle_type::value_type>(0));
			return *this;
		}

		constexpr BSPointerHandle& operator=(const BSPointerHandle&) noexcept = default;
		constexpr BSPointerHandle& operator=(BSPointerHandle&&) noexcept = default;

		[[nodiscard]] constexpr explicit operator bool() const noexcept
		{
			return _handle.has_value();
		}

		[[nodiscard]] constexpr NiPointer<T> operator*() const noexcept
		{
			REX::Assert(static_cast<bool>(*this));
			return get();
		}

		[[nodiscard]] constexpr NiPointer<T> operator->() const noexcept
		{
			REX::Assert(static_cast<bool>(*this));
			return get();
		}

		[[nodiscard]] constexpr bool has_value() const noexcept { return _handle.has_value(); }
		[[nodiscard]] constexpr handle_type::value_type get_handle() const noexcept { return _handle.value(); }

		[[nodiscard]] constexpr NiPointer<T> get() const noexcept { return get_smart_ptr(*this); }
		[[nodiscard]] constexpr T* underlying() const noexcept { return get().get(); }

		constexpr void reset() noexcept { _handle.reset(); }

		constexpr void swap(BSPointerHandle& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_handle, a_other._handle);
		}

	protected:
		template <class, class>
		friend class BSPointerHandle;

		[[nodiscard]] static constexpr BSPointerHandle<T> get_ptr_handle(const T* a_ptr) noexcept
		{
			return BSPointerHandleManagerInterface<T>::GetHandle(a_ptr);
		}

		[[nodiscard]] static constexpr NiPointer<T> get_smart_ptr(const BSPointerHandle& a_in) noexcept
		{
			return BSPointerHandleManagerInterface<T>::GetSmartPointer(a_in);
		}

		Handle _handle; // 00
	};

	extern template class BSPointerHandle<Actor>;
	extern template class BSPointerHandle<Projectile>;
	extern template class BSPointerHandle<TESObjectREFR>;

	using ActorHandle = BSPointerHandle<Actor>;
	using ProjectileHandle = BSPointerHandle<Projectile>;
	using ObjectRefHandle = BSPointerHandle<TESObjectREFR>;

	static_assert(std::is_trivially_destructible_v<ActorHandle>);
	static_assert(std::is_trivially_destructible_v<ProjectileHandle>);
	static_assert(std::is_trivially_destructible_v<ObjectRefHandle>);

	static_assert(std::is_trivially_copyable_v<ActorHandle>);
	static_assert(std::is_trivially_copyable_v<ProjectileHandle>);
	static_assert(std::is_trivially_copyable_v<ObjectRefHandle>);

	template <class T, class Manager>
	[[nodiscard]] constexpr bool operator==(const BSPointerHandle<T, Manager>& a_lhs, const BSPointerHandle<T, Manager>& a_rhs) noexcept
	{
		return a_lhs.get_handle() == a_rhs.get_handle();
	}

	template <class T, class Manager>
	[[nodiscard]] constexpr bool operator==(const BSPointerHandle<T, Manager>& a_lhs, std::nullptr_t) noexcept
	{
		return !a_lhs.has_value();
	}

	template <class T, class Manager>
	[[nodiscard]] constexpr bool operator==(std::nullptr_t, const BSPointerHandle<T, Manager>& a_rhs) noexcept
	{
		return !a_rhs.has_value();
	}

	template <class T, class Manager>
	[[nodiscard]] constexpr bool operator==(const BSPointerHandle<T, Manager>& a_lhs, const NiPointer<T>& a_rhs) noexcept
	{
		return a_lhs.underlying() == a_rhs.get();
	}

	template <class T, class Manager>
	[[nodiscard]] constexpr bool operator==(const NiPointer<T>& a_lhs, const BSPointerHandle<T, Manager>& a_rhs) noexcept
	{
		return a_lhs.get() == a_rhs.underlying();
	}

	template <class T, class Manager>
	[[nodiscard]] constexpr bool operator==(const BSPointerHandle<T, Manager>& a_lhs, const typename BSPointerHandle<T, Manager>::element_type* a_rhs) noexcept
	{
		return a_lhs.underlying() == a_rhs;
	}

	template <class T, class Manager>
	[[nodiscard]] constexpr bool operator==(const typename BSPointerHandle<T, Manager>::element_type* a_lhs, const BSPointerHandle<T, Manager>& a_rhs) noexcept
	{
		return a_lhs == a_rhs.underlying();
	}

	template <class T, class Manager>
	[[nodiscard]] constexpr auto operator<=>(const BSPointerHandle<T, Manager>& a_lhs, const BSPointerHandle<T, Manager>& a_rhs) noexcept
	{
		return a_lhs.get_handle() <=> a_rhs.get_handle();
	}

	template <class T, class Manager>
	[[nodiscard]] constexpr auto operator<=>(const BSPointerHandle<T, Manager>& a_lhs, std::nullptr_t) noexcept
	{
		return a_lhs.has_value() <=> false;
	}

	template <class T, class Manager>
	[[nodiscard]] constexpr auto operator<=>(std::nullptr_t, const BSPointerHandle<T, Manager>& a_rhs) noexcept
	{
		return false <=> a_rhs.has_value();
	}

	template <class T, class Manager>
	[[nodiscard]] constexpr auto operator<=>(const BSPointerHandle<T, Manager>& a_lhs, const NiPointer<T>& a_rhs) noexcept
	{
		return a_lhs.underlying() <=> a_rhs.get();
	}

	template <class T, class Manager>
	[[nodiscard]] constexpr auto operator<=>(const NiPointer<T>& a_lhs, const BSPointerHandle<T, Manager>& a_rhs) noexcept
	{
		return a_lhs.get() <=> a_rhs.underlying();
	}

	template <class T, class Manager>
	[[nodiscard]] constexpr auto operator<=>(const BSPointerHandle<T, Manager>& a_lhs, const typename BSPointerHandle<T, Manager>::element_type* a_rhs) noexcept
	{
		return a_lhs.underlying() <=> a_rhs;
	}

	template <class T, class Manager>
	[[nodiscard]] constexpr auto operator<=>(const typename BSPointerHandle<T, Manager>::element_type* a_lhs, const BSPointerHandle<T, Manager>& a_rhs) noexcept
	{
		return a_lhs <=> a_rhs.underlying();
	}

	extern template bool operator== <Actor>(const BSPointerHandle<Actor>&, const BSPointerHandle<Actor>&) noexcept;
	extern template bool operator== <Actor>(const BSPointerHandle<Actor>&, std::nullptr_t) noexcept;
	extern template bool operator== <Actor>(std::nullptr_t, const BSPointerHandle<Actor>&) noexcept;
	extern template bool operator== <Actor>(const BSPointerHandle<Actor>&, const NiPointer<Actor>&) noexcept;
	extern template bool operator== <Actor>(const NiPointer<Actor>&, const BSPointerHandle<Actor>&) noexcept;
	extern template bool operator== <Actor>(const BSPointerHandle<Actor>&, const Actor*) noexcept;
	extern template bool operator== <Actor>(const Actor*, const BSPointerHandle<Actor>&) noexcept;
	extern template auto operator<=> <Actor>(const BSPointerHandle<Actor>&, const BSPointerHandle<Actor>&) noexcept;
	extern template auto operator<=> <Actor>(const BSPointerHandle<Actor>&, std::nullptr_t) noexcept;
	extern template auto operator<=> <Actor>(std::nullptr_t, const BSPointerHandle<Actor>&) noexcept;
	extern template auto operator<=> <Actor>(const BSPointerHandle<Actor>&, const NiPointer<Actor>&) noexcept;
	extern template auto operator<=> <Actor>(const NiPointer<Actor>&, const BSPointerHandle<Actor>&) noexcept;
	extern template auto operator<=> <Actor>(const BSPointerHandle<Actor>&, const Actor*) noexcept;
	extern template auto operator<=> <Actor>(const Actor*, const BSPointerHandle<Actor>&) noexcept;

	extern template bool operator== <Projectile>(const BSPointerHandle<Projectile>&, const BSPointerHandle<Projectile>&) noexcept;
	extern template bool operator== <Projectile>(const BSPointerHandle<Projectile>&, std::nullptr_t) noexcept;
	extern template bool operator== <Projectile>(std::nullptr_t, const BSPointerHandle<Projectile>&) noexcept;
	extern template bool operator== <Projectile>(const BSPointerHandle<Projectile>&, const NiPointer<Projectile>&) noexcept;
	extern template bool operator== <Projectile>(const NiPointer<Projectile>&, const BSPointerHandle<Projectile>&) noexcept;
	extern template bool operator== <Projectile>(const BSPointerHandle<Projectile>&, const Projectile*) noexcept;
	extern template bool operator== <Projectile>(const Projectile*, const BSPointerHandle<Projectile>&) noexcept;
	extern template auto operator<=> <Projectile>(const BSPointerHandle<Projectile>&, const BSPointerHandle<Projectile>&) noexcept;
	extern template auto operator<=> <Projectile>(const BSPointerHandle<Projectile>&, std::nullptr_t) noexcept;
	extern template auto operator<=> <Projectile>(std::nullptr_t, const BSPointerHandle<Projectile>&) noexcept;
	extern template auto operator<=> <Projectile>(const BSPointerHandle<Projectile>&, const NiPointer<Projectile>&) noexcept;
	extern template auto operator<=> <Projectile>(const NiPointer<Projectile>&, const BSPointerHandle<Projectile>&) noexcept;
	extern template auto operator<=> <Projectile>(const BSPointerHandle<Projectile>&, const Projectile*) noexcept;
	extern template auto operator<=> <Projectile>(const Projectile*, const BSPointerHandle<Projectile>&) noexcept;

	extern template bool operator== <TESObjectREFR>(const BSPointerHandle<TESObjectREFR>&, const BSPointerHandle<TESObjectREFR>&) noexcept;
	extern template bool operator== <TESObjectREFR>(const BSPointerHandle<TESObjectREFR>&, std::nullptr_t) noexcept;
	extern template bool operator== <TESObjectREFR>(std::nullptr_t, const BSPointerHandle<TESObjectREFR>&) noexcept;
	extern template bool operator== <TESObjectREFR>(const BSPointerHandle<TESObjectREFR>&, const NiPointer<TESObjectREFR>&) noexcept;
	extern template bool operator== <TESObjectREFR>(const NiPointer<TESObjectREFR>&, const BSPointerHandle<TESObjectREFR>&) noexcept;
	extern template bool operator== <TESObjectREFR>(const BSPointerHandle<TESObjectREFR>&, const TESObjectREFR*) noexcept;
	extern template bool operator== <TESObjectREFR>(const TESObjectREFR*, const BSPointerHandle<TESObjectREFR>&) noexcept;
	extern template auto operator<=> <TESObjectREFR>(const BSPointerHandle<TESObjectREFR>&, const BSPointerHandle<TESObjectREFR>&) noexcept;
	extern template auto operator<=> <TESObjectREFR>(const BSPointerHandle<TESObjectREFR>&, std::nullptr_t) noexcept;
	extern template auto operator<=> <TESObjectREFR>(std::nullptr_t, const BSPointerHandle<TESObjectREFR>&) noexcept;
	extern template auto operator<=> <TESObjectREFR>(const BSPointerHandle<TESObjectREFR>&, const NiPointer<TESObjectREFR>&) noexcept;
	extern template auto operator<=> <TESObjectREFR>(const NiPointer<TESObjectREFR>&, const BSPointerHandle<TESObjectREFR>&) noexcept;
	extern template auto operator<=> <TESObjectREFR>(const BSPointerHandle<TESObjectREFR>&, const TESObjectREFR*) noexcept;
	extern template auto operator<=> <TESObjectREFR>(const TESObjectREFR*, const BSPointerHandle<TESObjectREFR>&) noexcept;

	template <class T, class Manager>
	constexpr void swap(BSPointerHandle<T, Manager>& a_lhs, BSPointerHandle<T, Manager>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	extern template void swap<Actor>(BSPointerHandle<Actor>&, BSPointerHandle<Actor>&) noexcept;
	extern template void swap<Projectile>(BSPointerHandle<Projectile>&, BSPointerHandle<Projectile>&) noexcept;
	extern template void swap<TESObjectREFR>(BSPointerHandle<TESObjectREFR>&, BSPointerHandle<TESObjectREFR>&) noexcept;

	template <class T, class Manager>
	class BSPointerHandleManagerInterface
	{
	public:
		using value_type = T;
		using manager_type = Manager;

		[[nodiscard]] static BSPointerHandle<T> GetHandle(const T* a_ptr) noexcept
		{
			try {
				using FuncType = decltype(&BSPointerHandleManagerInterface<T, Manager>::GetHandle);
				static const auto FUNC = REL::Relocation<FuncType>{ ID::BSPointerHandle::BSPointerHandleManagerInterface::GetHandle };
				return std::invoke(FUNC, a_ptr);
			}
			catch (...) {
				return BSPointerHandle<T>();
			}
		}

		static bool GetSmartPointer(const BSPointerHandle<T>& a_inHandle, NiPointer<T>& a_outHandle) noexcept
		{
			try {
				using FuncType = bool (*)(const BSPointerHandle<T>&, NiPointer<T>&);
				static const auto FUNC = REL::Relocation<FuncType>{ ID::BSPointerHandle::BSPointerHandleManagerInterface::GetSmartPointer };
				return std::invoke(FUNC, a_inHandle, a_outHandle);
			}
			catch (...) {
				return false;
			}
		}

		[[nodiscard]] static constexpr NiPointer<T> GetSmartPointer(const BSPointerHandle<T>& a_inHandle) noexcept
		{
			if (!a_inHandle) {
				return nullptr;
			}

			auto out = NiPointer<T>();
			if (!GetSmartPointer(a_inHandle, out)) {
				return nullptr;
			}

			return out;
		}
	};

	extern template class BSPointerHandleManagerInterface<Actor>;
	extern template class BSPointerHandleManagerInterface<Projectile>;
	extern template class BSPointerHandleManagerInterface<TESObjectREFR>;
}

namespace RE
{
	template <class T>
	struct BSCRC32<RE::BSPointerHandle<T>>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(const RE::BSPointerHandle<T>& a_key) const noexcept
		{
			return RE::HashCRC32(a_key.get_handle());
		}
	};

	extern template struct BSCRC32<RE::BSPointerHandle<Actor>>;
	extern template struct BSCRC32<RE::BSPointerHandle<Projectile>>;
	extern template struct BSCRC32<RE::BSPointerHandle<TESObjectREFR>>;
}

namespace std
{
	template <class T>
	struct hash<RE::BSPointerHandle<T>>
	{
	public:
		[[nodiscard]] std::size_t operator()(const RE::BSPointerHandle<T>& a_key) const noexcept
		{
			return REX::Hash(a_key.get_handle());
		}
	};

	extern template struct hash<RE::BSPointerHandle<RE::Actor>>;
	extern template struct hash<RE::BSPointerHandle<RE::Projectile>>;
	extern template struct hash<RE::BSPointerHandle<RE::TESObjectREFR>>;
}
