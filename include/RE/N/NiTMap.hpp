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
		NiTMapItem* next{ nullptr }; // 00
		key_type first{};			 // 08
		mapped_type second{};		 // ??
	};

	// hash table with separate chaining
	template <class Allocator, class Key, class T>
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
			iterator_base(const iterator_base<V>& a_rhs) noexcept
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
				: _proxy(a_rhs._proxy),
				  _iter(a_rhs._iter),
				  _index(a_rhs._index)
			{
			}

			template <class V>
			iterator_base& operator=(const iterator_base<V>& a_rhs) noexcept
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
			{
				REX::Assert(_proxy == a_rhs._proxy);

				_proxy = a_rhs._proxy;
				_iter = a_rhs._iter;
				_index = a_rhs._index;
				return *this;
			}

			[[nodiscard]] reference operator*() const noexcept
			{
				REX::Assert(_iter);
				REX::Assert(_index < _proxy->_capacity);
				return *_iter;
			}

			[[nodiscard]] pointer operator->() const noexcept
			{
				return std::pointer_traits<pointer>::pointer_to(operator*());
			}

			[[nodiscard]] bool operator==(const iterator_base& a_rhs) const noexcept
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

			[[nodiscard]] bool operator!=(const iterator_base& a_rhs) const noexcept
			{
				return !operator==(a_rhs);
			}

			iterator_base& operator++() noexcept
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

			iterator_base operator++(std::int32_t) noexcept
			{
				auto temp = iterator_base(*this);
				operator++();
				return temp;
			}

		protected:
			template <class, class, class>
			friend class NiTMapBase;

			iterator_base(NiTMapBase* a_proxy, std::uint32_t a_index) noexcept
				: _proxy(a_proxy),
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

			iterator_base(NiTMapBase* a_proxy, value_type* a_it, std::uint32_t a_index) noexcept
				: _proxy(a_proxy),
				  _iter(a_it),
				  _index(a_index)
			{
				REX::Assert(_proxy);
				REX::Assert(_iter);
			}

		private:
			// members
			NiTMapBase* _proxy{ nullptr }; // 00
			value_type* _iter{ nullptr };  // 08
			std::uint32_t _index{ 0 };	   // 10
		};

		class AntiBloatAllocator
			: public Allocator // 00
		{
		public:
			// members
			size_type size{ 0 }; // ??
		};

	public:
		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;
		using allocator_type = AntiBloatAllocator;

		NiTMapBase() = default;

		virtual ~NiTMapBase() // 00
		{
			free_resources();
		}

		NiTMapBase(const NiTMapBase&) = delete;

		NiTMapBase(NiTMapBase&& a_rhs) noexcept
			: _capacity(std::exchange(a_rhs._capacity, 0)),
			  _data(std::exchange(a_rhs._data, nullptr)),
			  _allocator(std::move(a_rhs._allocator))
		{
		}

		NiTMapBase& operator=(const NiTMapBase&) = delete;

		NiTMapBase& operator=(NiTMapBase&& a_rhs) noexcept
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
		virtual std::uint32_t hash_function(key_type a_key) const // 01
		{
			if constexpr (std::is_pointer_v<key_type>) {
				return std::bit_cast<std::uintptr_t>(a_key) % _capacity;
			}
			else {
				return a_key % _capacity;
			}
		}

		virtual bool key_eq(key_type a_lhs, key_type a_rhs) const // 02
		{
			return a_lhs == a_rhs;
		}

		virtual void assign_value(value_type* a_value, key_type a_key, mapped_type a_mapped) // 03
		{
			a_value->first = a_key;
			a_value->second = a_mapped;
		}

		virtual void clear_value([[maybe_unused]] value_type* a_value) // 04
		{
			return;
		}

		virtual value_type* malloc_value() = 0;			  // 05
		virtual void free_value(value_type* a_value) = 0; // 06

	public:
		[[nodiscard]] iterator begin() noexcept { return make_iterator<iterator>(0); }
		[[nodiscard]] const_iterator begin() const noexcept { return make_iterator<const_iterator>(0); }
		[[nodiscard]] const_iterator cbegin() const noexcept { return make_iterator<const_iterator>(0); }

		[[nodiscard]] iterator end() noexcept { return make_iterator<iterator>(_capacity); }
		[[nodiscard]] const_iterator end() const noexcept { return make_iterator<const_iterator>(_capacity); }
		[[nodiscard]] const_iterator cend() const noexcept { return make_iterator<const_iterator>(_capacity); }

		[[nodiscard]] size_type capacity() const noexcept { return _capacity; }
		[[nodiscard]] size_type size() const noexcept { return _allocator.size; }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

		[[nodiscard]] bool empty() const noexcept { return _allocator.size == 0; }

		[[nodiscard]] auto& at(const key_type& a_key)
		{
			const auto it = find(a_key);
			REX::Assert(it != end());
			return it->second;
		}

		[[nodiscard]] const auto& at(const key_type& a_key) const
		{
			const auto it = find(a_key);
			REX::Assert(it != end());
			return it->second;
		}

		[[nodiscard]] iterator find(const Key& a_key)
		{
			const auto result = do_find(a_key);
			return result ? make_iterator<iterator>(result->first, result->second) : end();
		}

		[[nodiscard]] const_iterator find(const Key& a_key) const
		{
			const auto result = do_find(a_key);
			return result ? make_iterator<const_iterator>(result->first, result->second) : end();
		}

		void clear()
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

	protected:
		template <class It>
		[[nodiscard]] It make_iterator() const noexcept
		{
			return It(this, 0);
		}

		template <class It>
		[[nodiscard]] It make_iterator(size_type a_index) const noexcept
		{
			return It(this, a_index);
		}

		template <class It>
		[[nodiscard]] It make_iterator(value_type* a_it, size_type a_index) const noexcept
		{
			return It(this, a_it, a_index);
		}

		[[nodiscard]] std::optional<std::pair<value_type*, std::uint32_t>> do_find(const Key& a_key) const
		{
			auto index = hash_function(a_key);
			for (auto it = _data[index]; it; it = it->next) {
				if (key_eq(a_key, it->first)) {
					return std::make_optional(std::make_pair(it, index));
				}
			}

			return std::nullopt;
		}

		void free_resources()
		{
			clear();

			if (_data) {
				free(_data);
				_data = nullptr;
			}

			_capacity = 0;
		}

		// members
		size_type _capacity{ 0 };	   // 08
		std::uint32_t _pad0C{ 0 };	   // 0C
		value_type** _data{ nullptr }; // 10
		allocator_type _allocator{};   // 18
	};

	template <class Key, class T>
	class NiTMap
		: public NiTMapBase<NiTDefaultAllocator<NiTMapItem<Key, T>>, Key, T> // 00
	{
	private:
		using super = NiTMapBase<NiTDefaultAllocator<NiTMapItem<Key, T>>, Key, T>;

	public:
		using key_type = super::key_type;
		using mapped_type = super::mapped_type;
		using value_type = super::value_type;
		using size_type = super::size_type;
		using difference_type = super::difference_type;
		using allocator_type = super::allocator_type;

	protected:
		value_type* malloc_value() override // 05
		{
			return new value_type();
		}

		void free_value(value_type* a_value) override // 06
		{
			delete a_value;
		}
	};
}
