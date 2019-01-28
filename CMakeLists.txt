project(TankWars)
cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
# Source Files
set(SOURCE_FILES
        src/main.cpp
        src/armas.cpp
        src/auxiliares.cpp
        src/cenario.cpp
        src/configmenu.cpp
        src/constantes.cpp
        src/explosoes.cpp
        src/globals.cpp
        src/interacoes.cpp
        src/interfaces.cpp
        src/jogador.cpp
        src/menu.cpp
        src/mundo.cpp
        src/municao.cpp
        src/objetos2D.cpp
        src/objetos3D.cpp
        src/terreno.cpp
        src/ui/menu/ItemMenu.cpp
        src/ui/menu/Botao.cpp)

add_executable(TankWars ${SOURCE_FILES})
#[[
Solução definitiva para fazer o OpenGL funcionar foi baseado nesta página
https://www.codepool.biz/cc-barcode-app-cmake-windows.html

Como o OpenGL já está instalado no meu PC, não precisei importar bibliotecas nem nada. Precisei apenas escrever
dentro do comando target_link_libraries os termos que precisam ser usados no linker, que eram

-lglu32 -lopengl32 -lglut32cu

Os termos a serem passados, portanto, são aqueles sem a letra L. Ficam conforme mostrado abaixo.

O que ainda preciso aprender para o futuro, e que ainda não consegui fazer funcionar:
 - Como realmente integrar uma biblioteca externa? Ou seja, uma que esteja no diretório lib?
]]
target_link_libraries(TankWars "glu32" "opengl32" "glut32cu")


# Tentativas anteriores

#link_directories(${PROJECT_SOURCE_DIR}/lib/gl)
#include_directories(${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/include)

##--- Find GLUT
#find_package(GLUT REQUIRED)
##include_directories(${GLUT_INCLUDE_DIRS})
##link_directories(${GLUT_LIBRARY_DIRS})
##add_definitions(${GLUT_DEFINITIONS})
#if(NOT GLUT_FOUND)
#    message(ERROR  " GLUT not found!")
#else()
#    message("GLUT_LIBRARY: " ${GLUT_LIBRARY})
#    message("GLUT_INCLUDE_DIRS: " ${GLUT_INCLUDE_DIRS})
#    message("GLUT_DEFINITIONS: " ${GLUT_DEFINITIONS})
#endif(NOT GLUT_FOUND)
#message("")
#
##--- Find OpenGL
#find_package(OpenGL REQUIRED)
##include_directories(${OpenGL_INCLUDE_DIRS})
##link_directories(${OpenGL_LIBRARY_DIRS})
##add_definitions(${OpenGL_DEFINITIONS})
#if(NOT OPENGL_FOUND)
#    message(ERROR " OPENGL not found!")
#else()
#    message("OPENGL_LIBRARY: " ${OPENGL_LIBRARY})
#    message("OPENGL_glu_LIBRARY: " ${OPENGL_glu_LIBRARY})
#    message("OPENGL_gl_LIBRARY: " ${OPENGL_gl_LIBRARY})
#    message("OPENGL_INCLUDE_DIRS: " ${OPENGL_INCLUDE_DIRS})
#    message("OPENGL_DEFINITIONS: " ${OPENGL_DEFINITIONS})
#    get_target_property(GLU_IMPORTED_LIBNAME OpenGL::GLU IMPORTED_LIBNAME)
#    message(STATUS "glu imported libname: ${GLU_IMPORTED_LIBNAME}")
#endif(NOT OPENGL_FOUND)
