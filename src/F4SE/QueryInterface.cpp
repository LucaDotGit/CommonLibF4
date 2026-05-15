#include "F4SE/QueryInterface.hpp"

namespace F4SE::Impl
{
	struct F4SEInterface final
	{
		std::uint32_t f4seVersion;
		std::uint32_t runtimeVersion;
		std::uint32_t editorVersion;
		std::uint32_t isEditor;
		void*(F4SE_API* QueryInterface)(std::uint32_t);
		PluginHandle(F4SE_API* GetPluginHandle)();
		std::uint32_t(F4SE_API* GetReleaseIndex)();
		const void*(F4SE_API* GetPluginInfo)(const char*);
		const char*(F4SE_API* GetSaveFolderName)(); // since F4SE v0.7.1
	};

	[[nodiscard]] __forceinline static const F4SEInterface& GetProxy(const QueryInterface* a_interface) noexcept
	{
		return reinterpret_cast<const F4SEInterface&>(*a_interface);
	}
}

namespace F4SE
{
	REX::Version QueryInterface::GetF4SEVersion() const noexcept
	{
		return REX::Version::Unpack(Impl::GetProxy(this).f4seVersion);
	}

	REX::Version QueryInterface::GetRuntimeVersion() const noexcept
	{
		return REX::Version::Unpack(Impl::GetProxy(this).runtimeVersion);
	}

	REX::Version QueryInterface::GetEditorVersion() const noexcept
	{
		return REX::Version::Unpack(Impl::GetProxy(this).editorVersion);
	}

	bool QueryInterface::IsEditor() const noexcept
	{
		return Impl::GetProxy(this).isEditor != 0;
	}

	REX::Observer<void*> QueryInterface::Query(InterfaceID a_id) const
	{
		return Impl::GetProxy(this).QueryInterface(std::to_underlying(a_id));
	}

	PluginHandle QueryInterface::GetPluginHandle() const
	{
		return Impl::GetProxy(this).GetPluginHandle();
	}

	std::uint32_t QueryInterface::GetReleaseIndex() const
	{
		return Impl::GetProxy(this).GetReleaseIndex();
	}

	REX::Observer<const PluginInfo*> QueryInterface::GetPluginInfo(const char* a_name) const
	{
		return std::invoke(GetPluginInfoAccessor(), a_name);
	}

	QueryInterface::PluginInfoAccessor QueryInterface::GetPluginInfoAccessor() const
	{
		return reinterpret_cast<PluginInfoAccessor>(Impl::GetProxy(this).GetPluginInfo);
	}

	std::string_view QueryInterface::GetSaveFolderName() const
	{
		if (F4SE::IsRuntimeAtLeastNG()) {
			return Impl::GetProxy(this).GetSaveFolderName();
		}

		if (F4SE::IsRuntimeOnlyVR()) {
			return "Fallout4VR"sv;
		}

		return "Fallout4"sv;
	}
}
