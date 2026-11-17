#pragma once

namespace Scaleform::GFx
{
	class ASStringManager;

	class ASStringNode
	{
	public:
		// members
		const char* data;		  // 0x00
		ASStringManager* manager; // 0x08

		union
		{
		public:
			ASStringNode* lower;
			ASStringNode* next;
		}; // 0x10

		std::uint32_t refCount;	 // 0x18
		std::uint32_t hashFlags; // 0x1C
		std::uint32_t size;		 // 0x20
	};

	static_assert(sizeof(ASStringNode) == 0x28);
}
