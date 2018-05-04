#
# Copyright 2017-2018 Lyashenko "Good_Pudge" Arsenii <arsenylyashenko.3@gmail.com>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

set(FIND_PATHS
		~/Library/Frameworks
		/Library/Frameworks
		/sw
		/opt/local
		/opt/csw
		/opt
		/usr
		/usr/local)

find_library(OHF_LIBRARIES
		NAMES ohf
		HINTS "${OHF_ROOT_DIR}"
		PATHS "${FIND_PATHS}"
		PATH_SUFFIXES lib)

find_path(OHF_INCLUDE_DIR
		NAME ohf/Config.hpp
		HINTS "${OHF_ROOT_DIR}"
		PATHS "${FIND_PATHS}"
		PATH_SUFFIXES include)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(OHF DEFAULT_MSG
		OHF_INCLUDE_DIR
		OHF_LIBRARIES)

if(OHF_FOUND)
	add_library(OHF::ohf UNKNOWN IMPORTED)
	set_target_properties(OHF::ohf PROPERTIES
			IMPORTED_LOCATION                 "${OHF_LIBRARIES}"
			INTERFACE_INCLUDE_DIRECTORIES     "${OHF_INCLUDE_DIR}"
			IMPORTED_LINK_INTERFACE_LANGUAGES "C CXX")
endif()

mark_as_advanced(OHF_INCLUDE_DIR OHF_LIBRARIES)
