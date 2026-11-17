#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"

namespace RE::BSResource
{
	class CacheDrive;

	class __declspec(novtable) ICacheDriveOp : public BSIntrusiveRefCounted // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSResource__ICacheDriveOp;
		inline static constexpr const auto& VTABLE = VTABLE::BSResource__ICacheDriveOp;

		virtual ~ICacheDriveOp() = default; // 0x00

		// add
		virtual void OnValid(CacheDrive& a_cacheDrive) = 0;							 // 0x01
		virtual void OnInit(CacheDrive& a_cacheDrive) = 0;							 // 0x02
		virtual void OnPacketWrite(CacheDrive& a_cacheDrive, std::uint64_t a_v) = 0; // 0x03
		virtual void OnComplete(CacheDrive& a_cacheDrive) = 0;						 // 0x04
		virtual void OnError(CacheDrive& a_cacheDrive) = 0;							 // 0x05
	};

	static_assert(sizeof(ICacheDriveOp) == 0x10);
}
