function(copy_xse_copy_output commonlib_plugin_name)
	if(DEFINED XSE_OUTPUT_PATH AND NOT XSE_OUTPUT_PATH STREQUAL "")
		add_custom_command(
			TARGET "${commonlib_plugin_name}"
			POST_BUILD
				COMMAND
					"${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:${commonlib_plugin_name}>" "${XSE_OUTPUT_PATH}/$<TARGET_FILE_NAME:${commonlib_plugin_name}>"
				COMMAND
					"${CMAKE_COMMAND}" -E copy "$<TARGET_PDB_FILE:${commonlib_plugin_name}>" "${XSE_OUTPUT_PATH}/$<TARGET_PDB_FILE_NAME:${commonlib_plugin_name}>"
		)
	endif()
endfunction()
