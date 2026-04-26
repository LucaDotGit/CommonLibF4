#pragma once

#include "REX/W32/CORE.hpp"

namespace REX::W32
{
	enum CP : std::int32_t
	{
		CP_UTF8 = 65001
	};

	enum DLL : std::int32_t
	{
		DLL_PROCESS_ATTACH = 1,
		DLL_PROCESS_DETACH = 0,
		DLL_THREAD_ATTACH = 2,
		DLL_THREAD_DETACH = 3
	};

	enum FILE_ATTRIBUTE : std::uint32_t
	{
		FILE_ATTRIBUTE_READONLY = 0x1,
		FILE_ATTRIBUTE_HIDDEN = 0x2,
		FILE_ATTRIBUTE_SYSTEM = 0x4,
		FILE_ATTRIBUTE_DIRECTORY = 0x10,
		FILE_ATTRIBUTE_ARCHIVE = 0x20,
		FILE_ATTRIBUTE_DEVICE = 0x40,
		FILE_ATTRIBUTE_NORMAL = 0x80,
		FILE_ATTRIBUTE_TEMPORARY = 0x100,
		FILE_ATTRIBUTE_SPARSE_FILE = 0x200,
		FILE_ATTRIBUTE_REPARSE_POINT = 0x400,
		FILE_ATTRIBUTE_COMPRESSED = 0x800,
		FILE_ATTRIBUTE_OFFLINE = 0x1000,
		FILE_ATTRIBUTE_NOT_CONTENT_INDEXED = 0x2000,
		FILE_ATTRIBUTE_ENCRYPTED = 0x4000,
		FILE_ATTRIBUTE_INTEGRITY_STREAM = 0x8000,
		FILE_ATTRIBUTE_VIRTUAL = 0x10000,
		FILE_ATTRIBUTE_NO_SCRUB_DATA = 0x20000,
		FILE_ATTRIBUTE_EA = 0x40000,
		FILE_ATTRIBUTE_PINNED = 0x80000,
		FILE_ATTRIBUTE_UNPINNED = 0x100000,
		FILE_ATTRIBUTE_RECALL_ON_OPEN = 0x40000,
		FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS = 0x400000
	};

	enum CREATE : std::int32_t
	{
		CREATE_NEW = 1,
		CREATE_ALWAYS = 2,
		OPEN_EXISTING = 3,
		OPEN_ALWAYS = 4,
		TRUNCATE_EXISTING = 5
	};

	enum STANDARD_RIGHTS : std::int32_t
	{
		STANDARD_RIGHTS_REQUIRED = 0xF0000,
		STANDARD_RIGHTS_ALL = 0x1F0000
	};

	enum SECTION : std::int32_t
	{
		SECTION_QUERY = 0x1,
		SECTION_MAP_WRITE = 0x2,
		SECTION_MAP_READ = 0x4,
		SECTION_MAP_EXECUTE = 0x8,
		SECTION_EXTEND_SIZE = 0x10,
		SECTION_MAP_EXECUTE_EXPLICIT = 0x20,

		SECTION_ALL_ACCESS = STANDARD_RIGHTS_REQUIRED |
							 SECTION_QUERY |
							 SECTION_MAP_WRITE |
							 SECTION_MAP_READ |
							 SECTION_MAP_EXECUTE |
							 SECTION_EXTEND_SIZE
	};

	enum FILE_MAP : std::uint32_t
	{
		FILE_MAP_ALL_ACCESS = SECTION_ALL_ACCESS,
		FILE_MAP_COPY = 0x1,
		FILE_MAP_WRITE = 0x2,
		FILE_MAP_READ = 0x4,
		FILE_MAP_EXECUTE = 0x20,
		FILE_MAP_LARGE_PAGES = 0x20000000,
		FILE_MAP_TARGETS_INVALID = 0x40000000,
		FILE_MAP_RESERVE = 0x80000000
	};

	enum GENERIC : std::uint32_t
	{
		GENERIC_READ = 0x80000000,
		GENERIC_WRITE = 0x40000000,
		GENERIC_EXECUTE = 0x20000000,
		GENERIC_ALL = 0x10000000
	};

	enum FILE_SHARE : std::uint32_t
	{
		FILE_SHARE_READ = 0x1,
		FILE_SHARE_WRITE = 0x2,
		FILE_SHARE_DELETE = 0x4
	};

	enum LCMAP : std::uint32_t
	{
		LCMAP_LOWERCASE = 0x100,
		LCMAP_UPPERCASE = 0x200,
		LCMAP_TITLECASE = 0x300,
		LCMAP_SORTKEY = 0x400,
		LCMAP_BYTEREV = 0x800,
		LCMAP_HIRAGANA = 0x100000,
		LCMAP_KATAKANA = 0x200000,
		LCMAP_HALFWIDTH = 0x400000,
		LCMAP_FULLWIDTH = 0x800000,
		LCMAP_LINGUISTIC_CASING = 0x1000000,
		LCMAP_SIMPLIFIED_CHINESE = 0x2000000,
		LCMAP_TRADITIONAL_CHINESE = 0x4000000
	};

	inline constexpr auto* LOCALE_NAME_USER_DEFAULT{ static_cast<const wchar_t*>(nullptr) };
	inline constexpr auto LOCALE_NAME_INVARIANT{ L""sv };
	inline constexpr auto LOCALE_NAME_SYSTEM_DEFAULT{ L"!x-sys-default-locale"sv };

	enum MEM : std::uint32_t
	{
		MEM_COMMIT = 0x1000,
		MEM_RESERVE = 0x2000,
		MEM_DECOMMIT = 0x4000,
		MEM_RELEASE = 0x8000,
		MEM_FREE = 0x10000,
		MEM_RESET = 0x80000,
		MEM_RESET_UNDO = 0x1000000
	};

	enum PAGE : std::uint32_t
	{
		PAGE_NOACCESS = 0x1,
		PAGE_READONLY = 0x2,
		PAGE_READWRITE = 0x4,
		PAGE_WRITECOPY = 0x8,
		PAGE_EXECUTE = 0x10,
		PAGE_EXECUTE_READ = 0x20,
		PAGE_EXECUTE_READWRITE = 0x40
	};

	enum IMAGE_DIRECTORY_ENTRY : std::int32_t
	{
		IMAGE_DIRECTORY_ENTRY_EXPORT = 0,
		IMAGE_DIRECTORY_ENTRY_IMPORT = 1,
		IMAGE_DIRECTORY_ENTRY_RESOURCE = 2,
		IMAGE_DIRECTORY_ENTRY_EXCEPTION = 3,
		IMAGE_DIRECTORY_ENTRY_SECURITY = 4,
		IMAGE_DIRECTORY_ENTRY_BASERELOC = 5,
		IMAGE_DIRECTORY_ENTRY_DEBUG = 6,
		IMAGE_DIRECTORY_ENTRY_ARCHITECTURE = 7,
		IMAGE_DIRECTORY_ENTRY_GLOBALPTR = 8,
		IMAGE_DIRECTORY_ENTRY_TLS = 9,
		IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG = 10,
		IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT = 11,
		IMAGE_DIRECTORY_ENTRY_IAT = 12,
		IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT = 13,
		IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR = 14,
		IMAGE_NUMBEROF_DIRECTORY_ENTRIES = 16
	};

	inline static constexpr auto IMAGE_DOS_SIGNATURE{ 0x5A4Dui32 };
	inline static constexpr auto IMAGE_NT_SIGNATURE{ 0x00004550ui32 };
	inline static constexpr auto IMAGE_NT_OPTIONAL_HDR32_MAGIC{ 0x10Bui32 };
	inline static constexpr auto IMAGE_NT_OPTIONAL_HDR64_MAGIC{ 0x20Bui32 };

	enum IMAGE_ORDINAL_FLAG : std::uint64_t
	{
		IMAGE_ORDINAL_FLAG32 = 0x80000000,
		IMAGE_ORDINAL_FLAG64 = 0x8000000000000000
	};

	enum IMAGE_SCN : std::uint32_t
	{
		IMAGE_SCN_MEM_SHARED = 0x10000000,
		IMAGE_SCN_MEM_EXECUTE = 0x20000000,
		IMAGE_SCN_MEM_READ = 0x40000000,
		IMAGE_SCN_MEM_WRITE = 0x80000000
	};

	inline static constexpr auto IMAGE_SIZEOF_SECTION_HEADER{ 40ui32 };
	inline static constexpr auto IMAGE_SIZEOF_SHORT_NAME{ 8ui32 };

	enum PROCESS : std::uint32_t
	{
		DEBUG_PROCESS = 0x1,
		DEBUG_ONLY_THIS_PROCESS = 0x2,
		CREATE_SUSPENDED = 0x4,
		DETACHED_PROCESS = 0x8,
		CREATE_NEW_CONSOLE = 0x10,
		NORMAL_PRIORITY_CLASS = 0x20,
		IDLE_PRIORITY_CLASS = 0x40,
		HIGH_PRIORITY_CLASS = 0x80,
		REALTIME_PRIORITY_CLASS = 0x100,
		CREATE_NEW_PROCESS_GROUP = 0x200,
		CREATE_UNICODE_ENVIRONMENT = 0x400,
		CREATE_FORCEDOS = 0x2000,
		BELOW_NORMAL_PRIORITY_CLASS = 0x4000,
		ABOVE_NORMAL_PRIORITY_CLASS = 0x8000,
		INHERIT_PARENT_AFFINITY = 0x10000,
		CREATE_PROTECTED_PROCESS = 0x40000,
		EXTENDED_STARTUPINFO_PRESENT = 0x80000,
		PROCESS_MODE_BACKGROUND_BEGIN = 0x100000,
		PROCESS_MODE_BACKGROUND_END = 0x200000,
		CREATE_SECURE_PROCESS = 0x400000,
		CREATE_BREAKAWAY_FROM_JOB = 0x1000000,
		CREATE_PRESERVE_CODE_AUTHZ_LEVEL = 0x2000000,
		CREATE_DEFAULT_ERROR_MODE = 0x4000000,
		CREATE_NO_WINDOW = 0x8000000
	};

	enum WAIT : std::uint32_t
	{
		WAIT_OBJECT_0 = 0x0,
		WAIT_ABANDONED = 0x80,
		WAIT_TIMEOUT = 0x102,

		WAIT_FAILED = std::numeric_limits<std::uint32_t>::max()
	};
}

namespace REX::W32
{
	struct IMAGE_DATA_DIRECTORY
	{
		std::uint32_t virtualAddress;
		std::uint32_t size;
	};
	static_assert(sizeof(IMAGE_DATA_DIRECTORY) == 0x08);

	struct IMAGE_DOS_HEADER
	{
		std::uint16_t magic;
		std::uint16_t cblp;
		std::uint16_t cp;
		std::uint16_t crlc;
		std::uint16_t cparhdr;
		std::uint16_t minalloc;
		std::uint16_t maxalloc;
		std::uint16_t ss;
		std::uint16_t sp;
		std::uint16_t csum;
		std::uint16_t ip;
		std::uint16_t cs;
		std::uint16_t lfarlc;
		std::uint16_t ovno;
		std::array<std::uint16_t, 4> res;
		std::uint16_t oemid;
		std::uint16_t oeminfo;
		std::array<std::uint16_t, 10> res2;
		std::int32_t lfanew;
	};
	static_assert(sizeof(IMAGE_DOS_HEADER) == 0x40);

	struct IMAGE_FILE_HEADER
	{
		std::uint16_t machine;
		std::uint16_t sectionCount;
		std::uint32_t timeDateStamp;
		std::uint32_t symbolTablePtr;
		std::uint32_t symbolCount;
		std::uint16_t optionalHeaderSize;
		std::uint16_t characteristics;
	};
	static_assert(sizeof(IMAGE_FILE_HEADER) == 0x14);

	struct IMAGE_IMPORT_BY_NAME
	{
		std::uint16_t hint;
		std::array<char, 1> name;
	};
	static_assert(sizeof(IMAGE_IMPORT_BY_NAME) == 0x04);

	struct IMAGE_IMPORT_DESCRIPTOR
	{
		union
		{
			std::uint32_t characteristics;
			std::uint32_t firstThunkOriginal;
		};

		std::uint32_t timeDateStamp;
		std::uint32_t forwarderChain;
		std::uint32_t name;
		std::uint32_t firstThunk;
	};
	static_assert(sizeof(IMAGE_IMPORT_DESCRIPTOR) == 0x14);

	struct IMAGE_OPTIONAL_HEADER64
	{
		std::uint16_t magic;
		std::uint8_t linkerVersionMajor;
		std::uint8_t linkerVersionMinor;
		std::uint32_t codeSize;
		std::uint32_t initializedDataSize;
		std::uint32_t uninitializedDataSize;
		std::uint32_t entryPointAddress;
		std::uint32_t codeBase;
		std::uint64_t imageBase;
		std::uint32_t sectionAlignment;
		std::uint32_t fileAlignment;
		std::uint16_t osVersionMajor;
		std::uint16_t osVersionMinor;
		std::uint16_t imageVersionMajor;
		std::uint16_t imageVersionMinor;
		std::uint16_t subsystemVersionMajor;
		std::uint16_t subsystemVersionMinor;
		std::uint32_t win32Version;
		std::uint32_t imageSize;
		std::uint32_t headersSize;
		std::uint32_t checksum;
		std::uint16_t subsystem;
		std::uint16_t dllCharacteristics;
		std::uint64_t stackReserveSize;
		std::uint64_t stackCommitSize;
		std::uint64_t heapReserveSize;
		std::uint64_t heapCommitSize;
		std::uint32_t loaderFlags;
		std::uint32_t rvaAndSizesCount;
		std::array<IMAGE_DATA_DIRECTORY, IMAGE_NUMBEROF_DIRECTORY_ENTRIES> dataDirectory;
	};
	static_assert(sizeof(IMAGE_OPTIONAL_HEADER64) == 0xF0);

	struct IMAGE_NT_HEADERS64
	{
		std::uint32_t signature;
		IMAGE_FILE_HEADER fileHeader;
		IMAGE_OPTIONAL_HEADER64 optionalHeader;
	};
	static_assert(sizeof(IMAGE_NT_HEADERS64) == 0x108);

	struct IMAGE_SECTION_HEADER
	{
		std::array<std::uint8_t, IMAGE_SIZEOF_SHORT_NAME> name;
		union
		{
			std::uint32_t physicalAddress;
			std::uint32_t virtualSize;
		};
		std::uint32_t virtualAddress;
		std::uint32_t rawDataSize;
		std::uint32_t rawDataPtr;
		std::uint32_t relocationsPtr;
		std::uint32_t lineNumbersPtr;
		std::uint16_t relocationsCount;
		std::uint16_t lineNumbersCount;
		std::uint32_t characteristics;
	};
	static_assert(sizeof(IMAGE_SECTION_HEADER) == 0x28);

	struct IMAGE_THUNK_DATA64
	{
		union
		{
			std::uint64_t forwarderString;
			std::uint64_t function;
			std::uint64_t ordinal;
			std::uint64_t address;
		};
	};
	static_assert(sizeof(IMAGE_THUNK_DATA64) == 0x08);

	struct MEMORY_BASIC_INFORMATION
	{
		void* baseAddress;
		void* allocationBase;
		std::uint32_t allocationProtect;
		std::uint16_t partitionID;
		std::size_t regionSize;
		std::uint32_t state;
		std::uint32_t protect;
		std::uint32_t type;
	};
	static_assert(sizeof(MEMORY_BASIC_INFORMATION) == 0x30);

	struct NLSVERSIONINFO
	{
		std::uint32_t nlsVersionInfoSize;
		std::uint32_t nlsVersion;
		std::uint32_t definedVersion;
		std::uint32_t effectiveID;
		GUID guidCustomVersion;
	};
	static_assert(sizeof(NLSVERSIONINFO) == 0x20);

	struct PROCESS_INFORMATION
	{
		void* process;
		void* thread;
		std::uint32_t processID;
		std::uint32_t threadID;
	};
	static_assert(sizeof(PROCESS_INFORMATION) == 0x18);

	struct SRWLOCK
	{
		void* ptr;
	};
	static_assert(sizeof(SRWLOCK) == 0x08);

	struct STARTUPINFOA
	{
		std::uint32_t size;
		char* reserved0;
		char* desktop;
		char* title;
		std::uint32_t x;
		std::uint32_t y;
		std::uint32_t xSize;
		std::uint32_t ySize;
		std::uint32_t xCountChars;
		std::uint32_t yCountChars;
		std::uint32_t fillAttribute;
		std::uint32_t flags;
		std::uint16_t showWindow;
		std::uint16_t reserved1;
		std::uint8_t* reserved2;
		void* stdIn;
		void* stdOut;
		void* stdErr;
	};
	static_assert(sizeof(STARTUPINFOA) == 0x68);

	struct STARTUPINFOW
	{
		std::uint32_t size;
		wchar_t* reserved0;
		wchar_t* desktop;
		wchar_t* title;
		std::uint32_t x;
		std::uint32_t y;
		std::uint32_t xSize;
		std::uint32_t ySize;
		std::uint32_t xCountChars;
		std::uint32_t yCountChars;
		std::uint32_t fillAttribute;
		std::uint32_t flags;
		std::uint16_t showWindow;
		std::uint16_t reserved1;
		std::uint8_t* reserved2;
		void* stdIn;
		void* stdOut;
		void* stdErr;
	};
	static_assert(sizeof(STARTUPINFOW) == 0x68);

	struct SYSTEM_INFO
	{
		union
		{
			std::uint32_t oemID;
			struct
			{
				std::uint16_t processorArch;
				std::uint16_t reserved;
			};
		};
		std::uint32_t pageSize;
		void* appAddressMin;
		void* appAddressMax;
		std::uintptr_t processorActiveMask;
		std::uint32_t processorCount;
		std::uint32_t processorType;
		std::uint32_t allocationGranularity;
		std::uint16_t processorLevel;
		std::uint16_t processorRevision;
	};
	static_assert(sizeof(SYSTEM_INFO) == 0x30);

	struct WIN32_FIND_DATAA
	{
		std::uint32_t fileAttributes;
		FILETIME creationTime;
		FILETIME lastAccessTime;
		FILETIME lastWriteTime;
		std::uint32_t fileSizeHigh;
		std::uint32_t fileSizeLow;
		std::uint32_t reserved0;
		std::uint32_t reserved1;
		std::array<char, MAX_PATH> fileName;
		std::array<char, 14> fileNameAlt;
	};
	static_assert(sizeof(WIN32_FIND_DATAA) == 0x140);

	struct WIN32_FIND_DATAW
	{
		std::uint32_t fileAttributes;
		FILETIME creationTime;
		FILETIME lastAccessTime;
		FILETIME lastWriteTime;
		std::uint32_t fileSizeHigh;
		std::uint32_t fileSizeLow;
		std::uint32_t reserved0;
		std::uint32_t reserved1;
		std::array<wchar_t, MAX_PATH> fileName;
		std::array<wchar_t, 14> fileNameAlt;
	};
	static_assert(sizeof(WIN32_FIND_DATAW) == 0x250);
}

namespace REX::W32
{
	using THREAD_START_ROUTINE = std::uint32_t(void* a_param);
}

namespace REX::W32
{
	void AcquireSRWLockShared(SRWLOCK* a_lock) noexcept;
	void AcquireSRWLockExclusive(SRWLOCK* a_lock) noexcept;
	bool CloseHandle(HANDLE a_handle) noexcept;
	HANDLE CreateFileA(const char* a_fileName, std::uint32_t a_desiredAccess, std::uint32_t a_shareMode, SECURITY_ATTRIBUTES* a_attributes, std::uint32_t a_creationDisposition, std::uint32_t a_flags, HANDLE a_templateFile) noexcept;
	HANDLE CreateFileW(const wchar_t* a_fileName, std::uint32_t a_desiredAccess, std::uint32_t a_shareMode, SECURITY_ATTRIBUTES* a_attributes, std::uint32_t a_creationDisposition, std::uint32_t a_flags, HANDLE a_templateFile) noexcept;
	HANDLE CreateFileMappingA(HANDLE a_file, SECURITY_ATTRIBUTES* a_attributes, std::uint32_t a_protect, std::uint32_t a_maxSizeHigh, std::uint32_t a_maxSizeLow, const char* a_name) noexcept;
	HANDLE CreateFileMappingW(HANDLE a_file, SECURITY_ATTRIBUTES* a_attributes, std::uint32_t a_protect, std::uint32_t a_maxSizeHigh, std::uint32_t a_maxSizeLow, const wchar_t* a_name) noexcept;
	bool CreateProcessA(const char* a_name, char* a_cmd, SECURITY_ATTRIBUTES* a_procAttr, SECURITY_ATTRIBUTES* a_threadAttr, bool a_inheritHandles, std::uint32_t a_flags, void* a_env, const char* a_curDir, STARTUPINFOA* a_startInfo, PROCESS_INFORMATION* a_procInfo) noexcept;
	bool CreateProcessW(const wchar_t* a_name, wchar_t* a_cmd, SECURITY_ATTRIBUTES* a_procAttr, SECURITY_ATTRIBUTES* a_threadAttr, bool a_inheritHandles, std::uint32_t a_flags, void* a_env, const wchar_t* a_curDir, STARTUPINFOW* a_startInfo, PROCESS_INFORMATION* a_procInfo) noexcept;
	HANDLE CreateRemoteThread(HANDLE a_process, SECURITY_ATTRIBUTES* a_threadAttr, std::size_t a_stackSize, THREAD_START_ROUTINE* a_startAddr, void* a_param, std::uint32_t a_flags, std::uint32_t* a_threadID);
	HANDLE CreateSemaphoreA(SECURITY_ATTRIBUTES* a_semaphoreAttr, std::int32_t a_initCount, std::int32_t a_maxCount, const char* a_name) noexcept;
	HANDLE CreateThread(SECURITY_ATTRIBUTES* a_threadAttr, std::size_t a_stackSize, THREAD_START_ROUTINE* a_startAddr, void* a_param, std::uint32_t a_flags, std::uint32_t* a_threadID);
	void DebugBreak() noexcept;
	void DebugBreakProcess(HANDLE a_process) noexcept;
	void DeleteCriticalSection(CRITICAL_SECTION* a_criticalSection) noexcept;
	void EnterCriticalSection(CRITICAL_SECTION* a_criticalSection) noexcept;
	[[noreturn]] void ExitProcess(std::uint32_t a_exitCode) noexcept;
	std::uint32_t ExpandEnvironmentStringsA(const char* a_src, char* a_dst, std::uint32_t a_dstLen) noexcept;
	std::uint32_t ExpandEnvironmentStringsW(const wchar_t* a_src, wchar_t* a_dst, std::uint32_t a_dstLen) noexcept;
	bool FindClose(HANDLE a_file) noexcept;
	HANDLE FindFirstFileA(const char* a_name, WIN32_FIND_DATAA* a_data) noexcept;
	HANDLE FindFirstFileW(const wchar_t* a_name, WIN32_FIND_DATAW* a_data) noexcept;
	bool FindNextFileA(HANDLE a_file, WIN32_FIND_DATAA* a_data) noexcept;
	bool FindNextFileW(HANDLE a_file, WIN32_FIND_DATAW* a_data) noexcept;
	bool FlushInstructionCache(HANDLE a_process, const void* a_baseAddr, std::size_t a_size) noexcept;
	bool FreeLibrary(HMODULE a_module) noexcept;
	bool GetComputerNameA(char* a_buffer, std::uint32_t* a_size) noexcept;
	bool GetComputerNameW(wchar_t* a_buffer, std::uint32_t* a_size) noexcept;
	std::uint32_t GetCurrentDirectoryA(std::uint32_t a_size, char* a_buffer) noexcept;
	std::uint32_t GetCurrentDirectoryW(std::uint32_t a_size, wchar_t* a_buffer) noexcept;
	HMODULE GetCurrentModule() noexcept;
	HANDLE GetCurrentProcess() noexcept;
	THREAD_ID GetCurrentThreadId() noexcept;
	std::uint32_t GetEnvironmentVariableA(const char* a_name, char* a_buffer, std::uint32_t a_bufLen) noexcept;
	std::uint32_t GetEnvironmentVariableW(const wchar_t* a_name, wchar_t* a_buffer, std::uint32_t a_bufLen) noexcept;
	bool GetFileSizeEx(HANDLE a_file, std::int64_t* a_fileSize) noexcept;
	ERROR_CODE GetLastError() noexcept;
	std::uint32_t GetModuleFileNameA(HMODULE a_module, char* a_name, std::uint32_t a_nameLen) noexcept;
	std::uint32_t GetModuleFileNameW(HMODULE a_module, wchar_t* a_name, std::uint32_t a_nameLen) noexcept;
	HMODULE GetModuleHandleA(const char* a_name) noexcept;
	HMODULE GetModuleHandleW(const wchar_t* a_name) noexcept;
	std::uint32_t GetPrivateProfileIntA(const char* a_app, const char* a_key, std::int32_t a_default, const char* a_name) noexcept;
	std::uint32_t GetPrivateProfileIntW(const wchar_t* a_app, const wchar_t* a_key, std::int32_t a_default, const wchar_t* a_name) noexcept;
	std::uint32_t GetPrivateProfileStringA(const char* a_app, const char* a_key, const char* a_default, char* a_buffer, std::uint32_t a_bufLen, const char* a_name) noexcept;
	std::uint32_t GetPrivateProfileStringW(const wchar_t* a_app, const wchar_t* a_key, const wchar_t* a_default, wchar_t* a_buffer, std::uint32_t a_bufLen, const wchar_t* a_name) noexcept;
	void* GetProcAddress(HMODULE a_module, const char* a_name) noexcept;
	void GetSystemInfo(SYSTEM_INFO* a_info) noexcept;
	bool IMAGE_SNAP_BY_ORDINAL64(std::uint64_t a_ordinal) noexcept;
	IMAGE_SECTION_HEADER* IMAGE_FIRST_SECTION(const IMAGE_NT_HEADERS64* a_header) noexcept;
	void InitializeCriticalSection(CRITICAL_SECTION* a_criticalSection) noexcept;
	bool InitializeCriticalSectionAndSpinCount(CRITICAL_SECTION* a_criticalSection, std::uint32_t a_spinCount) noexcept;
	void InitializeSRWLock(SRWLOCK* a_lock) noexcept;
	std::int32_t InterlockedAnd(volatile std::int32_t* a_target, std::int32_t a_value) noexcept;
	std::int8_t InterlockedAnd8(volatile std::int8_t* a_target, std::int8_t a_value) noexcept;
	std::int16_t InterlockedAnd16(volatile std::int16_t* a_target, std::int16_t a_value) noexcept;
	std::int64_t InterlockedAnd64(volatile std::int64_t* a_target, std::int64_t a_value) noexcept;
	std::int32_t InterlockedDecrement(volatile std::int32_t* a_target) noexcept;
	std::int16_t InterlockedDecrement16(volatile std::int16_t* a_target) noexcept;
	std::int64_t InterlockedDecrement64(volatile std::int64_t* a_target) noexcept;
	std::int32_t InterlockedCompareExchange(volatile std::int32_t* a_target, std::int32_t a_value, std::int32_t a_compare) noexcept;
	std::int8_t InterlockedCompareExchange8(volatile std::int8_t* a_target, std::int8_t a_value, std::int8_t a_compare) noexcept;
	std::int16_t InterlockedCompareExchange16(volatile std::int16_t* a_target, std::int16_t a_value, std::int16_t a_compare) noexcept;
	std::int64_t InterlockedCompareExchange64(volatile std::int64_t* a_target, std::int64_t a_value, std::int64_t a_compare) noexcept;
	void* InterlockedCompareExchangePointer(void* volatile* a_target, void* a_value, void* a_compare) noexcept;
	std::int32_t InterlockedExchange(volatile std::int32_t* a_target, std::int32_t a_value) noexcept;
	std::int8_t InterlockedExchange8(volatile std::int8_t* a_target, std::int8_t a_value) noexcept;
	std::int16_t InterlockedExchange16(volatile std::int16_t* a_target, std::int16_t a_value) noexcept;
	std::int64_t InterlockedExchange64(volatile std::int64_t* a_target, std::int64_t a_value) noexcept;
	std::int32_t InterlockedExchangeAdd(volatile std::int32_t* a_target, std::int32_t a_value) noexcept;
	std::int8_t InterlockedExchangeAdd8(volatile std::int8_t* a_target, std::int8_t a_value) noexcept;
	std::int16_t InterlockedExchangeAdd16(volatile std::int16_t* a_target, std::int16_t a_value) noexcept;
	std::int64_t InterlockedExchangeAdd64(volatile std::int64_t* a_target, std::int64_t a_value) noexcept;
	void* InterlockedExchangePointer(void* volatile* a_target, void* a_value) noexcept;
	std::int32_t InterlockedIncrement(volatile std::int32_t* a_target) noexcept;
	std::int16_t InterlockedIncrement16(volatile std::int16_t* a_target) noexcept;
	std::int64_t InterlockedIncrement64(volatile std::int64_t* a_target) noexcept;
	std::int32_t InterlockedOr(volatile std::int32_t* a_target, std::int32_t a_value) noexcept;
	std::int8_t InterlockedOr8(volatile std::int8_t* a_target, std::int8_t a_value) noexcept;
	std::int16_t InterlockedOr16(volatile std::int16_t* a_target, std::int16_t a_value) noexcept;
	std::int64_t InterlockedOr64(volatile std::int64_t* a_target, std::int64_t a_value) noexcept;
	std::int32_t InterlockedXor(volatile std::int32_t* a_target, std::int32_t a_value) noexcept;
	std::int8_t InterlockedXor8(volatile std::int8_t* a_target, std::int8_t a_value) noexcept;
	std::int16_t InterlockedXor16(volatile std::int16_t* a_target, std::int16_t a_value) noexcept;
	std::int64_t InterlockedXor64(volatile std::int64_t* a_target, std::int64_t a_value) noexcept;
	bool IsDebuggerPresent() noexcept;
	std::int32_t LCMapStringEx(const wchar_t* a_locale, std::uint32_t a_flags, const wchar_t* a_src, std::int32_t a_srcLen, wchar_t* a_dst, std::int32_t a_dstLen, NLSVERSIONINFO* a_info, void* a_reserved, std::intptr_t a_sortHandle) noexcept;
	void LeaveCriticalSection(CRITICAL_SECTION* a_criticalSection) noexcept;
	HMODULE LoadLibraryA(const char* a_name) noexcept;
	HMODULE LoadLibraryW(const wchar_t* a_name) noexcept;
	void* MapViewOfFile(HANDLE a_object, std::uint32_t a_desiredAccess, std::uint32_t a_fileOffsetHigh, std::uint32_t a_fileOffsetLow, std::size_t a_numBytes) noexcept;
	void* MapViewOfFileEx(HANDLE a_object, std::uint32_t a_desiredAccess, std::uint32_t a_fileOffsetHigh, std::uint32_t a_fileOffsetLow, std::size_t a_numBytes, void* a_baseAddr) noexcept;
	std::int32_t MultiByteToWideChar(std::uint32_t a_codePage, std::uint32_t a_flags, const char* a_src, std::int32_t a_srcLen, wchar_t* a_dst, std::int32_t a_dstLen) noexcept;
	HANDLE OpenFileMappingA(std::uint32_t a_desiredAccess, bool a_inheritHandle, const char* a_name) noexcept;
	HANDLE OpenFileMappingW(std::uint32_t a_desiredAccess, bool a_inheritHandle, const wchar_t* a_name) noexcept;
	void OutputDebugStringA(const char* a_str) noexcept;
	void OutputDebugStringW(const wchar_t* a_str) noexcept;
	bool QueryPerformanceCounter(std::int64_t* a_counter) noexcept;
	bool QueryPerformanceFrequency(std::int64_t* a_frequency) noexcept;
	bool ReleaseSemaphore(HANDLE a_semaphore, std::int32_t a_releaseCount, std::int32_t* a_previousCount) noexcept;
	void ReleaseSRWLockShared(SRWLOCK* a_lock) noexcept;
	void ReleaseSRWLockExclusive(SRWLOCK* a_lock) noexcept;
	std::uint32_t ResumeThread(HANDLE a_handle) noexcept;
	std::uint32_t SetCriticalSectionSpinCount(CRITICAL_SECTION* a_criticalSection, std::uint32_t a_spinCount) noexcept;
	bool SetEnvironmentVariableA(const char* a_name, const char* a_value) noexcept;
	bool SetEnvironmentVariableW(const wchar_t* a_name, const wchar_t* a_value) noexcept;
	void SetLastError(ERROR_CODE a_error) noexcept;
	void Sleep(std::uint32_t a_milliseconds) noexcept;
	[[noreturn]] void TerminateCurrentProcess(std::uint32_t a_exitCode) noexcept;
	bool TerminateProcess(HANDLE a_process, std::uint32_t a_exitCode) noexcept;
	void* TlsGetValue(std::uint32_t a_index) noexcept;
	bool TlsSetValue(std::uint32_t a_index, void* a_value) noexcept;
	bool TryAcquireSRWLockExclusive(SRWLOCK* a_lock) noexcept;
	bool TryAcquireSRWLockShared(SRWLOCK* a_lock) noexcept;
	bool TryEnterCriticalSection(CRITICAL_SECTION* a_criticalSection) noexcept;
	bool UnmapViewOfFile(const void* a_baseAddress) noexcept;
	void* VirtualAlloc(void* a_address, std::size_t a_size, std::uint32_t a_type, std::uint32_t a_protect) noexcept;
	void* VirtualAllocEx(HANDLE a_process, void* a_address, std::size_t a_size, std::uint32_t a_type, std::uint32_t a_protect) noexcept;
	bool VirtualFree(void* a_address, std::size_t a_size, std::uint32_t a_type) noexcept;
	bool VirtualFreeEx(HANDLE a_process, void* a_address, std::size_t a_size, std::uint32_t a_type) noexcept;
	bool VirtualProtect(void* a_address, std::size_t a_size, std::uint32_t a_newProtect, std::uint32_t* a_oldProtect) noexcept;
	bool VirtualProtectEx(HANDLE a_process, void* a_address, std::size_t a_size, std::uint32_t a_newProtect, std::uint32_t* a_oldProtect) noexcept;
	std::size_t VirtualQuery(const void* a_address, MEMORY_BASIC_INFORMATION* a_buffer, std::size_t a_bufLen) noexcept;
	std::size_t VirtualQueryEx(HANDLE a_process, const void* a_address, MEMORY_BASIC_INFORMATION* a_buffer, std::size_t a_bufLen) noexcept;
	std::uint32_t WaitForSingleObject(HANDLE a_handle, std::uint32_t a_milliseconds) noexcept;
	std::uint32_t WaitForSingleObjectEx(HANDLE a_handle, std::uint32_t a_milliseconds, bool a_alertable) noexcept;
	std::int32_t WideCharToMultiByte(std::uint32_t a_codePage, std::uint32_t a_flags, const wchar_t* a_src, std::int32_t a_srcLen, char* a_dst, std::int32_t a_dstLen, const char* a_default, std::int32_t* a_defaultLen) noexcept;
	bool WriteProcessMemory(HANDLE a_process, void* a_address, const void* a_buffer, std::size_t a_bufLen, std::size_t* a_bufWritten) noexcept;
}
