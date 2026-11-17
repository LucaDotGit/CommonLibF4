#include "RE/A/ActorValueInfo.hpp"

namespace RE
{
	auto ActorValueInfo::GetRuntimeData01() noexcept -> ActorValueInfo::RuntimeData01&
	{
		return REL::GetMemberAt<RuntimeData01>(Offset::ActorValueInfo::RuntimeData01, this);
	}

	auto ActorValueInfo::GetRuntimeData01() const noexcept -> const ActorValueInfo::RuntimeData01&
	{
		return REL::GetMemberAt<RuntimeData01>(Offset::ActorValueInfo::RuntimeData01, this);
	}

	auto ActorValueInfo::GetRuntimeData02() noexcept -> ActorValueInfo::RuntimeData02&
	{
		return REL::GetMemberAt<RuntimeData02>(Offset::ActorValueInfo::RuntimeData02, this);
	}

	auto ActorValueInfo::GetRuntimeData02() const noexcept -> const ActorValueInfo::RuntimeData02&
	{
		return REL::GetMemberAt<RuntimeData02>(Offset::ActorValueInfo::RuntimeData02, this);
	}

	auto ActorValueInfo::GetModifiedCallback() noexcept -> std::variant<
		std::reference_wrapper<msvc::function<ModifiedCallbackType>>,
		std::reference_wrapper<msvc::function_old<ModifiedCallbackType>>>
	{
#if ((COMMONLIB_RUNTIME_NG == 0 && COMMONLIB_RUNTIME_AE == 0) || \
	 (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0))
		return modifiedCallback;
#else
		if (F4SE::IsRuntimeAtLeastNG()) {
			return REL::GetMemberAt<msvc::function<ModifiedCallbackType>>(
				Offset::ActorValueInfo::ModifiedCallback,
				this);
		}

		return REL::GetMemberAt<msvc::function_old<ModifiedCallbackType>>(
			Offset::ActorValueInfo::ModifiedCallback,
			this);
#endif
	}

	auto ActorValueInfo::GetModifiedCallback() const noexcept -> std::variant<
		std::reference_wrapper<const msvc::function<ModifiedCallbackType>>,
		std::reference_wrapper<const msvc::function_old<ModifiedCallbackType>>>
	{
#if ((COMMONLIB_RUNTIME_NG == 0 && COMMONLIB_RUNTIME_AE == 0) || \
	 (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0))
		return modifiedCallback;
#else
		if (F4SE::IsRuntimeAtLeastNG()) {
			return REL::GetMemberAt<msvc::function<ModifiedCallbackType>>(
				Offset::ActorValueInfo::ModifiedCallback,
				this);
		}

		return REL::GetMemberAt<msvc::function_old<ModifiedCallbackType>>(
			Offset::ActorValueInfo::ModifiedCallback,
			this);
#endif
	}

	auto ActorValueInfo::GetDerivationFunction() noexcept -> std::variant<
		std::reference_wrapper<msvc::function<DerivationFunctionType>>,
		std::reference_wrapper<msvc::function_old<DerivationFunctionType>>>
	{
#if ((COMMONLIB_RUNTIME_NG == 0 && COMMONLIB_RUNTIME_AE == 0) || \
	 (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0))
		return derivationFunction;
#else
		if (F4SE::IsRuntimeAtLeastNG()) {
			return REL::GetMemberAt<msvc::function<DerivationFunctionType>>(
				Offset::ActorValueInfo::DerivationFunction,
				this);
		}

		return REL::GetMemberAt<msvc::function_old<DerivationFunctionType>>(
			Offset::ActorValueInfo::DerivationFunction,
			this);
#endif
	}

	auto ActorValueInfo::GetDerivationFunction() const noexcept -> std::variant<
		std::reference_wrapper<const msvc::function<DerivationFunctionType>>,
		std::reference_wrapper<const msvc::function_old<DerivationFunctionType>>>
	{
#if ((COMMONLIB_RUNTIME_NG == 0 && COMMONLIB_RUNTIME_AE == 0) || \
	 (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0))
		return derivationFunction;
#else
		if (F4SE::IsRuntimeAtLeastNG()) {
			return REL::GetMemberAt<msvc::function<DerivationFunctionType>>(
				Offset::ActorValueInfo::DerivationFunction,
				this);
		}

		return REL::GetMemberAt<msvc::function_old<DerivationFunctionType>>(
			Offset::ActorValueInfo::DerivationFunction,
			this);
#endif
	}
}
