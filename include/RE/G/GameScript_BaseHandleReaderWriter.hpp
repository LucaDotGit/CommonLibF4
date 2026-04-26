#pragma once

#include "RE/B/BSScript_IHandleReaderWriter.hpp"

namespace RE
{
	class BSStorage;
}

namespace RE::BSScript
{
	class IObjectHandlePolicy;
}

namespace RE::GameScript
{
	class __declspec(novtable) BaseHandleReaderWriter
		: public BSScript::IHandleReaderWriter // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__BaseHandleReaderWriter };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__BaseHandleReaderWriter };

		~BaseHandleReaderWriter() override; // 00

		// override (BSScript::IHandleReaderWriter)
		std::uint16_t GetHandleVersion() const override;														 // 01
		bool WriteHandle(BSStorage& storage, BSScript::ObjectHandle a_objectHandle) const override;				 // 02
		bool ReadHandle(const BSStorage& storage, BSScript::ObjectHandle& a_objectHandle) const override;		 // 03
		bool ReadHandleNoRemap(const BSStorage& storage, BSScript::ObjectHandle& a_objectHandle) const override; // 04

		// add
		virtual bool WriteFormID(BSStorage& storage, TESFormID a_formID) const = 0;		  // 05
		virtual bool ReadFormID(const BSStorage& storage, TESFormID& a_formID) const = 0; // 06

		// members
		BSScript::IObjectHandlePolicy* objectHandlePolicy; // 08
	};
	static_assert(sizeof(BaseHandleReaderWriter) == 0x10);
}
