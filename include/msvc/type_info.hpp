#pragma once

namespace msvc::detail
{
	inline constexpr auto SMALL_OBJECT_PTR_COUNT = static_cast<std::size_t>(6 + (16 / sizeof(std::uintptr_t)));
	inline constexpr auto SMALL_OBJECT_PTR_COUNT_OLD = static_cast<std::size_t>(SMALL_OBJECT_PTR_COUNT / 2);

	// struct `std::__type_info_node`
	struct type_info_node;

	// struct `std::__std_type_info_data`
	struct type_info_data
	{
	public:
		type_info_data() noexcept = delete;
		~type_info_data() noexcept = default;

		type_info_data(const type_info_data&) = delete;
		type_info_data(type_info_data&&) = delete;

		type_info_data& operator=(const type_info_data&) = delete;
		type_info_data& operator=(type_info_data&&) = delete;

		// members
		const char* undecoratedName;			 // 00
		std::array<const char, 1> decoratedName; // 08
	};
	static_assert(sizeof(type_info_data) == 0x10);
}

namespace msvc
{
	class __declspec(novtable) type_info
	{
	public:
		inline static constexpr auto RTTI{ RE::RTTI::type_info };
		inline static constexpr auto VTABLE{ RE::VTABLE::type_info };

		virtual ~type_info() noexcept = default; // 00

		[[nodiscard]] const char* name() const
		{
			if (F4SE::IsRuntimeAtLeastNG()) {
				using FuncType = const char* (*)(detail::type_info_data*, detail::type_info_node*);
				static const auto FUNC = REL::Relocation<FuncType*>{ RE::ID::msvc::type_info::name };
				return std::invoke(*FUNC, std::addressof(_data), std::addressof(get_root_node()));
			}

			using FuncType = const char* (*)(const type_info*, detail::type_info_node*);
			static const auto FUNC = REL::Relocation<FuncType*>{ RE::ID::msvc::type_info::name };
			return std::invoke(*FUNC, this, std::addressof(get_root_node()));
		}

		[[nodiscard]] const char* raw_name() const noexcept { return _data.decoratedName.data(); }

		[[nodiscard]] bool operator==(const type_info& a_rhs) const noexcept { return equal(a_rhs); }
		[[nodiscard]] bool operator!=(const type_info& a_rhs) const noexcept { return !equal(a_rhs); }

	private:
		[[nodiscard]] bool equal(const type_info& a_rhs) const noexcept
		{
			if (F4SE::IsRuntimeAtLeastNG()) {
				using FuncType = std::int32_t (*)(detail::type_info_data*, detail::type_info_data*) noexcept;
				static const auto FUNC = REL::Relocation<FuncType*>{ RE::ID::msvc::type_info::compare };
				return std::invoke(*FUNC, std::addressof(_data), std::addressof(a_rhs._data)) == 0;
			}

			using FuncType = bool (*)(const type_info*, const type_info&) noexcept;
			static const auto FUNC = REL::Relocation<FuncType*>{ RE::ID::msvc::type_info::equal };
			return std::invoke(*FUNC, this, a_rhs);
		}

		[[nodiscard]] static detail::type_info_node& get_root_node() noexcept
		{
			static const auto ROOT_NODE = REL::Relocation<detail::type_info_node*>{ RE::ID::msvc::type_info::root_node };
			return *ROOT_NODE;
		}

		// members
		mutable detail::type_info_data _data; // 00
	};
	static_assert(sizeof(msvc::type_info) == 0x18);
}
