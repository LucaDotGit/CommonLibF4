function(set_xse_output_path commonlib_plugin_name)
	set(__XSE_FO4_DO_PARENT_COPY "$ENV{XSE_FO4_DO_PARENT_COPY}")
	set(__XSE_FO4_MODS_PATH "$ENV{XSE_FO4_MODS_PATH}")
	set(__XSE_FO4_GAME_PATH "$ENV{XSE_FO4_GAME_PATH}")

	set(__XSE_OUTPUT_PATH "")

	if(__XSE_FO4_DO_PARENT_COPY)
		set(__XSE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/..")
	elseif(__XSE_FO4_MODS_PATH)
		set(__XSE_OUTPUT_PATH "${__XSE_FO4_MODS_PATH}/${commonlib_plugin_name}/F4SE/Plugins")
	elseif(__XSE_FO4_GAME_PATH)
		set(__XSE_OUTPUT_PATH "${__XSE_FO4_GAME_PATH}/Data/F4SE/Plugins")
	endif()

	set(XSE_OUTPUT_PATH "${__XSE_OUTPUT_PATH}" PARENT_SCOPE)
endfunction()
