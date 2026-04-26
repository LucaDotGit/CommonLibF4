#pragma once

#include "RE/B/BaseFormComponent.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE
{
	class __declspec(novtable) BGSIdleCollection
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSIdleCollection };
		inline static constexpr auto VTABLE{ VTABLE::BGSIdleCollection };

		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kPickSequence = 1 << 0,
			kOldPickConditions = 1 << 1,
			kDoOnce = 1 << 2,
			kLooseOnly = 1 << 3,
			kNoSandbox = 1 << 4
		};

		~BGSIdleCollection() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		[[nodiscard]] std::uint8_t GetIdleCount() const noexcept { return idleCount; }

		[[nodiscard]] std::span<TESIdleForm*> GetIdles() noexcept { return { idleArray.data(), idleCount }; }
		[[nodiscard]] std::span<TESIdleForm* const> GetIdles() const noexcept { return { idleArray.data(), idleCount }; }

		// members
		REX::EnumSet<Flags, std::uint8_t> idleFlags; // 08
		std::uint8_t idleCount;						 // 09
		SimpleArray<TESIdleForm*> idleArray;		 // 10
		REX::Float32 timerCheckForIdle;				 // 18
	};
	static_assert(sizeof(BGSIdleCollection) == 0x20);
}
