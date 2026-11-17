#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSLight;
	class ProjectileBeginUpdateEvent;
	class TESDeathEvent;
	class TESHitEvent;
	class VATSCameraContext;
	class VATSCommand;
	class WeaponFiredEvent;

	class __declspec(novtable) VATS :
		public BSTEventSink<WeaponFiredEvent>,			 // 0x00
		public BSTEventSink<ProjectileBeginUpdateEvent>, // 0x08
		public BSTEventSink<TESHitEvent>,				 // 0x10
		public BSTEventSink<TESDeathEvent>,				 // 0x18
		public BSTSingletonSDM<VATS>					 // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::VATS;
		inline static constexpr const auto& VTABLE = VTABLE::VATS;

		enum class VATS_MODE_ENUM : std::int32_t
		{
			None = 0,
			Playback = 1
		};

		~VATS() override; // 0x00

		// override (BSTEventSink<WeaponFiredEvent>)
		auto ProcessEvent(
			const WeaponFiredEvent& a_event,
			BSTEventSource<WeaponFiredEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<ProjectileBeginUpdateEvent>)
		auto ProcessEvent(
			const ProjectileBeginUpdateEvent& a_event,
			BSTEventSource<ProjectileBeginUpdateEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESHitEvent> and BSTEventSink<TESDeathEvent>)
		auto ProcessEvent(const TESHitEvent& a_event, BSTEventSource<TESHitEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESDeathEvent>)
		auto ProcessEvent(const TESDeathEvent& a_event, BSTEventSource<TESDeathEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> VATS*
		{
			static const auto SINGLETON = REL::Relocation<VATS**>(ID::VATS::Singleton);
			return *SINGLETON;
		}

		// members
		BSTArray<BSTSmartPointer<VATSCommand>> commands; // 0x28
		REX::Enum<VATS_MODE_ENUM, std::int32_t> mode;	 // 0x40
		VATSCameraContext* cameraContext;				 // 0x48
		REX::Float32 castingAfterKillDelay;				 // 0x50
		NiPointer<Projectile> firstProjectile;			 // 0x58
		NiPointer<Projectile> lastProjectile;			 // 0x60
		REX::Float32 fakeShotCounter;					 // 0x68
		TESIdleForm* meleeAttack;						 // 0x70
		NiPointer<BSLight> vatsLight;					 // 0x78
		std::int32_t killCount;							 // 0x80
		REX::Float32 magicTimeSlowdown;					 // 0x84
		REX::Float32 playerMagicTimeSlowdown;			 // 0x88
		NiPointer<TESObjectREFR> vatsTarget;			 // 0x90
		NiPointer<Actor> vatsAttacker;					 // 0x98
		NiPointer<Actor> stranger;						 // 0xA0
		NiPointer<Projectile> predictionProjectile;		 // 0xA8
		BSTSmartPointer<VATSCommand> reloadCommand;		 // 0xB0
		BSTSmartPointer<VATSCommand> sightedCommand;	 // 0xB8
		REX::Float32 vatsPlaybackTimer;					 // 0xC0
		REX::Float32 vatsCommandTimer;					 // 0xC4
		bool projectileNearTarget;						 // 0xC8
		bool applyCritical;								 // 0xC9
		bool firstAttackExecuted;						 // 0xCA
		bool firstAttackFired;							 // 0xCB
		bool readyForShutdown;							 // 0xCC
		bool wantsStranger;								 // 0xCD
		mutable BSSpinLock spinLock;					 // 0xD0
	};

	static_assert(sizeof(VATS) == 0xD8);
}
