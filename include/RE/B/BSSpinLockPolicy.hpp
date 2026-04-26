#pragma once

namespace RE::Impl
{
	template <class T>
	concept AutoLockDefaultPolicyConstraint =
		(requires(T a_mutex) { { a_mutex.lock() } -> std::same_as<void>; }) &&
		(requires(T a_mutex) { { a_mutex.unlock() } -> std::same_as<void>; });

	template <class T>
	concept AutoLockReadLockPolicyConstraint =
		(requires(T a_mutex) { { a_mutex.lock_shared() } -> std::same_as<void>; }) &&
		(requires(T a_mutex) { { a_mutex.unlock_shared() } -> std::same_as<void>; });

	template <class T>
	concept AutoLockWriteLockPolicyConstraint =
		(requires(T a_mutex) { { a_mutex.lock() } -> std::same_as<void>; }) &&
		(requires(T a_mutex) { { a_mutex.unlock() } -> std::same_as<void>; });

	template <class T>
	concept nothrow_lockable =
		std::is_nothrow_invocable_v<decltype(&T::lock), T&>;

	template <class T>
	concept nothrow_unlockable =
		std::is_nothrow_invocable_v<decltype(&T::unlock), T&>;

	template <class T>
	concept nothrow_read_lockable =
		std::is_nothrow_invocable_v<decltype(&T::lock_shared), T&>;

	template <class T>
	concept nothrow_read_unlockable =
		std::is_nothrow_invocable_v<decltype(&T::unlock_shared), T&>;

	template <class T>
	concept nothrow_write_lockable =
		std::is_nothrow_invocable_v<decltype(&T::lock), T&>;

	template <class T>
	concept nothrow_write_unlockable =
		std::is_nothrow_invocable_v<decltype(&T::unlock), T&>;

	inline constexpr auto SPIN_LOCK_SLEEP_DURATION_MS = 1ui32;
	inline constexpr auto SPIN_LOCK_YIELD_DURATION_MS = 0ui32;
	inline constexpr auto SPIN_LOCK_YIELD_COUNT = 10000ui32;
}

namespace RE
{
	template <Impl::AutoLockDefaultPolicyConstraint Mutex>
	class BSAutoLockDefaultPolicy
	{
	public:
		using mutex_type = Mutex;

		BSAutoLockDefaultPolicy() = delete;
		~BSAutoLockDefaultPolicy() = delete;

		BSAutoLockDefaultPolicy(const BSAutoLockDefaultPolicy&) = delete;
		BSAutoLockDefaultPolicy(BSAutoLockDefaultPolicy&&) = delete;

		BSAutoLockDefaultPolicy& operator=(const BSAutoLockDefaultPolicy&) = delete;
		BSAutoLockDefaultPolicy& operator=(BSAutoLockDefaultPolicy&&) = delete;

		static void lock(mutex_type& a_mutex) //
			noexcept(Impl::nothrow_lockable<mutex_type>)
		{
			a_mutex.lock();
		}

		static void unlock(mutex_type& a_mutex) //
			noexcept(Impl::nothrow_unlockable<mutex_type>)
		{
			a_mutex.unlock();
		}
	};

	template <Impl::AutoLockReadLockPolicyConstraint Mutex>
	class BSAutoLockReadLockPolicy
	{
	public:
		using mutex_type = Mutex;

		BSAutoLockReadLockPolicy() = delete;
		~BSAutoLockReadLockPolicy() = delete;

		BSAutoLockReadLockPolicy(const BSAutoLockReadLockPolicy&) = delete;
		BSAutoLockReadLockPolicy(BSAutoLockReadLockPolicy&&) = delete;

		BSAutoLockReadLockPolicy& operator=(const BSAutoLockReadLockPolicy&) = delete;
		BSAutoLockReadLockPolicy& operator=(BSAutoLockReadLockPolicy&&) = delete;

		static void lock(mutex_type& a_mutex) //
			noexcept(Impl::nothrow_read_lockable<mutex_type>)
		{
			a_mutex.lock_shared();
		}

		static void unlock(mutex_type& a_mutex) //
			noexcept(Impl::nothrow_read_unlockable<mutex_type>)
		{
			a_mutex.unlock_shared();
		}
	};

	template <Impl::AutoLockWriteLockPolicyConstraint Mutex>
	class BSAutoLockWriteLockPolicy
	{
	public:
		using mutex_type = Mutex;

		BSAutoLockWriteLockPolicy() = delete;
		~BSAutoLockWriteLockPolicy() = delete;

		BSAutoLockWriteLockPolicy(const BSAutoLockWriteLockPolicy&) = delete;
		BSAutoLockWriteLockPolicy(BSAutoLockWriteLockPolicy&&) = delete;

		BSAutoLockWriteLockPolicy& operator=(const BSAutoLockWriteLockPolicy&) = delete;
		BSAutoLockWriteLockPolicy& operator=(BSAutoLockWriteLockPolicy&&) = delete;

		static void lock(mutex_type& a_mutex) //
			noexcept(Impl::nothrow_write_lockable<mutex_type>)
		{
			a_mutex.lock();
		}

		static void unlock(mutex_type& a_mutex) //
			noexcept(Impl::nothrow_write_unlockable<mutex_type>)
		{
			a_mutex.unlock();
		}
	};

	template <class Mutex, template <class> class Policy = BSAutoLockDefaultPolicy>
	class BSAutoLock
	{
	public:
		using mutex_type = Mutex;
		using policy_type = Policy<mutex_type>;

		explicit BSAutoLock(mutex_type& a_mutex) //
			noexcept(Impl::nothrow_lockable<mutex_type>)
			: _lock(std::addressof(a_mutex))
		{
			lock();
		}

		~BSAutoLock() //
			noexcept(Impl::nothrow_unlockable<mutex_type>)
		{
			unlock();
		}

		BSAutoLock(const BSAutoLock&) = delete;
		BSAutoLock(BSAutoLock&&) noexcept = default;

		BSAutoLock& operator=(const BSAutoLock&) = delete;
		BSAutoLock& operator=(BSAutoLock&&) noexcept = default;

		void lock() const //
			noexcept(Impl::nothrow_lockable<mutex_type>)
		{
			if (_lock) {
				policy_type::lock(*_lock);
			}
		}

		void unlock() const //
			noexcept(Impl::nothrow_unlockable<mutex_type>)
		{
			if (_lock) {
				policy_type::unlock(*_lock);
			}
		}

	private:
		// members
		mutable mutex_type* _lock{ nullptr }; // 00
	};

	template <class Mutex>
	BSAutoLock(Mutex&) -> BSAutoLock<Mutex>;

	template <class Mutex>
	BSAutoLock(Mutex*) -> BSAutoLock<Mutex>;
}
