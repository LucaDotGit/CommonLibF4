#pragma once

#include "RE/B/BGSInventoryItem.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSInputEventUser.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint2.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiQuaternion.hpp"

namespace RE::nsInventory3DManager
{
	class NewInventoryMenuItemLoadTask;
}

namespace RE
{
	class ExtraDataList;
	class LoadedInventoryModel;

	class __declspec(novtable) Inventory3DManager : public BSInputEventUser // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::Inventory3DManager;
		inline static constexpr const auto& VTABLE = VTABLE::Inventory3DManager;

		void Begin3D()
		{
			using FuncType = decltype(&Inventory3DManager::Begin3D);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Inventory3DManager::Begin3D);
			std::invoke(FUNC, this);
		}

		void ClearModel()
		{
			using FuncType = decltype(&Inventory3DManager::ClearModel);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Inventory3DManager::ClearModel);
			std::invoke(FUNC, this);
		}

		void DisableRendering(const BSFixedString& a_userID)
		{
			using FuncType = decltype(&Inventory3DManager::DisableRendering);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Inventory3DManager::DisableRendering);
			std::invoke(FUNC, this, a_userID);
		}

		void EnableRendering(const BSFixedString& a_userID)
		{
			using FuncType = decltype(&Inventory3DManager::EnableRendering);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Inventory3DManager::EnableRendering);
			std::invoke(FUNC, this, a_userID);
		}

		void End3D()
		{
			using FuncType = decltype(&Inventory3DManager::End3D);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Inventory3DManager::End3D);
			std::invoke(FUNC, this);
		}

		void SetModelScale(REX::Float32 a_scale)
		{
			using FuncType = decltype(&Inventory3DManager::SetModelScale);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Inventory3DManager::SetModelScale);
			std::invoke(FUNC, this, a_scale);
		}

		void SetModelScreenPosition(const NiPoint3& a_position, bool a_screenCoords)
		{
			using FuncType = decltype(&Inventory3DManager::SetModelScreenPosition);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Inventory3DManager::SetModelScreenPosition);
			std::invoke(FUNC, this, a_position, a_screenCoords);
		}

		// members
		bool useBoundForScale			 : 1;									// 0x010:0
		bool startedZoomThisFrame		 : 1;									// 0x010:1
		bool useStoredModelPosition		 : 1;									// 0x010:2
		bool rotating					 : 1;									// 0x010:3
		bool modelPositionInScreenCoords : 1;									// 0x010:4
		bool centerOnBoundCenter		 : 1;									// 0x010:5
		NiPoint3 modelPosition;													// 0x014
		REX::Float32 modelScale;												// 0x020
		BSTArray<LoadedInventoryModel> loadedModels;							// 0x030
		NiPoint3 initialPosition;												// 0x048
		NiPoint3 storedPostion;													// 0x054
		NiMatrix3 initialRotation;												// 0x060
		NiQuaternion storedRotation;											// 0x090
		NiPoint2 previousInput;													// 0x0A0
		NiPointer<nsInventory3DManager::NewInventoryMenuItemLoadTask> loadTask; // 0x0A8
		TESObjectREFR* tempRef;													// 0x0B0
		BSTSmartPointer<ExtraDataList> originalExtra;							// 0x0B8
		BSFixedString str3DRendererName;										// 0x0C0
		BGSInventoryItem queuedDisplayItem;										// 0x0C8
		std::uint32_t itemExtraIndex;											// 0x0D8
		TESForm* itemBase;														// 0x0E0
		std::int8_t disableInputUserCount;										// 0x0E8
		BSTSet<BSFixedString> disableRendererUsers;								// 0x0F0
		REX::Float32 storedXRotation;											// 0x120
		REX::Float32 zoomDirection;												// 0x124
		REX::Float32 zoomProgress;												// 0x128
		REX::Float32 minZoomModifier;											// 0x12C
		REX::Float32 maxZoomModifier;											// 0x130
		std::uint32_t hightlightedPart;											// 0x134
		bool queueShowItem;														// 0x138
		bool mouseRotation;														// 0x139
		bool prevUsesCursorFlag;												// 0x13A
		bool prevUpdateUsesCursorFlag;											// 0x13B
		bool addedLightsToScene;												// 0x13C
	};

	static_assert(sizeof(Inventory3DManager) == 0x140);
}
