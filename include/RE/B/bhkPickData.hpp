#pragma once

#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hknpBSWorld.hpp"
#include "RE/H/hknpRayCastQuery.hpp"
#include "RE/H/hknpRayCastQueryResult.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class hknpBody;
	class hknpCollisionQueryCollector;
	class NiAVObject;

	class bhkPickData
	{
	public:
		enum class COLLECTOR_TYPE : std::int32_t
		{
		};

		bhkPickData()
		{
			using FuncType = void (bhkPickData::*)();
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkPickData::ctor };
			FUNC(this);
		}

		bool GetAllCollectorRayHitAt(std::uint32_t a_index, hknpCollisionResult& a_result) const
		{
			using FuncType = decltype(&bhkPickData::GetAllCollectorRayHitAt);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkPickData::GetAllCollectorRayHitAt };
			return std::invoke(FUNC, this, a_index, a_result);
		}

		[[nodiscard]] std::int32_t GetAllCollectorRayHitSize() const
		{
			using FuncType = decltype(&bhkPickData::GetAllCollectorRayHitSize);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkPickData::GetAllCollectorRayHitSize };
			return std::invoke(FUNC, this);
		}

		[[nodiscard]] hknpBody* GetBody() const
		{
			using FuncType = decltype(&bhkPickData::GetBody);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkPickData::GetBody };
			return std::invoke(FUNC, this);
		}

		[[nodiscard]] REX::Float32 GetHitFraction() const
		{
			using FuncType = decltype(&bhkPickData::GetHitFraction);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkPickData::GetHitFraction };
			return std::invoke(FUNC, this);
		}

		[[nodiscard]] NiAVObject* GetNiAVObject() const
		{
			using FuncType = decltype(&bhkPickData::GetNiAVObject);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkPickData::GetNiAVObject };
			return std::invoke(FUNC, this);
		}

		bool HasHit() const
		{
			using FuncType = decltype(&bhkPickData::HasHit);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkPickData::HasHit };
			return std::invoke(FUNC, this);
		}

		void Reset()
		{
			using FuncType = decltype(&bhkPickData::Reset);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkPickData::Reset };
			FUNC(this);
		}

		void SetStartEnd(const NiPoint3& a_start, const NiPoint3& a_end)
		{
			using FuncType = decltype(&bhkPickData::SetStartEnd);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkPickData::SetStartEnd };
			FUNC(this, a_start, a_end);
		}

		void SortAllCollectorHits()
		{
			using FuncType = decltype(&bhkPickData::SortAllCollectorHits);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::bhkPickData::SortAllCollectorHits };
			FUNC(this);
		}

		GAME_HEAP_REDEFINE_NEW(bhkPickData);

		// members
		hknpRayCastQuery castQuery;							   // 00
		hknpRayCastQueryResult result;						   // 60
		hkRefPtr<hknpBSWorld> castWorld;					   // C0
		std::uint64_t customCollideLayers{ 0 };				   // C8
		hknpCollisionQueryCollector* collector{ nullptr };	   // D0
		REX::Enum<COLLECTOR_TYPE, std::int32_t> collectorType; // D8
		bool incrementPickTime{ false };					   // DC
		bool allowFailedPicks{ false };						   // DD
		bool pickFailed{ false };							   // DE
	};
	static_assert(sizeof(bhkPickData) == 0xE0);
};
