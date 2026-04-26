#pragma once

#include "RE/F/FormType.hpp"

namespace RE
{
	class GameVM;
}

namespace RE::GameScript
{
	class FormOrInventoryObj
	{
	public:
		inline static constexpr auto FORM_TYPE = FormType::kNone;
		inline static constexpr auto INVALID_UNIQUE_ID = std::numeric_limits<ContainerID>::max();

		constexpr FormOrInventoryObj() noexcept = default;
		constexpr ~FormOrInventoryObj() noexcept = default;

		constexpr explicit FormOrInventoryObj(TESForm* a_form) noexcept
			: _formOrContainer(a_form)
		{
		}

		constexpr explicit FormOrInventoryObj(TESForm* a_container, ContainerID a_uniqueID) noexcept
			: _formOrContainer(a_container),
			  _uniqueID(a_uniqueID)
		{
		}

		FormOrInventoryObj(const GameVM& a_gameVM, BSScript::ObjectHandle a_objectHandle);

		constexpr FormOrInventoryObj(const FormOrInventoryObj&) noexcept = default;
		constexpr FormOrInventoryObj(FormOrInventoryObj&&) noexcept = default;

		constexpr FormOrInventoryObj& operator=(const FormOrInventoryObj&) noexcept = default;
		constexpr FormOrInventoryObj& operator=(FormOrInventoryObj&&) noexcept = default;

		[[nodiscard]] constexpr explicit operator bool() const noexcept { return IsForm() || IsInventoryObject(); }

		[[nodiscard]] BSScript::ObjectHandle GetHandle() const;

		// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
		[[nodiscard]] constexpr FormType GetFormType() const noexcept { return FORM_TYPE; }

		[[nodiscard]] constexpr bool IsForm() const noexcept { return _formOrContainer != nullptr; }
		[[nodiscard]] constexpr bool IsInventoryObject() const noexcept { return _formOrContainer != nullptr && _uniqueID != INVALID_UNIQUE_ID; }

		[[nodiscard]] constexpr TESForm* GetForm() const noexcept { return _formOrContainer; }
		[[nodiscard]] constexpr TESForm* GetContainer() const noexcept { return _formOrContainer; }
		[[nodiscard]] constexpr ContainerID GetUniqueID() const noexcept { return _uniqueID; }

	private:
		// members
		TESForm* _formOrContainer{ nullptr }; // 00
		ContainerID _uniqueID{ 0 };			  // 08
	};
	static_assert(sizeof(FormOrInventoryObj) == 0x10);
}
