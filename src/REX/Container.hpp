#pragma once

#include "REX/Casting.hpp"
#include "REX/Concepts.hpp"
#include "REX/ScopeExit.hpp"
#include "REX/UninitializedValue.hpp"

namespace REX
{
	// Source: https://stackoverflow.com/questions/79004127/stdflat-map-stdflat-set-and-reserving-storage

	template <class Key, class Value, class Compare, class KeyContainer, class ValueContainer>
	constexpr void Reserve(
		std::flat_map<Key, Value, Compare, KeyContainer, ValueContainer>& a_container,
		std::size_t a_newCapacity)
	{
		auto&& [keys, values] = std::move(a_container).extract();

		const auto scopeExit = REX::ScopeExit([&a_container, &keys, &values]() mutable noexcept -> void {
			a_container.replace(std::move(keys), std::move(values));
		});

		if constexpr (REX::reservable<decltype(keys)>) {
			keys.reserve(a_newCapacity);
		}

		if constexpr (REX::reservable<decltype(values)>) {
			values.reserve(a_newCapacity);
		}
	}

	template <class Key, class Compare, class KeyContainer>
	constexpr void Reserve(std::flat_set<Key, Compare, KeyContainer>& a_container, std::size_t a_newCapacity)
	{
		auto&& keys = std::move(a_container).extract();

		const auto scopeExit = REX::ScopeExit([&a_container, &keys]() mutable noexcept -> void {
			a_container.replace(std::move(keys));
		});

		if constexpr (REX::reservable<decltype(keys)>) {
			keys.reserve(a_newCapacity);
		}
	}

	template <class Key, class Value, class Compare, class KeyContainer, class ValueContainer>
	constexpr void Reserve(
		std::flat_multimap<Key, Value, Compare, KeyContainer, ValueContainer>& a_container,
		std::size_t a_newCapacity)
	{
		auto&& [keys, values] = std::move(a_container).extract();

		const auto scopeExit = REX::ScopeExit([&a_container, &keys, &values]() mutable noexcept -> void {
			a_container.replace(std::move(keys), std::move(values));
		});

		if constexpr (REX::reservable<decltype(keys)>) {
			keys.reserve(a_newCapacity);
		}

		if constexpr (REX::reservable<decltype(values)>) {
			values.reserve(a_newCapacity);
		}
	}

	template <class Key, class Compare, class KeyContainer>
	constexpr void Reserve(std::flat_multiset<Key, Compare, KeyContainer>& a_container, std::size_t a_newCapacity)
	{
		auto&& keys = std::move(a_container).extract();

		const auto scopeExit = REX::ScopeExit([&a_container, &keys]() mutable noexcept -> void {
			a_container.replace(std::move(keys));
		});

		if constexpr (REX::reservable<decltype(keys)>) {
			keys.reserve(a_newCapacity);
		}
	}

	template <class Key, class Value, class Compare, class KeyContainer, class ValueContainer>
	constexpr void Resize(
		std::flat_map<Key, Value, Compare, KeyContainer, ValueContainer>& a_container,
		std::size_t a_newSize)
	{
		auto&& [keys, values] = std::move(a_container).extract();

		const auto scopeExit = REX::ScopeExit([&a_container, &keys, &values]() mutable noexcept -> void {
			a_container.replace(std::move(keys), std::move(values));
		});

		if constexpr (REX::resizable<decltype(keys)>) {
			keys.resize(a_newSize);
		}

		if constexpr (REX::resizable<decltype(values)>) {
			values.resize(a_newSize);
		}
	}

	template <class Key, class Compare, class KeyContainer>
	constexpr void Resize(std::flat_set<Key, Compare, KeyContainer>& a_container, std::size_t a_newSize)
	{
		auto&& keys = std::move(a_container).extract();

		const auto scopeExit = REX::ScopeExit([&a_container, &keys]() mutable noexcept -> void {
			a_container.replace(std::move(keys));
		});

		if constexpr (REX::resizable<decltype(keys)>) {
			keys.resize(a_newSize);
		}
	}

	template <class Key, class Value, class Compare, class KeyContainer, class ValueContainer>
	constexpr void Resize(
		std::flat_multimap<Key, Value, Compare, KeyContainer, ValueContainer>& a_container,
		std::size_t a_newSize)
	{
		auto&& [keys, values] = std::move(a_container).extract();

		const auto scopeExit = REX::ScopeExit([&a_container, &keys, &values]() mutable noexcept -> void {
			a_container.replace(std::move(keys), std::move(values));
		});

		if constexpr (REX::resizable<decltype(keys)>) {
			keys.resize(a_newSize);
		}

		if constexpr (REX::resizable<decltype(values)>) {
			values.resize(a_newSize);
		}
	}

	template <class Key, class Compare, class KeyContainer>
	constexpr void Resize(std::flat_multiset<Key, Compare, KeyContainer>& a_container, std::size_t a_newSize)
	{
		auto&& keys = std::move(a_container).extract();

		const auto scopeExit = REX::ScopeExit([&a_container, &keys]() mutable noexcept -> void {
			a_container.replace(std::move(keys));
		});

		if constexpr (REX::resizable<decltype(keys)>) {
			keys.resize(a_newSize);
		}
	}

	template <class T, class Allocator>
	constexpr auto Pop(std::stack<T, Allocator>& a_container) noexcept(noexcept(a_container.top()))
	{
		auto result = std::move(a_container.top());
		a_container.pop();
		return result;
	}

	template <class T, class Container>
	constexpr auto Pop(std::queue<T, Container>& a_container) noexcept(noexcept(a_container.front()))
	{
		auto result = std::move(a_container.front());
		a_container.pop();
		return result;
	}

	template <class T, class Container, class Compare>
	constexpr auto Pop(std::priority_queue<T, Container, Compare>& a_container) noexcept(noexcept(a_container.top()))
	{
		auto result = std::move(const_cast<std::remove_cvref_t<decltype(a_container.top())>&>(a_container.top()));
		a_container.pop();
		return result;
	}

	template <class T, class Allocator>
	constexpr auto PopFront(std::deque<T, Allocator>& a_container) noexcept(noexcept(a_container.front()))
	{
		auto result = std::move(a_container.front());
		a_container.pop_front();
		return result;
	}

	template <class T, class Allocator>
	constexpr auto PopFront(std::list<T, Allocator>& a_container) noexcept(noexcept(a_container.front()))
	{
		auto result = std::move(a_container.front());
		a_container.pop_front();
		return result;
	}

	template <class T, class Allocator>
	constexpr auto PopFront(std::forward_list<T, Allocator>& a_container) noexcept(noexcept(a_container.front()))
	{
		auto result = std::move(a_container.front());
		a_container.pop_front();
		return result;
	}

	template <class T, class Allocator>
	constexpr auto PopBack(std::deque<T, Allocator>& a_container) noexcept(noexcept(a_container.back()))
	{
		auto result = std::move(a_container.back());
		a_container.pop_back();
		return result;
	}

	template <class T, class Allocator>
	constexpr auto PopBack(std::list<T, Allocator>& a_container) noexcept(noexcept(a_container.back()))
	{
		auto result = std::move(a_container.back());
		a_container.pop_back();
		return result;
	}

	template <class T, class Allocator>
	constexpr auto PopBack(std::forward_list<T, Allocator>& a_container) noexcept(noexcept(a_container.back()))
	{
		auto result = std::move(a_container.back());
		a_container.pop_back();
		return result;
	}

	// Source: https://geeksforgeeks.org/cpp/resize-vector-without-initializing-new-elements-in-cpp

	template <class CharT, class Traits, class Allocator>
	constexpr void ResizeForOverwrite(std::basic_string<CharT, Traits, Allocator>& a_container, std::size_t a_newSize)
	{
		a_container.resize_and_overwrite(a_newSize, [](CharT* a_data, std::size_t a_size) noexcept -> std::size_t {
			std::uninitialized_default_construct_n(a_data, a_size);
			return a_size;
		});
	}

	template <class T, class Allocator>
	constexpr void ResizeForOverwrite(std::vector<T, Allocator>& a_container, std::size_t a_newSize)
	{
		if constexpr (!REX::trivially_writable<T> || REX::boolean<T>) {
			a_container.resize(a_newSize);
		}
		else {
			using UninitializedAllocator =
				std::allocator_traits<Allocator>::template rebind_alloc<REX::UninitializedValue<T>>;

			auto& uninitializedContainer =
				REX::CheckedReinterpretCast<std::vector<REX::UninitializedValue<T>, UninitializedAllocator>&>(
					a_container);
			uninitializedContainer.resize(a_newSize);
		}
	}

#if (__cpp_lib_inplace_vector >= 202'603l)
	template <class T, std::size_t N>
	constexpr void ResizeForOverwrite(std::inplace_vector<T, N>& a_container, std::size_t a_newSize)
	{
		if constexpr (!REX::trivially_writable<T> || REX::boolean<T>) {
			a_container.resize(a_newSize);
		}
		else {
			auto& uninitializedContainer =
				REX::CheckedReinterpretCast<std::inplace_vector<REX::UninitializedValue<T>, N>&>(a_container);
			uninitializedContainer.resize(a_newSize);
		}
	}
#endif

	template <class T, class Allocator>
	constexpr void ResizeForOverwrite(std::deque<T, Allocator>& a_container, std::size_t a_newSize)
	{
		if constexpr (!REX::trivially_writable<T> || REX::boolean<T>) {
			a_container.resize(a_newSize);
		}
		else {
			using UninitializedAllocator =
				std::allocator_traits<Allocator>::template rebind_alloc<REX::UninitializedValue<T>>;

			auto& uninitializedContainer =
				REX::CheckedReinterpretCast<std::deque<REX::UninitializedValue<T>, UninitializedAllocator>&>(
					a_container);
			uninitializedContainer.resize(a_newSize);
		}
	}

	template <class T, class Allocator>
	constexpr void ResizeForOverwrite(std::list<T, Allocator>& a_container, std::size_t a_newSize)
	{
		if constexpr (!REX::trivially_writable<T> || REX::boolean<T>) {
			a_container.resize(a_newSize);
		}
		else {
			using UninitializedAllocator =
				std::allocator_traits<Allocator>::template rebind_alloc<REX::UninitializedValue<T>>;

			auto& uninitializedContainer =
				REX::CheckedReinterpretCast<std::list<REX::UninitializedValue<T>, UninitializedAllocator>&>(
					a_container);
			uninitializedContainer.resize(a_newSize);
		}
	}

	template <class T, class Allocator>
	constexpr void ResizeForOverwrite(std::forward_list<T, Allocator>& a_container, std::size_t a_newSize)
	{
		if constexpr (!REX::trivially_writable<T> || REX::boolean<T>) {
			a_container.resize(a_newSize);
		}
		else {
			using UninitializedAllocator =
				std::allocator_traits<Allocator>::template rebind_alloc<REX::UninitializedValue<T>>;

			auto& uninitializedContainer =
				REX::CheckedReinterpretCast<std::forward_list<REX::UninitializedValue<T>, UninitializedAllocator>&>(
					a_container);
			uninitializedContainer.resize(a_newSize);
		}
	}
}
