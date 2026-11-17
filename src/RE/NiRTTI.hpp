#pragma once

namespace RE
{
	class NiRTTI final
	{
	public:
		constexpr NiRTTI() noexcept = default;
		constexpr ~NiRTTI() noexcept = default;

		constexpr NiRTTI(const char* a_name, NiRTTI* a_baseRTTI) noexcept :
			name(a_name),
			baseRTTI(a_baseRTTI)
		{
		}

		constexpr NiRTTI(const NiRTTI&) noexcept = default;
		constexpr NiRTTI(NiRTTI&&) noexcept = default;

		constexpr auto operator=(const NiRTTI&) noexcept -> NiRTTI& = default;
		constexpr auto operator=(NiRTTI&&) noexcept -> NiRTTI& = default;

		[[nodiscard]]
		constexpr auto GetName() const noexcept -> const char*
		{
			return name;
		}

		[[nodiscard]]
		constexpr auto GetBaseRTTI() const noexcept -> const NiRTTI*
		{
			return baseRTTI;
		}

		[[nodiscard]]
		constexpr auto IsKindOf(const NiRTTI* a_rtti) const noexcept -> bool
		{
			if (!a_rtti) {
				return false;
			}

			for (const auto* rttiIt = this; rttiIt; rttiIt = rttiIt->GetBaseRTTI()) {
				if (rttiIt == a_rtti) {
					return true;
				}
			}

			return false;
		}

		// members
		const char* name; // 0x00
		NiRTTI* baseRTTI; // 0x08
	};

	static_assert(sizeof(NiRTTI) == 0x10);
}

namespace RE::NiImpl
{
	template <class From, class To>
	concept compatible_type = (std::is_lvalue_reference_v<std::remove_cv_t<From>> && REX::reference<To>) ||
							  (REX::pointer<std::remove_cv_t<From>> && REX::pointer<To>);

	template <class Base, class Derived>
	concept derived_from_no_cvpr = std::derived_from<REX::remove_cvpr_t<Derived>, REX::remove_cvpr_t<Base>>;

	template <class T>
	concept has_rtti = std::derived_from<std::remove_reference_t<decltype(REX::remove_cvpr_t<T>::NI_RTTI)>, REL::IId>;

	template <class From, class To>
	concept valid_cast = compatible_type<From, To> && derived_from_no_cvpr<From, To> && has_rtti<From> && has_rtti<To>;
}

namespace RE
{
	// down-cast
	template <class To, class From>
	[[nodiscard]]
	auto NiDynamicCast(const From* a_from) -> To
		requires(NiImpl::valid_cast<const From*, To>)
	{
		if (!a_from) {
			return nullptr;
		}

		static const auto TO_RTTI = REL::Relocation<const NiRTTI*>(REX::remove_cvpr_t<To>::NI_RTTI);

		const auto* fromRTTI = a_from->GetRTTI();
		const auto* toRTTI = TO_RTTI.get();

		while (fromRTTI) {
			if (fromRTTI == toRTTI) {
				return static_cast<To>(const_cast<From*>(a_from));
			}

			fromRTTI = fromRTTI->GetBaseRTTI();
		}

		return nullptr;
	}

	// up-cast
	template <class To, class From>
	[[nodiscard]]
	auto NiDynamicCast(const From* a_from) -> To
		requires(NiImpl::valid_cast<To, const From*>)
	{
		return static_cast<To>(const_cast<From*>(a_from));
	}
}
