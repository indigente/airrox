#
# 
#  Makefile do AirHockey
#
#  alvos: linux    -- compila pra Linux
#         win      -- compila pra Windows
#         clean    -- remove arquivos temporarios (*.o)
#  
#  alvo padrao: linux
#
########################################################
#
# Para rodar no Windows, usando o Dev-C++:
#
#   Mude a variável DEVCPP_PATH, se necessário
#   Descomente o $(INCLUDEWIN) na linha de compilação
#


# caminhos 
LOADER3D_PATH = 3DSLoader
DEVCPP_PATH = C:\Arquiv~1\Programacao\Dev-Cpp


# arquivos utilizados na compilacao
#main.o auxiliar.o visual.o controle.o vetor.o modelo.o jogador.o
OBJS = controle.o \
audio.o \
disco.o \
jogador.o \
jogadorIA.o \
jogadorNet.o \
eventos.o \
jogo.o \
main.o \
objeto.o \
partida.o \
vetor.o \
visual.o \
camera.o \
colisao.o \
comunicacao.o \
conexao.o \
gui/menuitem.o \
gui/menu.o \
gui/textwidget.o \
$(LOADER3D_PATH)/texture.o \
$(LOADER3D_PATH)/3dsloader.o

# bibliotecas para Linux
LIBSLINUX = -L/usr/X11R6/lib -lGL -lGLU -lglut -L/usr/lib -lSDL_mixer -lSDL -lpthread `sdl-config --cflags --libs`

# bibliotecas para Windows
LIBSWIN = -lopengl32 -lglu32 -lglut32 -lmingw32 -lSDLmain -lSDL -lSDL_mixer -mwindows -L$(DEVCPP_PATH)\lib


# executavel gerado pelo Linux
BINLINUX  = air
# executavel gerado pelo Windows
BINWIN = $(BINLINUX).exe

# flags (otimizacao e nao exibir warnings)
FLAGS = -O2 -DREENTRANT -DHAVE_OPENGL -g 

INCLUDEWIN = -I$(DEVCPP_PATH)\include -I$(DEVCPP_PATH)\include\c++ -I$(DEVCPP_PATH)\include\c++\mingw32 -I$(DEVCPP_PATH)\include\c++\backward


#########################################################

# Linkagem: Linux (target padrao)
linux: $(OBJS)
	g++ $? -o $(BINLINUX) -L/usr/X11R6/lib $(LIBSLINUX) $(FLAGS)

# Linkagem: Windows
win: $(OBJS)
	g++ $? -o $(BINWIN) $(LIBSWIN) $(FLAGS)

# Compilacao (Linux e Windows)
$(OBJS): %.o: %.cpp
	g++ -c $< -o $@ $(FLAGS)
# $(INCLUDEWIN)

# Apagar objetos pra comecar do zero
clean:
	rm -f $(OBJS)

