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
		inline static constexpr const auto& RTTI = RTTI::BSResource__Location;
		inline static constexpr const auto& VTABLE = VTABLE::BSResource__Location;

		virtual ~Location(); // 0x00

		// add
		virtual auto DoMount() -> ErrorCode; // 0x01 - { return ErrorCode::None; }
		virtual void DoUnmount();			 // 0x02 - { return; }
		virtual auto DoCreateStream(
			const char* a_path,
			BSTSmartPointer<Stream>& a_result,
			Location*& a_location,
			bool a_writable,
			LocationTraverser* a_traverser) -> ErrorCode = 0; // 0x03
		virtual auto DoCreateAsyncStream(
			const char* a_path,
			BSTSmartPointer<AsyncStream>& a_result,
			Location*& a_location,
			bool a_writable,
			LocationTraverser* a_traverser) -> ErrorCode; // 0x04 - { return ErrorCode::Unsupported; }
		virtual auto DoTraversePrefix(const char* a_prefix, LocationTraverser& a_traverser) -> ErrorCode = 0; // 0x05
		virtual auto DoGetInfo(
			const char* a_path,
			Info& a_result,
			LocationTraverser* a_traverser) -> ErrorCode; // 0x07 - { return ErrorCode::Unsupported; }
		virtual auto DoGetInfo(
			const char* a_path,
			Info& a_result,
			Location*& a_location) -> ErrorCode;				// 0x06 - { return ErrorCode::Unsupported; }
		virtual auto DoDelete(const char* a_path) -> ErrorCode; // 0x08 - { return ErrorCode::Unsupported; }
		[[nodiscard]]
		virtual auto DoGetName() const -> const char*; // 0x09 - { return nullptr; }
		[[nodiscard]]
		virtual auto DoQBufferHint() const -> std::uint32_t; // 0x0A - { return 0x10000; }
		[[nodiscard]]
		virtual auto DoGetMinimumAsyncPacketSize() const -> std::uint32_t; // 0x0B - { return 0x10000; }

		GAME_HEAP_REDEFINE_NEW(Location);

		// members
		bool mounted; // 0x08
	};

	static_assert(sizeof(Location) == 0x10);
}
