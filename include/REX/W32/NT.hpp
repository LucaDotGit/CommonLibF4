#pragma once

#include "REX/W32/CORE.hpp"

namespace REX::W32
{
	struct EXCEPTION_REGISTRATION_RECORD;
	struct PEB_LDR_DATA;
	struct RTL_USER_PROCESS_PARAMETERS;

	using PS_POST_PROCESS_INIT_ROUTINE = void (*)();

	struct LIST_ENTRY
	{
		struct LIST_ENTRY* fLink;
		struct LIST_ENTRY* bLink;
	};

	struct NT_TIB
	{
		EXCEPTION_REGISTRATION_RECORD* exceptionList;
		void* stackBase;
		void* stackLimit;
		void* subSystemTib;
		union
		{
			void* fiberData;
			std::uint32_t version;
		};
		void* arbitraryUserPointer;
		struct NT_TIB* self;
	};

	struct PEB
	{
		std::array<std::byte, 2> reserved1;
		std::byte beingDebugged;
		std::array<std::byte, 1> reserved2;
		std::array<void*, 2> reserved3;
		PEB_LDR_DATA* ldr;
		RTL_USER_PROCESS_PARAMETERS* processParameters;
		std::array<void*, 3> reserved4;
		void* atlThunkSListPtr;
		void* reserved5;
		std::uint32_t reserved6;
		void* reserved7;
		std::uint32_t reserved8;
		std::uint32_t atlThunkSListPtr32;
		std::array<void*, 45> reserved9;
		std::array<std::byte, 96> reserved10;
		PS_POST_PROCESS_INIT_ROUTINE postProcessInitRoutine;
		std::array<std::byte, 128> reserved11;
		std::array<void*, 1> reserved12;
		std::uint32_t sessionID;
	};

	struct PEB_LDR_DATA
	{
		std::array<std::byte, 8> reserved1;
		std::array<void*, 3> reserved2;
		LIST_ENTRY inMemoryOrderModuleList;
	};

	struct RTL_USER_PROCESS_PARAMETERS
	{
		std::array<std::byte, 16> reserved1;
		std::array<void*, 10> reserved2;
		UNICODE_STRING imagePathName;
		UNICODE_STRING commandLine;
	};

	struct TEB
	{
		std::array<void*, 11> reserved1;
		void* threadLocalStoragePointer;
		PEB* processEnvironmentBlock;
		std::array<void*, 399> reserved2;
		std::array<std::byte, 1952> reserved3;
		std::array<void*, 64> tlsSlots;
		std::array<std::byte, 8> reserved4;
		std::array<void*, 26> reserved5;
		void* reservedForOle;
		std::array<void*, 4> reserved6;
		void* tlsExpansionSlots;
	};
}

namespace REX::W32
{
	TEB* NtCurrentTeb() noexcept;
}
