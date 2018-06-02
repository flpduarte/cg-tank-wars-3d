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
FONTES = bomb.cpp armas.cpp explosoes.cpp jogador.cpp mundo.cpp municao.cpp
OBJS = $(FONTES:.cpp=.o)

# Headers comuns a todos os arquivos. Headers específicos serão gravados em suas respectivas regras
DEP_COMUNS = constantes.hpp Makefile

# default target
bomb: $(OBJS)
	$(CXX) $(CXXFLAGS) -o bomb $(OBJS) $(LDLIBS)

# dependencias comuns
$(OBJS): $(DEP_COMUNS)

# dependencias especificas
armas.o: armas.hpp
jogador.o mundo.o: jogador.hpp
mundo.o: mundo.hpp
municao.o mundo.o armas.o: municao.hpp
explosoes.o municao.o: explosoes.hpp


clean:
	del *.exe *.o *.gch
