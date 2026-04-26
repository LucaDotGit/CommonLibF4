#pragma once

#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) TESGrass
		: public TESBoundObject, // 00
		  public TESModel		 // 68
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESGrass };
		inline static constexpr auto VTABLE{ VTABLE::TESGrass };
		inline static constexpr auto FORM_TYPE{ FormType::kGrass };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class GRASS_WATER_STATE : std::int32_t
		{
			kAboveOnlyAtLeast = 0,
			kAboveOnlyAtMost = 1,
			kBelowOnlyAtLeast = 2,
			kBelowOnlyAtMost = 3,
			kBothAtLeast = 4,
			kBothAtMost = 5,
			kBothAtMostAbove = 6,
			kBothAtMostBelow = 7,

			kTotal = 8
		};

		class GRASS_DATA
		{
		public:
			enum class Flags : std::uint8_t
			{
				kNone = 0,
				kVertexLighting = 1 << 0,
				kUniformScale = 1 << 1,
				kFitSlope = 1 << 2
			};

			// members
			std::int8_t density;								   // 00
			std::int8_t minSlopeDegrees;						   // 01
			std::int8_t maxSlopeDegrees;						   // 02
			std::uint16_t distanceFromWaterLevel;				   // 04
			REX::Enum<GRASS_WATER_STATE, std::int32_t> waterState; // 08
			REX::Float32 positionRange;							   // 0C
			REX::Float32 heightRange;							   // 10
			REX::Float32 colorRange;							   // 14
			REX::Float32 wavePeriod;							   // 18
			REX::EnumSet<Flags, std::uint8_t> flags;			   // 1C
		};
		static_assert(sizeof(GRASS_DATA) == 0x20);

		// add
		virtual std::int8_t GetDensity() const;																	  // 67 - { return data.density; }
		virtual bool SetDensity(std::int8_t a_density);															  // 68
		virtual std::int8_t GetMinSlopeDegrees() const;															  // 69 - { return data.minSlopeDegrees; }
		virtual bool SetMinSlopeDegrees(std::int8_t a_minSlopeDegrees);											  // 6A
		virtual std::int8_t GetMaxSlopeDegrees() const;															  // 6B - { return data.maxSlopeDegrees; }
		virtual bool SetMaxSlopeDegrees(std::int8_t a_maxSlopeDegrees);											  // 6C
		virtual REX::Float32 GetMinSlope() const;																  // 6D
		virtual REX::Float32 GetMaxSlope() const;																  // 6E
		virtual std::uint16_t GetDistanceFromWaterLevel() const;												  // 6F - { return data.distanceFromWaterLevel; }
		virtual void SetDistanceFromWaterLevel(std::uint16_t a_distanceFromWaterLevel);							  // 70 - { data.distanceFromWaterLevel = a_distanceFromWaterLevel; }
		virtual GRASS_WATER_STATE GetUnderwaterState() const;													  // 71 - { return *data.waterState; }
		virtual void SetUnderwaterState(const GRASS_WATER_STATE a_underwater) { data.waterState = a_underwater; } // 72
		virtual REX::Float32 GetPositionRange() const;															  // 73 - { return data.positionRange; }
		virtual bool SetPositionRange(REX::Float32 a_range);													  // 74
		virtual REX::Float32 GetHeightRange() const;															  // 75 - { return data.heightRange; }
		virtual bool SetHeightRange(REX::Float32 a_range);														  // 76
		virtual REX::Float32 GetColorRange() const;																  // 77 - { return data.colorRange; }
		virtual bool SetColorRange(REX::Float32 a_range);														  // 78
		virtual REX::Float32 GetWavePeriod() const;																  // 79 - { return data.wavePeriod; }
		virtual bool SetWavePeriod(REX::Float32 a_period);														  // 7A
		virtual bool GetVertexLighting() const;																	  // 7B
		virtual void SetVertexLighting(bool a_set);																  // 7C
		virtual bool GetUniformScaling() const;																	  // 7D
		virtual void SetUniformScaling(bool a_set);																  // 7E
		virtual bool GetFitToSlope() const;																		  // 7F
		virtual void SetFitToSlope(bool a_set) const;															  // 80

		// members
		GRASS_DATA data; // 98
	};
	static_assert(sizeof(TESGrass) == 0xB8);
}
