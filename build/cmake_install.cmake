# Install script for directory: C:/DDNetClients/FeX/FeX.1

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/DDNet")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "E:/MSYS2/ucrt64/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "data" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet" TYPE DIRECTORY FILES "C:/DDNetClients/FeX/FeX.1/data")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/FeX.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/FeX.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/FeX.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/FeX.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/game-client.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/DDNetClients/FeX/FeX.1/build/libsteam_api.dll.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE SHARED_LIBRARY FILES "C:/DDNetClients/FeX/FeX.1/build/steam_api.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/steam_api.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/steam_api.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/steam_api.dll")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/steam_api.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "server" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/FeX-Server.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/FeX-Server.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/FeX-Server.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/FeX-Server.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "server" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/game-server.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/config_retrieve.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/config_retrieve.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/config_retrieve.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/config_retrieve.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/config_retrieve.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/config_store.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/config_store.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/config_store.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/config_store.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/config_store.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/crapnet.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/crapnet.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/crapnet.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/crapnet.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/crapnet.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/demo_extract_chat.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/demo_extract_chat.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/demo_extract_chat.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/demo_extract_chat.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/demo_extract_chat.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/dilate.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/dilate.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/dilate.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/dilate.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/dilate.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/dummy_map.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/dummy_map.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/dummy_map.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/dummy_map.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/dummy_map.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/map_convert_07.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_convert_07.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_convert_07.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_convert_07.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/map_convert_07.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/map_create_pixelart.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_create_pixelart.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_create_pixelart.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_create_pixelart.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/map_create_pixelart.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/map_diff.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_diff.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_diff.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_diff.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/map_diff.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/map_extract.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_extract.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_extract.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_extract.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/map_extract.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/map_find_env.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_find_env.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_find_env.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_find_env.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/map_find_env.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/map_optimize.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_optimize.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_optimize.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_optimize.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/map_optimize.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/map_replace_area.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_replace_area.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_replace_area.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_replace_area.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/map_replace_area.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/map_replace_image.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_replace_image.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_replace_image.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_replace_image.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/map_replace_image.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/map_resave.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_resave.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_resave.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/map_resave.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/map_resave.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/packetgen.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/packetgen.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/packetgen.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/packetgen.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/packetgen.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/stun.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/stun.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/stun.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/stun.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/stun.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/twping.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/twping.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/twping.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/twping.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/twping.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/unicode_confusables.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/unicode_confusables.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/unicode_confusables.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/unicode_confusables.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/unicode_confusables.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/ddnet" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/uuid.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/uuid.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/uuid.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/ddnet/uuid.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "tools" OR NOT CMAKE_INSTALL_COMPONENT)
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/uuid.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/applications" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/other/ddnet.desktop")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/16x16/apps" TYPE FILE RENAME "ddnet.png" FILES "C:/DDNetClients/FeX/FeX.1/other/icons/DDNet_16x16x32.png")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "server" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/16x16/apps" TYPE FILE RENAME "ddnet-server.png" FILES "C:/DDNetClients/FeX/FeX.1/other/icons/DDNet-Server_16x16x32.png")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/32x32/apps" TYPE FILE RENAME "ddnet.png" FILES "C:/DDNetClients/FeX/FeX.1/other/icons/DDNet_32x32x32.png")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "server" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/32x32/apps" TYPE FILE RENAME "ddnet-server.png" FILES "C:/DDNetClients/FeX/FeX.1/other/icons/DDNet-Server_32x32x32.png")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/48x48/apps" TYPE FILE RENAME "ddnet.png" FILES "C:/DDNetClients/FeX/FeX.1/other/icons/DDNet_48x48x32.png")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "server" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/48x48/apps" TYPE FILE RENAME "ddnet-server.png" FILES "C:/DDNetClients/FeX/FeX.1/other/icons/DDNet-Server_48x48x32.png")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/256x256/apps" TYPE FILE RENAME "ddnet.png" FILES "C:/DDNetClients/FeX/FeX.1/other/icons/DDNet_256x256x32.png")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "server" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/256x256/apps" TYPE FILE RENAME "ddnet-server.png" FILES "C:/DDNetClients/FeX/FeX.1/other/icons/DDNet-Server_256x256x32.png")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/prim.frag.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/prim_textured.frag.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/prim.vert.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/prim_textured.vert.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/prim3d.frag.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/prim3d_textured.frag.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/prim3d.vert.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/prim3d_textured.vert.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/text.frag.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/text.vert.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/primex.frag.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/primex.vert.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/primex_rotationless.frag.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/primex_rotationless.vert.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/primex_tex.frag.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/primex_tex.vert.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/primex_tex_rotationless.frag.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/primex_tex_rotationless.vert.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/spritemulti.frag.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/spritemulti.vert.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/spritemulti_push.frag.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/spritemulti_push.vert.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/tile.frag.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/tile.vert.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/tile_textured.frag.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/tile_textured.vert.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/tile_border.frag.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/tile_border.vert.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/tile_border_textured.frag.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/tile_border_textured.vert.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/quad.frag.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/quad.vert.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/quad_push.frag.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/quad_push.vert.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/quad_textured.frag.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/quad_textured.vert.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/quad_push_textured.frag.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "client" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ddnet/data/shader/vulkan" TYPE FILE FILES "C:/DDNetClients/FeX/FeX.1/build/data/shader/vulkan/quad_push_textured.vert.spv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/FeX.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/FeX.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/FeX.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/FeX.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/game-client.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/FeX-Server.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/FeX-Server.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/FeX-Server.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/FeX-Server.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/game-server.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/config_retrieve.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/config_retrieve.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/config_retrieve.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/config_retrieve.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/config_retrieve.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/config_store.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/config_store.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/config_store.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/config_store.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/config_store.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/demo_extract_chat.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/demo_extract_chat.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/demo_extract_chat.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/demo_extract_chat.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/demo_extract_chat.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/dilate.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/dilate.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/dilate.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/dilate.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/dilate.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/map_convert_07.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/map_convert_07.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/map_convert_07.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/map_convert_07.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/map_convert_07.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/map_create_pixelart.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/map_create_pixelart.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/map_create_pixelart.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/map_create_pixelart.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/map_create_pixelart.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/map_diff.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/map_diff.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/map_diff.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/map_diff.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/map_diff.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64" TYPE EXECUTABLE FILES "C:/DDNetClients/FeX/FeX.1/build/map_extract.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/map_extract.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/map_extract.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/map_extract.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/map_extract.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/DDNetClients/FeX/FeX.1/build/libsteam_api.dll.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64" TYPE SHARED_LIBRARY FILES "C:/DDNetClients/FeX/FeX.1/build/steam_api.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/steam_api.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/steam_api.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "E:/MSYS2/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64/steam_api.dll")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  include("C:/DDNetClients/FeX/FeX.1/build/CMakeFiles/steam_api.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64" TYPE DIRECTORY FILES "C:/DDNetClients/FeX/FeX.1/data")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "portable")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/DDNet-19.1-win64" TYPE FILE FILES
    "C:/DDNetClients/FeX/FeX.1/license.txt"
    "C:/DDNetClients/FeX/FeX.1/storage.cfg"
    "C:/DDNetClients/FeX/FeX.1/ddnet-libs/curl/windows/lib64/libcurl.dll"
    "C:/DDNetClients/FeX/FeX.1/ddnet-libs/curl/windows/lib64/zlib1.dll"
    "C:/DDNetClients/FeX/FeX.1/ddnet-libs/freetype/windows/lib64/libfreetype.dll"
    "C:/DDNetClients/FeX/FeX.1/ddnet-libs/opus/windows/lib64/libogg.dll"
    "C:/DDNetClients/FeX/FeX.1/ddnet-libs/opus/windows/lib64/libopus.dll"
    "C:/DDNetClients/FeX/FeX.1/ddnet-libs/opus/windows/lib64/libopusfile.dll"
    "C:/DDNetClients/FeX/FeX.1/ddnet-libs/opus/windows/lib64/libwinpthread-1.dll"
    "C:/DDNetClients/FeX/FeX.1/ddnet-libs/png/windows/lib64/libpng16-16.dll"
    "C:/DDNetClients/FeX/FeX.1/ddnet-libs/sdl/windows/lib64/SDL2.dll"
    "C:/DDNetClients/FeX/FeX.1/ddnet-libs/sqlite3/windows/lib64/sqlite3.dll"
    "C:/DDNetClients/FeX/FeX.1/ddnet-libs/ffmpeg/windows/lib64/avcodec-61.dll"
    "C:/DDNetClients/FeX/FeX.1/ddnet-libs/ffmpeg/windows/lib64/avformat-61.dll"
    "C:/DDNetClients/FeX/FeX.1/ddnet-libs/ffmpeg/windows/lib64/avutil-59.dll"
    "C:/DDNetClients/FeX/FeX.1/ddnet-libs/ffmpeg/windows/lib64/swresample-5.dll"
    "C:/DDNetClients/FeX/FeX.1/ddnet-libs/ffmpeg/windows/lib64/swscale-8.dll"
    "C:/DDNetClients/FeX/FeX.1/ddnet-libs/ssp/windows/lib64/libssp-0.dll"
    "C:/DDNetClients/FeX/FeX.1/other/config_directory.bat"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/prim.frag.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/prim_textured.frag.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/prim.vert.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/prim_textured.vert.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/prim3d.frag.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/prim3d_textured.frag.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/prim3d.vert.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/prim3d_textured.vert.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/text.frag.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/text.vert.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/primex.frag.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/primex.vert.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/primex_rotationless.frag.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/primex_rotationless.vert.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/primex_tex.frag.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/primex_tex.vert.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/primex_tex_rotationless.frag.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/primex_tex_rotationless.vert.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/spritemulti.frag.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/spritemulti.vert.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/spritemulti_push.frag.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/spritemulti_push.vert.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/tile.frag.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/tile.vert.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/tile_textured.frag.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/tile_textured.vert.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/tile_border.frag.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/tile_border.vert.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/tile_border_textured.frag.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/tile_border_textured.vert.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/quad.frag.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/quad.vert.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/quad_push.frag.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/quad_push.vert.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/quad_textured.frag.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/quad_textured.vert.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/quad_push_textured.frag.spv"
    "C:/DDNetClients/FeX/FeX.1/data/shader/vulkan/quad_push_textured.vert.spv"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/DDNetClients/FeX/FeX.1/build/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/DDNetClients/FeX/FeX.1/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
