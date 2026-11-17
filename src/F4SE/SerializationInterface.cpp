#include "F4SE/SerializationInterface.hpp"

#include "F4SE/Api.hpp"
#include "F4SE/Core.hpp"
#include "RE/B/BSScript_ObjectHandle.hpp"
#include "RE/T/TESFormID.hpp"
#include "REX/Container.hpp"
#include "REX/Macros.hpp"
#include "REX/NotNull.hpp"
#include "REX/Ownership.hpp"

namespace F4SE::Impl
{
	namespace
	{
		class F4SESerializationInterface final
		{
		public:
			F4SESerializationInterface() = delete;
			~F4SESerializationInterface() = delete;

			F4SESerializationInterface(const F4SESerializationInterface&) = delete;
			F4SESerializationInterface(F4SESerializationInterface&&) = delete;

			auto operator=(const F4SESerializationInterface&) -> F4SESerializationInterface& = delete;
			auto operator=(F4SESerializationInterface&&) -> F4SESerializationInterface& = delete;

			F4SE::InterfaceVersion interfaceVersion;
			void(F4SE_API* setUniqueID)(F4SE::PluginHandle, std::uint32_t);
			void(F4SE_API* setRevertCallback)(F4SE::PluginHandle, F4SE::SerializationInterface::EventCallback*);
			void(F4SE_API* setSaveCallback)(F4SE::PluginHandle, F4SE::SerializationInterface::EventCallback*);
			void(F4SE_API* setLoadCallback)(F4SE::PluginHandle, F4SE::SerializationInterface::EventCallback*);
			void(
				F4SE_API* setFormDeleteCallback)(F4SE::PluginHandle, F4SE::SerializationInterface::FormDeleteCallback*);
			bool(F4SE_API*
					 writeRecord)(std::uint32_t, std::uint32_t, const void*, F4SE::SerializationInterface::size_type);
			bool(F4SE_API* openRecord)(std::uint32_t, std::uint32_t);
			bool(F4SE_API* writeRecordData)(const void*, F4SE::SerializationInterface::size_type);
			bool(F4SE_API* getNextRecordInfo)(std::uint32_t*, std::uint32_t*, F4SE::SerializationInterface::size_type*);
			F4SE::SerializationInterface::size_type(
				F4SE_API* readRecordData)(void*, F4SE::SerializationInterface::size_type);
			bool(F4SE_API* resolveHandle)(RE::BSScript::ObjectHandle, RE::BSScript::ObjectHandle*);
			bool(F4SE_API* resolveFormID)(RE::TESFormID, RE::TESFormID*);
		};

		[[nodiscard]] [[REX_ALWAYS_INLINE]]
		auto GetProxy(const SerializationInterface& a_interface) noexcept -> const F4SESerializationInterface&
		{
			return reinterpret_cast<const F4SESerializationInterface&>(a_interface);
		}
	}
}

namespace F4SE
{
	auto SerializationInterface::GetVersion() const noexcept -> F4SE::InterfaceVersion
	{
		return Impl::GetProxy(*this).interfaceVersion;
	}

	void SerializationInterface::SetUniqueID(std::uint32_t a_id) const
	{
		Impl::GetProxy(*this).setUniqueID(F4SE::GetPluginHandle(), a_id);
	}

	void SerializationInterface::SetRevertCallback(REX::NotNull<REX::Observer<EventCallback*>> a_callback) const
	{
		Impl::GetProxy(*this).setRevertCallback(F4SE::GetPluginHandle(), a_callback.get());
	}

	void SerializationInterface::SetSaveCallback(REX::NotNull<REX::Observer<EventCallback*>> a_callback) const
	{
		Impl::GetProxy(*this).setSaveCallback(F4SE::GetPluginHandle(), a_callback.get());
	}

	void SerializationInterface::SetLoadCallback(REX::NotNull<REX::Observer<EventCallback*>> a_callback) const
	{
		Impl::GetProxy(*this).setLoadCallback(F4SE::GetPluginHandle(), a_callback.get());
	}

	void SerializationInterface::SetFormDeleteCallback(
		REX::NotNull<REX::Observer<FormDeleteCallback*>> a_callback) const
	{
		Impl::GetProxy(*this).setFormDeleteCallback(F4SE::GetPluginHandle(), a_callback.get());
	}

	auto SerializationInterface::WriteRecord(
		std::uint32_t a_type,
		std::uint32_t a_version,
		const_pointer a_data,
		F4SE::SerializationInterface::size_type a_size) const -> bool
	{
		return Impl::GetProxy(*this).writeRecord(a_type, a_version, a_data, a_size);
	}

	auto SerializationInterface::OpenRecord(std::uint32_t a_type, std::uint32_t a_version) const -> bool
	{
		return Impl::GetProxy(*this).openRecord(a_type, a_version);
	}

	auto SerializationInterface::WriteRecordData(const_pointer a_data, F4SE::SerializationInterface::size_type a_size)
		const -> bool
	{
		return Impl::GetProxy(*this).writeRecordData(a_data, a_size);
	}

	auto SerializationInterface::GetNextRecordInfo(
		std::uint32_t& a_type,
		std::uint32_t& a_version,
		F4SE::SerializationInterface::size_type& a_size) const -> bool
	{
		return Impl::GetProxy(*this).getNextRecordInfo(
			std::addressof(a_type),
			std::addressof(a_version),
			std::addressof(a_size));
	}

	auto SerializationInterface::ReadRecordData(pointer a_buffer, F4SE::SerializationInterface::size_type a_size) const
		-> F4SE::SerializationInterface::size_type
	{
		return Impl::GetProxy(*this).readRecordData(a_buffer, a_size);
	}

	auto SerializationInterface::ResolveHandle(RE::BSScript::ObjectHandle a_objectHandle) const
		-> std::optional<RE::BSScript::ObjectHandle>
	{
		auto result = static_cast<RE::BSScript::ObjectHandle>(0);
		if (!Impl::GetProxy(*this).resolveHandle(a_objectHandle, std::addressof(result))) {
			return std::nullopt;
		}

		return result;
	}

	auto SerializationInterface::ResolveFormID(RE::TESFormID a_formID) const -> std::optional<RE::TESFormID>
	{
		auto result = static_cast<RE::TESFormID>(0);
		if (!Impl::GetProxy(*this).resolveFormID(a_formID, std::addressof(result))) {
			return std::nullopt;
		}

		return result;
	}

	auto SerializationInterface::ReadRecord(std::uint32_t a_type, std::uint32_t a_version) const
		-> std::optional<std::vector<value_type>>
	{
		auto readType = static_cast<std::uint32_t>(0);
		auto readVersion = static_cast<std::uint32_t>(0);
		auto readSize = static_cast<size_type>(0);

		if (!GetNextRecordInfo(readType, readVersion, readSize) || readType != a_type || readVersion != a_version) {
			return std::nullopt;
		}

		auto result = std::vector<value_type>();
		REX::ResizeForOverwrite(result, readSize);

		if (ReadRecordData(result.data(), readSize) != readSize) {
			return std::nullopt;
		}

		return result;
	}
}
