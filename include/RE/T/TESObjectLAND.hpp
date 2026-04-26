#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/C/CHAR_NORM.hpp"
#include "RE/H/hkRefPtr.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/O/OBJ_LAND.hpp"
#include "RE/T/TESChildCell.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class QueuedFile;
	class hknpShape;
	class NiNode;
	class BSTriShape;
	class TESLandTexture;

	class __declspec(novtable) TESObjectLAND
		: public TESForm,	  // 00
		  public TESChildCell // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESObjectLAND };
		inline static constexpr auto VTABLE{ VTABLE::TESObjectLAND };
		inline static constexpr auto FORM_TYPE{ FormType::kLandscape };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kCompressed = 1 << 18
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class COORD_DATA_FLAGS : std::uint32_t
		{
			kNone = 0,
			kVertexCoord = 1 << 0,
			kForceToVertex = 1 << 1,
			kCalcNearest = 1 << 2,
			kBlockOnly = 1 << 3,
			kDefaults = kCalcNearest | kVertexCoord
		};

		class LoadedLandData
		{
		public:
			// members
			std::array<NiNode*, 4> mesh;												// 0000
			std::array<REX::Float32, 1156> heights;										// 0020
			std::array<std::array<std::array<std::uint8_t, 12>, 289>, 4> percentArrays; // 1230
			std::array<std::array<std::array<std::uint8_t, 3>, 289>, 4> colors;			// 4860
			std::array<std::array<CHAR_NORM, 289>, 4> normals;							// 55EC
			BSTArray<hkRefPtr<const hknpShape>> saveLoadHFDataArray;					// 6378
			std::array<NiPointer<BSTriShape>, 4> geom;									// 6390
			NiPointer<BSTriShape> border;												// 63B0
			NiPoint2 heightExtends;														// 63B8
			std::array<TESLandTexture*, 4> defQuadTexture;								// 63C0
			std::array<std::array<TESLandTexture*, 12>, 4> quadTextureArray;			// 63E0
			std::int32_t cellX;															// 6560
			std::int32_t cellY;															// 6564
			REX::Float32 baseHeight;													// 6568
			LoadedLandData* next;														// 6570
		};
		static_assert(sizeof(LoadedLandData) == 0x6578);

		// members
		OBJ_LAND data;						  // 28
		TESObjectCELL* parentCell;			  // 30
		NiPointer<QueuedFile> queuedTextures; // 38
		LoadedLandData* loadedData;			  // 40
	};
	static_assert(sizeof(TESObjectLAND) == 0x48);
}
