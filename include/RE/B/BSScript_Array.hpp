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

	class Array
		: public BSIntrusiveRefCounted // 00
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

		Array& operator=(const Array&) = delete;
		Array& operator=(Array&&) = delete;

		[[nodiscard]] reference operator[](size_type a_index) noexcept { return elements[a_index]; }
		[[nodiscard]] const_reference operator[](size_type a_index) const noexcept { return elements[a_index]; }

		[[nodiscard]] reference at(size_type a_index) noexcept { return elements.at(a_index); }
		[[nodiscard]] const_reference at(size_type a_index) const noexcept { return elements.at(a_index); }

		[[nodiscard]] reference front() noexcept { return elements.front(); }
		[[nodiscard]] const_reference front() const noexcept { return elements.front(); }

		[[nodiscard]] reference back() noexcept { return elements.back(); }
		[[nodiscard]] const_reference back() const noexcept { return elements.back(); }

		[[nodiscard]] pointer data() noexcept { return elements.data(); }
		[[nodiscard]] const_pointer data() const noexcept { return elements.data(); }

		[[nodiscard]] iterator begin() noexcept { return elements.begin(); }
		[[nodiscard]] const_iterator begin() const noexcept { return elements.begin(); }
		[[nodiscard]] const_iterator cbegin() const noexcept { return elements.cbegin(); }

		[[nodiscard]] iterator end() noexcept { return elements.end(); }
		[[nodiscard]] const_iterator end() const noexcept { return elements.end(); }
		[[nodiscard]] const_iterator cend() const noexcept { return elements.cend(); }

		[[nodiscard]] reverse_iterator rbegin() noexcept { return elements.rbegin(); }
		[[nodiscard]] const_reverse_iterator rbegin() const noexcept { return elements.rbegin(); }
		[[nodiscard]] const_reverse_iterator crbegin() const noexcept { return elements.crbegin(); }

		[[nodiscard]] reverse_iterator rend() noexcept { return elements.rend(); }
		[[nodiscard]] const_reverse_iterator rend() const noexcept { return elements.rend(); }
		[[nodiscard]] const_reverse_iterator crend() const noexcept { return elements.crend(); }

		[[nodiscard]] size_type size() const noexcept { return elements.size(); }
		[[nodiscard]] size_type capacity() const noexcept { return elements.capacity(); }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return elements.max_size(); }

		[[nodiscard]] bool empty() const noexcept { return elements.empty(); }

		[[nodiscard]] bool IsObjectArray() const noexcept { return elementType.IsObject(); }
		[[nodiscard]] bool IsStringArray() const noexcept { return elementType.IsString(); }
		[[nodiscard]] bool IsIntArray() const noexcept { return elementType.IsInt(); }
		[[nodiscard]] bool IsUIntArray() const noexcept { return elementType.IsUInt(); }
		[[nodiscard]] bool IsFloatArray() const noexcept { return elementType.IsFloat(); }
		[[nodiscard]] bool IsBoolArray() const noexcept { return elementType.IsBool(); }
		[[nodiscard]] bool IsVarArray() const noexcept { return elementType.IsVar(); }
		[[nodiscard]] bool IsStructArray() const noexcept { return elementType.IsStruct(); }

		[[nodiscard]] bool Equals(const Array& a_rhs) const noexcept;
		[[nodiscard]] bool RefEquals(const Array& a_rhs) const noexcept;
		[[nodiscard]] bool DeepEquals(const Array& a_rhs) const noexcept;

		[[nodiscard]] std::strong_ordering Compare(const Array& a_rhs) const noexcept;
		[[nodiscard]] std::strong_ordering RefCompare(const Array& a_rhs) const noexcept;
		[[nodiscard]] std::partial_ordering DeepCompare(const Array& a_rhs) const noexcept;

		[[nodiscard]] TypeInfo GetTypeInfo() const noexcept;

		[[nodiscard]] TypeInfo& GetElementTypeInfo() noexcept { return elementType; }
		[[nodiscard]] const TypeInfo& GetElementTypeInfo() const noexcept { return elementType; }

		[[nodiscard]] BSTSmartPointer<Array> Clone(IVirtualMachine& a_vm) const;
		[[nodiscard]] BSTSmartPointer<Array> DeepClone(IVirtualMachine& a_vm) const;

		[[nodiscard]] std::string ToString() const;

		// members
		TypeInfo elementType;			 // 08
		mutable BSSpinLock elementsLock; // 10
		BSTArray<Variable> elements;	 // 18
	};
	static_assert(sizeof(Array) == 0x30);
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<RE::BSScript::Array>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSScript::Array& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <>
	struct formatter<RE::BSScript::Array>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSScript::Array& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif
