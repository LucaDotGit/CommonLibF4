function(configure_xse_plugin_info commonlib_source_dir)
	set(_xse_plugin_info_source "${commonlib_source_dir}/assets/build/XsePluginInfo.cpp.in")
	set(_xse_plugin_info_target "${CMAKE_CURRENT_BINARY_DIR}/include/XsePluginInfo.cpp")

	set(_win32_version_source "${commonlib_source_dir}/assets/build/Win32Version.rc.in")
	set(_win32_version_target "${CMAKE_CURRENT_BINARY_DIR}/include/Win32Version.rc")

	configure_file(
		"${_xse_plugin_info_source}"
		"${_xse_plugin_info_target}"
		@ONLY
	)

	configure_file(
		"${_win32_version_source}"
		"${_win32_version_target}"
		@ONLY
	)

	target_sources(
		"${PROJECT_NAME}"
		PRIVATE
		"${_xse_plugin_info_target}"
		"${_win32_version_target}"
	)
endfunction()
