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

		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr BSPointerHandle(std::nullptr_t) noexcept :
			_handle()
		{
		}

		template <class U>
		constexpr explicit BSPointerHandle(U* a_rhs) noexcept
			requires(std::is_convertible_v<U*, T*>)
			:
			_handle(get_ptr_handle(a_rhs).get_handle())
		{
		}

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr BSPointerHandle(const BSPointerHandle<U, Handle>& a_rhs) noexcept
			requires(std::is_convertible_v<U*, T*>)
			:
			_handle(a_rhs._handle)
		{
		}

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor, cppcoreguidelines-rvalue-reference-param-not-moved)
		constexpr BSPointerHandle(BSPointerHandle<U, Handle>&& a_rhs) noexcept
			requires(std::is_convertible_v<U*, T*>)
			:
			_handle(std::exchange(a_rhs._handle, static_cast<handle_type::value_type>(0)))
		{
		}

		constexpr BSPointerHandle(const BSPointerHandle&) noexcept = default;
		constexpr BSPointerHandle(BSPointerHandle&&) noexcept = default;

		constexpr auto operator=(std::nullptr_t) noexcept -> BSPointerHandle&
		{
			_handle.reset();
			return *this;
		}

		template <class U>
		constexpr auto operator=(U* a_rhs) noexcept -> BSPointerHandle&
			requires(std::is_convertible_v<U*, T*>)
		{
			_handle = get_ptr_handle(a_rhs).get_handle();
			return *this;
		}

		template <class U>
		constexpr auto operator=(const BSPointerHandle<U, Handle>& a_rhs) noexcept -> BSPointerHandle&
			requires(std::is_convertible_v<U*, T*>)
		{
			_handle = a_rhs._handle;
			return *this;
		}

		template <class U>
		// NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
		constexpr auto operator=(BSPointerHandle<U, Handle>&& a_rhs) noexcept -> BSPointerHandle&
			requires(std::is_convertible_v<U*, T*>)
		{
			_handle = std::exchange(a_rhs._handle, static_cast<handle_type::value_type>(0));
			return *this;
		}

		constexpr auto operator=(const BSPointerHandle&) noexcept -> BSPointerHandle& = default;
		constexpr auto operator=(BSPointerHandle&&) noexcept -> BSPointerHandle& = default;

		[[nodiscard]]
		constexpr explicit operator bool() const noexcept
		{
			return _handle.has_value();
		}

		[[nodiscard]]
		constexpr auto operator*() const noexcept -> NiPointer<T>
		{
			REX::Assert(static_cast<bool>(*this));
			return get();
		}

		[[nodiscard]]
		constexpr auto operator->() const noexcept -> NiPointer<T>
		{
			REX::Assert(static_cast<bool>(*this));
			return get();
		}

		[[nodiscard]]
		constexpr auto has_value() const noexcept -> bool
		{
			return _handle.has_value();
		}

		[[nodiscard]]
		constexpr auto get_handle() const noexcept -> handle_type::value_type
		{
			return _handle.value();
		}

		[[nodiscard]]
		constexpr auto get() const noexcept -> NiPointer<T>
		{
			return get_shared_ptr(*this);
		}

		constexpr void reset() noexcept
		{
			_handle.reset();
		}

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

		[[nodiscard]]
		static constexpr auto get_ptr_handle(const T* a_ptr) noexcept -> BSPointerHandle<T>
		{
			return BSPointerHandleManagerInterface<T>::GetHandle(a_ptr);
		}

		[[nodiscard]]
		static constexpr auto get_shared_ptr(const BSPointerHandle& a_in) noexcept -> NiPointer<T>
		{
			return BSPointerHandleManagerInterface<T>::GetSmartPointer(a_in);
		}

		Handle _handle; // 0x00
	};

	using ActorHandle = BSPointerHandle<Actor>;
	static_assert(sizeof(ActorHandle) == 0x04);

	using ProjectileHandle = BSPointerHandle<Projectile>;
	static_assert(sizeof(ProjectileHandle) == 0x04);

	using ObjectRefHandle = BSPointerHandle<TESObjectREFR>;
	static_assert(sizeof(ObjectRefHandle) == 0x04);

	static_assert(std::is_trivially_destructible_v<ActorHandle>);
	static_assert(std::is_trivially_destructible_v<ProjectileHandle>);
	static_assert(std::is_trivially_destructible_v<ObjectRefHandle>);

	static_assert(std::is_trivially_copyable_v<ActorHandle>);
	static_assert(std::is_trivially_copyable_v<ProjectileHandle>);
	static_assert(std::is_trivially_copyable_v<ObjectRefHandle>);

	static_assert(std::is_trivially_move_constructible_v<ActorHandle>);
	static_assert(std::is_trivially_move_constructible_v<ProjectileHandle>);
	static_assert(std::is_trivially_move_constructible_v<ObjectRefHandle>);

	template <class T, class Manager>
	[[nodiscard]]
	constexpr auto operator==(const BSPointerHandle<T, Manager>& a_lhs, const BSPointerHandle<T, Manager>& a_rhs)
		noexcept -> bool
	{
		return a_lhs.get_handle() == a_rhs.get_handle();
	}

	template <class T, class Manager>
	[[nodiscard]]
	constexpr auto operator==(const BSPointerHandle<T, Manager>& a_lhs, std::nullptr_t) noexcept -> bool
	{
		return !a_lhs.has_value();
	}

	template <class T, class Manager>
	[[nodiscard]]
	constexpr auto operator==(std::nullptr_t, const BSPointerHandle<T, Manager>& a_rhs) noexcept -> bool
	{
		return !a_rhs.has_value();
	}

	template <class T, class Manager>
	[[nodiscard]]
	constexpr auto operator==(const BSPointerHandle<T, Manager>& a_lhs, const NiPointer<T>& a_rhs) noexcept -> bool
	{
		return a_lhs.get() == a_rhs;
	}

	template <class T, class Manager>
	[[nodiscard]]
	constexpr auto operator==(const NiPointer<T>& a_lhs, const BSPointerHandle<T, Manager>& a_rhs) noexcept -> bool
	{
		return a_lhs == a_rhs.get();
	}

	template <class T, class Manager>
	[[nodiscard]]
	constexpr auto operator==(
		const BSPointerHandle<T, Manager>& a_lhs,
		const typename BSPointerHandle<T, Manager>::element_type* a_rhs) noexcept -> bool
	{
		return a_lhs.get() == a_rhs;
	}

	template <class T, class Manager>
	[[nodiscard]]
	constexpr auto operator==(
		const typename BSPointerHandle<T, Manager>::element_type* a_lhs,
		const BSPointerHandle<T, Manager>& a_rhs) noexcept -> bool
	{
		return a_lhs == a_rhs.get();
	}

	template <class T, class Manager>
	[[nodiscard]]
	constexpr auto operator<=>(const BSPointerHandle<T, Manager>& a_lhs, const BSPointerHandle<T, Manager>& a_rhs)
		noexcept
	{
		return a_lhs.get_handle() <=> a_rhs.get_handle();
	}

	template <class T, class Manager>
	[[nodiscard]]
	constexpr auto operator<=>(const BSPointerHandle<T, Manager>& a_lhs, std::nullptr_t) noexcept -> auto
	{
		return a_lhs.has_value() <=> false;
	}

	template <class T, class Manager>
	[[nodiscard]]
	constexpr auto operator<=>(std::nullptr_t, const BSPointerHandle<T, Manager>& a_rhs) noexcept -> auto
	{
		return false <=> a_rhs.has_value();
	}

	template <class T, class Manager>
	[[nodiscard]]
	constexpr auto operator<=>(const BSPointerHandle<T, Manager>& a_lhs, const NiPointer<T>& a_rhs) noexcept -> auto
	{
		return a_lhs.get() <=> a_rhs;
	}

	template <class T, class Manager>
	[[nodiscard]]
	constexpr auto operator<=>(const NiPointer<T>& a_lhs, const BSPointerHandle<T, Manager>& a_rhs) noexcept -> auto
	{
		return a_lhs <=> a_rhs.get();
	}

	template <class T, class Manager>
	[[nodiscard]]
	constexpr auto operator<=>(
		const BSPointerHandle<T, Manager>& a_lhs,
		const typename BSPointerHandle<T, Manager>::element_type* a_rhs) noexcept
	{
		return a_lhs.get() <=> a_rhs;
	}

	template <class T, class Manager>
	[[nodiscard]]
	constexpr auto operator<=>(
		const typename BSPointerHandle<T, Manager>::element_type* a_lhs,
		const BSPointerHandle<T, Manager>& a_rhs) noexcept
	{
		return a_lhs <=> a_rhs.get();
	}

	template <class T, class Manager>
	class BSPointerHandleManagerInterface
	{
	public:
		using value_type = T;
		using manager_type = Manager;

		[[nodiscard]]
		static auto GetHandle(const T* a_ptr) noexcept -> BSPointerHandle<T>
		{
			try {
				using FuncType = decltype(&BSPointerHandleManagerInterface<T, Manager>::GetHandle);
				static const auto FUNC =
					REL::Relocation<FuncType>{ID::BSPointerHandle::BSPointerHandleManagerInterface::GetHandle};
				return std::invoke(FUNC, a_ptr);
			}
			catch (...) {
				return {};
			}
		}

		static auto GetSmartPointer(const BSPointerHandle<T>& a_inHandle, NiPointer<T>& a_outHandle) noexcept -> bool
		{
			try {
				using FuncType = bool (*)(const BSPointerHandle<T>&, NiPointer<T>&);
				static const auto FUNC =
					REL::Relocation<FuncType>{ID::BSPointerHandle::BSPointerHandleManagerInterface::GetSmartPointer};
				return std::invoke(FUNC, a_inHandle, a_outHandle);
			}
			catch (...) {
				return false;
			}
		}

		[[nodiscard]]
		static constexpr auto GetSmartPointer(const BSPointerHandle<T>& a_inHandle) noexcept -> NiPointer<T>
		{
			if (!a_inHandle) {
				return nullptr;
			}

			auto result = NiPointer<T>();
			if (!GetSmartPointer(a_inHandle, result)) {
				return nullptr;
			}

			return result;
		}
	};

	static_assert(std::is_empty_v<BSPointerHandleManagerInterface<Actor>>);
	static_assert(std::is_empty_v<BSPointerHandleManagerInterface<Projectile>>);
	static_assert(std::is_empty_v<BSPointerHandleManagerInterface<TESObjectREFR>>);
}

namespace RE
{
	template <class T>
	struct BSCRC32<RE::BSPointerHandle<T>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(const RE::BSPointerHandle<T>& a_key) const noexcept -> std::uint32_t
		{
			return RE::HashCRC32(a_key.get_handle());
		}
	};
}

namespace std
{
	template <class T>
	struct hash<RE::BSPointerHandle<T>>
	{
	public:
		[[nodiscard]]
		auto operator()(const RE::BSPointerHandle<T>& a_key) const noexcept -> std::size_t
		{
			return REX::Hash(a_key.get_handle());
		}
	};
}
