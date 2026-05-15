#include "F4SE/SerializationInterface.hpp"

#include "F4SE/API.hpp"

#include "REX/Message.hpp"

namespace F4SE::Impl
{
	struct F4SESerializationInterface final
	{
		std::uint32_t interfaceVersion;
		void(F4SE_API* SetUniqueID)(std::uint32_t, std::uint32_t);
		void(F4SE_API* SetRevertCallback)(std::uint32_t, void*);
		void(F4SE_API* SetSaveCallback)(std::uint32_t, void*);
		void(F4SE_API* SetLoadCallback)(std::uint32_t, void*);
		void(F4SE_API* SetFormDeleteCallback)(std::uint32_t, void*);
		bool(F4SE_API* WriteRecord)(std::uint32_t, std::uint32_t, const void*, std::uint32_t);
		bool(F4SE_API* OpenRecord)(std::uint32_t, std::uint32_t);
		bool(F4SE_API* WriteRecordData)(const void*, std::uint32_t);
		bool(F4SE_API* GetNextRecordInfo)(std::uint32_t*, std::uint32_t*, std::uint32_t*);
		std::uint32_t(F4SE_API* ReadRecordData)(void*, std::uint32_t);
		bool(F4SE_API* ResolveHandle)(RE::BSScript::ObjectHandle, RE::BSScript::ObjectHandle*);
		bool(F4SE_API* ResolveFormID)(RE::TESFormID, RE::TESFormID*);
	};

	[[nodiscard]] __forceinline static const F4SESerializationInterface& GetProxy(const SerializationInterface* a_interface) noexcept
	{
		return reinterpret_cast<const F4SESerializationInterface&>(*a_interface);
	}
}

namespace F4SE
{
	std::uint32_t SerializationInterface::GetVersion() const noexcept
	{
		return Impl::GetProxy(this).interfaceVersion;
	}

	void SerializationInterface::SetUniqueID(std::uint32_t a_id) const
	{
		Impl::GetProxy(this).SetUniqueID(F4SE::GetPluginHandle(), a_id);
	}

	void SerializationInterface::SetRevertCallback(REX::NotNull<REX::Observer<EventCallback*>> a_callback) const
	{
		Impl::GetProxy(this).SetRevertCallback(F4SE::GetPluginHandle(), reinterpret_cast<void*>(a_callback.get()));
	}

	void SerializationInterface::SetSaveCallback(REX::NotNull<REX::Observer<EventCallback*>> a_callback) const
	{
		Impl::GetProxy(this).SetSaveCallback(F4SE::GetPluginHandle(), reinterpret_cast<void*>(a_callback.get()));
	}

	void SerializationInterface::SetLoadCallback(REX::NotNull<REX::Observer<EventCallback*>> a_callback) const
	{
		Impl::GetProxy(this).SetLoadCallback(F4SE::GetPluginHandle(), reinterpret_cast<void*>(a_callback.get()));
	}

	void SerializationInterface::SetFormDeleteCallback(REX::NotNull<REX::Observer<FormDeleteCallback*>> a_callback) const
	{
		Impl::GetProxy(this).SetFormDeleteCallback(F4SE::GetPluginHandle(), reinterpret_cast<void*>(a_callback.get()));
	}

	bool SerializationInterface::WriteRecord(std::uint32_t a_type, std::uint32_t a_version, const std::byte* a_data, std::uint32_t a_size) const
	{
		const auto result = Impl::GetProxy(this).WriteRecord(a_type, a_version, a_data, a_size);
		if (!result) [[unlikely]] {
			REX::Fail("Failed to write full record of type {} and version {}."sv,
				a_type, a_version);
		}

		return result;
	}

	bool SerializationInterface::OpenRecord(std::uint32_t a_type, std::uint32_t a_version) const
	{
		const auto result = Impl::GetProxy(this).OpenRecord(a_type, a_version);
		if (!result) [[unlikely]] {
			REX::Fail("Failed to open record of type {} and version {}."sv,
				a_type, a_version);
		}

		return result;
	}

	bool SerializationInterface::WriteRecordData(const std::byte* a_value, std::uint32_t a_size) const
	{
		const auto result = Impl::GetProxy(this).WriteRecordData(a_value, a_size);
		if (!result) [[unlikely]] {
			REX::Fail("Failed to write record data of size {}."sv,
				a_size);
		}

		return result;
	}

	bool SerializationInterface::GetNextRecordInfo(std::uint32_t& a_type, std::uint32_t& a_version, std::uint32_t& a_size) const
	{
		return Impl::GetProxy(this).GetNextRecordInfo(std::addressof(a_type), std::addressof(a_version), std::addressof(a_size));
	}

	std::uint32_t SerializationInterface::ReadRecordData(std::byte* a_buffer, std::uint32_t a_size) const
	{
		const auto result = Impl::GetProxy(this).ReadRecordData(a_buffer, a_size);
		if (result != a_size) [[unlikely]] {
			REX::Fail("Failed to read record data of size {}."sv,
				a_size);
		}

		return result;
	}

	auto SerializationInterface::ResolveHandle(RE::BSScript::ObjectHandle a_objectHandle) const
		-> std::optional<RE::BSScript::ObjectHandle>
	{
		auto result = static_cast<RE::BSScript::ObjectHandle>(0);
		if (!Impl::GetProxy(this).ResolveHandle(a_objectHandle, std::addressof(result))) {
			return std::nullopt;
		}

		return result;
	}

	auto SerializationInterface::ResolveFormID(RE::TESFormID a_formID) const
		-> std::optional<RE::TESFormID>
	{
		auto result = static_cast<RE::TESFormID>(0);
		if (!Impl::GetProxy(this).ResolveFormID(a_formID, std::addressof(result))) {
			return std::nullopt;
		}

		return result;
	}
}
