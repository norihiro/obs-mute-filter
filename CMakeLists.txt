cmake_minimum_required(VERSION 3.12)

project(obs-mute-filter VERSION 0.3.0)

# Replace `Your Name Here` with the name (yours or your organization's) you want
# to see as the author of the plugin (in the plugin's metadata itself and in the installers)
set(PLUGIN_AUTHOR "Norihiro Kamae")

# Replace `com.example.obs-plugin-template` with a unique Bundle ID for macOS releases
# (used both in the installer and when submitting the installer for notarization)
set(MACOS_BUNDLEID "net.nagater.obs-mute-filter")
set(MACOS_PACKAGE_UUID "AC34BEA6-6AAB-4CAE-AE0F-222F49F0503A")
set(MACOS_INSTALLER_UUID "4F2A848B-08BE-4EED-AD7F-824BD7B97A8A")
set(PLUGIN_URL "https://obsproject.com/forum/resources/mute-filter.1478/")
set(ID_PREFIX "net.nagater.obs-mute-filter.")

# Replace `me@contoso.com` with the maintainer email address you want to put in Linux packages
set(LINUX_MAINTAINER_EMAIL "norihiro@nagater.net")

# TAKE NOTE: No need to edit things past this point

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
	find_package(libobs REQUIRED)
	include(cmake/ObsPluginHelpers.cmake)
endif()

configure_file(
	src/plugin-macros.h.in
	plugin-macros.generated.h
)

set(PLUGIN_SOURCES
	src/plugin-main.c
	src/mute-filter.c
	src/mute-filter-by-ui.c
)

add_library(${PROJECT_NAME} MODULE ${PLUGIN_SOURCES})

target_link_libraries(${PROJECT_NAME}
	OBS::libobs
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

if(OS_WINDOWS)
	# Enable Multicore Builds and disable FH4 (to not depend on VCRUNTIME140_1.DLL when building with VS2019)
	if (MSVC)
		add_definitions(/MP /d2FH4-)
	endif()

	target_link_libraries(${PROJECT_NAME} OBS::w32-pthreads)
endif()

if(OS_LINUX)
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

if(APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -fvisibility=default")

	set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
	set(MACOSX_PLUGIN_GUI_IDENTIFIER "${MACOS_BUNDLEID}")
	set(MACOSX_PLUGIN_BUNDLE_VERSION "${PROJECT_VERSION}")
	set(MACOSX_PLUGIN_SHORT_VERSION_STRING "1")
endif()

setup_plugin_target(${PROJECT_NAME})

configure_file(installer/installer-macOS.pkgproj.in installer-macOS.generated.pkgproj)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
	configure_file(
		installer/installer-Windows.iss.in
		installer-Windows.generated.iss
	)

	configure_file(
		ci/ci_includes.sh.in
		ci/ci_includes.generated.sh
	)

	configure_file(
		ci/ci_includes.cmd.in
		ci/ci_includes.generated.cmd
	)
endif()
