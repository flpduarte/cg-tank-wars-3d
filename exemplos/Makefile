# Variáveis utilizadas pelas instruções implícitas
CXXFLAGS = -O0 -ggdb3
LDLIBS   = -lm -lglut32cu -lglu32 -lopengl32

DEPS_TANQUE  = ..\src\objetos3D.o ..\src\auxiliares.o ..\src\constantes.o ..\src\jogador.o ..\src\armas.o ..\src\municao.o ..\src\explosoes.o
DEPS_TERRENO = ..\src\objetos3D.o ..\src\auxiliares.o ..\src\constantes.o ..\src\jogador.o ..\src\armas.o ..\src\municao.o ..\src\explosoes.o ..\src\cenario.o ..\src\terreno.o

# default target
terreno: Makefile teste_terreno.o $(DEPS_TERRENO)
	$(CXX) $(CXXFLAGS) -o terreno teste_terreno.o $(DEPS_TERRENO) $(LDLIBS)

tanque: Makefile teste_tanque.o $(DEPS_TANQUE)
	$(CXX) $(CXXFLAGS) -o tanque teste_tanque.o $(DEPS_TANQUE) $(LDLIBS)


auxiliares.o objetos3D.o terreno.o: auxiliares.hpp constantes.hpp
cenario.o mundo.o: cenario.hpp constantes.hpp
armas.o jogador.o: armas.hpp constantes.hpp
explosoes.o municao.o: explosoes.hpp constantes.hpp
interacoes.o: interacoes.hpp constantes.hpp
cenario.o configmenu.o jogador.o mundo.o: jogador.hpp constantes.hpp
configmenu.o menu.o: menu.hpp constantes.hpp
configmenu.o mundo.o: mundo.hpp constantes.hpp
jogador.o municao.o mundo.o armas.o: municao.hpp constantes.hpp
menu.o objetos2D.o: objetos2D.hpp constantes.hpp
jogador.o objetos3D.o: objetos3D.hpp constantes.hpp
terreno.o cenario.o: terreno.hpp constantes.hpp