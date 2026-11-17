#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class IVirtualMachine;

	class Array : public BSIntrusiveRefCounted // 0x00
	{
	public:
		using value_type = Variable;
		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = value_type*;
		using const_iterator = const value_type*;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		inline static constexpr auto INTERNAL_MAX_SIZE = static_cast<size_type>(128);

		Array() noexcept;
		~Array() noexcept;

		Array(const Array&) = delete;
		Array(Array&&) = delete;

		auto operator=(const Array&) -> Array& = delete;
		auto operator=(Array&&) -> Array& = delete;

		[[nodiscard]]
		auto operator[](size_type a_index) noexcept -> reference
		{
			return elements[a_index];
		}

		[[nodiscard]]
		auto operator[](size_type a_index) const noexcept -> const_reference
		{
			return elements[a_index];
		}

		[[nodiscard]]
		auto at(size_type a_index) noexcept -> reference
		{
			return elements.at(a_index);
		}

		[[nodiscard]]
		auto at(size_type a_index) const noexcept -> const_reference
		{
			return elements.at(a_index);
		}

		[[nodiscard]]
		auto front() noexcept -> reference
		{
			return elements.front();
		}

		[[nodiscard]]
		auto front() const noexcept -> const_reference
		{
			return elements.front();
		}

		[[nodiscard]]
		auto back() noexcept -> reference
		{
			return elements.back();
		}

		[[nodiscard]]
		auto back() const noexcept -> const_reference
		{
			return elements.back();
		}

		[[nodiscard]]
		auto data() noexcept -> pointer
		{
			return elements.data();
		}

		[[nodiscard]]
		auto data() const noexcept -> const_pointer
		{
			return elements.data();
		}

		[[nodiscard]]
		auto begin() noexcept -> iterator
		{
			return elements.begin();
		}

		[[nodiscard]]
		auto begin() const noexcept -> const_iterator
		{
			return elements.begin();
		}

		[[nodiscard]]
		auto cbegin() const noexcept -> const_iterator
		{
			return elements.cbegin();
		}

		[[nodiscard]]
		auto end() noexcept -> iterator
		{
			return elements.end();
		}

		[[nodiscard]]
		auto end() const noexcept -> const_iterator
		{
			return elements.end();
		}

		[[nodiscard]]
		auto cend() const noexcept -> const_iterator
		{
			return elements.cend();
		}

		[[nodiscard]]
		auto rbegin() noexcept -> reverse_iterator
		{
			return elements.rbegin();
		}

		[[nodiscard]]
		auto rbegin() const noexcept -> const_reverse_iterator
		{
			return elements.rbegin();
		}

		[[nodiscard]]
		auto crbegin() const noexcept -> const_reverse_iterator
		{
			return elements.crbegin();
		}

		[[nodiscard]]
		auto rend() noexcept -> reverse_iterator
		{
			return elements.rend();
		}

		[[nodiscard]]
		auto rend() const noexcept -> const_reverse_iterator
		{
			return elements.rend();
		}

		[[nodiscard]]
		auto crend() const noexcept -> const_reverse_iterator
		{
			return elements.crend();
		}

		[[nodiscard]]
		auto size() const noexcept -> size_type
		{
			return elements.size();
		}

		[[nodiscard]]
		auto capacity() const noexcept -> size_type
		{
			return elements.capacity();
		}

		[[nodiscard]]
		constexpr auto max_size() const noexcept -> size_type
		{
			return elements.max_size();
		}

		[[nodiscard]]
		auto empty() const noexcept -> bool
		{
			return elements.empty();
		}

		[[nodiscard]]
		auto IsObjectArray() const noexcept -> bool
		{
			return elementType.IsObject();
		}

		[[nodiscard]]
		auto IsStringArray() const noexcept -> bool
		{
			return elementType.IsString();
		}

		[[nodiscard]]
		auto IsIntArray() const noexcept -> bool
		{
			return elementType.IsInt();
		}

		[[nodiscard]]
		auto IsUIntArray() const noexcept -> bool
		{
			return elementType.IsUInt();
		}

		[[nodiscard]]
		auto IsFloatArray() const noexcept -> bool
		{
			return elementType.IsFloat();
		}

		[[nodiscard]]
		auto IsBoolArray() const noexcept -> bool
		{
			return elementType.IsBool();
		}

		[[nodiscard]]
		auto IsVariantArray() const noexcept -> bool
		{
			return elementType.IsVariant();
		}

		[[nodiscard]]
		auto IsStructArray() const noexcept -> bool
		{
			return elementType.IsStruct();
		}

		[[nodiscard]]
		auto Equals(const Array& a_rhs) const noexcept -> bool;
		[[nodiscard]]
		auto RefEquals(const Array& a_rhs) const noexcept -> bool;
		[[nodiscard]]
		auto DeepEquals(const Array& a_rhs) const noexcept -> bool;

		[[nodiscard]]
		auto Compare(const Array& a_rhs) const noexcept -> std::strong_ordering;
		[[nodiscard]]
		auto RefCompare(const Array& a_rhs) const noexcept -> std::strong_ordering;
		[[nodiscard]]
		auto DeepCompare(const Array& a_rhs) const noexcept -> std::partial_ordering;

		[[nodiscard]]
		auto GetTypeInfo() const noexcept -> TypeInfo;

		[[nodiscard]]
		auto GetElementTypeInfo() noexcept -> TypeInfo&
		{
			return elementType;
		}

		[[nodiscard]]
		auto GetElementTypeInfo() const noexcept -> const TypeInfo&
		{
			return elementType;
		}

		[[nodiscard]]
		auto Clone(IVirtualMachine& a_vm) const -> BSTSmartPointer<Array>;
		[[nodiscard]]
		auto DeepClone(IVirtualMachine& a_vm) const -> BSTSmartPointer<Array>;

		[[nodiscard]]
		auto ToString() const -> std::string;

		// members
		TypeInfo elementType;			 // 0x08
		mutable BSSpinLock elementsLock; // 0x10
		BSTArray<Variable> elements;	 // 0x18
	};

	static_assert(sizeof(Array) == 0x30);
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<RE::BSScript::Array> : public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const RE::BSScript::Array& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <>
	struct formatter<RE::BSScript::Array> : public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const RE::BSScript::Array& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif
