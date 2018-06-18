#
# Makefile para Tank Wars versão 3D
#
# Instruções sobre o Makefile:
# https://www.gnu.org/software/make/manual/make.html
#
# Variáveis usadas pelas instruções implícitas
# https://www.gnu.org/software/make/manual/make.html#Implicit-Variables
#

# pastas - dividir o programa em pastas posteriormente
#INC_DIR = ..\include
#OBJ_DIR = ..\obj

# Variáveis utilizadas pelas instruções implícitas
CXXFLAGS = -Wall -Werror -O0 -ggdb3
LDLIBS   = -lm -lglut32cu -lglu32 -lopengl32

# Arquivos fonte
FONTES = bomb.cpp armas.cpp auxiliares.cpp cenario.cpp constantes.cpp configmenu.o \
		 explosoes.cpp globals.cpp interfaces.cpp interacoes.cpp jogador.cpp menu.cpp \
		 mundo.cpp municao.cpp objetos2D.cpp objetos3D.cpp terreno.cpp
OBJS = $(FONTES:.cpp=.o)

# Headers comuns a todos os arquivos. Headers específicos serão gravados em suas respectivas regras
DEP_COMUNS = constantes.hpp globals.hpp interfaces.hpp objetos3D.hpp Makefile

# default target
bomb: $(OBJS)
	$(CXX) $(CXXFLAGS) -o bomb $(OBJS) $(LDLIBS)

# dependencias comuns
$(OBJS): $(DEP_COMUNS)

# dependencias especificas
auxiliares.o objetos3D.o terreno.o: auxiliares.hpp
cenario.o mundo.o: cenario.hpp
armas.o jogador.o: armas.hpp
explosoes.o municao.o: explosoes.hpp
interacoes.o: interacoes.hpp
cenario.o configmenu.o jogador.o mundo.o: jogador.hpp
configmenu.o menu.o: menu.hpp
configmenu.o mundo.o: mundo.hpp
jogador.o municao.o mundo.o armas.o: municao.hpp
menu.o objetos2D.o: objetos2D.hpp
jogador.o objetos3D.o: objetos3D.hpp
terreno.o cenario.o: terreno.hpp


clean:
	del *.exe *.o *.gch
