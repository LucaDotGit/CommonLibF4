# --- Project ---

cmake_minimum_required(VERSION 3.30)

project(
	CommonLibF4
	LANGUAGES CXX
)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
	message(FATAL_ERROR "In-source builds are not allowed.")
endif()

include(GNUInstallDirs)

# --- Options ---

option(ENABLE_FALLOUT_F4 "Enable support for Fallout 4 in the dynamic runtime feature." ON)
option(ENABLE_FALLOUT_NG "Enable support for Next-Gen Update Fallout 4 in the dynamic runtime feature." ON)
option(ENABLE_FALLOUT_VR "Enable support for Fallout 4 VR in the dynamic runtime feature." OFF)

option(F4SE_SUPPORT_XBYAK "Enables trampoline support for Xbyak." OFF)
option(REX_OPTION_INI "Enables ini config support for REX." OFF)
option(REX_OPTION_JSON "Enables json config support for REX." OFF)
option(REX_OPTION_TOML "Enables toml config support for REX." OFF)

message("Options:")

message("\tEnable Fallout 4: ${ENABLE_FALLOUT_F4}")
message("\tEnable Next-Gen Fallout 4: ${ENABLE_FALLOUT_NG}")
message("\tEnable Fallout 4 VR: ${ENABLE_FALLOUT_VR}")

message("\tEnable Xbyak: ${F4SE_SUPPORT_XBYAK}")
message("\tEnable INI: ${REX_OPTION_INI}")
message("\tEnable JSON: ${REX_OPTION_JSON}")
message("\tEnable TOML: ${REX_OPTION_TOML}")

if(NOT ENABLE_FALLOUT_F4 AND NOT ENABLE_FALLOUT_NG AND NOT ENABLE_FALLOUT_VR)
	message(FATAL_ERROR "At least one Fallout runtime must be supported by the CommonLibF4 build.")
endif()

# --- Add Dependencies ---

find_package(mmio REQUIRED CONFIG)
find_package(spdlog REQUIRED CONFIG)

if(ENABLE_FALLOUT_VR)
	find_path(RAPIDCSV_INCLUDE_DIRS "rapidcsv.h")
endif()

if(F4SE_SUPPORT_XBYAK)
	find_package(xbyak REQUIRED CONFIG)
endif()

if(REX_OPTION_INI)
	find_path(SIMPLEINI_INCLUDE_DIRS "simpleini.h")
endif()

if(REX_OPTION_JSON)
	find_package(nlohmann_json REQUIRED CONFIG)
endif()

if(REX_OPTION_TOML)
	find_package(toml11 REQUIRED CONFIG)
endif()

# --- Add Sources ---

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
		"${CMAKE_CURRENT_SOURCE_DIR}/include/F4SE/Impl/PCH.hpp"
)

source_group(
	TREE "${CMAKE_CURRENT_SOURCE_DIR}"
	FILES "${SOURCES}"
)

# --- Include ---

add_library(
	"${PROJECT_NAME}"
	STATIC
		"${SOURCES}"
)

add_library(
	"${PROJECT_NAME}::${PROJECT_NAME}"
	ALIAS
		"${PROJECT_NAME}"
)

target_include_directories(
	"${PROJECT_NAME}"
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
		"$<$<BOOL:${REX_OPTION_INI}>:${SIMPLEINI_INCLUDE_DIRS}>"
		"$<$<BOOL:${ENABLE_FALLOUT_VR}>:${RAPIDCSV_INCLUDE_DIRS}>"
)

target_precompile_headers(
	"${PROJECT_NAME}"
	PRIVATE
		"${CMAKE_CURRENT_SOURCE_DIR}/include/F4SE/Impl/PCH.hpp"
)

# --- Compile ---

target_compile_definitions(
	"${PROJECT_NAME}"
	PUBLIC
		WINVER=0x0601 # windows 7, minimum supported version by fallout 4
		_WIN32_WINNT=0x0601
		WIN32_LEAN_AND_MEAN
		NOMINMAX
		"$<$<BOOL:${REX_OPTION_INI}>:REX_OPTION_INI=1>"
		"$<$<BOOL:${REX_OPTION_JSON}>:REX_OPTION_JSON=1>"
		"$<$<BOOL:${REX_OPTION_TOML}>:REX_OPTION_TOML=1>"
		"$<$<BOOL:${F4SE_SUPPORT_XBYAK}>:F4SE_SUPPORT_XBYAK=1>"
		"$<$<BOOL:${ENABLE_FALLOUT_F4}>:ENABLE_FALLOUT_F4=1>"
		"$<$<BOOL:${ENABLE_FALLOUT_NG}>:ENABLE_FALLOUT_NG=1>"
		"$<$<BOOL:${ENABLE_FALLOUT_VR}>:ENABLE_FALLOUT_VR=1>"
)

target_compile_options(
	"${PROJECT_NAME}"
	PUBLIC
		/wd4200 # nonstandard extension used: zero-sized array in struct/union
		/wd4201 # nonstandard extension used: nameless struct/union
		/wd4324 # structure was padded due to alignment specifier
)

if(MSVC)
	target_link_options(
		"${PROJECT_NAME}"
		PUBLIC
			/WX
			"$<$<CONFIG:DEBUG>:/INCREMENTAL;/OPT:NOREF;/OPT:NOICF>"
			"$<$<CONFIG:RELEASE>:/INCREMENTAL:NO;/OPT:REF;/OPT:ICF;/DEBUG:FULL>"
	)

	target_compile_options(
		"${PROJECT_NAME}"
		PUBLIC
			/utf-8
			/WX
			/W4
			/MP
			/cgthreads8
			/Zi
			/sdl
			/permissive-
			/bigobj
			/Zc:__cplusplus
			/Zc:preprocessor
			/Zc:enumTypes
			/Zc:strictStrings
			/Zc:referenceBinding
			/Zc:rvalueCast
			/Zc:ternary
			/Zc:templateScope
			/Zc:throwingNew
			"$<$<CONFIG:DEBUG>:>"
			"$<$<CONFIG:RELEASE>:/O2;/GL;/Gw;/Oi;/Qpar>;/Zc:inline;/JMC-"
	)
endif()

# --- Link ---

target_link_libraries(
	"${PROJECT_NAME}"
	PUBLIC
		advapi32.lib
		bcrypt.lib
		d3d11.lib
		d3dcompiler.lib
		dbghelp.lib
		dxgi.lib
		ole32.lib
		version.lib
		mmio::mmio
		spdlog::spdlog
		"$<$<BOOL:${F4SE_SUPPORT_XBYAK}>:xbyak::xbyak>"
		"$<$<BOOL:${REX_OPTION_JSON}>:nlohmann_json::nlohmann_json>"
		"$<$<BOOL:${REX_OPTION_TOML}>:toml11::toml11>"
)

# --- Install ---

install(
	TARGETS "${PROJECT_NAME}"
	EXPORT "${PROJECT_NAME}-targets"
)

install(
	EXPORT "${PROJECT_NAME}-targets"
	NAMESPACE "${PROJECT_NAME}::"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

install(
	DIRECTORY
		"include/F4SE"
		"include/RE"
		"include/REL"
		"include/REX"
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
