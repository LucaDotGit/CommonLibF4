function(configure_xse_output_path)
	set(_xse_fo4_relative_plugins_path "F4SE/Plugins")

	set(_xse_fo4_do_parent_copy "$ENV{XSE_FO4_DO_PARENT_COPY}")
	set(_xse_fo4_mods_path "$ENV{XSE_FO4_MODS_PATH}")
	set(_xse_fo4_game_path "$ENV{XSE_FO4_GAME_PATH}")

	set(_xse_output_path "")

	if(_xse_fo4_do_parent_copy)
		set(_xse_output_path "${CMAKE_CURRENT_SOURCE_DIR}/..")
	elseif(_xse_fo4_mods_path)
		set(_xse_output_path "${_xse_fo4_mods_path}/${PROJECT_NAME}/${_xse_fo4_relative_plugins_path}")
	elseif(_xse_fo4_game_path)
		set(_xse_output_path "${_xse_fo4_game_path}/Data/${_xse_fo4_relative_plugins_path}")
	endif()

	install(
		FILES "$<TARGET_FILE:${PROJECT_NAME}>"
		DESTINATION "${_xse_fo4_relative_plugins_path}"
	)

	install(
		FILES "$<TARGET_PDB_FILE:${PROJECT_NAME}>"
		DESTINATION "${_xse_fo4_relative_plugins_path}"
	)

	install(
		DIRECTORY "${CMAKE_SOURCE_DIR}/assets/"
		DESTINATION "."
	)

	if(_xse_output_path)
		add_custom_command(
			TARGET "${PROJECT_NAME}"
			POST_BUILD
			COMMAND
			"${CMAKE_COMMAND}" -E make_directory
			"${_xse_output_path}"
			COMMAND
			"${CMAKE_COMMAND}" -E copy
			"$<TARGET_FILE:${PROJECT_NAME}>"
			"${_xse_output_path}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
			COMMAND
			"${CMAKE_COMMAND}" -E copy
			"$<TARGET_PDB_FILE:${PROJECT_NAME}>"
			"${_xse_output_path}/$<TARGET_PDB_FILE_NAME:${PROJECT_NAME}>"
		)
	endif()
endfunction()
