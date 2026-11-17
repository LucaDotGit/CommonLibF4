#pragma once

#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) TESGrass :
		public TESBoundObject, // 0x00
		public TESModel		   // 0x68
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESGrass;
		inline static constexpr const auto& VTABLE = VTABLE::TESGrass;
		inline static constexpr auto FORM_TYPE = FormType::Grass;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class GRASS_WATER_STATE : std::int32_t
		{
			AboveOnlyAtLeast = 0,
			AboveOnlyAtMost = 1,
			BelowOnlyAtLeast = 2,
			BelowOnlyAtMost = 3,
			BothAtLeast = 4,
			BothAtMost = 5,
			BothAtMostAbove = 6,
			BothAtMostBelow = 7,

			_Count = 8
		};

		class GRASS_DATA
		{
		public:
			enum class Flags : std::uint8_t
			{
				None = 0,
				VertexLighting = 1 << 0,
				UniformScale = 1 << 1,
				FitSlope = 1 << 2
			};

			// members
			std::int8_t density;								   // 0x00
			std::int8_t minSlopeDegrees;						   // 0x01
			std::int8_t maxSlopeDegrees;						   // 0x02
			std::uint16_t distanceFromWaterLevel;				   // 0x04
			REX::Enum<GRASS_WATER_STATE, std::int32_t> waterState; // 0x08
			REX::Float32 positionRange;							   // 0x0C
			REX::Float32 heightRange;							   // 0x10
			REX::Float32 colorRange;							   // 0x14
			REX::Float32 wavePeriod;							   // 0x18
			REX::EnumSet<Flags, std::uint8_t> flags;			   // 0x1C
		};

		static_assert(sizeof(GRASS_DATA) == 0x20);

		// add
		virtual auto GetDensity() const -> std::int8_t;			// 0x67 - { return data.density; }
		virtual auto SetDensity(std::int8_t a_density) -> bool; // 0x68
		virtual auto GetMinSlopeDegrees() const -> std::int8_t; // 0x69 - { return data.minSlopeDegrees; }
		virtual auto SetMinSlopeDegrees(std::int8_t a_minSlopeDegrees) -> bool; // 0x6A
		virtual auto GetMaxSlopeDegrees() const -> std::int8_t; // 0x6B - { return data.maxSlopeDegrees; }
		virtual auto SetMaxSlopeDegrees(std::int8_t a_maxSlopeDegrees) -> bool; // 0x6C
		virtual auto GetMinSlope() const -> REX::Float32;						// 0x6D
		virtual auto GetMaxSlope() const -> REX::Float32;						// 0x6E
		virtual auto GetDistanceFromWaterLevel() const
			-> std::uint16_t; // 0x6F - { return data.distanceFromWaterLevel; }
		virtual void SetDistanceFromWaterLevel(
			std::uint16_t
				a_distanceFromWaterLevel); // 0x70 - { data.distanceFromWaterLevel = a_distanceFromWaterLevel; }
		virtual auto GetUnderwaterState() const -> GRASS_WATER_STATE;	 // 0x71 - { return *data.waterState; }
		virtual void SetUnderwaterState(GRASS_WATER_STATE a_underwater); // 0x72 - { data.waterState = a_underwater; }
		virtual auto GetPositionRange() const -> REX::Float32;			 // 0x73 - { return data.positionRange; }
		virtual auto SetPositionRange(REX::Float32 a_range) -> bool;	 // 0x74
		virtual auto GetHeightRange() const -> REX::Float32;			 // 0x75 - { return data.heightRange; }
		virtual auto SetHeightRange(REX::Float32 a_range) -> bool;		 // 0x76
		virtual auto GetColorRange() const -> REX::Float32;				 // 0x77 - { return data.colorRange; }
		virtual auto SetColorRange(REX::Float32 a_range) -> bool;		 // 0x78
		virtual auto GetWavePeriod() const -> REX::Float32;				 // 0x79 - { return data.wavePeriod; }
		virtual auto SetWavePeriod(REX::Float32 a_period) -> bool;		 // 0x7A
		virtual auto GetVertexLighting() const -> bool;					 // 0x7B
		virtual void SetVertexLighting(bool a_set);						 // 0x7C
		virtual auto GetUniformScaling() const -> bool;					 // 0x7D
		virtual void SetUniformScaling(bool a_set);						 // 0x7E
		virtual auto GetFitToSlope() const -> bool;						 // 0x7F
		virtual void SetFitToSlope(bool a_set) const;					 // 0x80

		// members
		GRASS_DATA data; // 0x98
	};

	static_assert(sizeof(TESGrass) == 0xB8);
}
