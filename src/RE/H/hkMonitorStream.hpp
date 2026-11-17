#pragma once

#include "RE/H/hkPadSpu.hpp"

namespace RE
{
	class hkMonitorStream
	{
	public:
		[[nodiscard]]
		static auto GetThreadLocalIndex() noexcept -> std::uint32_t
		{
			static const auto THREAD_LOCAL_INDEX =
				REL::Relocation<std::uint32_t*>{ID::hkMonitorStream::ThreadLocalIndex};
			return *THREAD_LOCAL_INDEX;
		}

		[[nodiscard]]
		static auto GetInstance() noexcept -> hkMonitorStream*
		{
			return static_cast<hkMonitorStream*>(REX::W32::TlsGetValue(GetThreadLocalIndex()));
		}

		static void SetInstance(hkMonitorStream* a_stream) noexcept
		{
			REX::W32::TlsSetValue(GetThreadLocalIndex(), a_stream);
		}

		void Clear()
		{
			using FuncType = decltype(&hkMonitorStream::Clear);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hkMonitorStream::Clear);
			std::invoke(FUNC, this);
		}

		void Reset()
		{
			end = start;
		}

		void Resize(std::int32_t a_newSize)
		{
			using FuncType = decltype(&hkMonitorStream::Resize);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hkMonitorStream::Resize);
			std::invoke(FUNC, this, a_newSize);
		}

		// members
		hkPadSpu<char*> start;			 // 0x00
		hkPadSpu<char*> end;			 // 0x08
		hkPadSpu<char*> capacity;		 // 0x10
		hkPadSpu<char*> capacityMinus16; // 0x18
		bool isBufferAllocatedOnTheHeap; // 0x20
	};

	static_assert(sizeof(hkMonitorStream) == 0x28);
}
