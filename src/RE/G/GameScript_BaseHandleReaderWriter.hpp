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
	class __declspec(novtable) BaseHandleReaderWriter : public BSScript::IHandleReaderWriter // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__BaseHandleReaderWriter;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__BaseHandleReaderWriter;

		~BaseHandleReaderWriter() override; // 0x00

		// override (BSScript::IHandleReaderWriter)
		auto GetHandleVersion() const -> std::uint16_t override;											// 0x01
		auto WriteHandle(BSStorage& storage, BSScript::ObjectHandle a_objectHandle) const -> bool override; // 0x02
		auto ReadHandle(const BSStorage& storage, BSScript::ObjectHandle& a_outObjectHandle) const
			-> bool override; // 0x03
		auto ReadHandleNoRemap(const BSStorage& storage, BSScript::ObjectHandle& a_outObjectHandle) const
			-> bool override; // 0x04

		// add
		virtual auto WriteFormID(BSStorage& storage, TESFormID a_formID) const -> bool = 0;			 // 0x05
		virtual auto ReadFormID(const BSStorage& storage, TESFormID& a_outFormID) const -> bool = 0; // 0x06

		// members
		BSScript::IObjectHandlePolicy* objectHandlePolicy; // 0x08
	};

	static_assert(sizeof(BaseHandleReaderWriter) == 0x10);
}
