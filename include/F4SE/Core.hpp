#pragma once

namespace F4SE
{
	using PluginHandle = std::uint32_t;
	using ObjectHandle = std::int32_t;
	using SerializationTag = std::monostate;

	inline constexpr auto INVALID_PLUGIN_HANDLE = std::numeric_limits<PluginHandle>::max();
	inline constexpr auto DEFAULT_SERIALIZATION_TAG = SerializationTag();
}

#define F4SE_API __cdecl
#define F4SE_EXPORT extern "C" __declspec(dllexport)

#define F4SE_PLUGIN_VERSION F4SE_EXPORT constexpr F4SE::PluginVersionData F4SEPlugin_Version
#define F4SE_PLUGIN_PRELOAD(...) F4SE_EXPORT bool F4SEPlugin_Preload(__VA_ARGS__)
#define F4SE_PLUGIN_QUERY(...) F4SE_EXPORT bool F4SEPlugin_Query(__VA_ARGS__)
#define F4SE_PLUGIN_LOAD(...) F4SE_EXPORT bool F4SEPlugin_Load(__VA_ARGS__)
