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
		type_info_data() = delete;
		~type_info_data() noexcept = default;

		type_info_data(const type_info_data&) = delete;
		type_info_data(type_info_data&&) = delete;

		auto operator=(const type_info_data&) -> type_info_data& = delete;
		auto operator=(type_info_data&&) -> type_info_data& = delete;

		// members
		const char* undecoratedName;			 // 0x00
		std::array<const char, 1> decoratedName; // 0x08
	};

	static_assert(sizeof(type_info_data) == 0x10);
}

namespace msvc
{
	class __declspec(novtable) type_info
	{
	public:
		inline static constexpr const auto& RTTI = RE::RTTI::type_info;
		inline static constexpr const auto& VTABLE = RE::VTABLE::type_info;

		virtual ~type_info() noexcept = default; // 0x00

		[[nodiscard]]
		auto name() const noexcept -> const char*
		{
			if (F4SE::IsRuntimeAtLeastNG()) {
				using FuncType =
					std::add_pointer_t<const char* (*)(detail::type_info_data*, detail::type_info_node*) noexcept>;
				static const auto FUNC = REL::Relocation<FuncType>(RE::ID::msvc::type_info::name);
				return std::invoke(*FUNC, std::addressof(_data), std::addressof(get_root_node()));
			}

			using FuncType = std::add_pointer_t<const char* (type_info::*)(detail::type_info_node*) const noexcept>;
			static const auto FUNC = REL::Relocation<FuncType>(RE::ID::msvc::type_info::name);
			return std::invoke(*FUNC, this, std::addressof(get_root_node()));
		}

		[[nodiscard]]
		auto raw_name() const noexcept -> const char*
		{
			return _data.decoratedName.data();
		}

		[[nodiscard]]
		constexpr auto operator==(const type_info& a_rhs) const noexcept -> bool
		{
			return equal(a_rhs);
		}

	private:
		[[nodiscard]]
		constexpr auto equal(const type_info& a_rhs) const noexcept -> bool
		{
			if (std::is_constant_evaluated()) [[unlikely]] {
				return std::addressof(_data) == std::addressof(a_rhs._data);
			}

			if (F4SE::IsRuntimeAtLeastNG()) {
				using FuncType = std::add_pointer_t<
					std::int32_t (*)(const detail::type_info_data*, const detail::type_info_data*) noexcept>;
				static const auto FUNC = REL::Relocation<FuncType>(RE::ID::msvc::type_info::compare);
				return std::invoke(*FUNC, std::addressof(_data), std::addressof(a_rhs._data)) == 0;
			}

			using FuncType = std::add_pointer_t<bool (type_info::*)(const type_info&) const noexcept>;
			static const auto FUNC = REL::Relocation<FuncType>(RE::ID::msvc::type_info::equal);
			return std::invoke(*FUNC, this, a_rhs);
		}

		[[nodiscard]]
		static auto get_root_node() noexcept -> detail::type_info_node&
		{
			static const auto ROOT_NODE = REL::Relocation<detail::type_info_node*>(RE::ID::msvc::type_info::root_node);
			return *ROOT_NODE;
		}

		// members
		mutable detail::type_info_data _data; // 0x00
	};

	static_assert(sizeof(msvc::type_info) == 0x18);
}
