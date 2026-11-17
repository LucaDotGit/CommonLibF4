#pragma once

#include "F4SE/Core.hpp"
#include "F4SE/QueryInterface.hpp"
#include "RE/CoreTypes.hpp"
#include "REX/Concepts.hpp"
#include "REX/NotNull.hpp"
#include "REX/Ownership.hpp"

namespace F4SE
{
	class SerializationInterface final
	{
	public:
		using value_type = std::byte;
		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;

		inline static constexpr auto INTERFACE_ID = QueryInterface::InterfaceID::Serialization;
		inline static constexpr auto INTERFACE_VERSION = static_cast<std::uint32_t>(1);

		SerializationInterface() = delete;
		~SerializationInterface() = delete;

		SerializationInterface(const SerializationInterface&) = delete;
		SerializationInterface(SerializationInterface&&) = delete;

		auto operator=(const SerializationInterface&) -> SerializationInterface& = delete;
		auto operator=(SerializationInterface&&) -> SerializationInterface& = delete;

		using EventCallback = void F4SE_API(const SerializationInterface* a_interface);
		using FormDeleteCallback = void F4SE_API(RE::BSScript::ObjectHandle a_objectHandle);

		[[nodiscard]]
		auto GetVersion() const noexcept -> F4SE::InterfaceVersion;

		void SetUniqueID(std::uint32_t a_id) const;
		void SetRevertCallback(REX::NotNull<REX::Observer<EventCallback*>> a_callback) const;
		void SetSaveCallback(REX::NotNull<REX::Observer<EventCallback*>> a_callback) const;
		void SetLoadCallback(REX::NotNull<REX::Observer<EventCallback*>> a_callback) const;
		void SetFormDeleteCallback(REX::NotNull<REX::Observer<FormDeleteCallback*>> a_callback)
			const; // the callback never gets invoked by F4SE
		auto WriteRecord(std::uint32_t a_type, std::uint32_t a_version, const_pointer a_data, size_type a_size) const
			-> bool;
		auto OpenRecord(std::uint32_t a_type, std::uint32_t a_version) const -> bool;
		auto WriteRecordData(const_pointer a_data, size_type a_size) const -> bool;
		auto GetNextRecordInfo(std::uint32_t& a_type, std::uint32_t& a_version, size_type& a_size) const -> bool;
		auto ReadRecordData(pointer a_buffer, size_type a_size) const -> size_type;
		[[nodiscard]]
		auto ResolveHandle(RE::BSScript::ObjectHandle a_objectHandle) const
			-> std::optional<RE::BSScript::ObjectHandle>;
		[[nodiscard]]
		auto ResolveFormID(RE::TESFormID a_formID) const -> std::optional<RE::TESFormID>;

		[[nodiscard]]
		auto ReadRecord(std::uint32_t a_type, std::uint32_t a_version) const -> std::optional<std::vector<value_type>>;

		template <REX::trivially_readable T>
		auto WriteRecord(std::uint32_t a_type, std::uint32_t a_version, const T* a_data, size_type a_size) const -> bool
		{
			return WriteRecord(a_type, a_version, reinterpret_cast<const_pointer>(a_data), a_size * sizeof(T));
		}

		template <REX::trivially_readable T, std::size_t N>
		auto WriteRecord(std::uint32_t a_type, std::uint32_t a_version, std::span<const T, N> a_span) const -> bool
		{
			return WriteRecord(
				a_type,
				a_version,
				reinterpret_cast<const_pointer>(a_span.data()),
				static_cast<size_type>(a_span.size_bytes()));
		}

		template <REX::trivially_readable T>
		auto WriteRecord(std::uint32_t a_type, std::uint32_t a_version, const T& a_value) const -> bool
		{
			return WriteRecord(a_type, a_version, reinterpret_cast<const_pointer>(std::addressof(a_value)), sizeof(T));
		}

		template <REX::trivially_writable T>
		auto ReadRecordData(T* a_buffer, size_type a_size) const -> size_type
		{
			return ReadRecordData(reinterpret_cast<pointer>(a_buffer), a_size * sizeof(T));
		}

		template <REX::trivially_writable T, std::size_t N>
		auto ReadRecordData(std::span<T, N> a_buffer) const -> size_type
		{
			return ReadRecordData(
				reinterpret_cast<pointer>(a_buffer.data()),
				static_cast<size_type>(a_buffer.size_bytes()));
		}

		template <REX::trivially_writable T>
		auto ReadRecordData(T& a_outValue) const -> size_type
		{
			return ReadRecordData(reinterpret_cast<pointer>(std::addressof(a_outValue)), sizeof(T));
		}

		template <REX::trivially_writable T>
		[[nodiscard]]
		auto ReadRecordData() const -> std::expected<T, size_type>
		{
			auto result = T();

			const auto readSize = ReadRecordData(reinterpret_cast<pointer>(std::addressof(result)), sizeof(T));
			if (readSize != sizeof(T)) [[unlikely]] {
				return std::unexpected(readSize);
			}

			return result;
		}

		template <REX::trivially_readable T>
		auto WriteRecordData(const T* a_data, size_type a_size) const -> bool
		{
			return WriteRecordData(reinterpret_cast<const_pointer>(a_data), a_size * sizeof(T));
		}

		template <REX::trivially_readable T, std::size_t N>
		auto WriteRecordData(std::span<const T, N> a_span) const -> bool
		{
			return WriteRecordData(
				reinterpret_cast<const_pointer>(a_span.data()),
				static_cast<size_type>(a_span.size_bytes()));
		}

		template <REX::trivially_readable T>
		auto WriteRecordData(const T& a_value) const -> bool
		{
			return WriteRecordData(reinterpret_cast<const_pointer>(std::addressof(a_value)), sizeof(T));
		}
	};

	static_assert(std::is_empty_v<SerializationInterface>);
}
