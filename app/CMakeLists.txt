cmake_minimum_required(VERSION 3.16)
project(Fichaje VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# --- Icono macOS (.icns) ---
set(APP_ICON_MAC "${CMAKE_CURRENT_SOURCE_DIR}/resources/AppIcon.icns")
set_source_files_properties(
  ${APP_ICON_MAC}
  PROPERTIES MACOSX_PACKAGE_LOCATION "Resources"
)

# --- Icono Windows: .rc + .ico ---
if(WIN32)
  set(APP_ICON_RC "${CMAKE_CURRENT_SOURCE_DIR}/resources/app.rc")
  set_source_files_properties(${APP_ICON_RC} PROPERTIES LANGUAGE RC)
endif()

# Fuentes de tu aplicación
set(PROJECT_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.ui
)

# Crea el ejecutable incluyendo iconos según plataforma
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  # En Qt6 usamos qt_add_executable y MANUAL_FINALIZATION para Bundle
  qt_add_executable(Fichaje
    MANUAL_FINALIZATION
	${PROJECT_SOURCES}
	${APP_ICON_MAC}
	$<$<BOOL:${WIN32}>:${APP_ICON_RC}>
	resources/resources.qrc
  )

else()
  if(ANDROID)
    add_library(Fichaje SHARED
      ${PROJECT_SOURCES}
      ${APP_ICON_MAC}
      $<$<BOOL:${WIN32}>:${APP_ICON_RC}>
    )
  else()
    add_executable(Fichaje
      ${PROJECT_SOURCES}
      ${APP_ICON_MAC}
      $<$<BOOL:${WIN32}>:${APP_ICON_RC}>
    )
  endif()
endif()

target_link_libraries(Fichaje PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Propiedades de Bundle para macOS
set_target_properties(Fichaje PROPERTIES
  MACOSX_BUNDLE            TRUE
  MACOSX_BUNDLE_ICON_FILE  "AppIcon.icns"
  MACOSX_BUNDLE_BUNDLE_VERSION       ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  WIN32_EXECUTABLE         TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(Fichaje)
endif()

include(GNUInstallDirs)
install(TARGETS Fichaje
  BUNDLE   DESTINATION .
  LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
)
