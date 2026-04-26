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
		inline static constexpr auto RTTI{ RTTI::BSScript__IHandleReaderWriter };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__IHandleReaderWriter };

		virtual ~IHandleReaderWriter(); // 00

		// add
		virtual std::uint16_t GetHandleVersion() const = 0;												  // 01
		virtual bool WriteHandle(BSStorage& storage, ObjectHandle a_objectHandle) const = 0;			  // 02
		virtual bool ReadHandle(const BSStorage& storage, ObjectHandle& a_objectHandle) const = 0;		  // 03
		virtual bool ReadHandleNoRemap(const BSStorage& storage, ObjectHandle& a_objectHandle) const = 0; // 04
	};
	static_assert(sizeof(IHandleReaderWriter) == 0x08);
}
