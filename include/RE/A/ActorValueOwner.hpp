#pragma once

namespace RE
{
	enum class ACTOR_VALUE_MODIFIER : std::int32_t;

	class __declspec(novtable) ActorValueOwner
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ActorValueOwner };
		inline static constexpr auto VTABLE{ VTABLE::ActorValueOwner };

		virtual ~ActorValueOwner(); // 00

		// add
		virtual REX::Float32 GetActorValue(const ActorValueInfo& a_info) const;											 // 01 - { return 0.0_f32; }
		virtual REX::Float32 GetPermanentActorValue(const ActorValueInfo& a_info) const;								 // 02 - { return 0.0_f32; }
		virtual REX::Float32 GetBaseActorValue(const ActorValueInfo& a_info) const;										 // 03 - { return 0.0_f32; }
		virtual void SetBaseActorValue(const ActorValueInfo& a_info, REX::Float32 a_value);								 // 04 - { return; }
		virtual void ModBaseActorValue(const ActorValueInfo& a_info, REX::Float32 a_delta);								 // 05 - { return; }
		virtual void ModActorValue(ACTOR_VALUE_MODIFIER a_modifier, const ActorValueInfo& a_info, REX::Float32 a_delta); // 06 - { return; }
		virtual REX::Float32 GetModifier(ACTOR_VALUE_MODIFIER a_modifier, const ActorValueInfo& a_info) const;			 // 07 - { return 0.0_f32; }
		virtual void RestoreActorValue(const ActorValueInfo& a_info, REX::Float32 a_amount);							 // 08 - { return; }
		virtual void SetActorValue(const ActorValueInfo& a_info, REX::Float32 a_value);									 // 09 - { SetBaseActorValue(a_info, a_value); }
		virtual bool GetIsPlayerOwner() const;																			 // 0A - { return false; }
	};
	static_assert(sizeof(ActorValueOwner) == 0x08);
}
