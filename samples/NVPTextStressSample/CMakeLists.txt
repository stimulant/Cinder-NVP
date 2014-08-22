cmake_minimum_required(VERSION 2.8 FATAL_ERROR)


### =====================================================================================================
### Entry point. Check to see if the environment is set. 
### The path to cinder's root dir is a prerequisite.
### =====================================================================================================
set (CINDER_ROOT $ENV{CINDER_ROOT})
if ( "${CINDER_ROOT}" STREQUAL "" )
	message(FATAL_ERROR "
	**** 
	You must export the env variable CINDER_ROOT pointing to your Cinder root directory in order to proceed.. 
	Example: export CINDER_ROOT=/some/dir 
	Or you can add it permantly by modifying your .bashrc file 	
	NOTE: Always use absolute path to point to your Cinder installation
	****" )
endif()


### =====================================================================================================
### Cinder header files + default library dependencies. 
### =====================================================================================================
include (${CINDER_ROOT}/CMakeModules/CinderInclude.cmake)
include (${CINDER_ROOT}/CMakeModules/CinderDepends.cmake)


### =====================================================================================================
### Project name.
### =====================================================================================================
PROJECT( NVPTextStressSampleLinux ) 

### =====================================================================================================
### Turn ON to install the data under /usr/local/share/cinderapps.
### Default is OFF. Check the following comment about CMAKE_INSTALL_PREFIX.
### =====================================================================================================
option( INSTALL_APP_DATA_SYSTEM_WIDE "Install data under /usr/local/share/cinderapps" OFF ) 

### =====================================================================================================
### The directory where your bin along with any resources / assets 
### will be installed after running : make install 
### Defaults to '/usr/local/bin' but since it feels a bit awkward to be owened by
### by root without explicit reason we set it to the user home directory.
### This will create a dir with the following structure if INSTALL_APP_DATA_SYSTEM_WIDE option is OFF:
###
###     ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/bin
###     ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/resources
###     ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/assets
###
### If the INSTALL_APP_DATA_SYSTEM_WIDE option is ON then it will create the following dir structure:
###
###     ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/bin
###     /usr/local/share/cinderapps/resources
###     /usr/local/share/cinderapps/assets
###
### Change the install prefix to the directory of your choice.
### =====================================================================================================
set(CMAKE_INSTALL_PREFIX "$ENV{HOME}")


### =====================================================================================================
### VERBOSE CMAKE 
### =====================================================================================================
set ( CMAKE_COLOR_MAKEFILE ON )
set ( CMAKE_VERBOSE_MAKEFILE ON )


### =====================================================================================================
### COMPILER FLAGS 
### =====================================================================================================
if( CMAKE_COMPILER_IS_GNUCXX )
    set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -Wall -Wextra -Winvalid-pch -Wnon-virtual-dtor -Wsign-promo -Wshadow -Winit-self -Wno-unknown-pragmas -Wno-unused-parameter -Wno-write-strings" )
    set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -Wuninitialized" )
endif( CMAKE_COMPILER_IS_GNUCXX )


### =====================================================================================================
### INCLUDE DIRS 
### =====================================================================================================
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ../../src/include ${CMAKE_CURRENT_SOURCE_DIR}/include/ include ${CINDER_INCLUDE})


### =====================================================================================================
### SOURCE FILES 
### =====================================================================================================
list (APPEND source_files include/Globals.h include/Cinder-NVP/NVPTextBoxTest.h src/NVPTextStressSample.cpp src/Globals.cpp src/Cinder-NVP/NVPTextBoxTest.cpp ../../src/include/NVPFont.h ../../src/include/NVPTextBox.h ../../src/src/NVPFont.cpp ../../src/src/NVPTextBox.cpp)




###======================================================================================================
### You shouldn't ( need to ) modify anything below this line.
###======================================================================================================


###======================================================================================================
### Find cinder and glfw. 
###======================================================================================================
find_library(   CINDER_DEBUG 
                NAMES cinderDebug
                PATH_SUFFIXES CMake/libs libs
                PATHS $ENV{CINDER_ROOT}
            )

find_library(   CINDER_RELEASE 
                NAMES cinderRelease
                PATH_SUFFIXES CMake/libs libs
                PATHS $ENV{CINDER_ROOT}
            )

find_library(   GLFW3 
                NAMES glfw3
                PATH_SUFFIXES CMake/libs libs
                PATHS $ENV{CINDER_ROOT}
            )


###======================================================================================================
### Work with what you found. 
###======================================================================================================
if( CINDER_DEBUG AND NOT CINDER_RELEASE )
    set( CINDER_RELEASE ${CINDER_DEBUG} )
elseif( CINDER_RELEASE AND NOT CINDER_DEBUG)
    set( CINDER_DEBUG ${CINDER_RELEASE} )
elseif( NOT CINDER_DEBUG AND NOT CINDER_RELEASE )
    message(FATAL_ERROR " Neither Debug or Release build of Cinder could be found !! ")
endif( CINDER_DEBUG AND NOT CINDER_RELEASE )


###======================================================================================================
### Set the bin name according to the build type. 
###======================================================================================================
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set( bin ${PROJECT_NAME}_D )
else()
    set( bin ${PROJECT_NAME} )
endif()


###======================================================================================================
### Build bin from the specified source files. 
###======================================================================================================
add_executable( ${bin} ${source_files} )


###======================================================================================================
### Output directory for the executable. 
###======================================================================================================
set ( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )


###======================================================================================================
### Choose debug or release based on build type. 
###======================================================================================================
set( CINDER debug ${CINDER_DEBUG} optimized ${CINDER_RELEASE} )


###======================================================================================================
### Where to install the app data and bin. 
###======================================================================================================
if(INSTALL_APP_DATA_SYSTEM_WIDE)
    INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/resources DESTINATION "/usr/local/share/cinderapps" ) 
    INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/assets DESTINATION "/usr/local/share/cinderapps" ) 
else()
    INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/resources DESTINATION "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}" ) 
    INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/assets DESTINATION "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}" ) 
endif(INSTALL_APP_DATA_SYSTEM_WIDE)

INSTALL(TARGETS ${bin} DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/bin ) 


###======================================================================================================
### Link the executable with the necessary libraries. 
###======================================================================================================
target_link_libraries( ${bin} ${CINDER} ${GLFW3} ${CINDER_DEPENDS}) 

###======================================================================================================
### This is experimenting for now. 
###======================================================================================================
#set ( SOURCE_CODE_DIRECTORY ${CMAKE_SOURCE_DIR} )
#set ( APP_ROOT_DIR ${SOURCE_CODE_DIRECTORY} )
#configure_file( "CinderLinuxConfig.h.in" "${SOURCE_CODE_DIRECTORY}/include/CinderLinuxConfig.h" )
###======================================================================================================

