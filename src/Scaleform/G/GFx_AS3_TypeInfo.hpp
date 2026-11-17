#pragma once

namespace Scaleform::GFx::AS3
{
	class TypeInfo
	{
	public:
		// members
		std::uint32_t flags;			 // 0x00
		std::uint16_t instanceSize;		 // 0x04
		std::uint16_t classMethodNum;	 // 0x06
		std::uint16_t classMemberNum;	 // 0x08
		std::uint16_t instanceMethodNum; // 0x0A
		std::uint16_t instanceMemberNum; // 0x0C
		const char* name;				 // 0x10
		const char* packageName;		 // 0x18
		TypeInfo* parent;				 // 0x20
		TypeInfo** implements;			 // 0x28
	};

	static_assert(sizeof(TypeInfo) == 0x30);
}
