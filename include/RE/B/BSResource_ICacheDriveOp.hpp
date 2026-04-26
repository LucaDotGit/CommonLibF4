#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"

namespace RE::BSResource
{
	class CacheDrive;

	class __declspec(novtable) ICacheDriveOp
		: public BSIntrusiveRefCounted // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSResource__ICacheDriveOp };
		inline static constexpr auto VTABLE{ VTABLE::BSResource__ICacheDriveOp };

		virtual ~ICacheDriveOp() = default; // 00

		// add
		virtual void OnValid(CacheDrive& a_cacheDrive) = 0;							 // 01
		virtual void OnInit(CacheDrive& a_cacheDrive) = 0;							 // 02
		virtual void OnPacketWrite(CacheDrive& a_cacheDrive, std::uint64_t a_v) = 0; // 03
		virtual void OnComplete(CacheDrive& a_cacheDrive) = 0;						 // 04
		virtual void OnError(CacheDrive& a_cacheDrive) = 0;							 // 05
	};
	static_assert(sizeof(ICacheDriveOp) == 0x10);
}
