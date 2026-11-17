#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSStreamHeader.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiTLargeArray.hpp"
#include "RE/N/NiTPointerMap.hpp"

namespace RE
{
	class NiBinaryStream;
	class NiObject;
	class NiObjectGroup;
	class NiSearchPath;

	class __declspec(novtable) NiStream
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiStream;
		inline static constexpr const auto& VTABLE = VTABLE::NiStream;

		virtual ~NiStream(); // 0x00

		// add
		auto Load(NiBinaryStream* a_inputStream) -> bool;						   // 0x01
		auto Load(char* a_buffer, std::uint64_t a_bufferSize) -> bool;			   // 0x02
		auto Load(const char* a_fileName) -> bool;								   // 0x03
		auto Save(NiBinaryStream* a_outputStream) -> bool;						   // 0x04
		auto Save(char*& a_buffer, std::uint64_t& a_bufferSize) -> bool;		   // 0x05
		auto Save(const char* a_fileName) -> bool;								   // 0x06
		auto RegisterFixedString(const BSFixedString& a_string) -> bool;		   // 0x07
		auto RegisterSaveObject(NiObject* a_object) -> bool;					   // 0x08
		void ChangeObject(NiObject* a_newObject);								   // 0x09
		auto GetLinkIDFromObject(const NiObject* a_object) const -> std::uint32_t; // 0x0A
		void SaveLinkID(const NiObject* a_object);								   // 0x0B
		auto LoadHeader() -> bool;												   // 0x0C
		void SaveHeader();														   // 0x0D
		auto LoadStream() -> bool;												   // 0x0E
		auto SaveStream() -> bool;												   // 0x0F
		void RegisterObjects();													   // 0x10
		void LoadTopLevelObjects();												   // 0x11
		void SaveTopLevelObjects();												   // 0x12
		auto LoadObject() -> bool;												   // 0x13
		auto PreSaveObjectSizeTable() -> std::uint64_t;							   // 0x14
		auto SaveObjectSizeTable(std::uint64_t a_startOffset) -> bool;			   // 0x15
		auto LoadObjectSizeTable() -> bool;										   // 0x16

		// members
		BSStreamHeader bsStreamHeader;							   // 0x008
		BSTSmallArray<NiObjectGroup*, 4> groups;				   // 0x1D0
		std::uint32_t nifFileVersion;							   // 0x200
		std::uint32_t nifFileUserDefinedVersion;				   // 0x204
		REX::StaticString<REX::W32::MAX_PATH> fileName;			   // 0x208
		bool saveLittleEndian;									   // 0x30C
		bool sourceIsLittleEndian;								   // 0x30D
		NiSearchPath* searchPath;								   // 0x310
		NiTLargeObjectArray<NiPointer<NiObject>> objects;		   // 0x318
		NiTLargePrimitiveArray<std::uint32_t> objectSizes;		   // 0x338
		NiTLargeObjectArray<NiPointer<NiObject>> topObjects;	   // 0x358
		NiTLargeObjectArray<BSFixedString> fixedStrings;		   // 0x378
		NiBinaryStream* inputStream;							   // 0x398
		NiBinaryStream* outputStream;							   // 0x3A0
		std::uint32_t linkIndex;								   // 0x3A8
		std::uint32_t linkBlockIndex;							   // 0x3AC
		NiTPointerMap<const NiObject*, std::uint32_t> registerMap; // 0x3B0
		std::uint16_t niAVObjectFlags;							   // 0x3D0
		std::uint16_t niTimeControllerFlags;					   // 0x3D2
		std::uint16_t niPropertyFlags;							   // 0x3D4
		std::uint16_t streamFlags;								   // 0x3D6
		std::uint32_t load;										   // 0x3D8
		std::uint32_t link;										   // 0x3DC
		std::uint32_t postLink;									   // 0x3E0
		REX::StaticString<260> lastLoadedRTTI;					   // 0x3E4
		std::uint32_t lastError;								   // 0x4E8
		REX::StaticString<260> lastErrorMessage;				   // 0x4EC
		REX::StaticString<REX::W32::MAX_PATH> filePath;			   // 0x5F0
	};

	static_assert(sizeof(NiStream) == 0x6F8);
}
