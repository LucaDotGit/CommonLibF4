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
		REX::W32::ID3D11Buffer* buffer;						  // 00
		std::byte* data;									  // 08
		Buffer* next;										  // 10
		REX::W32::ID3D11ShaderResourceView* shaderResource;	  // 18
		REX::W32::ID3D11UnorderedAccessView* unorderedAccess; // 20
		BSEventFlag* requestEventToWait;					  // 28
		std::uint32_t maxDataSize;							  // 30
		std::uint32_t dataSize;								  // 34
		std::uint32_t refCount;								  // 38
		BSTAtomicValue<std::uint32_t> SRAcquire;			  // 3C
		BSTAtomicValue<std::uint32_t> UAVAcquire;			  // 40
		BSTAtomicValue<std::uint32_t> pendingRequests;		  // 44
		std::uint32_t dataOffset;							  // 48
		bool invalidCpuData;								  // 4C
		bool heapAllocated;									  // 4D
		volatile bool pendingCopy;							  // 4E
	};
	static_assert(sizeof(Buffer) == 0x50);
}
