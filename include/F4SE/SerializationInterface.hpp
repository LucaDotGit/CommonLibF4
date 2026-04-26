#pragma once

#include "F4SE/Core.hpp"
#include "F4SE/QueryInterface.hpp"

#include "RE/CoreTypes.hpp"

#include "REX/Concepts.hpp"
#include "REX/NotNull.hpp"
#include "REX/Own.hpp"

namespace F4SE
{
	class SerializationInterface final
	{
	public:
		inline static constexpr auto INTERFACE_ID{ QueryInterface::InterfaceID::kSerialization };
		inline static constexpr auto INTERFACE_VERSION{ 1ui32 };

		SerializationInterface() = delete;
		~SerializationInterface() = delete;

		SerializationInterface(const SerializationInterface&) = delete;
		SerializationInterface(SerializationInterface&&) = delete;

		SerializationInterface& operator=(const SerializationInterface&) = delete;
		SerializationInterface& operator=(SerializationInterface&&) = delete;

		using EventCallback = void F4SE_API(const SerializationInterface* a_interface);
		using FormDeleteCallback = void F4SE_API(RE::BSScript::ObjectHandle a_objectHandle);

		[[nodiscard]] std::uint32_t GetVersion() const noexcept;

		void SetUniqueID(std::uint32_t a_id) const;
		void SetRevertCallback(REX::NotNull<REX::Observer<EventCallback*>> a_callback) const;
		void SetSaveCallback(REX::NotNull<REX::Observer<EventCallback*>> a_callback) const;
		void SetLoadCallback(REX::NotNull<REX::Observer<EventCallback*>> a_callback) const;
		void SetFormDeleteCallback(REX::NotNull<REX::Observer<FormDeleteCallback*>> a_callback) const; // the callback never gets invoked by F4SE
		bool WriteRecord(std::uint32_t a_type, std::uint32_t a_version, const std::byte* a_data, std::uint32_t a_size) const;
		bool OpenRecord(std::uint32_t a_type, std::uint32_t a_version) const;
		bool WriteRecordData(const std::byte* a_value, std::uint32_t a_size) const;
		bool GetNextRecordInfo(std::uint32_t& a_type, std::uint32_t& a_version, std::uint32_t& a_size) const;
		std::uint32_t ReadRecordData(std::byte* a_buffer, std::uint32_t a_size) const;
		[[nodiscard]] auto ResolveHandle(RE::BSScript::ObjectHandle a_objectHandle) const -> std::optional<RE::BSScript::ObjectHandle>;
		[[nodiscard]] auto ResolveFormID(RE::TESFormID a_formID) const -> std::optional<RE::TESFormID>;

		template <REX::trivially_readable T>
		bool WriteRecord(std::uint32_t a_type, std::uint32_t a_version, const T* a_data, std::uint32_t a_size) const
		{
			return WriteRecord(a_type, a_version, reinterpret_cast<const std::byte*>(a_data), a_size * sizeof(T));
		}

		template <REX::trivially_readable T>
		bool WriteRecord(std::uint32_t a_type, std::uint32_t a_version, const T& a_value) const
		{
			return WriteRecord(a_type, a_version, reinterpret_cast<const std::byte*>(std::addressof(a_value)), sizeof(T));
		}

		template <REX::trivially_readable T>
		bool WriteRecord(std::uint32_t a_type, std::uint32_t a_version, std::span<const T> a_data) const
		{
			return WriteRecord(a_type, a_version, reinterpret_cast<const std::byte*>(a_data.data()), static_cast<std::uint32_t>(a_data.size_bytes()));
		}

		template <std::ranges::input_range T>
		bool ReadRecord(std::uint32_t a_type, std::uint32_t a_version, T& a_buffer) const
			requires(REX::trivially_writable<std::ranges::range_value_t<T>> && requires(T a_buffer, std::uint32_t a_size) { { a_buffer.resize(a_size) } -> std::same_as<void>; })
		{
			auto readType = 0ui32;
			auto readVersion = 0ui32;
			auto readLength = 0ui32;

			if (!GetNextRecordInfo(readType, readVersion, readLength) || readType != a_type || readVersion != a_version) {
				return false;
			}

			a_buffer.resize(readLength);

			return ReadRecordData(a_buffer.data(), readLength) == readLength;
		}

		template <REX::trivially_writable T>
		std::uint32_t ReadRecordData(T* a_buffer, std::uint32_t a_size) const
		{
			return ReadRecordData(reinterpret_cast<std::byte*>(a_buffer), a_size * sizeof(T));
		}

		template <REX::trivially_writable T>
		std::uint32_t ReadRecordData(T& a_value) const
		{
			return ReadRecordData(reinterpret_cast<std::byte*>(std::addressof(a_value)), sizeof(T));
		}

		template <REX::trivially_writable T>
		std::uint32_t ReadRecordData(std::span<T> a_buffer) const
		{
			return ReadRecordData(reinterpret_cast<std::byte*>(a_buffer.data()), static_cast<std::uint32_t>(a_buffer.size_bytes()));
		}

		template <REX::trivially_readable T>
		bool WriteRecordData(const T* a_value, std::uint32_t a_size) const
		{
			return WriteRecordData(reinterpret_cast<const std::byte*>(a_value), a_size * sizeof(T));
		}

		template <REX::trivially_readable T>
		bool WriteRecordData(const T& a_value) const
		{
			return WriteRecordData(reinterpret_cast<const std::byte*>(std::addressof(a_value)), sizeof(T));
		}

		template <REX::trivially_readable T>
		bool WriteRecordData(std::span<const T> a_data) const
		{
			return WriteRecordData(reinterpret_cast<const std::byte*>(a_data.data()), static_cast<std::uint32_t>(a_data.size_bytes()));
		}
	};
	static_assert(std::is_empty_v<SerializationInterface>);
}
