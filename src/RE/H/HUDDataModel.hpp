#pragma once

#include "RE/B/BSInputEventReceiver.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/C/CalculateCompassMarkersFunctor.hpp"
#include "RE/C/ConditionBoyEvent.hpp"
#include "RE/H/HUDActiveEffectsModel.hpp"
#include "RE/H/HUDAmmoCountModel.hpp"
#include "RE/H/HUDDirectionalHitIndicatorDataModel.hpp"
#include "RE/H/HUDExplosivesDataModel.hpp"
#include "RE/H/HUDMessagesModel.hpp"
#include "RE/H/HUDNotificationsModel.hpp"
#include "RE/H/HUDPerkVaultBoyModel.hpp"
#include "RE/H/HUDRadiationModel.hpp"
#include "RE/H/HUDRolloverModel.hpp"
#include "RE/H/HUDTargetHealthModel.hpp"

namespace RE
{
	class __declspec(novtable) HUDDataModel :
		public BSInputEventReceiver,		 // 0x0000
		public BSTSingletonSDM<HUDDataModel> // 0x0010
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::HUDDataModel;
		inline static constexpr const auto& VTABLE = VTABLE::HUDDataModel;

		// override (BSInputEventReceiver)
		void PerformInputProcessing(const InputEvent* a_queueHead) override; // 0x00

		// add
		virtual ~HUDDataModel(); // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> HUDDataModel*
		{
			static const auto SINGLETON = REL::Relocation<HUDDataModel**>(ID::HUDDataModel::Singleton);
			return *SINGLETON;
		}

		// members
		HUDRolloverModel rolloverModel;										  // 0x0018
		HUDTargetHealthModel targetHealthModel;								  // 0x05C0
		HUDRadiationModel radiationModel;									  // 0x0698
		HUDExplosivesDataModel explosivesDataModel;							  // 0x0910
		HUDDirectionalHitIndicatorDataModel directionalHitIndicatorDataModel; // 0x0968
		HUDAmmoCountModel ammoCountModel;									  // 0x09E0
		HUDMessagesModel messagesModel;										  // 0x0A08
		HUDPerkVaultBoyModel perkVaultBoyModel;								  // 0x0B68
		HUDNotificationsModel notificationsModel;							  // 0x0C40
		HUDActiveEffectsModel activeEffectsModel;							  // 0x0EC0
		BSTValueEventSource<ConditionBoyEvent> conditionBoy;				  // 0x1320
		CalculateCompassMarkersFunctor compassMarkerFunctor;				  // 0x1340
		mutable BSSpinLock compassMarkerArrayLock;							  // 0x1398
	};

	static_assert(sizeof(HUDDataModel) == 0x13A0);
}
