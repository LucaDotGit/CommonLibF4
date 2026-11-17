#pragma once

namespace RE
{
	enum class ACTOR_VALUE_MODIFIER : std::int32_t;

	class __declspec(novtable) ActorValueOwner
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ActorValueOwner;
		inline static constexpr const auto& VTABLE = VTABLE::ActorValueOwner;

		virtual ~ActorValueOwner(); // 0x00

		// add
		virtual auto GetActorValue(const ActorValueInfo& a_info) const
			-> REX::Float32; // 0x01 - { return static_cast<REX::Float32>(0.0); }
		virtual auto GetPermanentActorValue(const ActorValueInfo& a_info) const
			-> REX::Float32; // 0x02 - { return static_cast<REX::Float32>(0.0); }
		virtual auto GetBaseActorValue(const ActorValueInfo& a_info) const
			-> REX::Float32; // 0x03 - { return static_cast<REX::Float32>(0.0); }
		virtual void SetBaseActorValue(const ActorValueInfo& a_info, REX::Float32 a_value); // 0x04 - { return; }
		virtual void ModBaseActorValue(const ActorValueInfo& a_info, REX::Float32 a_delta); // 0x05 - { return; }
		virtual void ModActorValue(
			ACTOR_VALUE_MODIFIER a_modifier,
			const ActorValueInfo& a_info,
			REX::Float32 a_delta); // 0x06 - { return; }
		virtual auto GetModifier(ACTOR_VALUE_MODIFIER a_modifier, const ActorValueInfo& a_info) const
			-> REX::Float32; // 0x07 - { return static_cast<REX::Float32>(0.0); }
		virtual void RestoreActorValue(const ActorValueInfo& a_info, REX::Float32 a_amount); // 0x08 - { return; }
		virtual void SetActorValue(
			const ActorValueInfo& a_info,
			REX::Float32 a_value);					   // 0x09 - { SetBaseActorValue(a_info, a_value); }
		virtual auto GetIsPlayerOwner() const -> bool; // 0x0A - { return false; }
	};

	static_assert(sizeof(ActorValueOwner) == 0x08);
}
