#include "F4SE/Runtimes.hpp"

#include "F4SE/Api.hpp"
#include "F4SE/Versions.hpp"
#include "REX/Version.hpp"

namespace F4SE
{
	auto IsRuntimeAtLeastVR() noexcept -> bool
	{
		const auto runtimeVersion = F4SE::GetRuntimeVersion();
		return runtimeVersion >= F4SE::RUNTIME_LATEST_VR.GetMinVersion();
	}

	auto IsRuntimeAtLeastOG() noexcept -> bool
	{
		const auto runtimeVersion = F4SE::GetRuntimeVersion();
		return runtimeVersion >= F4SE::RUNTIME_LATEST_OG.GetMinVersion();
	}

	auto IsRuntimeAtLeastNG() noexcept -> bool
	{
		const auto runtimeVersion = F4SE::GetRuntimeVersion();
		return runtimeVersion >= F4SE::RUNTIME_LATEST_NG.GetMinVersion();
	}

	auto IsRuntimeAtLeastAE() noexcept -> bool
	{
		const auto runtimeVersion = F4SE::GetRuntimeVersion();
		return runtimeVersion >= F4SE::RUNTIME_LATEST_AE.GetMinVersion();
	}

	auto IsRuntimeOnlyVR() noexcept -> bool
	{
		const auto runtimeVersion = F4SE::GetRuntimeVersion();
		return runtimeVersion == F4SE::RUNTIME_LATEST_VR.GetMinVersion();
	}

	auto IsRuntimeOnlyOG() noexcept -> bool
	{
		const auto runtimeVersion = F4SE::GetRuntimeVersion();
		return runtimeVersion == F4SE::RUNTIME_LATEST_OG.GetMinVersion();
	}

	auto IsRuntimeOnlyNG() noexcept -> bool
	{
		const auto runtimeVersion = F4SE::GetRuntimeVersion();
		return runtimeVersion == F4SE::RUNTIME_LATEST_NG.GetMinVersion();
	}

	auto IsRuntimeOnlyAE() noexcept -> bool
	{
		const auto runtimeVersion = F4SE::GetRuntimeVersion();
		return runtimeVersion >= F4SE::RUNTIME_LATEST_AE.GetMinVersion();
	}
}
