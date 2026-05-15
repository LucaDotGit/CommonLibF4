#include "F4SE/Runtimes.hpp"

#include "REL/Module.hpp"

#include "REX/Enum.hpp"
#include "REX/Message.hpp"

namespace F4SE::Impl
{
	class RuntimeInfo final
		: public REX::Singleton<RuntimeInfo>
	{
	public:
		RuntimeInfo() = default;
		~RuntimeInfo() noexcept = default;

		RuntimeInfo(const RuntimeInfo&) = delete;
		RuntimeInfo(RuntimeInfo&&) = delete;

		RuntimeInfo& operator=(const RuntimeInfo&) = delete;
		RuntimeInfo& operator=(RuntimeInfo&&) = delete;

		REX::Enum<RuntimeType> runtimeType;
	};

	void InitRuntime(REX::Version a_runtimeVersion)
	{
		static_assert(RuntimeType::kAE > RuntimeType::kNG);
		static_assert(RuntimeType::kNG > RuntimeType::kOG);
		static_assert(RuntimeType::kOG > RuntimeType::kVR);

		static_assert(F4SE::RUNTIME_LATEST_AE > F4SE::RUNTIME_LATEST_NG);
		static_assert(F4SE::RUNTIME_LATEST_NG > F4SE::RUNTIME_LATEST_OG);
		static_assert(F4SE::RUNTIME_LATEST_OG > F4SE::RUNTIME_LATEST_VR);

		auto runtimeType = REX::Enum(RuntimeType::kNone);
		auto runtime = REL::Runtime::INVALID;

#if COMMONLIB_RUNTIME_AE == 1 || (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0)
		if (runtimeType == RuntimeType::kNone && a_runtimeVersion >= F4SE::RUNTIME_LATEST_AE) {
			runtimeType = RuntimeType::kAE;
			runtime = REL::CreateRuntime(a_runtimeVersion);
		}
#endif

#if COMMONLIB_RUNTIME_NG == 1
		if (runtimeType == RuntimeType::kNone && a_runtimeVersion >= F4SE::RUNTIME_LATEST_NG) {
			runtimeType = RuntimeType::kNG;
			runtime = REL::CreateRuntime(a_runtimeVersion);
		}
#endif

#if COMMONLIB_RUNTIME_OG == 1
		if (runtimeType == RuntimeType::kNone && a_runtimeVersion >= F4SE::RUNTIME_LATEST_OG) {
			runtimeType = RuntimeType::kOG;
			runtime = REL::CreateRuntime(a_runtimeVersion);
		}
#endif

#if COMMONLIB_RUNTIME_VR == 1
		if (runtimeType == RuntimeType::kNone && a_runtimeVersion >= F4SE::RUNTIME_LATEST_VR) {
			runtimeType = RuntimeType::kVR;
			runtime = REL::CreateVRRuntime(a_runtimeVersion);
		}
#endif

		if (runtimeType == RuntimeType::kNone) [[unlikely]] {
			REX::Fail(
				"Failed to initialize runtime due to unsupported version.\n"
				"Runtime Version: {}"sv,
				a_runtimeVersion);
		}

		const auto& runtimeInfo = RuntimeInfo::GetSingleton();
		runtimeInfo->runtimeType = runtimeType;

		const auto& module = REL::Module::GetSingleton();
		module->SetRuntime(runtime);
	}
}

namespace F4SE
{
	RuntimeType GetRuntimeType() noexcept
	{
		return Impl::RuntimeInfo::GetSingleton()->runtimeType.get();
	}

	bool IsRuntimeAtLeastVR() noexcept
	{
		const auto runtimeType = Impl::RuntimeInfo::GetSingleton()->runtimeType;
		REX::Assert(runtimeType != RuntimeType::kNone);
		return runtimeType.any(RuntimeType::kVR, RuntimeType::kOG, RuntimeType::kNG, RuntimeType::kAE);
	}

	bool IsRuntimeAtLeastOG() noexcept
	{
		const auto runtimeType = Impl::RuntimeInfo::GetSingleton()->runtimeType;
		REX::Assert(runtimeType != RuntimeType::kNone);
		return runtimeType.any(RuntimeType::kOG, RuntimeType::kNG, RuntimeType::kAE);
	}

	bool IsRuntimeAtLeastNG() noexcept
	{
		const auto runtimeType = Impl::RuntimeInfo::GetSingleton()->runtimeType;
		REX::Assert(runtimeType != RuntimeType::kNone);
		return runtimeType.any(RuntimeType::kNG, RuntimeType::kAE);
	}

	bool IsRuntimeAtLeastAE() noexcept
	{
		const auto runtimeType = Impl::RuntimeInfo::GetSingleton()->runtimeType;
		REX::Assert(runtimeType != RuntimeType::kNone);
		return runtimeType.any(RuntimeType::kAE);
	}

	bool IsRuntimeOnlyVR() noexcept
	{
		const auto runtimeType = Impl::RuntimeInfo::GetSingleton()->runtimeType;
		REX::Assert(runtimeType != RuntimeType::kNone);
		return runtimeType == RuntimeType::kVR;
	}

	bool IsRuntimeOnlyOG() noexcept
	{
		const auto runtimeType = Impl::RuntimeInfo::GetSingleton()->runtimeType;
		REX::Assert(runtimeType != RuntimeType::kNone);
		return runtimeType == RuntimeType::kOG;
	}

	bool IsRuntimeOnlyNG() noexcept
	{
		const auto runtimeType = Impl::RuntimeInfo::GetSingleton()->runtimeType;
		REX::Assert(runtimeType != RuntimeType::kNone);
		return runtimeType == RuntimeType::kNG;
	}

	bool IsRuntimeOnlyAE() noexcept
	{
		const auto runtimeType = Impl::RuntimeInfo::GetSingleton()->runtimeType;
		REX::Assert(runtimeType != RuntimeType::kNone);
		return runtimeType == RuntimeType::kAE;
	}
}
