# MIT License

# Copyright (c) 2023 Ralf Hochhausen

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
###########################################################################################

# Component is compiled into a library
add_library(hwdrv_dig_input "")

target_sources(hwdrv_dig_input
	PRIVATE
		src/HighActiveInput/HighActiveInput.cpp
)

# Component include pathes
target_include_directories(hwdrv_dig_input
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_link_libraries(hwdrv_dig_input
    PRIVATE
        cmsis_core
        cmsis_device
        mcal_dio
        mcal_dioport
)

target_compile_features(hwdrv_dig_input PUBLIC cxx_std_17)