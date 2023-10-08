add_library(osal)

target_link_libraries( osal
	PRIVATE
		freertos_kernel
)

target_include_directories( osal
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_sources( osal
	PRIVATE
		src/freeRTOS/osal_freeRTOS.cpp
)
