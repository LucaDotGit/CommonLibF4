#pragma once

#include "RE/G/GameScript_BaseHandleReaderWriter.hpp"

namespace RE
{
	class BSStorage;
	class TESFile;
}

namespace RE::GameScript
{
	class __declspec(novtable) DataFileHandleReaderWriter : public BaseHandleReaderWriter // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__DataFileHandleReaderWriter;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__DataFileHandleReaderWriter;

		~DataFileHandleReaderWriter() override; // 0x00

		// override (BaseHandleReaderWriter)
		auto WriteFormID(BSStorage& storage, TESFormID a_formID) const -> bool override;		  // 0x05
		auto ReadFormID(const BSStorage& storage, TESFormID& a_outFormID) const -> bool override; // 0x06

		// members
		TESFile* file; // 0x10
	};

	static_assert(sizeof(DataFileHandleReaderWriter) == 0x18);
}
