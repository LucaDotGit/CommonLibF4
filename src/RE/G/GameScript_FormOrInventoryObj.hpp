#pragma once

#include "RE/F/FormType.hpp"

namespace RE::GameScript
{
	class HandlePolicy;

	class FormOrInventoryObj
	{
	public:
		inline static constexpr auto FORM_TYPE = FormType::None;
		inline static constexpr auto INVALID_UNIQUE_ID = std::numeric_limits<ContainerID>::max();

		constexpr FormOrInventoryObj() noexcept = default;
		constexpr ~FormOrInventoryObj() noexcept = default;

		constexpr explicit FormOrInventoryObj(TESForm* a_form) noexcept :
			_formOrContainer(a_form)
		{
		}

		constexpr FormOrInventoryObj(TESForm* a_container, ContainerID a_uniqueID) noexcept :
			_formOrContainer(a_container),
			_uniqueID(a_uniqueID)
		{
		}

		FormOrInventoryObj(const HandlePolicy& a_handlePolicy, BSScript::ObjectHandle a_objectHandle);

		constexpr FormOrInventoryObj(const FormOrInventoryObj&) noexcept = default;
		constexpr FormOrInventoryObj(FormOrInventoryObj&&) noexcept = default;

		constexpr auto operator=(const FormOrInventoryObj&) noexcept -> FormOrInventoryObj& = default;
		constexpr auto operator=(FormOrInventoryObj&&) noexcept -> FormOrInventoryObj& = default;

		[[nodiscard]]
		constexpr explicit operator bool() const noexcept
		{
			return IsForm() || IsInventoryObject();
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
			return _formOrContainer != nullptr;
		}

		[[nodiscard]]
		constexpr auto IsInventoryObject() const noexcept -> bool
		{
			return _formOrContainer != nullptr && _uniqueID != INVALID_UNIQUE_ID;
		}

		[[nodiscard]]
		constexpr auto GetForm() const noexcept -> TESForm*
		{
			return _formOrContainer;
		}

		[[nodiscard]]
		constexpr auto GetContainer() const noexcept -> TESForm*
		{
			return _formOrContainer;
		}

		[[nodiscard]]
		constexpr auto GetUniqueID() const noexcept -> ContainerID
		{
			return _uniqueID;
		}

	private:
		// members
		TESForm* _formOrContainer{nullptr}; // 0x00
		ContainerID _uniqueID{0};			// 0x08
	};

	static_assert(sizeof(FormOrInventoryObj) == 0x10);
}
