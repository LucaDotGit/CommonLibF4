#pragma once

#include "RE/B/BSResource_ErrorCode.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BSResource
{
	class AsyncStream;
	class Info;
	class LocationTraverser;
	class Stream;

	class __declspec(novtable) Location
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSResource__Location };
		inline static constexpr auto VTABLE{ VTABLE::BSResource__Location };

		virtual ~Location(); // 00

		// add
		virtual ErrorCode DoMount();																																			   // 01 - { return ErrorCode::kNone; }
		virtual void DoUnmount();																																				   // 02 - { return; }
		virtual ErrorCode DoCreateStream(const char* a_path, BSTSmartPointer<Stream>& a_result, Location*& a_location, bool a_writable, LocationTraverser* a_traverser) = 0;	   // 03
		virtual ErrorCode DoCreateAsyncStream(const char* a_path, BSTSmartPointer<AsyncStream>& a_result, Location*& a_location, bool a_writable, LocationTraverser* a_traverser); // 04 - { return ErrorCode::kUnsupported; }
		virtual ErrorCode DoTraversePrefix(const char* a_prefix, LocationTraverser& a_traverser) = 0;																			   // 05
		virtual ErrorCode DoGetInfo(const char* a_path, Info& a_result, LocationTraverser* a_traverser);																		   // 07 - { return ErrorCode::kUnsupported; }
		virtual ErrorCode DoGetInfo(const char* a_path, Info& a_result, Location*& a_location);																					   // 06 - { return ErrorCode::kUnsupported; }
		virtual ErrorCode DoDelete(const char* a_path);																															   // 08 - { return ErrorCode::kUnsupported; }
		[[nodiscard]] virtual const char* DoGetName() const;																													   // 09 - { return nullptr; }
		[[nodiscard]] virtual std::uint32_t DoQBufferHint() const;																												   // 0A - { return 0x10000; }
		[[nodiscard]] virtual std::uint32_t DoGetMinimumAsyncPacketSize() const;																								   // 0B - { return 0x10000; }

		GAME_HEAP_REDEFINE_NEW(Location);

		// members
		bool mounted; // 08
	};
	static_assert(sizeof(Location) == 0x10);
}
