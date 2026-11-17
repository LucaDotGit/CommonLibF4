#pragma once

#include "RE/F/FormType.hpp"
#include "RE/T/TESObjectREFR.hpp"

namespace RE::GameScript
{
	class HandlePolicy;

	class RefrOrInventoryObj
	{
	public:
		inline static constexpr auto FORM_TYPE = FormType::ObjectReference;
		inline static constexpr auto INVALID_UNIQUE_ID = std::numeric_limits<ContainerID>::max();

		constexpr RefrOrInventoryObj() noexcept = default;
		constexpr ~RefrOrInventoryObj() noexcept = default;

		constexpr explicit RefrOrInventoryObj(TESObjectREFR* a_ref) noexcept :
			_ref(a_ref)
		{
		}

		constexpr RefrOrInventoryObj(TESObjectREFR* a_containerRef, ContainerID a_uniqueID) noexcept :
			_containerRef(a_containerRef),
			_uniqueID(a_uniqueID)
		{
		}

		constexpr RefrOrInventoryObj(TESObjectREFR* a_ref, TESObjectREFR* a_containerRef, ContainerID a_uniqueID)
			noexcept :
			_ref(a_ref),
			_containerRef(a_containerRef),
			_uniqueID(a_uniqueID)
		{
		}

		RefrOrInventoryObj(const HandlePolicy& a_handlePolicy, BSScript::ObjectHandle a_objectHandle);

		constexpr RefrOrInventoryObj(const RefrOrInventoryObj&) noexcept = default;
		constexpr RefrOrInventoryObj(RefrOrInventoryObj&&) noexcept = default;

		constexpr auto operator=(const RefrOrInventoryObj&) noexcept -> RefrOrInventoryObj& = default;
		constexpr auto operator=(RefrOrInventoryObj&&) noexcept -> RefrOrInventoryObj& = default;

		[[nodiscard]]
		constexpr explicit operator bool() const noexcept
		{
			return IsReference() || IsInventoryObject();
		}

		[[nodiscard]]
		auto GetHandle() const -> BSScript::ObjectHandle;

		// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
		[[nodiscard]]
		constexpr auto GetFormType() const noexcept -> FormType
		{
			return FORM_TYPE;
		}

		[[nodiscard]]
		constexpr auto IsForm() const noexcept -> bool
		{
			return _ref != nullptr;
		}

		[[nodiscard]]
		constexpr auto IsReference() const noexcept -> bool
		{
			return _ref != nullptr;
		}

		[[nodiscard]]
		constexpr auto IsInventoryObject() const noexcept -> bool
		{
			return _containerRef != nullptr && _uniqueID != INVALID_UNIQUE_ID;
		}

		[[nodiscard]]
		constexpr auto GetForm() const noexcept -> TESForm*
		{
			return _ref;
		}

		[[nodiscard]]
		constexpr auto GetContainer() const noexcept -> TESForm*
		{
			return _containerRef;
		}

		[[nodiscard]]
		constexpr auto GetReference() const noexcept -> TESObjectREFR*
		{
			return _ref;
		}

		[[nodiscard]]
		constexpr auto GetContainerRef() const noexcept -> TESObjectREFR*
		{
			return _containerRef;
		}

		[[nodiscard]]
		constexpr auto GetUniqueID() const noexcept -> ContainerID
		{
			return _uniqueID;
		}

	private:
		// members
		TESObjectREFR* _ref{nullptr};		   // 0x00
		TESObjectREFR* _containerRef{nullptr}; // 0x08
		ContainerID _uniqueID{0};			   // 0x10
	};

	static_assert(sizeof(RefrOrInventoryObj) == 0x18);
}
