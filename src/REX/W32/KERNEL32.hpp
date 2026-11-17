#pragma once

#include "REX/StaticString.hpp"
#include "REX/W32/CORE.hpp"

namespace REX::W32
{
	enum CP : std::int32_t
	{
		CP_UTF8 = 65'001
	};

	enum DLL : std::int32_t
	{
		DLL_PROCESS_DETACH = 0,
		DLL_PROCESS_ATTACH = 1,
		DLL_THREAD_ATTACH = 2,
		DLL_THREAD_DETACH = 3
	};

	enum FILE_ACCESS : std::uint32_t
	{
		FILE_LIST_DIRECTORY = 0x01,
		FILE_READ_DATA = 0x01,
		FILE_ADD_FILE = 0x02,
		FILE_WRITE_DATA = 0x02,
		FILE_ADD_SUBDIRECTORY = 0x04,
		FILE_APPEND_DATA = 0x04,
		FILE_CREATE_PIPE_INSTANCE = 0x04,
		FILE_READ_EA = 0x08,
		FILE_WRITE_EA = 0x10,
		FILE_EXECUTE = 0x20,
		FILE_TRAVERSE = 0x20,
		FILE_DELETE_CHILD = 0x40,
		FILE_READ_ATTRIBUTES = 0x80,
		FILE_WRITE_ATTRIBUTES = 0x100
	};

	enum FILE_ATTRIBUTE : std::uint32_t
	{
		FILE_ATTRIBUTE_READONLY = 0x01,
		FILE_ATTRIBUTE_HIDDEN = 0x02,
		FILE_ATTRIBUTE_SYSTEM = 0x04,
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
		FILE_ATTRIBUTE_VIRTUAL = 0x1'0000,
		FILE_ATTRIBUTE_NO_SCRUB_DATA = 0x2'0000,
		FILE_ATTRIBUTE_EA = 0x4'0000,
		FILE_ATTRIBUTE_RECALL_ON_OPEN = 0x4'0000,
		FILE_ATTRIBUTE_PINNED = 0x8'0000,
		FILE_ATTRIBUTE_UNPINNED = 0x10'0000,
		FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS = 0x40'0000
	};

	enum FILE_FLAG : std::uint32_t
	{
		FILE_FLAG_OPEN_NO_RECALL = 0x10'0000,
		FILE_FLAG_OPEN_REPARSE_POINT = 0x20'0000,
		FILE_FLAG_SESSION_AWARE = 0x80'0000,
		FILE_FLAG_POSIX_SEMANTICS = 0x100'0000,
		FILE_FLAG_BACKUP_SEMANTICS = 0x200'0000,
		FILE_FLAG_DELETE_ON_CLOSE = 0x400'0000,
		FILE_FLAG_SEQUENTIAL_SCAN = 0x800'0000,
		FILE_FLAG_RANDOM_ACCESS = 0x1000'0000,
		FILE_FLAG_NO_BUFFERING = 0x2000'0000,
		FILE_FLAG_OVERLAPPED = 0x4000'0000,
		FILE_FLAG_WRITE_THROUGH = 0x8000'0000
	};

	enum FILE_MODE : std::int32_t
	{
		CREATE_NEW = 1,
		CREATE_ALWAYS = 2,
		OPEN_EXISTING = 3,
		OPEN_ALWAYS = 4,
		TRUNCATE_EXISTING = 5
	};

	enum FILE_MOVE_METHOD : std::int32_t
	{
		FILE_BEGIN = 0,
		FILE_CURRENT = 1,
		FILE_END = 2
	};

	enum FILE_SHARE : std::uint32_t
	{
		FILE_SHARE_READ = 0x01,
		FILE_SHARE_WRITE = 0x02,
		FILE_SHARE_DELETE = 0x04
	};

	enum GENERIC : std::uint32_t
	{
		GENERIC_ALL = 0x1000'0000,
		GENERIC_EXECUTE = 0x2000'0000,
		GENERIC_WRITE = 0x4000'0000,
		GENERIC_READ = 0x8000'0000
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

	inline constexpr auto IMAGE_DOS_SIGNATURE = static_cast<std::uint32_t>(0x5A4D);
	inline constexpr auto IMAGE_NT_OPTIONAL_HDR32_MAGIC = static_cast<std::uint32_t>(0x10B);
	inline constexpr auto IMAGE_NT_OPTIONAL_HDR64_MAGIC = static_cast<std::uint32_t>(0x20B);
	inline constexpr auto IMAGE_NT_SIGNATURE = static_cast<std::uint32_t>(0x4550);

	enum IMAGE_ORDINAL_FLAG : std::uint64_t
	{
		IMAGE_ORDINAL_FLAG32 = 0x8000'0000,
		IMAGE_ORDINAL_FLAG64 = 0x8000'0000'0000'0000
	};

	enum IMAGE_SCN_MEM : std::uint32_t
	{
		IMAGE_SCN_MEM_SHARED = 0x1000'0000,
		IMAGE_SCN_MEM_EXECUTE = 0x2000'0000,
		IMAGE_SCN_MEM_READ = 0x4000'0000,
		IMAGE_SCN_MEM_WRITE = 0x8000'0000
	};

	inline constexpr auto IMAGE_SIZEOF_SECTION_HEADER = static_cast<std::uint32_t>(40);
	inline constexpr auto IMAGE_SIZEOF_SHORT_NAME = static_cast<std::uint32_t>(8);

	enum LCMAP : std::uint32_t
	{
		LCMAP_LOWERCASE = 0x100,
		LCMAP_UPPERCASE = 0x200,
		LCMAP_TITLECASE = 0x300,
		LCMAP_SORTKEY = 0x400,
		LCMAP_BYTEREV = 0x800,
		LCMAP_HIRAGANA = 0x10'0000,
		LCMAP_KATAKANA = 0x20'0000,
		LCMAP_HALFWIDTH = 0x40'0000,
		LCMAP_FULLWIDTH = 0x80'0000,
		LCMAP_LINGUISTIC_CASING = 0x100'0000,
		LCMAP_SIMPLIFIED_CHINESE = 0x200'0000,
		LCMAP_TRADITIONAL_CHINESE = 0x400'0000
	};

	inline constexpr auto LOCALE_NAME_INVARIANT = L""sv;
	inline constexpr auto LOCALE_NAME_SYSTEM_DEFAULT = L"!x-sys-default-locale"sv;
	inline constexpr const auto* LOCALE_NAME_USER_DEFAULT{static_cast<const wchar_t*>(nullptr)};

	enum MEM : std::uint32_t
	{
		MEM_COMMIT = 0x1000,
		MEM_RESERVE = 0x2000,
		MEM_DECOMMIT = 0x4000,
		MEM_RELEASE = 0x8000,
		MEM_FREE = 0x1'0000,
		MEM_RESET = 0x8'0000,
		MEM_RESET_UNDO = 0x100'0000
	};

	enum PAGE : std::uint32_t
	{
		PAGE_NOACCESS = 0x01,
		PAGE_READONLY = 0x02,
		PAGE_READWRITE = 0x04,
		PAGE_WRITECOPY = 0x08,
		PAGE_EXECUTE = 0x10,
		PAGE_EXECUTE_READ = 0x20,
		PAGE_EXECUTE_READWRITE = 0x40,
		PAGE_EXECUTE_WRITECOPY = 0x80,
		PAGE_GUARD = 0x100,
		PAGE_NOCACHE = 0x200,
		PAGE_WRITECOMBINE = 0x400,
		PAGE_TARGETS_INVALID = 0x4000'0000,
		PAGE_TARGETS_NO_UPDATE = 0x4000'0000,
		PAGE_ENCLAVE_UNVALIDATED = 0x2000'0000,
		PAGE_ENCLAVE_DECOMMIT = 0x4000'0000,
		PAGE_ENCLAVE_THREAD_CONTROL = 0x8000'0000
	};

	enum PROCESS : std::uint32_t
	{
		DEBUG_PROCESS = 0x01,
		DEBUG_ONLY_THIS_PROCESS = 0x02,
		CREATE_SUSPENDED = 0x04,
		DETACHED_PROCESS = 0x08,
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
		INHERIT_PARENT_AFFINITY = 0x1'0000,
		CREATE_PROTECTED_PROCESS = 0x4'0000,
		EXTENDED_STARTUPINFO_PRESENT = 0x8'0000,
		PROCESS_MODE_BACKGROUND_BEGIN = 0x10'0000,
		PROCESS_MODE_BACKGROUND_END = 0x20'0000,
		CREATE_SECURE_PROCESS = 0x40'0000,
		CREATE_BREAKAWAY_FROM_JOB = 0x100'0000,
		CREATE_PRESERVE_CODE_AUTHZ_LEVEL = 0x200'0000,
		CREATE_DEFAULT_ERROR_MODE = 0x400'0000,
		CREATE_NO_WINDOW = 0x800'0000
	};

	enum RIGHT : std::uint32_t
	{
		DELETE = 0x1'0000,
		READ_CONTROL = 0x2'0000,
		WRITE_DAC = 0x4'0000,
		WRITE_OWNER = 0x8'0000,
		SYNCHRONIZE = 0x10'0000
	};

	enum SECURITY : std::int32_t
	{
		SECURITY_ANONYMOUS = 0,
		SECURITY_IDENTIFICATION = 1,
		SECURITY_IMPERSONATION = 2,
		SECURITY_DELEGATION = 3
	};

	enum STANDARD_RIGHTS : std::uint32_t
	{
		STANDARD_RIGHTS_REQUIRED = DELETE | READ_CONTROL | WRITE_DAC | WRITE_OWNER,
		STANDARD_RIGHTS_READ = READ_CONTROL,
		STANDARD_RIGHTS_WRITE = READ_CONTROL,
		STANDARD_RIGHTS_EXECUTE = READ_CONTROL,
		STANDARD_RIGHTS_ALL = DELETE | READ_CONTROL | WRITE_DAC | WRITE_OWNER | SYNCHRONIZE
	};

	enum FILE_GENERIC : std::uint32_t
	{
		FILE_GENERIC_READ = FILE_READ_ATTRIBUTES | FILE_READ_DATA | FILE_READ_EA | STANDARD_RIGHTS_READ | SYNCHRONIZE,
		FILE_GENERIC_WRITE = FILE_APPEND_DATA |
			FILE_WRITE_ATTRIBUTES |
			FILE_WRITE_DATA |
			FILE_WRITE_EA |
			STANDARD_RIGHTS_READ |
			SYNCHRONIZE,
		FILE_GENERIC_EXECUTE = FILE_EXECUTE | FILE_READ_ATTRIBUTES | STANDARD_RIGHTS_EXECUTE | SYNCHRONIZE
	};

	enum SECTION : std::uint32_t
	{
		SECTION_QUERY = 0x01,
		SECTION_MAP_WRITE = 0x02,
		SECTION_MAP_READ = 0x04,
		SECTION_MAP_EXECUTE = 0x08,
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
		FILE_MAP_COPY = 0x01,
		FILE_MAP_WRITE = 0x02,
		FILE_MAP_READ = 0x04,
		FILE_MAP_EXECUTE = 0x20,
		FILE_MAP_LARGE_PAGES = 0x2000'0000,
		FILE_MAP_TARGETS_INVALID = 0x4000'0000,
		FILE_MAP_RESERVE = 0x8000'0000,
		FILE_MAP_ALL_ACCESS = SECTION_ALL_ACCESS
	};

	enum WAIT : std::uint32_t
	{
		WAIT_OBJECT_0 = 0x00,
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

	struct IMAGE_IMPORT_BY_NAME
	{
		std::uint16_t hint;
		REX::StaticString<1> name;
	};

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

	struct IMAGE_NT_HEADERS64
	{
		std::uint32_t signature;
		IMAGE_FILE_HEADER fileHeader;
		IMAGE_OPTIONAL_HEADER64 optionalHeader;
	};

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

	struct NLSVERSIONINFO
	{
		std::uint32_t nlsVersionInfoSize;
		std::uint32_t nlsVersion;
		std::uint32_t definedVersion;
		std::uint32_t effectiveID;
		GUID guidCustomVersion;
	};

	struct PROCESS_INFORMATION
	{
		void* process;
		void* thread;
		std::uint32_t processID;
		std::uint32_t threadID;
	};

	struct SRWLOCK
	{
		void* ptr;
	};

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
		REX::StaticString<MAX_PATH> fileName;
		REX::StaticString<14> fileNameAlt;
	};

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
		REX::StaticWString<MAX_PATH> fileName;
		REX::StaticWString<14> fileNameAlt;
	};
}

namespace REX::W32
{
	using THREAD_START_ROUTINE = std::uint32_t(void* a_param);
}

namespace REX::W32
{
	void AcquireSRWLockShared(SRWLOCK* a_lock) noexcept;
	void AcquireSRWLockExclusive(SRWLOCK* a_lock) noexcept;
	auto CloseHandle(HANDLE a_handle) noexcept -> bool;
	auto CreateFileA(
		const char* a_fileName,
		std::uint32_t a_desiredAccess,
		std::uint32_t a_shareMode,
		SECURITY_ATTRIBUTES* a_attributes,
		std::uint32_t a_creationDisposition,
		std::uint32_t a_flags,
		HANDLE a_templateFile) noexcept -> HANDLE;
	auto CreateFileW(
		const wchar_t* a_fileName,
		std::uint32_t a_desiredAccess,
		std::uint32_t a_shareMode,
		SECURITY_ATTRIBUTES* a_attributes,
		std::uint32_t a_creationDisposition,
		std::uint32_t a_flags,
		HANDLE a_templateFile) noexcept -> HANDLE;
	auto CreateFileMappingA(
		HANDLE a_file,
		SECURITY_ATTRIBUTES* a_attributes,
		std::uint32_t a_protect,
		std::uint64_t a_maxSize,
		const char* a_name) noexcept -> HANDLE;
	auto CreateFileMappingW(
		HANDLE a_file,
		SECURITY_ATTRIBUTES* a_attributes,
		std::uint32_t a_protect,
		std::uint64_t a_maxSize,
		const wchar_t* a_name) noexcept -> HANDLE;
	auto CreateProcessA(
		const char* a_name,
		char* a_cmd,
		SECURITY_ATTRIBUTES* a_procAttr,
		SECURITY_ATTRIBUTES* a_threadAttr,
		bool a_inheritHandles,
		std::uint32_t a_flags,
		void* a_env,
		const char* a_curDir,
		STARTUPINFOA* a_startInfo,
		PROCESS_INFORMATION* a_procInfo) noexcept -> bool;
	auto CreateProcessW(
		const wchar_t* a_name,
		wchar_t* a_cmd,
		SECURITY_ATTRIBUTES* a_procAttr,
		SECURITY_ATTRIBUTES* a_threadAttr,
		bool a_inheritHandles,
		std::uint32_t a_flags,
		void* a_env,
		const wchar_t* a_curDir,
		STARTUPINFOW* a_startInfo,
		PROCESS_INFORMATION* a_procInfo) noexcept -> bool;
	auto CreateRemoteThread(
		HANDLE a_process,
		SECURITY_ATTRIBUTES* a_threadAttr,
		std::size_t a_stackSize,
		THREAD_START_ROUTINE* a_startAddr,
		void* a_param,
		std::uint32_t a_flags,
		std::uint32_t* a_threadID) -> HANDLE;
	auto CreateSemaphoreA(
		SECURITY_ATTRIBUTES* a_semaphoreAttr,
		std::int32_t a_initCount,
		std::int32_t a_maxCount,
		const char* a_name) noexcept -> HANDLE;
	auto CreateThread(
		SECURITY_ATTRIBUTES* a_threadAttr,
		std::size_t a_stackSize,
		THREAD_START_ROUTINE* a_startAddr,
		void* a_param,
		std::uint32_t a_flags,
		std::uint32_t* a_threadID) -> HANDLE;
	void DebugBreak() noexcept;
	void DebugBreakProcess(HANDLE a_process) noexcept;
	void DeleteCriticalSection(CRITICAL_SECTION* a_criticalSection) noexcept;
	void EnterCriticalSection(CRITICAL_SECTION* a_criticalSection) noexcept;
	[[noreturn]]
	void ExitProcess(std::uint32_t a_exitCode) noexcept;
	auto ExpandEnvironmentStringsA(const char* a_source, char* a_target, std::uint32_t a_targetLength) noexcept
		-> std::uint32_t;
	auto ExpandEnvironmentStringsW(const wchar_t* a_source, wchar_t* a_target, std::uint32_t a_targetLength) noexcept
		-> std::uint32_t;
	auto FindClose(HANDLE a_file) noexcept -> bool;
	auto FindFirstFileA(const char* a_name, WIN32_FIND_DATAA* a_data) noexcept -> HANDLE;
	auto FindFirstFileW(const wchar_t* a_name, WIN32_FIND_DATAW* a_data) noexcept -> HANDLE;
	auto FindNextFileA(HANDLE a_file, WIN32_FIND_DATAA* a_data) noexcept -> bool;
	auto FindNextFileW(HANDLE a_file, WIN32_FIND_DATAW* a_data) noexcept -> bool;
	auto FlushInstructionCache(HANDLE a_process, const void* a_baseAddr, std::size_t a_size) noexcept -> bool;
	auto FreeLibrary(HMODULE a_module) noexcept -> bool;
	auto GetComputerNameA(char* a_buffer, std::uint32_t* a_size) noexcept -> bool;
	auto GetComputerNameW(wchar_t* a_buffer, std::uint32_t* a_size) noexcept -> bool;
	auto GetCurrentDirectoryA(std::uint32_t a_size, char* a_buffer) noexcept -> std::uint32_t;
	auto GetCurrentDirectoryW(std::uint32_t a_size, wchar_t* a_buffer) noexcept -> std::uint32_t;
	auto GetCurrentModule() noexcept -> HMODULE;
	auto GetCurrentProcess() noexcept -> HANDLE;
	auto GetCurrentThreadId() noexcept -> THREAD_ID;
	auto GetEnvironmentVariableA(const char* a_name, char* a_buffer, std::uint32_t a_bufferLength) noexcept
		-> std::uint32_t;
	auto GetEnvironmentVariableW(const wchar_t* a_name, wchar_t* a_buffer, std::uint32_t a_bufferLength) noexcept
		-> std::uint32_t;
	auto GetFileSize(HANDLE a_file, std::uint32_t* a_fileSizeHigh) noexcept -> std::uint32_t;
	auto GetFileSizeEx(HANDLE a_file, std::int64_t* a_fileSize) noexcept -> bool;
	auto GetLastError() noexcept -> ERROR_CODE;
	auto GetModuleFileNameA(HMODULE a_module, char* a_name, std::uint32_t a_nameLength) noexcept -> std::uint32_t;
	auto GetModuleFileNameW(HMODULE a_module, wchar_t* a_name, std::uint32_t a_nameLength) noexcept -> std::uint32_t;
	auto GetModuleHandleA(const char* a_name) noexcept -> HMODULE;
	auto GetModuleHandleW(const wchar_t* a_name) noexcept -> HMODULE;
	auto GetParentModule() noexcept -> HMODULE;
	auto GetPrivateProfileIntA(const char* a_app, const char* a_key, std::int32_t a_default, const char* a_name)
		noexcept -> std::uint32_t;
	auto GetPrivateProfileIntW(
		const wchar_t* a_app,
		const wchar_t* a_key,
		std::int32_t a_default,
		const wchar_t* a_name) noexcept -> std::uint32_t;
	auto GetPrivateProfileStringA(
		const char* a_app,
		const char* a_key,
		const char* a_default,
		char* a_buffer,
		std::uint32_t a_bufferLength,
		const char* a_name) noexcept -> std::uint32_t;
	auto GetPrivateProfileStringW(
		const wchar_t* a_app,
		const wchar_t* a_key,
		const wchar_t* a_default,
		wchar_t* a_buffer,
		std::uint32_t a_bufferLength,
		const wchar_t* a_name) noexcept -> std::uint32_t;
	auto GetProcAddress(HMODULE a_module, const char* a_name) noexcept -> void*;
	void GetSystemInfo(SYSTEM_INFO* a_info) noexcept;
	auto GetUserNameA(char* a_buffer, std::uint32_t* a_size) noexcept -> bool;
	auto GetUserNameW(wchar_t* a_buffer, std::uint32_t* a_size) noexcept -> bool;
	auto GetVersion() noexcept -> std::uint32_t;
	auto IMAGE_SNAP_BY_ORDINAL64(std::uint64_t a_ordinal) noexcept -> bool;
	auto IMAGE_FIRST_SECTION(const IMAGE_NT_HEADERS64* a_header) noexcept -> IMAGE_SECTION_HEADER*;
	void InitializeCriticalSection(CRITICAL_SECTION* a_criticalSection) noexcept;
	auto InitializeCriticalSectionAndSpinCount(CRITICAL_SECTION* a_criticalSection, std::uint32_t a_spinCount) noexcept
		-> bool;
	void InitializeSRWLock(SRWLOCK* a_lock) noexcept;
	auto InterlockedAnd(volatile std::int32_t* a_target, std::int32_t a_value) noexcept -> std::int32_t;
	auto InterlockedAnd8(volatile std::int8_t* a_target, std::int8_t a_value) noexcept -> std::int8_t;
	auto InterlockedAnd16(volatile std::int16_t* a_target, std::int16_t a_value) noexcept -> std::int16_t;
	auto InterlockedAnd64(volatile std::int64_t* a_target, std::int64_t a_value) noexcept -> std::int64_t;
	auto InterlockedDecrement(volatile std::int32_t* a_target) noexcept -> std::int32_t;
	auto InterlockedDecrement16(volatile std::int16_t* a_target) noexcept -> std::int16_t;
	auto InterlockedDecrement64(volatile std::int64_t* a_target) noexcept -> std::int64_t;
	auto InterlockedCompareExchange(volatile std::int32_t* a_target, std::int32_t a_value, std::int32_t a_compare)
		noexcept -> std::int32_t;
	auto InterlockedCompareExchange8(volatile std::int8_t* a_target, std::int8_t a_value, std::int8_t a_compare)
		noexcept -> std::int8_t;
	auto InterlockedCompareExchange16(volatile std::int16_t* a_target, std::int16_t a_value, std::int16_t a_compare)
		noexcept -> std::int16_t;
	auto InterlockedCompareExchange64(volatile std::int64_t* a_target, std::int64_t a_value, std::int64_t a_compare)
		noexcept -> std::int64_t;
	auto InterlockedCompareExchangePointer(void* volatile* a_target, void* a_value, void* a_compare) noexcept -> void*;
	auto InterlockedExchange(volatile std::int32_t* a_target, std::int32_t a_value) noexcept -> std::int32_t;
	auto InterlockedExchange8(volatile std::int8_t* a_target, std::int8_t a_value) noexcept -> std::int8_t;
	auto InterlockedExchange16(volatile std::int16_t* a_target, std::int16_t a_value) noexcept -> std::int16_t;
	auto InterlockedExchange64(volatile std::int64_t* a_target, std::int64_t a_value) noexcept -> std::int64_t;
	auto InterlockedExchangeAdd(volatile std::int32_t* a_target, std::int32_t a_value) noexcept -> std::int32_t;
	auto InterlockedExchangeAdd8(volatile std::int8_t* a_target, std::int8_t a_value) noexcept -> std::int8_t;
	auto InterlockedExchangeAdd16(volatile std::int16_t* a_target, std::int16_t a_value) noexcept -> std::int16_t;
	auto InterlockedExchangeAdd64(volatile std::int64_t* a_target, std::int64_t a_value) noexcept -> std::int64_t;
	auto InterlockedExchangePointer(void* volatile* a_target, void* a_value) noexcept -> void*;
	auto InterlockedIncrement(volatile std::int32_t* a_target) noexcept -> std::int32_t;
	auto InterlockedIncrement16(volatile std::int16_t* a_target) noexcept -> std::int16_t;
	auto InterlockedIncrement64(volatile std::int64_t* a_target) noexcept -> std::int64_t;
	auto InterlockedOr(volatile std::int32_t* a_target, std::int32_t a_value) noexcept -> std::int32_t;
	auto InterlockedOr8(volatile std::int8_t* a_target, std::int8_t a_value) noexcept -> std::int8_t;
	auto InterlockedOr16(volatile std::int16_t* a_target, std::int16_t a_value) noexcept -> std::int16_t;
	auto InterlockedOr64(volatile std::int64_t* a_target, std::int64_t a_value) noexcept -> std::int64_t;
	auto InterlockedXor(volatile std::int32_t* a_target, std::int32_t a_value) noexcept -> std::int32_t;
	auto InterlockedXor8(volatile std::int8_t* a_target, std::int8_t a_value) noexcept -> std::int8_t;
	auto InterlockedXor16(volatile std::int16_t* a_target, std::int16_t a_value) noexcept -> std::int16_t;
	auto InterlockedXor64(volatile std::int64_t* a_target, std::int64_t a_value) noexcept -> std::int64_t;
	auto IsDebuggerPresent() noexcept -> bool;
	auto LCMapStringEx(
		const wchar_t* a_locale,
		std::uint32_t a_flags,
		const wchar_t* a_source,
		std::int32_t a_sourceLength,
		wchar_t* a_target,
		std::int32_t a_targetLength,
		NLSVERSIONINFO* a_info,
		void* a_reserved,
		std::intptr_t a_sortHandle) noexcept -> std::int32_t;
	void LeaveCriticalSection(CRITICAL_SECTION* a_criticalSection) noexcept;
	auto LoadLibraryA(const char* a_name) noexcept -> HMODULE;
	auto LoadLibraryW(const wchar_t* a_name) noexcept -> HMODULE;
	auto MapViewOfFile(
		HANDLE a_object,
		std::uint32_t a_desiredAccess,
		std::uint64_t a_fileOffset,
		std::size_t a_numBytes) noexcept -> void*;
	auto MapViewOfFileEx(
		HANDLE a_object,
		std::uint32_t a_desiredAccess,
		std::uint64_t a_fileOffset,
		std::size_t a_numBytes,
		void* a_baseAddr) noexcept -> void*;
	auto MultiByteToWideChar(
		std::uint32_t a_codePage,
		std::uint32_t a_flags,
		const char* a_source,
		std::int32_t a_sourceLength,
		wchar_t* a_target,
		std::int32_t a_targetLength) noexcept -> std::int32_t;
	auto OpenFileMappingA(std::uint32_t a_desiredAccess, bool a_inheritHandle, const char* a_name) noexcept -> HANDLE;
	auto OpenFileMappingW(std::uint32_t a_desiredAccess, bool a_inheritHandle, const wchar_t* a_name) noexcept
		-> HANDLE;
	void OutputDebugStringA(const char* a_str) noexcept;
	void OutputDebugStringW(const wchar_t* a_str) noexcept;
	auto QueryPerformanceCounter(std::int64_t* a_counter) noexcept -> bool;
	auto QueryPerformanceFrequency(std::int64_t* a_frequency) noexcept -> bool;
	auto ReadFile(
		HANDLE a_file,
		void* a_buffer,
		std::uint32_t a_bytesToRead,
		std::uint32_t* a_bytesRead,
		OVERLAPPED* a_overlapped) noexcept -> bool;
	auto ReleaseSemaphore(HANDLE a_semaphore, std::int32_t a_releaseCount, std::int32_t* a_previousCount) noexcept
		-> bool;
	void ReleaseSRWLockShared(SRWLOCK* a_lock) noexcept;
	void ReleaseSRWLockExclusive(SRWLOCK* a_lock) noexcept;
	auto ResumeThread(HANDLE a_handle) noexcept -> std::uint32_t;
	auto SetCriticalSectionSpinCount(CRITICAL_SECTION* a_criticalSection, std::uint32_t a_spinCount) noexcept
		-> std::uint32_t;
	auto SetEndOfFile(HANDLE a_file) noexcept -> bool;
	auto SetEnvironmentVariableA(const char* a_name, const char* a_value) noexcept -> bool;
	auto SetEnvironmentVariableW(const wchar_t* a_name, const wchar_t* a_value) noexcept -> bool;
	auto SetFilePointer(HANDLE a_file, std::int32_t a_distanceLow, std::int32_t* a_distanceHigh, std::uint32_t a_method)
		noexcept -> std::uint32_t;
	auto SetFilePointerEx(
		HANDLE a_file,
		std::int64_t a_distance,
		std::int64_t* a_newFilePointer,
		std::uint32_t a_method) noexcept -> bool;
	void SetLastError(ERROR_CODE a_error) noexcept;
	void Sleep(std::uint32_t a_milliseconds) noexcept;
	[[noreturn]]
	void TerminateCurrentProcess(std::uint32_t a_exitCode) noexcept;
	auto TerminateProcess(HANDLE a_process, std::uint32_t a_exitCode) noexcept -> bool;
	auto TlsGetValue(std::uint32_t a_index) noexcept -> void*;
	auto TlsSetValue(std::uint32_t a_index, void* a_value) noexcept -> bool;
	auto TryAcquireSRWLockExclusive(SRWLOCK* a_lock) noexcept -> bool;
	auto TryAcquireSRWLockShared(SRWLOCK* a_lock) noexcept -> bool;
	auto TryEnterCriticalSection(CRITICAL_SECTION* a_criticalSection) noexcept -> bool;
	auto UnmapViewOfFile(const void* a_baseAddress) noexcept -> bool;
	auto VirtualAlloc(void* a_address, std::size_t a_size, std::uint32_t a_type, std::uint32_t a_protect) noexcept
		-> void*;
	auto VirtualAllocEx(
		HANDLE a_process,
		void* a_address,
		std::size_t a_size,
		std::uint32_t a_type,
		std::uint32_t a_protect) noexcept -> void*;
	auto VirtualFree(void* a_address, std::size_t a_size, std::uint32_t a_type) noexcept -> bool;
	auto VirtualFreeEx(HANDLE a_process, void* a_address, std::size_t a_size, std::uint32_t a_type) noexcept -> bool;
	auto VirtualProtect(void* a_address, std::size_t a_size, std::uint32_t a_newProtect, std::uint32_t* a_oldProtect)
		noexcept -> bool;
	auto VirtualProtectEx(
		HANDLE a_process,
		void* a_address,
		std::size_t a_size,
		std::uint32_t a_newProtect,
		std::uint32_t* a_oldProtect) noexcept -> bool;
	auto VirtualQuery(const void* a_address, MEMORY_BASIC_INFORMATION* a_buffer, std::size_t a_bufferLength) noexcept
		-> std::size_t;
	auto VirtualQueryEx(
		HANDLE a_process,
		const void* a_address,
		MEMORY_BASIC_INFORMATION* a_buffer,
		std::size_t a_bufferLength) noexcept -> std::size_t;
	auto WaitForSingleObject(HANDLE a_handle, std::uint32_t a_milliseconds) noexcept -> std::uint32_t;
	auto WaitForSingleObjectEx(HANDLE a_handle, std::uint32_t a_milliseconds, bool a_alertable) noexcept
		-> std::uint32_t;
	auto WideCharToMultiByte(
		std::uint32_t a_codePage,
		std::uint32_t a_flags,
		const wchar_t* a_source,
		std::int32_t a_sourceLength,
		char* a_target,
		std::int32_t a_targetLength,
		const char* a_default,
		std::int32_t* a_defaultLength) noexcept -> std::int32_t;
	auto WriteFile(
		HANDLE a_file,
		const void* a_buffer,
		std::uint32_t a_bytesToWrite,
		std::uint32_t* a_bytesWritten,
		OVERLAPPED* a_overlapped) noexcept -> bool;
	auto WriteProcessMemory(
		HANDLE a_process,
		void* a_address,
		const void* a_buffer,
		std::size_t a_bufferLength,
		std::size_t* a_bufferWritten) noexcept -> bool;
}
