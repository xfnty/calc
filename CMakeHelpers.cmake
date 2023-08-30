cmake_minimum_required(VERSION 3.5)


macro(list_sources OUTPUT DIRECTORY)
    file(GLOB_RECURSE ALL_SOURCES "${DIRECTORY}/*.c*")
    list(APPEND ${OUTPUT} ${ALL_SOURCES})
	list(FILTER ${OUTPUT} EXCLUDE REGEX ".ignore")
endmacro()


macro(list_subdirs OUTPUT DIRECTORY)
    file(GLOB children RELATIVE "${DIRECTORY}" "${DIRECTORY}/*")
    set(subdirs "")
    foreach(child ${children})
        if(IS_DIRECTORY "${DIRECTORY}/${child}")
            list(APPEND subdirs ${child})
        endif()
    endforeach()
    set(${OUTPUT} ${subdirs})
endmacro()


macro(include_thirdparty NAME INCLUDE_DIR LIBNAME)
    set("${NAME}_DIR" "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${NAME}")
    add_subdirectory(${${NAME}_DIR})
    list(APPEND INCLUDES "${${NAME}_DIR}/${INCLUDE_DIR}")
    list(APPEND LINK_LIBRARIES "${LIBNAME}")
endmacro()
