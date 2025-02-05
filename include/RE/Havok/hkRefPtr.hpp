#pragma once

namespace RE
{
	template <class T>
	class hkRefPtr
	{
	public:
		hkRefPtr() noexcept = default;

		hkRefPtr(T* a_ptr)
		{
			_ptr = a_ptr;
			TryAttach();
		}

		~hkRefPtr() noexcept
		{
			TryDetach();
		}

		void operator=(hkRefPtr<T>& a_other)
		{
			TryDetach();
			_ptr = a_other._ptr;
			TryAttach();
		}

		void operator=(const hkRefPtr<T>& a_other)
		{
			TryDetach();
			_ptr = a_other._ptr;
			TryAttach();
		}

		void operator=(hkRefPtr<T>&& a_other)
		{
			TryDetach();
			_ptr = a_other._ptr;
			a_other._ptr = nullptr;
		}
		void operator=(const hkRefPtr<T>&&) = delete;

		void operator=(std::nullptr_t)
		{
			reset();
		}

		void reset()
		{
			_ptr = nullptr;
		}

		T* get() const
		{
			return _ptr;
		}

		T* operator->() const
		{
			return _ptr;
		}

		T& operator*() const
		{
			return *_ptr;
		}

		operator bool() const
		{
			return _ptr != nullptr;
		}

		bool operator==(const hkRefPtr<T>& a_other)
		{
			return _ptr == a_other._ptr;
		}

		bool operator==(std::nullptr_t)
		{
			return _ptr == nullptr;
		}

	private:
		inline void TryAttach()
		{
			if (_ptr) {
				_ptr->addReference();
			}
		}

		inline void TryDetach()
		{
			if (_ptr) {
				_ptr->removeReference();
				_ptr = nullptr;
			}
		}

		T* _ptr{ nullptr };
	};
}