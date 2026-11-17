# --- Project ---

cmake_minimum_required(VERSION 4.5.0)

option(
	COMMONLIB_FEATURE_FMT
	"Enable formatting support for `REX::Format`."
	TRUE
)

option(
	COMMONLIB_FEATURE_INI
	"Enable setting support for `REX::INI`."
	TRUE
)

option(
	COMMONLIB_FEATURE_TOML
	"Enable setting support for `REX::TOML`."
	TRUE
)

option(
	COMMONLIB_FEATURE_JSON
	"Enable setting support for `REX::JSON`."
	TRUE
)

option(
	COMMONLIB_FEATURE_YAML
	"Enable setting support for `REX::YAML`."
	TRUE
)

option(
	COMMONLIB_FEATURE_XBYAK
	"Enable hooking support for `REX::Trampoline`."
	TRUE
)

option(
	COMMONLIB_RUNTIME_VR
	"Enable runtime support for Virtual Reality (VR)."
	FALSE
)

option(
	COMMONLIB_RUNTIME_OG
	"Enable runtime support for Old-Gen (OG)."
	TRUE
)

option(
	COMMONLIB_RUNTIME_NG
	"Enable runtime support for Next-Gen (NG)."
	TRUE
)

option(
	COMMONLIB_RUNTIME_AE
	"Enable runtime support for the Anniversary Edition (AE)."
	TRUE
)

project(
	"CommonLibF4"
	SPDX_LICENSE "GPL-3.0-or-later"
	LANGUAGES CXX
)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
	message(
		FATAL_ERROR
		"In-source builds are not allowed."
	)
endif()

if(NOT (COMMONLIB_RUNTIME_VR OR COMMONLIB_RUNTIME_OG OR COMMONLIB_RUNTIME_NG OR COMMONLIB_RUNTIME_AE))
	message(
		FATAL_ERROR
		"At least one runtime option must be enabled."
	)
endif()

set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}")

include(CTest)
include(CPack)

# --- Dependencies ---

if(COMMONLIB_FEATURE_FMT)
	find_package(
		fmt
		REQUIRED
		CONFIG
	)
endif()

if(COMMONLIB_FEATURE_INI)
	find_path(
		SIMPLEINI_INCLUDE_DIR
		"SimpleIni.h"
		REQUIRED
	)
endif()

if(COMMONLIB_FEATURE_TOML OR COMMONLIB_FEATURE_JSON OR COMMONLIB_FEATURE_YAML OR COMMONLIB_RUNTIME_VR)
	# To-Do: Remove the git fetching once glaze is updated on vcpkg (v9.1.1+).

	include(FetchContent)

	FetchContent_Declare(
		glaze
		GIT_REPOSITORY "https://github.com/stephenberry/glaze.git"
		GIT_TAG "19bfcf599043377ba473fbac3f2e3a75912f53c7"
		OVERRIDE_FIND_PACKAGE
	)

	find_package(
		glaze
		REQUIRED
		CONFIG
	)
endif()

if(COMMONLIB_FEATURE_XBYAK)
	find_package(
		xbyak
		REQUIRED
		CONFIG
	)
endif()

# --- Source Files ---

add_library(
	"${PROJECT_NAME}"
	STATIC
)

add_library(
	"${PROJECT_NAME}::${PROJECT_NAME}"
	ALIAS
	"${PROJECT_NAME}"
)

file(
	GLOB_RECURSE
	_headers
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

file(
	GLOB_RECURSE
	_modules
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm"
)

file(
	GLOB_RECURSE
	_sources
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

target_sources(
	"${PROJECT_NAME}"
	PUBLIC
	FILE_SET HEADERS
	FILES ${_headers}

	PUBLIC
	FILE_SET CXX_MODULES
	FILES ${_modules}

	PRIVATE
	${_sources}
)

target_precompile_headers(
	"${PROJECT_NAME}"
	PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/src/F4SE/Impl/PCH.hpp"
)

target_include_directories(
	"${PROJECT_NAME}"
	PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/src"

	PUBLIC
	"$<$<BOOL:${COMMONLIB_FEATURE_INI}>:${SIMPLEINI_INCLUDE_DIR}>"
)

# --- Compilation ---

function(configure_compile_pathmap_options)
	foreach(_prefix_path IN LISTS CMAKE_SYSTEM_PREFIX_PATH)
		if(NOT IS_ABSOLUTE "${_prefix_path}")
			continue()
		endif()

		cmake_path(
			GET
			_prefix_path
			FILENAME
			_prefix_name
		)

		string(
			REGEX
			REPLACE
			"[^a-zA-Z0-9]+"
			"_"
			_prefix_name
			"${_prefix_name}"
		)

		string(
			REGEX
			REPLACE
			"_+"
			"_"
			_prefix_name
			"${_prefix_name}"
		)

		string(
			REGEX
			REPLACE
			"^_+|_+$"
			""
			_prefix_name
			"${_prefix_name}"
		)

		string(
			TOUPPER
			"${_prefix_name}"
			_prefix_name
		)

		target_compile_options(
			"${PROJECT_NAME}"
			PUBLIC
			"/pathmap:${_prefix_path}=__${_prefix_name}__"
		)
	endforeach()
endfunction()

target_compile_definitions(
	"${PROJECT_NAME}"
	PUBLIC
	"WINVER=0x0A00"
	"_WIN32_WINNT=0x0A00"
	"WIN32_LEAN_AND_MEAN=1"
	"VC_EXTRALEAN=1"
	"NOMINMAX=1"

	PUBLIC
	"COMMONLIB_FEATURE_FMT=$<IF:$<BOOL:${COMMONLIB_FEATURE_FMT}>,1,0>"
	"COMMONLIB_FEATURE_INI=$<IF:$<BOOL:${COMMONLIB_FEATURE_INI}>,1,0>"
	"COMMONLIB_FEATURE_TOML=$<IF:$<BOOL:${COMMONLIB_FEATURE_TOML}>,1,0>"
	"COMMONLIB_FEATURE_JSON=$<IF:$<BOOL:${COMMONLIB_FEATURE_JSON}>,1,0>"
	"COMMONLIB_FEATURE_YAML=$<IF:$<BOOL:${COMMONLIB_FEATURE_YAML}>,1,0>"
	"COMMONLIB_FEATURE_XBYAK=$<IF:$<BOOL:${COMMONLIB_FEATURE_XBYAK}>,1,0>"
	"COMMONLIB_RUNTIME_VR=$<IF:$<BOOL:${COMMONLIB_RUNTIME_VR}>,1,0>"
	"COMMONLIB_RUNTIME_OG=$<IF:$<BOOL:${COMMONLIB_RUNTIME_OG}>,1,0>"
	"COMMONLIB_RUNTIME_NG=$<IF:$<BOOL:${COMMONLIB_RUNTIME_NG}>,1,0>"
	"COMMONLIB_RUNTIME_AE=$<IF:$<BOOL:${COMMONLIB_RUNTIME_AE}>,1,0>"

	PUBLIC
	"$<$<BOOL:${COMMONLIB_FEATURE_INI}>:SI_NO_CONVERSION=1>"
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "19.52")
		message(
			FATAL_ERROR
			"Unsupported MSVC version: ${CMAKE_CXX_COMPILER_VERSION}."
		)
	endif()

	target_compile_options(
		"${PROJECT_NAME}"
		PUBLIC
		"/arch:SSE4.2"
		"/bigobj"
		"/Brepro"
		"/diagnostics:caret"
		"/EHsc"
		"/external:W0"
		"/fp:contract"
		"/fp:except-"
		"/guard:cf-"
		"/jumptablerdata"
		"/MP"
		"/nologo"
		"/options:strict"
		"/permissive-"
		"/sdl"
		"/utf-8"
		"/volatile:iso"
		"/volatileMetadata"
		"/Zc:__cplusplus"
		"/Zc:checkGwOdr"
		"/Zc:enumTypes"
		"/Zc:inline"
		"/Zc:preprocessor"
		"/Zc:templateScope"
		"/Zc:throwingNew"
		"/Zf"
		"/ZH:SHA_256"
		"/Zi"
	)

	# Deterministic MSVC builds seem to be currently broken with Ninja.
	if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
		target_compile_options(
			"${PROJECT_NAME}"
			PUBLIC
			"/experimental:deterministic"
			"/pathmap:${CMAKE_SOURCE_DIR}=__ROOT__/${CMAKE_PROJECT_NAME}"
		)

		configure_compile_pathmap_options()
	endif()

	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(
			"${PROJECT_NAME}"
			PUBLIC
			"/JMC"
			"/MDd"
			"/Ob0"
			"/Od"
		)
	else()
		target_compile_options(
			"${PROJECT_NAME}"
			PUBLIC
			"/GL"
			"/Gw"
			"/MD"
			"/Ob2"
		)

		if(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
			target_compile_options(
				"${PROJECT_NAME}"
				PUBLIC
				"/O1"
			)
		else()
			target_compile_options(
				"${PROJECT_NAME}"
				PUBLIC
				"/O2"
			)
		endif()
	endif()

	target_compile_options(
		"${PROJECT_NAME}"
		PUBLIC
		"/WX"

		PUBLIC
		"/Wall"

		PUBLIC
		"/wd4061"
		"/wd4200"
		"/wd4201"
		"/wd4263"
		"/wd4264"
		"/wd4266"
		"/wd4324"
		"/wd4365"
		"/wd4464"
		"/wd4514"
		"/wd4582"
		"/wd4583"
		"/wd4599"
		"/wd4623"
		"/wd4624"
		"/wd4625"
		"/wd4626"
		"/wd4668"
		"/wd4710"
		"/wd4711"
		"/wd4820"
		"/wd4866"
		"/wd4868"
		"/wd5024"
		"/wd5026"
		"/wd5027"
		"/wd5045"
		"/wd5220"
		"/wd5246"
		"/wd5291"
	)

	target_link_options(
		"${PROJECT_NAME}"
		PUBLIC
		"/brepro"
		"/debug:full"
		"/nologo"
		"/pdbaltpath:$<TARGET_PDB_FILE_NAME:${CMAKE_PROJECT_NAME}>"
		"/wx"
	)

	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_link_options(
			"${PROJECT_NAME}"
			PUBLIC
			"/incremental:no"
			"/opt:noicf,noref"
		)
	else()
		target_link_options(
			"${PROJECT_NAME}"
			PUBLIC
			"/incremental:no"
			"/ltcg"
			"/opt:icf=2"
			"/opt:ref"
		)
	endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "23.1.0")
		message(
			FATAL_ERROR
			"Unsupported clang-cl version: ${CMAKE_CXX_COMPILER_VERSION}."
		)
	endif()

	target_compile_options(
		"${PROJECT_NAME}"
		PUBLIC
		"/clang:-fms-extensions"
		"/clang:-fno-ms-compatibility"

		PUBLIC
		"/clang:-fgnuc-version=0"
		"/clang:-fno-delayed-template-parsing"
		"/clang:-fstrict-aliasing"
		"/clang:-fwrapv"

		PUBLIC
		"/clang:-ffile-compilation-dir=."
		"/clang:-ffile-reproducible"
		"/clang:-msse4.2"
		"/clang:-no-canonical-prefixes"

		PUBLIC
		"/Brepro"
		"/diagnostics:caret"
		"/EHsc"
		"/experimental:deterministic"
		"/external:W0"
		"/fp:contract"
		"/fp:except-"
		"/guard:cf-"
		"/pathmap:${CMAKE_SOURCE_DIR}=__ROOT__/${CMAKE_PROJECT_NAME}"
		"/permissive-"
		"/utf-8"
		"/volatile:iso"
		"/ZH:SHA_256"
		"/Zi"
	)

	configure_compile_pathmap_options()

	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(
			"${PROJECT_NAME}"
			PUBLIC
			"/JMC"
			"/MDd"
			"/Ob0"
			"/Od"
		)
	else()
		target_compile_options(
			"${PROJECT_NAME}"
			PUBLIC
			"/clang:-flto"

			PUBLIC
			"/Gw"
			"/MD"
			"/Ob2"
		)

		if(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
			target_compile_options(
				"${PROJECT_NAME}"
				PUBLIC
				"/O1"
			)
		else()
			target_compile_options(
				"${PROJECT_NAME}"
				PUBLIC
				"/O2"
			)
		endif()
	endif()

	target_compile_options(
		"${PROJECT_NAME}"
		PUBLIC
		"/clang:-Werror"

		PUBLIC
		"/clang:-Weverything"

		PUBLIC
		"/clang:-Wno-c++98-compat"
		"/clang:-Wno-c++98-compat-pedantic"
		# "/clang:-Wno-c++98-extensions"

		"/clang:-Wno-c++11-compat"
		"/clang:-Wno-c++11-compat-pedantic"
		"/clang:-Wno-c++11-extensions"

		"/clang:-Wno-c++14-compat"
		"/clang:-Wno-c++14-compat-pedantic"
		"/clang:-Wno-c++14-extensions"

		"/clang:-Wno-c++17-compat"
		"/clang:-Wno-c++17-compat-pedantic"
		"/clang:-Wno-c++17-extensions"

		"/clang:-Wno-c++20-compat"
		"/clang:-Wno-c++20-compat-pedantic"
		"/clang:-Wno-c++20-extensions"

		# "/clang:-Wno-c++23-compat"
		# "/clang:-Wno-c++23-compat-pedantic"
		"/clang:-Wno-c++23-extensions"

		"/clang:-Wpre-c++26-compat"
		"/clang:-Wpre-c++26-compat-pedantic"

		PUBLIC
		"/clang:-Wno-covered-switch-default"
		"/clang:-Wno-ctad-maybe-unsupported"
		"/clang:-Wno-dollar-in-identifier-extension"
		"/clang:-Wno-exit-time-destructors"
		"/clang:-Wno-extra-semi"
		"/clang:-Wno-float-equal"
		"/clang:-Wno-global-constructors"
		"/clang:-Wno-gnu-anonymous-struct"
		"/clang:-Wno-gnu-zero-variadic-macro-arguments"
		"/clang:-Wno-language-extension-token"
		"/clang:-Wno-lifetime-safety-invalidation"
		"/clang:-Wno-lifetime-safety-suggestions"
		"/clang:-Wno-missing-prototypes"
		"/clang:-Wno-missing-variable-declarations"
		"/clang:-Wno-nested-anon-types"
		"/clang:-Wno-nrvo"
		"/clang:-Wno-overloaded-virtual"
		"/clang:-Wno-padded"
		"/clang:-Wno-reserved-identifier"
		"/clang:-Wno-shadow-uncaptured-local"
		"/clang:-Wno-switch-enum"
		"/clang:-Wno-undef"
		"/clang:-Wno-unsafe-buffer-usage"
		"/clang:-Wno-unused-macros"
		"/clang:-Wno-unused-member-function"
		"/clang:-Wno-zero-length-array"
	)

	target_link_options(
		"${PROJECT_NAME}"
		PUBLIC
		"/brepro"
		"/debug:full"
		"/nologo"
		"/pdbaltpath:$<TARGET_PDB_FILE_NAME:${CMAKE_PROJECT_NAME}>"
		"/wx"
	)

	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_link_options(
			"${PROJECT_NAME}"
			PUBLIC
			"/incremental:no"
			"/opt:noicf,noref"
		)
	else()
		target_link_options(
			"${PROJECT_NAME}"
			PUBLIC
			"/incremental:no"
			"/ltcg"
			"/opt:icf=2"
			"/opt:ref"
		)
	endif()
else()
	message(
		FATAL_ERROR
		"Unsupported compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT} ${CMAKE_CXX_COMPILER_VERSION}."
	)
endif()

# --- Linkage ---

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

	PUBLIC
	"$<$<BOOL:${COMMONLIB_FEATURE_FMT}>:fmt::fmt>"
	"$<$<OR:$<BOOL:${COMMONLIB_FEATURE_TOML}>,$<BOOL:${COMMONLIB_FEATURE_JSON}>,$<BOOL:${COMMONLIB_FEATURE_YAML}>,$<BOOL:${COMMONLIB_RUNTIME_VR}>>:glaze::glaze>"
	"$<$<BOOL:${COMMONLIB_FEATURE_XBYAK}>:xbyak::xbyak>"
)
