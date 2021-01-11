project(TankWars)
cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 14)

# Source Files
set(SOURCE_FILES
        src/main.cpp
        src/auxiliares/auxiliares.cpp
        src/objetos/armas/Arma.cpp
        src/objetos/armas/armas.cpp
        src/objetos/armas/Incinerador.cpp
        src/objetos/armas/IncineradorMk2.cpp
        src/objetos/armas/Bomba20Kilotons.cpp
        src/objetos/armas/Bomba5Megatons.cpp
        src/cenario/Cenario.cpp
        src/objetos/explosoes/BolaDeFogo.cpp
        src/globals.cpp
        src/interacoes.cpp
        src/objetos/jogador.cpp
        src/ui/menu/Menu.cpp
        src/mundo.cpp
        src/objetos2D.cpp
        src/objetos3D.cpp
        src/cenario/Terreno.cpp
        src/ui/menu/ItemMenu.cpp
        src/ui/menu/ItemMenuBotao.cpp
        src/graphics/cor.cpp
        src/ui/menu/ItemMenuEditarNome.cpp
        src/ui/menu/ItemMenuAlterarValorNumerico.cpp
        src/ui/menu/ItemMenuRetangular.cpp
        src/cenario/Tanque.cpp
        src/cenario/Projetil.cpp
        src/cenario/CenarioObject.cpp
        )

add_executable(TankWars ${SOURCE_FILES})
include_directories(include)

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
#target_link_libraries(TankWars "glu32" "opengl32" "glut32cu")

# em 2020 - Após instalar o MSYS2 para utilizar o mingw64, passei a utilizar a biblioteca FreeGlut
# que vem disponiblizada e configurada pelo próprio MSYS2.
# Dessa forma, as novas bibliotecas a serem linkadas são glu32, freeglut e opengl32.
target_link_libraries(TankWars "glu32" "freeglut" "opengl32")