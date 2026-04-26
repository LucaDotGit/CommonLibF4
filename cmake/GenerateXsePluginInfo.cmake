function(generate_xse_plugin_info commonlib_root_dir)
	set(__XSE_PLUGIN_INFO_HPP_SOURCE "${commonlib_root_dir}/res/XsePluginInfo.hpp.in")
	set(__XSE_PLUGIN_INFO_HPP_TARGET "${CMAKE_CURRENT_BINARY_DIR}/include/XsePluginInfo.hpp")

	set(__XSE_PLUGIN_INFO_CPP_SOURCE "${commonlib_root_dir}/res/XsePluginInfo.cpp.in")
	set(__XSE_PLUGIN_INFO_CPP_TARGET "${CMAKE_CURRENT_BINARY_DIR}/include/XsePluginInfo.cpp")

	set(__WIN32_VERSION_SOURCE "${commonlib_root_dir}/res/Win32Version.rc.in")
	set(__WIN32_VERSION_TARGET "${CMAKE_CURRENT_BINARY_DIR}/include/Win32Version.rc")

	configure_file("${__XSE_PLUGIN_INFO_HPP_SOURCE}" "${__XSE_PLUGIN_INFO_HPP_TARGET}" "@ONLY")
	configure_file("${__XSE_PLUGIN_INFO_CPP_SOURCE}" "${__XSE_PLUGIN_INFO_CPP_TARGET}" "@ONLY")
	configure_file("${__WIN32_VERSION_SOURCE}" "${__WIN32_VERSION_TARGET}" "@ONLY")

	set(XSE_PLUGIN_INFO_HPP_TARGET "${__XSE_PLUGIN_INFO_HPP_TARGET}" PARENT_SCOPE)
	set(XSE_PLUGIN_INFO_CPP_TARGET "${__XSE_PLUGIN_INFO_CPP_TARGET}" PARENT_SCOPE)
	set(WIN32_VERSION_TARGET "${__WIN32_VERSION_TARGET}" PARENT_SCOPE)
endfunction()
