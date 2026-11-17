#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/C/CHAR_NORM.hpp"
#include "RE/H/hkRefPtr.hpp"
#include "RE/N/NiPoint2.hpp"
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

	class __declspec(novtable) TESObjectLAND :
		public TESForm,		// 0x00
		public TESChildCell // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESObjectLAND;
		inline static constexpr const auto& VTABLE = VTABLE::TESObjectLAND;
		inline static constexpr auto FORM_TYPE = FormType::Landscape;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12,
				Compressed = 1 << 18
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class COORD_DATA_FLAGS : std::uint32_t
		{
			None = 0,
			VertexCoord = 1 << 0,
			ForceToVertex = 1 << 1,
			CalcNearest = 1 << 2,
			BlockOnly = 1 << 3,
			Defaults = CalcNearest | VertexCoord
		};

		class LoadedLandData
		{
		public:
			// members
			std::array<NiNode*, 4> mesh;												// 0x0000
			std::array<REX::Float32, 1'156> heights;									// 0x0020
			std::array<std::array<std::array<std::uint8_t, 12>, 289>, 4> percentArrays; // 0x1230
			std::array<std::array<std::array<std::uint8_t, 3>, 289>, 4> colors;			// 0x4860
			std::array<std::array<CHAR_NORM, 289>, 4> normals;							// 0x55EC
			BSTArray<hkRefPtr<const hknpShape>> saveLoadHFDataArray;					// 0x6378
			std::array<NiPointer<BSTriShape>, 4> geom;									// 0x6390
			NiPointer<BSTriShape> border;												// 0x63B0
			NiPoint2 heightExtends;														// 0x63B8
			std::array<TESLandTexture*, 4> defQuadTexture;								// 0x63C0
			std::array<std::array<TESLandTexture*, 12>, 4> quadTextureArray;			// 0x63E0
			std::int32_t cellX;															// 0x6560
			std::int32_t cellY;															// 0x6564
			REX::Float32 baseHeight;													// 0x6568
			LoadedLandData* next;														// 0x6570
		};

		static_assert(sizeof(LoadedLandData) == 0x6578);

		~TESObjectLAND() override; // 0x00

		// members
		OBJ_LAND data;						  // 0x28
		TESObjectCELL* parentCell;			  // 0x30
		NiPointer<QueuedFile> queuedTextures; // 0x38
		LoadedLandData* loadedData;			  // 0x40
	};

	static_assert(sizeof(TESObjectLAND) == 0x48);
}
