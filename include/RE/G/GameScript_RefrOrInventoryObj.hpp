#pragma once

#include "RE/F/FormType.hpp"
#include "RE/T/TESObjectREFR.hpp"

namespace RE
{
	class GameVM;
}

namespace RE::GameScript
{
	class RefrOrInventoryObj
	{
	public:
		inline static constexpr auto FORM_TYPE = FormType::kObjectReference;
		inline static constexpr auto INVALID_UNIQUE_ID = std::numeric_limits<ContainerID>::max();

		constexpr RefrOrInventoryObj() noexcept = default;
		constexpr ~RefrOrInventoryObj() noexcept = default;

		constexpr explicit RefrOrInventoryObj(TESObjectREFR* a_ref) noexcept
			: _ref(a_ref)
		{
		}

		constexpr explicit RefrOrInventoryObj(TESObjectREFR* a_containerRef, ContainerID a_uniqueID) noexcept
			: _containerRef(a_containerRef),
			  _uniqueID(a_uniqueID)
		{
		}

		constexpr explicit RefrOrInventoryObj(TESObjectREFR* a_ref, TESObjectREFR* a_containerRef, ContainerID a_uniqueID) noexcept
			: _ref(a_ref),
			  _containerRef(a_containerRef),
			  _uniqueID(a_uniqueID)
		{
		}

		RefrOrInventoryObj(const GameVM& a_gameVM, BSScript::ObjectHandle a_objectHandle);

		constexpr RefrOrInventoryObj(const RefrOrInventoryObj&) noexcept = default;
		constexpr RefrOrInventoryObj(RefrOrInventoryObj&&) noexcept = default;

		constexpr RefrOrInventoryObj& operator=(const RefrOrInventoryObj&) noexcept = default;
		constexpr RefrOrInventoryObj& operator=(RefrOrInventoryObj&&) noexcept = default;

		[[nodiscard]] constexpr explicit operator bool() const noexcept { return IsReference() || IsInventoryObject(); }

		[[nodiscard]] BSScript::ObjectHandle GetHandle() const;

		// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
		[[nodiscard]] constexpr FormType GetFormType() const noexcept { return FORM_TYPE; }

		[[nodiscard]] constexpr bool IsForm() const noexcept { return _ref != nullptr; }
		[[nodiscard]] constexpr bool IsReference() const noexcept { return _ref != nullptr; }
		[[nodiscard]] constexpr bool IsInventoryObject() const noexcept { return _containerRef != nullptr && _uniqueID != INVALID_UNIQUE_ID; }

		[[nodiscard]] constexpr TESForm* GetForm() const noexcept { return _ref; }
		[[nodiscard]] constexpr TESForm* GetContainer() const noexcept { return _containerRef; }

		[[nodiscard]] constexpr TESObjectREFR* GetReference() const noexcept { return _ref; }
		[[nodiscard]] constexpr TESObjectREFR* GetContainerRef() const noexcept { return _containerRef; }

		[[nodiscard]] constexpr ContainerID GetUniqueID() const noexcept { return _uniqueID; }

	private:
		// members
		TESObjectREFR* _ref{ nullptr };			 // 00
		TESObjectREFR* _containerRef{ nullptr }; // 08
		ContainerID _uniqueID{ 0 };				 // 10
	};
	static_assert(sizeof(RefrOrInventoryObj) == 0x18);
}
