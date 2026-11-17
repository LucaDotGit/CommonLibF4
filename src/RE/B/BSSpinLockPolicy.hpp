#pragma once

namespace RE::Impl
{
	template <class T>
	concept AutoLockDefaultPolicyConstraint = (requires(T a_mutex) {
												  {
													  a_mutex.lock()
												  } -> std::same_as<void>;
											  }) && (requires(T a_mutex) {
												  {
													  a_mutex.unlock()
												  } -> std::same_as<void>;
											  });

	template <class T>
	concept AutoLockReadLockPolicyConstraint = (requires(T a_mutex) {
												   {
													   a_mutex.lock_shared()
												   } -> std::same_as<void>;
											   }) && (requires(T a_mutex) {
												   {
													   a_mutex.unlock_shared()
												   } -> std::same_as<void>;
											   });

	template <class T>
	concept AutoLockWriteLockPolicyConstraint = (requires(T a_mutex) {
													{
														a_mutex.lock()
													} -> std::same_as<void>;
												}) && (requires(T a_mutex) {
													{
														a_mutex.unlock()
													} -> std::same_as<void>;
												});

	template <class T>
	concept nothrow_lockable = std::is_nothrow_invocable_v<decltype(&T::lock), T&>;

	template <class T>
	concept nothrow_unlockable = std::is_nothrow_invocable_v<decltype(&T::unlock), T&>;

	template <class T>
	concept nothrow_read_lockable = std::is_nothrow_invocable_v<decltype(&T::lock_shared), T&>;

	template <class T>
	concept nothrow_read_unlockable = std::is_nothrow_invocable_v<decltype(&T::unlock_shared), T&>;

	template <class T>
	concept nothrow_write_lockable = std::is_nothrow_invocable_v<decltype(&T::lock), T&>;

	template <class T>
	concept nothrow_write_unlockable = std::is_nothrow_invocable_v<decltype(&T::unlock), T&>;

	inline constexpr auto SPIN_LOCK_SLEEP_DURATION = static_cast<std::chrono::milliseconds>(1);
	inline constexpr auto SPIN_LOCK_YIELD_COUNT = static_cast<std::uint32_t>(10'000);
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

		auto operator=(const BSAutoLockDefaultPolicy&) -> BSAutoLockDefaultPolicy& = delete;
		auto operator=(BSAutoLockDefaultPolicy&&) -> BSAutoLockDefaultPolicy& = delete;

		static void lock(mutex_type& a_mutex) noexcept(Impl::nothrow_lockable<mutex_type>)
		{
			a_mutex.lock();
		}

		static void unlock(mutex_type& a_mutex) noexcept(Impl::nothrow_unlockable<mutex_type>)
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

		auto operator=(const BSAutoLockReadLockPolicy&) -> BSAutoLockReadLockPolicy& = delete;
		auto operator=(BSAutoLockReadLockPolicy&&) -> BSAutoLockReadLockPolicy& = delete;

		static void lock(mutex_type& a_mutex) noexcept(Impl::nothrow_read_lockable<mutex_type>)
		{
			a_mutex.lock_shared();
		}

		static void unlock(mutex_type& a_mutex) noexcept(Impl::nothrow_read_unlockable<mutex_type>)
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

		auto operator=(const BSAutoLockWriteLockPolicy&) -> BSAutoLockWriteLockPolicy& = delete;
		auto operator=(BSAutoLockWriteLockPolicy&&) -> BSAutoLockWriteLockPolicy& = delete;

		static void lock(mutex_type& a_mutex) noexcept(Impl::nothrow_write_lockable<mutex_type>)
		{
			a_mutex.lock();
		}

		static void unlock(mutex_type& a_mutex) noexcept(Impl::nothrow_write_unlockable<mutex_type>)
		{
			a_mutex.unlock();
		}
	};

	template <Impl::AutoLockDefaultPolicyConstraint Mutex, template <class> class Policy>
	class BSAutoLock
	{
	public:
		using mutex_type = Mutex;
		using policy_type = Policy<mutex_type>;

		explicit BSAutoLock(mutex_type& a_mutex) noexcept(Impl::nothrow_lockable<mutex_type>) :
			_lock(std::addressof(a_mutex))
		{
			lock();
		}

		~BSAutoLock() noexcept(Impl::nothrow_unlockable<mutex_type>)
		{
			unlock();
		}

		BSAutoLock(const BSAutoLock&) = delete;
		BSAutoLock(BSAutoLock&&) noexcept = default;

		auto operator=(const BSAutoLock&) -> BSAutoLock& = delete;
		auto operator=(BSAutoLock&&) noexcept -> BSAutoLock& = default;

		void lock() //
			noexcept(Impl::nothrow_lockable<mutex_type>)
		{
			if (_lock) {
				policy_type::lock(*_lock);
			}
		}

		void unlock() //
			noexcept(Impl::nothrow_unlockable<mutex_type>)
		{
			if (_lock) {
				policy_type::unlock(*_lock);
			}
		}

	private:
		// members
		mutex_type* _lock{nullptr}; // 0x00
	};
}
