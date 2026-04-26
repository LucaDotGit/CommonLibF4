# --- Project ---

cmake_minimum_required(VERSION 4.3.0)

project(
	"CommonLibF4"
	LANGUAGES CXX
)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
	message(FATAL_ERROR "In-source builds are not allowed.")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_DEBUG OFF)
set(CMAKE_OPTIMIZE_DEPENDENCIES ON)

include(GNUInstallDirs)

# --- Options ---

option(COMMONLIB_RUNTIME_VR "Enable runtime support for VR." OFF)
option(COMMONLIB_RUNTIME_OG "Enable runtime support for Old-Gen." ON)
option(COMMONLIB_RUNTIME_NG "Enable runtime support for Next-Gen." ON)
option(COMMONLIB_RUNTIME_AE "Enable runtime support for the Anniversary Edition." ON)

option(COMMONLIB_OPTION_FMT "Enable support for the fmt library." ON)
option(COMMONLIB_OPTION_XBYAK "Enable Trampoline support through Xbyak." OFF)
option(COMMONLIB_OPTION_INI "Enable INI config support through REX." OFF)
option(COMMONLIB_OPTION_TOML "Enable TOML config support through REX." OFF)
option(COMMONLIB_OPTION_JSON "Enable JSON config support through REX." OFF)

if(NOT (COMMONLIB_RUNTIME_VR OR COMMONLIB_RUNTIME_OG OR COMMONLIB_RUNTIME_NG OR COMMONLIB_RUNTIME_AE))
	message(FATAL_ERROR "At least one of the runtime options must be enabled.")
endif()

# --- Add Dependencies ---

find_package(fmt REQUIRED CONFIG)
find_package(spdlog REQUIRED CONFIG)

if(COMMONLIB_RUNTIME_VR)
	find_path(RAPIDCSV_INCLUDE_DIR "rapidcsv.h")
endif()

if(COMMONLIB_OPTION_XBYAK)
	find_package(xbyak REQUIRED CONFIG)
endif()

if(COMMONLIB_OPTION_INI)
	find_path(SIMPLEINI_INCLUDE_DIR "SimpleIni.h")
endif()

if(COMMONLIB_OPTION_TOML)
	find_package(toml11 REQUIRED CONFIG)
endif()

if(COMMONLIB_OPTION_JSON)
	find_package(nlohmann_json REQUIRED CONFIG)
endif()

# --- Add Sources ---

set(
	PCH_SOURCE
	"${CMAKE_CURRENT_SOURCE_DIR}/include/F4SE/Impl/PCH.hpp"
)

file(
	GLOB_RECURSE
		SOURCES
	CONFIGURE_DEPENDS
		"${CMAKE_CURRENT_SOURCE_DIR}/include/*"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*"
)

list(
	REMOVE_ITEM
		SOURCES
		"${PCH_SOURCE}"
)

source_group(
	TREE
		"${CMAKE_CURRENT_SOURCE_DIR}"
	FILES
		${SOURCES}
)

# --- Include ---

add_library(
	"${PROJECT_NAME}"
	STATIC
		${SOURCES}
)

add_library(
	"${PROJECT_NAME}::${PROJECT_NAME}"
	ALIAS
		"${PROJECT_NAME}"
)

target_include_directories(
	"${PROJECT_NAME}"
	PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}/include"
		"${CMAKE_CURRENT_SOURCE_DIR}/src"
		"$<$<BOOL:${COMMONLIB_RUNTIME_VR}>:${RAPIDCSV_INCLUDE_DIR}>"
		"$<$<BOOL:${COMMONLIB_OPTION_INI}>:${SIMPLEINI_INCLUDE_DIR}>"
)

target_precompile_headers(
	"${PROJECT_NAME}"
	PRIVATE
		"${PCH_SOURCE}"
)

# --- Compile ---

target_compile_definitions(
	"${PROJECT_NAME}"
	PUBLIC
		"WINVER=0x0A00" # Windows 10
		"_WIN32_WINNT=0x0A00" # Windows 10
		"NTDDI_VERSION=0x0A000008" # Windows 10, Version 2004
		"WIN32_LEAN_AND_MEAN=1"
		"VC_EXTRALEAN=1"
		"NOMINMAX=1"
		"COMMONLIB_RUNTIME_VR=$<IF:$<BOOL:${COMMONLIB_RUNTIME_VR}>,1,0>"
		"COMMONLIB_RUNTIME_OG=$<IF:$<BOOL:${COMMONLIB_RUNTIME_OG}>,1,0>"
		"COMMONLIB_RUNTIME_NG=$<IF:$<BOOL:${COMMONLIB_RUNTIME_NG}>,1,0>"
		"COMMONLIB_RUNTIME_AE=$<IF:$<BOOL:${COMMONLIB_RUNTIME_AE}>,1,0>"
		"COMMONLIB_OPTION_FMT=$<IF:$<BOOL:${COMMONLIB_OPTION_FMT}>,1,0>"
		"COMMONLIB_OPTION_XBYAK=$<IF:$<BOOL:${COMMONLIB_OPTION_XBYAK}>,1,0>"
		"COMMONLIB_OPTION_INI=$<IF:$<BOOL:${COMMONLIB_OPTION_INI}>,1,0>"
		"COMMONLIB_OPTION_TOML=$<IF:$<BOOL:${COMMONLIB_OPTION_TOML}>,1,0>"
		"COMMONLIB_OPTION_JSON=$<IF:$<BOOL:${COMMONLIB_OPTION_JSON}>,1,0>"
		"$<$<BOOL:${COMMONLIB_OPTION_INI}>:SI_NO_CONVERSION=1>"
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_link_options(
		"${PROJECT_NAME}"
		PUBLIC
			"/CGTHREADS:8"
			"/DEBUG:FULL"
			"/WX"
			"$<$<CONFIG:Debug>:/INCREMENTAL:NO;/OPT:NOICF,NOLBR,NOREF>"
			"$<$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>,$<CONFIG:MinSizeRel>>:/INCREMENTAL:NO;/OPT:ICF=4;/OPT:LBR,REF>"
	)

	target_compile_options(
		"${PROJECT_NAME}"
		PUBLIC
			"/arch:SSE4.2"
			"/await:strict"
			"/bigobj"
			"/cgthreads8"
			"/diagnostics:caret"
			"/EHsc"
			"/external:W0"
			"/fp:contract"
			"/fp:except-"
			"/jumptablerdata"
			"/MP"
			"/nologo"
			"/options:strict"
			"/permissive-"
			"/utf-8"
			"/volatile:iso"
			"/W4"
			"/WX"
			"/Zc:__cplusplus"
			"/Zc:checkGwOdr"
			"/Zc:enumTypes"
			"/Zc:inline"
			"/Zc:preprocessor"
			"/Zc:templateScope"
			"/Zc:throwingNew"
			"/Zc:trigraphs"
			"/Zf"
			"/ZH:SHA_256"
			"/Zi"
			"$<$<CONFIG:Debug>:/JMC;/Ob0;/Od;/RTC1>"
			"$<$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>,$<CONFIG:MinSizeRel>>:/GL;/Gw;/Ob2>"
			"$<$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>>:/O2>"
			"$<$<CONFIG:MinSizeRel>:/O1>"
	)

	target_compile_options(
		"${PROJECT_NAME}"
		PUBLIC
			"/we4746" # volatile access of '<expression>' is subject to /volatile:[iso|ms] setting; consider using __iso_volatile_load/store intrinsic functions.
	)

	target_compile_options(
		"${PROJECT_NAME}"
		PUBLIC
			"/wd4200" # nonstandard extension used: zero-sized array in struct/union
			"/wd4201" # nonstandard extension used: nameless struct/union
			"/wd4324" # 'type': structure was padded due to alignment specifier
	)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	target_link_options(
		"${PROJECT_NAME}"
		PUBLIC
			"/DEBUG:FULL"
			"/WX"
			"$<$<CONFIG:Debug>:/INCREMENTAL:NO;/OPT:NOICF,NOLBR,NOREF>"
			"$<$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>,$<CONFIG:MinSizeRel>>:/INCREMENTAL:NO;/OPT:ICF=4;/OPT:LBR,REF>"
	)

	target_compile_options(
		"${PROJECT_NAME}"
		PUBLIC
			"-fdelayed-template-parsing"
			"-fms-compatibility"
			"-fms-extensions"
			"-fstandalone-debug"
			"-g"
			"-gcodeview"
			"/arch:SSE4.2"
			"/diagnostics:caret"
			"/EHsc"
			"/external:W0"
			"/fp:contract"
			"/fp:except-"
			"/permissive-"
			"/utf-8"
			"/volatile:iso"
			"/W4"
			"/WX"
			"/Zc:trigraphs"
			"/ZH:SHA_256"
			"/Zi"
			"$<$<CONFIG:Debug>:/JMC;/Ob0;/Od>"
			"$<$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>,$<CONFIG:MinSizeRel>>:-flto;/Gw;/Ob2>"
			"$<$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>>:/O2>"
			"$<$<CONFIG:MinSizeRel>:/O1>"
	)

	target_compile_options(
		"${PROJECT_NAME}"
		PUBLIC
			"-Wno-deprecated-volatile"
			"-Wno-invalid-offsetof"
			"-Wno-missing-braces"
			"-Wno-missing-designated-field-initializers"
			"-Wno-overloaded-virtual"
			"$<$<BOOL:${COMMONLIB_OPTION_TOML}>:-Wno-unused-command-line-argument>" # Ignore invalid compiler flag "/Zc:preprocessor" from toml11.
	)
else()
	message(FATAL_ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}. Please use either MSVC or clang-cl.")
endif()

# --- Link ---

target_link_libraries(
	"${PROJECT_NAME}"
	PUBLIC
		"advapi32.lib"
		"bcrypt.lib"
		"d3d11.lib"
		"d3dcompiler.lib"
		"dbghelp.lib"
		"dxgi.lib"
		"ole32.lib"
		"shell32.lib"
		"user32.lib"
		"version.lib"
		"ws2_32.lib"
		"fmt::fmt"
		"spdlog::spdlog"
		"$<$<BOOL:${COMMONLIB_OPTION_XBYAK}>:xbyak::xbyak>"
		"$<$<BOOL:${COMMONLIB_OPTION_TOML}>:toml11::toml11>"
		"$<$<BOOL:${COMMONLIB_OPTION_JSON}>:nlohmann_json::nlohmann_json>"
)

# --- Install ---

install(
	TARGETS
		"${PROJECT_NAME}"
	EXPORT
		"${PROJECT_NAME}Targets"
	ARCHIVE
		DESTINATION
			"${CMAKE_INSTALL_LIBDIR}"
	LIBRARY
		DESTINATION
			"${CMAKE_INSTALL_LIBDIR}"
	RUNTIME
		DESTINATION
			"${CMAKE_INSTALL_BINDIR}"
	INCLUDES
		DESTINATION
			"${CMAKE_INSTALL_INCLUDEDIR}"
)
