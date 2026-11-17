#pragma once

#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hknpBSWorld.hpp"
#include "RE/H/hknpRayCastQuery.hpp"
#include "RE/H/hknpRayCastQueryResult.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class hknpBody;
	class hknpCollisionQueryCollector;
	class NiAVObject;
	class NiPoint3;

	class bhkPickData
	{
	public:
		enum class COLLECTOR_TYPE : std::int32_t
		{
		};

		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
		bhkPickData()
		{
			using FuncType = void (bhkPickData::*)();
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkPickData::ctor);
			std::invoke(FUNC, this);
		}

		auto GetAllCollectorRayHitAt(std::uint32_t a_index, hknpCollisionResult& a_result) const -> bool
		{
			using FuncType = decltype(&bhkPickData::GetAllCollectorRayHitAt);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkPickData::GetAllCollectorRayHitAt);
			return std::invoke(FUNC, this, a_index, a_result);
		}

		[[nodiscard]]
		auto GetAllCollectorRayHitSize() const -> std::int32_t
		{
			using FuncType = decltype(&bhkPickData::GetAllCollectorRayHitSize);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkPickData::GetAllCollectorRayHitSize);
			return std::invoke(FUNC, this);
		}

		[[nodiscard]]
		auto GetBody() const -> hknpBody*
		{
			using FuncType = decltype(&bhkPickData::GetBody);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkPickData::GetBody);
			return std::invoke(FUNC, this);
		}

		[[nodiscard]]
		auto GetHitFraction() const -> REX::Float32
		{
			using FuncType = decltype(&bhkPickData::GetHitFraction);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkPickData::GetHitFraction);
			return std::invoke(FUNC, this);
		}

		[[nodiscard]]
		auto GetNiAVObject() const -> NiAVObject*
		{
			using FuncType = decltype(&bhkPickData::GetNiAVObject);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkPickData::GetNiAVObject);
			return std::invoke(FUNC, this);
		}

		auto HasHit() const -> bool
		{
			using FuncType = decltype(&bhkPickData::HasHit);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkPickData::HasHit);
			return std::invoke(FUNC, this);
		}

		void Reset()
		{
			using FuncType = decltype(&bhkPickData::Reset);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkPickData::Reset);
			std::invoke(FUNC, this);
		}

		void SetStartEnd(const NiPoint3& a_start, const NiPoint3& a_end)
		{
			using FuncType = decltype(&bhkPickData::SetStartEnd);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkPickData::SetStartEnd);
			std::invoke(FUNC, this, a_start, a_end);
		}

		void SortAllCollectorHits()
		{
			using FuncType = decltype(&bhkPickData::SortAllCollectorHits);
			static const auto FUNC = REL::Relocation<FuncType>(ID::bhkPickData::SortAllCollectorHits);
			std::invoke(FUNC, this);
		}

		GAME_HEAP_REDEFINE_NEW(bhkPickData);

		// members
		hknpRayCastQuery castQuery;							   // 0x00
		hknpRayCastQueryResult result;						   // 0x60
		hkRefPtr<hknpBSWorld> castWorld;					   // 0xC0
		std::uint64_t customCollideLayers;					   // 0xC8
		hknpCollisionQueryCollector* collector;				   // 0xD0
		REX::Enum<COLLECTOR_TYPE, std::int32_t> collectorType; // 0xD8
		bool incrementPickTime;								   // 0xDC
		bool allowFailedPicks;								   // 0xDD
		bool pickFailed;									   // 0xDE
	};

	static_assert(sizeof(bhkPickData) == 0xE0);
};
