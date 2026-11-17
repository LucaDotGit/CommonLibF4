#include "F4SE/QueryInterface.hpp"

#include "F4SE/Core.hpp"
#include "F4SE/Runtimes.hpp"
#include "REX/Macros.hpp"
#include "REX/Ownership.hpp"

namespace F4SE::Impl
{
	namespace
	{
		class F4SEInterface final
		{
		public:
			F4SEInterface() = delete;
			~F4SEInterface() = delete;

			F4SEInterface(const F4SEInterface&) = delete;
			F4SEInterface(F4SEInterface&&) = delete;

			auto operator=(const F4SEInterface&) -> F4SEInterface& = delete;
			auto operator=(F4SEInterface&&) -> F4SEInterface& = delete;

			std::uint32_t f4seVersion;
			std::uint32_t runtimeVersion;
			std::uint32_t editorVersion;
			std::uint32_t isEditor;
			void*(F4SE_API* queryInterface)(std::uint32_t);
			F4SE::PluginHandle(F4SE_API* getPluginHandle)();
			std::uint32_t(F4SE_API* getReleaseIndex)();
			const F4SE::PluginInfo*(F4SE_API* getPluginInfo)(const char*);
			const char*(F4SE_API* getSaveFolderName)(); // since F4SE v0.7.1
		};

		[[nodiscard]] [[REX_ALWAYS_INLINE]]
		auto GetProxy(const QueryInterface& a_interface) noexcept -> const F4SEInterface&
		{
			return reinterpret_cast<const F4SEInterface&>(a_interface);
		}
	}
}

namespace F4SE
{
	auto QueryInterface::GetXseVersion() const noexcept -> REX::Version
	{
		return REX::Version::Unpack(Impl::GetProxy(*this).f4seVersion);
	}

	auto QueryInterface::GetRuntimeVersion() const noexcept -> REX::Version
	{
		return REX::Version::Unpack(Impl::GetProxy(*this).runtimeVersion);
	}

	auto QueryInterface::GetEditorVersion() const noexcept -> REX::Version
	{
		return REX::Version::Unpack(Impl::GetProxy(*this).editorVersion);
	}

	auto QueryInterface::IsEditor() const noexcept -> bool
	{
		return Impl::GetProxy(*this).isEditor != 0;
	}

	auto QueryInterface::Query(InterfaceID a_id) const -> REX::Observer<void*>
	{
		return Impl::GetProxy(*this).queryInterface(std::to_underlying(a_id));
	}

	auto QueryInterface::GetPluginHandle() const -> F4SE::PluginHandle
	{
		return Impl::GetProxy(*this).getPluginHandle();
	}

	auto QueryInterface::GetReleaseIndex() const -> std::uint32_t
	{
		return Impl::GetProxy(*this).getReleaseIndex();
	}

	auto QueryInterface::GetPluginInfo(const char* a_name) const -> REX::Observer<const PluginInfo*>
	{
		return std::invoke(GetPluginInfoFunctor(), a_name);
	}

	auto QueryInterface::GetPluginInfoFunctor() const -> PluginInfoFunctor
	{
		return Impl::GetProxy(*this).getPluginInfo;
	}

	auto QueryInterface::GetSaveFolderName() const -> std::string_view
	{
		if (F4SE::IsRuntimeAtLeastNG()) {
			return Impl::GetProxy(*this).getSaveFolderName();
		}

		if (F4SE::IsRuntimeOnlyVR()) {
			return "Fallout4VR"sv;
		}

		return "Fallout4"sv;
	}
}
