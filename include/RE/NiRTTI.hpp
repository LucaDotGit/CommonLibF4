#pragma once

namespace RE
{
	class NiRTTI
	{
	public:
		constexpr NiRTTI() noexcept = default;
		constexpr ~NiRTTI() noexcept = default;

		constexpr NiRTTI(const char* a_name, NiRTTI* a_baseRTTI) noexcept
			: name(a_name),
			  baseRTTI(a_baseRTTI)
		{
		}

		constexpr NiRTTI(const NiRTTI&) noexcept = default;
		constexpr NiRTTI(NiRTTI&&) noexcept = default;

		constexpr NiRTTI& operator=(const NiRTTI&) noexcept = default;
		constexpr NiRTTI& operator=(NiRTTI&&) noexcept = default;

		[[nodiscard]] constexpr const char* GetName() const noexcept { return name; }
		[[nodiscard]] constexpr const NiRTTI* GetBaseRTTI() const noexcept { return baseRTTI; }

		[[nodiscard]] constexpr bool IsKindOf(const NiRTTI* a_rtti) const noexcept
		{
			for (const auto* it = this; it; it = it->GetBaseRTTI()) {
				if (it == a_rtti) {
					return true;
				}
			}

			return false;
		}

		// members
		const char* name; // 00
		NiRTTI* baseRTTI; // 08
	};
	static_assert(sizeof(NiRTTI) == 0x10);
}

namespace RE::NiImpl
{
	template <class From, class To>
	concept compatible_type =
		(std::is_lvalue_reference_v<std::remove_cv_t<From>> &&
			std::is_reference_v<To>) ||
		(std::is_pointer_v<std::remove_cv_t<From>> &&
			std::is_pointer_v<To>);

	template <class Base, class Derived>
	concept derived_from_no_cvpr =
		std::derived_from<REX::remove_cvpr_t<Derived>, REX::remove_cvpr_t<Base>>;

	template <class T>
	concept has_rtti =
		std::derived_from<decltype(REX::remove_cvpr_t<T>::NI_RTTI), REL::IId>;

	template <class From, class To>
	concept valid_cast =
		compatible_type<From, To> &&
		derived_from_no_cvpr<From, To> &&
		has_rtti<From> &&
		has_rtti<To>;
}

namespace RE
{
	// downcast
	template <class To, class From>
	[[nodiscard]] To NiDynamicCast(const From* a_from)
		requires(NiImpl::valid_cast<const From*, To>)
	{
		if (!a_from) {
			return nullptr;
		}

		static const auto TO_RTTI = REL::Relocation<const NiRTTI*>{ REX::remove_cvpr_t<To>::NI_RTTI };

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

	// upcast
	template <class To, class From>
	[[nodiscard]] To NiDynamicCast(const From* a_from)
		requires(NiImpl::valid_cast<To, const From*>)
	{
		return static_cast<To>(const_cast<From*>(a_from));
	}
}
