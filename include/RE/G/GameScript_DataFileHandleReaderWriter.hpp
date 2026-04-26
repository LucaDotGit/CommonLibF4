#pragma once

#include "RE/G/GameScript_BaseHandleReaderWriter.hpp"

namespace RE
{
	class BSStorage;
	class TESFile;
}

namespace RE::GameScript
{
	class __declspec(novtable) DataFileHandleReaderWriter
		: public BaseHandleReaderWriter // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__DataFileHandleReaderWriter };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__DataFileHandleReaderWriter };

		~DataFileHandleReaderWriter() override; // 00

		// override (BaseHandleReaderWriter)
		bool WriteFormID(BSStorage& storage, TESFormID a_formID) const override;	   // 05
		bool ReadFormID(const BSStorage& storage, TESFormID& a_formID) const override; // 06

		// members
		TESFile* file; // 10
	};
	static_assert(sizeof(DataFileHandleReaderWriter) == 0x18);
}
