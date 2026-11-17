#pragma once

#include "RE/B/BaseFormComponent.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE
{
	class __declspec(novtable) BGSIdleCollection : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSIdleCollection;
		inline static constexpr const auto& VTABLE = VTABLE::BGSIdleCollection;

		enum class Flags : std::uint8_t
		{
			None = 0,
			PickSequence = 1 << 0,
			OldPickConditions = 1 << 1,
			DoOnce = 1 << 2,
			LooseOnly = 1 << 3,
			NoSandbox = 1 << 4
		};

		~BGSIdleCollection() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		[[nodiscard]]
		auto GetIdleCount() const noexcept -> std::uint8_t
		{
			return idleCount;
		}

		[[nodiscard]]
		auto GetIdles() noexcept -> std::span<TESIdleForm*>
		{
			return {idleArray.data(), idleCount};
		}

		[[nodiscard]]
		auto GetIdles() const noexcept -> std::span<TESIdleForm* const>
		{
			return {idleArray.data(), idleCount};
		}

		// members
		REX::EnumSet<Flags, std::uint8_t> idleFlags; // 0x08
		std::uint8_t idleCount;						 // 0x09
		SimpleArray<TESIdleForm*> idleArray;		 // 0x10
		REX::Float32 timerCheckForIdle;				 // 0x18
	};

	static_assert(sizeof(BGSIdleCollection) == 0x20);
}
