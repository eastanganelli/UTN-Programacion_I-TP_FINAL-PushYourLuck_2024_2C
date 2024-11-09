cmake_minimum_required(VERSION 3.16)

project(TP_FINAL_V2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TP_FINAL_V2 main.cpp
    creditos.cpp creditos.h menu.h rlutil.h juego.cpp juego.h
    creditos.cpp creditos.h main.cpp menu.cpp menu.h rlutil.h juego.cpp juego.h
    estadistica.cpp estadistica.h)

include(GNUInstallDirs)
install(TARGETS TP_FINAL_V2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
