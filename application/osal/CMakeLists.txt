add_library(osal)

target_link_libraries( osal
	INTERFACE
		freertos_kernel
)

target_include_directories( osal
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_sources( osal
	PRIVATE
		src/freeRTOS/osal_freeRTOS.cpp
)
