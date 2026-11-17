#pragma once

#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiTDefaultAllocator.hpp"

namespace RE
{
	template <class Key, class T>
	class NiTMapItem
	{
	public:
		using key_type = Key;
		using mapped_type = T;

		// members
		NiTMapItem* next{nullptr}; // 0x00
		key_type first{};		   // 0x08
		mapped_type second{};	   // 0x??
	};

	// hash table with separate chaining
	template <class Key, class T, class Allocator>
	class NiTMapBase
	{
	public:
		using key_type = Key;
		using mapped_type = T;
		using value_type = NiTMapItem<Key, T>;
		using size_type = std::uint32_t;
		using difference_type = std::int32_t;

	protected:
		template <class U>
		class iterator_base
		{
		public:
			using value_type = U;
			using size_type = std::uint32_t;
			using difference_type = std::int32_t;
			using pointer = U*;
			using reference = U&;
			using iterator_category = std::forward_iterator_tag;

			iterator_base() noexcept = default;
			~iterator_base() noexcept = default;

			template <class V>
			// NOLINTNEXTLINE(misc-explicit-constructor)
			iterator_base(const iterator_base<V>& a_rhs) noexcept
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
				:
				_proxy(a_rhs._proxy),
				_iter(a_rhs._iter),
				_index(a_rhs._index)
			{
			}

			iterator_base(const iterator_base&) = default;
			iterator_base(iterator_base&&) noexcept = default;

			template <class V>
			auto operator=(const iterator_base<V>& a_rhs) noexcept -> iterator_base&
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
			{
				REX::Assert(_proxy == a_rhs._proxy);

				_proxy = a_rhs._proxy;
				_iter = a_rhs._iter;
				_index = a_rhs._index;
				return *this;
			}

			auto operator=(const iterator_base&) -> iterator_base& = default;
			auto operator=(iterator_base&&) noexcept -> iterator_base& = default;

			[[nodiscard]]
			auto operator*() const noexcept -> reference
			{
				REX::Assert(_iter);
				REX::Assert(_index < _proxy->_capacity);
				return *_iter;
			}

			[[nodiscard]]
			auto operator->() const noexcept -> pointer
			{
				return std::pointer_traits<pointer>::pointer_to(operator*());
			}

			[[nodiscard]]
			auto operator==(const iterator_base& a_rhs) const noexcept -> bool
			{
				REX::Assert(_proxy == a_rhs._proxy);

				if (_index != a_rhs._index) {
					return false;
				}

				if (_index < _proxy->_capacity) {
					return _iter == a_rhs._iter;
				}

				return true;
			}

			auto operator++() noexcept -> iterator_base&
			{
				REX::Assert(_proxy);
				REX::Assert(_iter);
				REX::Assert(_index < _proxy->_capacity);

				if (_iter->next) {
					_iter = _iter->next;
				}
				else {
					do {
						_index++;
						_iter = _proxy->_data[_index];
					}
					while (!_iter && _index < _proxy->_capacity);
				}

				return *this;
			}

			auto operator++(std::int32_t) noexcept -> iterator_base
			{
				auto temp = iterator_base(*this);
				operator++();
				return temp;
			}

		protected:
			template <class, class, class>
			friend class NiTMapBase;

			iterator_base(NiTMapBase* a_proxy, std::uint32_t a_index) noexcept :
				_proxy(a_proxy),
				_iter(nullptr),
				_index(a_index)
			{
				REX::Assert(_proxy);

				_iter = _proxy->_data[_index];
				while (!_iter && _index < _proxy->_capacity) {
					_index++;
					_iter = _proxy->_data[_index];
				}
			}

			iterator_base(NiTMapBase* a_proxy, value_type* a_it, std::uint32_t a_index) noexcept :
				_proxy(a_proxy),
				_iter(a_it),
				_index(a_index)
			{
				REX::Assert(_proxy);
				REX::Assert(_iter);
			}

		private:
			// members
			NiTMapBase* _proxy{nullptr}; // 0x00
			value_type* _iter{nullptr};	 // 0x08
			std::uint32_t _index{0};	 // 0x10
		};

		class AntiBloatAllocator : public Allocator // 0x00
		{
		public:
			// members
			size_type size{0}; // 0x??
		};

	public:
		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;
		using allocator_type = AntiBloatAllocator;

		NiTMapBase() noexcept(std::is_nothrow_default_constructible_v<allocator_type>) = default;

		virtual ~NiTMapBase() noexcept // 0x00
		{
			free_resources();
		}

		NiTMapBase(const NiTMapBase&) = delete;

		NiTMapBase(NiTMapBase&& a_rhs) noexcept :
			_capacity(std::exchange(a_rhs._capacity, 0)),
			_data(std::exchange(a_rhs._data, nullptr)),
			_allocator(std::move(a_rhs._allocator))
		{
		}

		auto operator=(const NiTMapBase&) -> NiTMapBase& = delete;

		auto operator=(NiTMapBase&& a_rhs) noexcept -> NiTMapBase&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			free_resources();

			_capacity = std::exchange(a_rhs._capacity, 0);
			_data = std::exchange(a_rhs._data, nullptr);
			_allocator = std::move(a_rhs._allocator);
			return *this;
		}

	protected:
		// add
		virtual auto hash_function(key_type a_key) const -> std::uint32_t // 0x01
		{
			if constexpr (REX::pointer<key_type>) {
				return std::bit_cast<std::uintptr_t>(a_key) % _capacity;
			}
			else {
				return a_key % _capacity;
			}
		}

		virtual auto key_eq(key_type a_lhs, key_type a_rhs) const -> bool // 0x02
		{
			return a_lhs == a_rhs;
		}

		virtual void assign_value(value_type* a_value, key_type a_key, mapped_type a_mapped) // 0x03
		{
			a_value->first = a_key;
			a_value->second = a_mapped;
		}

		virtual void clear_value([[maybe_unused]] value_type* a_value) // 0x04
		{
			return;
		}

		virtual auto malloc_value() -> value_type* = 0;	  // 0x05
		virtual void free_value(value_type* a_value) = 0; // 0x06

	public:
		[[nodiscard]]
		auto begin() noexcept -> iterator
		{
			return make_iterator<iterator>(0);
		}

		[[nodiscard]]
		auto begin() const noexcept -> const_iterator
		{
			return make_iterator<const_iterator>(0);
		}

		[[nodiscard]]
		auto cbegin() const noexcept -> const_iterator
		{
			return make_iterator<const_iterator>(0);
		}

		[[nodiscard]]
		auto end() noexcept -> iterator
		{
			return make_iterator<iterator>(_capacity);
		}

		[[nodiscard]]
		auto end() const noexcept -> const_iterator
		{
			return make_iterator<const_iterator>(_capacity);
		}

		[[nodiscard]]
		auto cend() const noexcept -> const_iterator
		{
			return make_iterator<const_iterator>(_capacity);
		}

		[[nodiscard]]
		auto capacity() const noexcept -> size_type
		{
			return _capacity;
		}

		[[nodiscard]]
		auto size() const noexcept -> size_type
		{
			return _allocator.size;
		}

		[[nodiscard]]
		// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
		constexpr auto max_size() const noexcept -> size_type
		{
			return std::numeric_limits<size_type>::max();
		}

		[[nodiscard]]
		auto empty() const noexcept -> bool
		{
			return _allocator.size == 0;
		}

		[[nodiscard]]
		auto at(const key_type& a_key) -> auto&
		{
			const auto it = find(a_key);
			REX::Assert(it != end());
			return it->second;
		}

		[[nodiscard]]
		auto at(const key_type& a_key) const -> const auto&
		{
			const auto it = find(a_key);
			REX::Assert(it != end());
			return it->second;
		}

		[[nodiscard]]
		auto find(const Key& a_key) -> iterator
		{
			const auto result = do_find(a_key);
			return result ? make_iterator<iterator>(result->first, result->second) : end();
		}

		[[nodiscard]]
		auto find(const Key& a_key) const -> const_iterator
		{
			const auto result = do_find(a_key);
			return result ? make_iterator<const_iterator>(result->first, result->second) : end();
		}

		void clear() noexcept
		{
			for (auto i = static_cast<size_type>(0); i < _capacity; i++) {
				while (_data[i]) {
					auto* element = _data[i];
					_data[i] = _data[i]->next;

					clear_value(element);
					free_value(element);
				}
			}

			_allocator.size = 0;
		}

		void swap(NiTMapBase& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_capacity, a_other._capacity);
			std::swap(_data, a_other._data);
			std::swap(_allocator, a_other._allocator);
		}

	protected:
		template <class It>
		[[nodiscard]]
		auto make_iterator() const noexcept -> It
		{
			return It(this, 0);
		}

		template <class It>
		[[nodiscard]]
		auto make_iterator(size_type a_index) const noexcept -> It
		{
			return It(this, a_index);
		}

		template <class It>
		[[nodiscard]]
		auto make_iterator(value_type* a_it, size_type a_index) const noexcept -> It
		{
			return It(this, a_it, a_index);
		}

		[[nodiscard]]
		auto do_find(const Key& a_key) const -> std::optional<std::pair<value_type*, std::uint32_t>>
		{
			auto index = hash_function(a_key);
			for (auto it = _data[index]; it; it = it->next) {
				if (key_eq(a_key, it->first)) {
					return std::make_optional(std::make_pair(it, index));
				}
			}

			return std::nullopt;
		}

		void free_resources() noexcept
		{
			clear();

			if (_data) {
				free(_data);
				_data = nullptr;
			}

			_capacity = 0;
		}

		// members
		size_type _capacity{0};		 // 0x08
		value_type** _data{nullptr}; // 0x10
		allocator_type _allocator{}; // 0x18
	};

	template <class Key, class T>
	class NiTMap : public NiTMapBase<Key, T, NiTDefaultAllocator<NiTMapItem<Key, T>>> // 0x00
	{
	private:
		using super = NiTMapBase<Key, T, NiTDefaultAllocator<NiTMapItem<Key, T>>>;

	public:
		using key_type = super::key_type;
		using mapped_type = super::mapped_type;
		using value_type = super::value_type;
		using size_type = super::size_type;
		using difference_type = super::difference_type;
		using allocator_type = super::allocator_type;

	protected:
		auto malloc_value() -> value_type* override // 0x05
		{
			return new value_type();
		}

		void free_value(value_type* a_value) override // 0x06
		{
			delete a_value;
		}
	};
}
