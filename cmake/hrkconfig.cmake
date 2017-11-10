# lic:#
# lic:#    Copyright (C) 2017  Harkaitz Agirre Ezama
# lic:#
# lic:#    This file is part of hrk-package.
# lic:#
# lic:#    hrk-package is free software: you can redistribute it and/or modify
# lic:#    it under the terms of the GNU Lesser General Public License as published by
# lic:#    the Free Software Foundation, either version 3 of the License, or
# lic:#    (at your option) any later version.
# lic:#
# lic:#    hrk-package is distributed in the hope that it will be useful,
# lic:#    but WITHOUT ANY WARRANTY; without even the implied warranty of
# lic:#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# lic:#    GNU Lesser General Public License for more details.
# lic:#
# lic:#    You should have received a copy of the GNU Lesser General Public License
# lic:#    along with hrk-package.  If not, see <http://www.gnu.org/licenses/>.
# lic:#
## 
##
if(EXISTS ${CMAKE_SOURCE_DIR}/cmake/project-config.cmake.in)
include(CMakePackageConfigHelpers)
configure_package_config_file(
  cmake/project-config.cmake.in
  ${PROJECT_NAME}-config.cmake
  INSTALL_DESTINATION lib/${PROJECT_NAME}-${PROJECT_VERSION})
write_basic_package_version_file(
  ${PROJECT_NAME}-config-version.cmake
  VERSION       ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)
install(
  FILES
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  DESTINATION lib/${PROJECT_NAME}-${PROJECT_VERSION})
endif()
