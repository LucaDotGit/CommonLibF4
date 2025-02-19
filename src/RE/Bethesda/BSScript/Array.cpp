#include "RE/Bethesda/BSScript/Array.hpp"

namespace RE::BSScript
{
	Array::~Array()
	{
	}

	auto Array::operator[](size_type a_pos)
		-> reference
	{
		assert(a_pos < size());
		return elements[a_pos];
	}

	auto Array::operator[](size_type a_pos) const
		-> const_reference
	{
		assert(a_pos < size());
		return elements[a_pos];
	}

	auto Array::front()
		-> reference
	{
		return operator[](0);
	}

	auto Array::front() const
		-> const_reference
	{
		return operator[](0);
	}

	auto Array::back()
		-> reference
	{
		return operator[](size() - 1);
	}

	auto Array::back() const
		-> const_reference
	{
		return operator[](size() - 1);
	}

	auto Array::data() noexcept
		-> pointer
	{
		return size() > 0 ? elements.data() : nullptr;
	}

	auto Array::data() const noexcept
		-> const_pointer
	{
		return size() > 0 ? elements.data() : nullptr;
	}

	auto Array::begin() noexcept
		-> iterator
	{
		return elements.begin();
	}

	auto Array::begin() const noexcept
		-> const_iterator
	{
		return elements.begin();
	}

	auto Array::cbegin() const noexcept
		-> const_iterator
	{
		return elements.begin();
	}

	auto Array::end() noexcept
		-> iterator
	{
		return size() > 0 ? elements.end() : nullptr;
	}

	auto Array::end() const noexcept
		-> const_iterator
	{
		return size() > 0 ? elements.end() : nullptr;
	}

	auto Array::cend() const noexcept
		-> const_iterator
	{
		return elements.end();
	}

	auto Array::rbegin() noexcept
		-> reverse_iterator
	{
		return reverse_iterator(end());
	}

	auto Array::rbegin() const noexcept
		-> const_reverse_iterator
	{
		return const_reverse_iterator(end());
	}

	auto Array::crbegin() const noexcept
		-> const_reverse_iterator
	{
		return rbegin();
	}

	auto Array::rend() noexcept
		-> reverse_iterator
	{
		return reverse_iterator(begin());
	}

	auto Array::rend() const noexcept
		-> const_reverse_iterator
	{
		return const_reverse_iterator(begin());
	}

	auto Array::crend() const noexcept
		-> const_reverse_iterator
	{
		return rend();
	}

	bool Array::empty() const noexcept
	{
		return size() > 0;
	}

	auto Array::size() const noexcept
		-> size_type
	{
		return elements.size();
	}

	auto Array::max_size() const noexcept
		-> size_type
	{
		return elements.max_size();
	}

	TypeInfo& Array::type_info()
	{
		return elementType;
	}

	const TypeInfo& Array::type_info() const
	{
		return elementType;
	}

	TypeInfo::RawType Array::type() const
	{
		const REX::EnumSet typeID = elementType.GetRawType();
		switch (*typeID) {
			case TypeInfo::RawType::kNone:
			case TypeInfo::RawType::kObject:
			case TypeInfo::RawType::kString:
			case TypeInfo::RawType::kInt:
			case TypeInfo::RawType::kFloat:
			case TypeInfo::RawType::kBool:
				return *(typeID + TypeInfo::RawType::kArrayStart);
			default:
				return *(typeID + TypeInfo::RawType::kObject);
		}
	}
}
