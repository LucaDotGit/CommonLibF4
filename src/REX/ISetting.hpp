#pragma once

#include "REX/Error.hpp"
#include "REX/Hashing.hpp"

namespace REX
{
	template <class Entry>
	class ISetting : public std::enable_shared_from_this<ISetting<Entry>>
	{
	public:
		using entry_type = Entry;

		ISetting() noexcept = default;
		virtual ~ISetting() noexcept = default;

		ISetting(const ISetting&) = delete;
		ISetting(ISetting&&) noexcept = default;

		auto operator=(const ISetting&) -> ISetting& = delete;
		auto operator=(ISetting&&) noexcept -> ISetting& = default;

		[[nodiscard]]
		auto operator==(const ISetting& a_other) const noexcept -> bool
		{
			return GetKey() == a_other.GetKey();
		}

		[[nodiscard]]
		auto operator<=>(const ISetting& a_other) const noexcept -> auto
		{
			return GetKey() <=> a_other.GetKey();
		}

		[[nodiscard]]
		virtual auto GetKey() const noexcept -> std::string_view = 0;

		virtual auto LoadEntry(const entry_type& a_parent) -> REX::SystemError = 0;
		virtual auto SaveEntry(entry_type& a_parent) const -> REX::SystemError = 0;
	};
}

namespace std
{
	template <class T>
		requires(std::derived_from<T, REX::ISetting<typename T::entry_type>>)
	struct hash<T>
	{
	public:
		[[nodiscard]]
		auto operator()(const T& a_setting) const noexcept -> std::size_t
		{
			return REX::Hash(a_setting.GetKey());
		}
	};
}
