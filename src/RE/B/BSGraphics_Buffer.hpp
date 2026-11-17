#pragma once

#include "RE/B/BSTAtomicValue.hpp"

namespace RE
{
	class BSEventFlag;
}

namespace RE::BSGraphics
{
	class Buffer
	{
	public:
		// members
		REX::W32::ID3D11Buffer* buffer;						  // 0x00
		std::byte* data;									  // 0x08
		Buffer* next;										  // 0x10
		REX::W32::ID3D11ShaderResourceView* shaderResource;	  // 0x18
		REX::W32::ID3D11UnorderedAccessView* unorderedAccess; // 0x20
		BSEventFlag* requestEventToWait;					  // 0x28
		std::uint32_t maxDataSize;							  // 0x30
		std::uint32_t dataSize;								  // 0x34
		std::uint32_t refCount;								  // 0x38
		BSTAtomicValue<std::uint32_t> SRAcquire;			  // 0x3C
		BSTAtomicValue<std::uint32_t> UAVAcquire;			  // 0x40
		BSTAtomicValue<std::uint32_t> pendingRequests;		  // 0x44
		std::uint32_t dataOffset;							  // 0x48
		bool invalidCpuData;								  // 0x4C
		bool heapAllocated;									  // 0x4D
		volatile bool pendingCopy;							  // 0x4E
	};

	static_assert(sizeof(Buffer) == 0x50);
}
