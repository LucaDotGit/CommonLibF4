#pragma once

#include "RE/H/hkPadSpu.hpp"

namespace RE
{
	class hkMonitorStream
	{
	public:
		[[nodiscard]] static hkMonitorStream* GetSingleton()
		{
			static const auto THREAD_LOCAL_INSTANCE = REL::Relocation<std::uint32_t*>{ ID::hkMonitorStream::ThreadLocalInstance };
			return reinterpret_cast<hkMonitorStream*>(REX::W32::TlsGetValue(*THREAD_LOCAL_INSTANCE));
		}

		void Clear()
		{
			using FuncType = decltype(&hkMonitorStream::Clear);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::hkMonitorStream::Clear };
			std::invoke(FUNC, this);
		}

		void Reset()
		{
			end = start;
		}

		void Resize(std::int32_t a_newSize)
		{
			using FuncType = decltype(&hkMonitorStream::Resize);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::hkMonitorStream::Resize };
			std::invoke(FUNC, this, a_newSize);
		}

		// members
		hkPadSpu<char*> start;			 // 00
		hkPadSpu<char*> end;			 // 08
		hkPadSpu<char*> capacity;		 // 10
		hkPadSpu<char*> capacityMinus16; // 18
		bool isBufferAllocatedOnTheHeap; // 20
	};
	static_assert(sizeof(hkMonitorStream) == 0x28);
}
