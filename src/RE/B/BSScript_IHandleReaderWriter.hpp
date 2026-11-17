#pragma once

namespace RE
{
	class BSStorage;
}

namespace RE::BSScript
{
	class __declspec(novtable) IHandleReaderWriter
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__IHandleReaderWriter;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__IHandleReaderWriter;

		virtual ~IHandleReaderWriter(); // 0x00

		// add
		virtual auto GetHandleVersion() const -> std::uint16_t = 0;											  // 0x01
		virtual auto WriteHandle(BSStorage& storage, ObjectHandle a_objectHandle) const -> bool = 0;		  // 0x02
		virtual auto ReadHandle(const BSStorage& storage, ObjectHandle& a_outObjectHandle) const -> bool = 0; // 0x03
		virtual auto ReadHandleNoRemap(const BSStorage& storage, ObjectHandle& a_outObjectHandle) const
			-> bool = 0; // 0x04
	};

	static_assert(sizeof(IHandleReaderWriter) == 0x08);
}
