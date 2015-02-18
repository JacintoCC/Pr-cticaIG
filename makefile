########################################################################
##
## Prácticas IG, curso 2014-15  
## Carlos Ureña, Oct-2014
## 
## archivo 'make' para compilar, enlazar y ejecutar
## invocar von 'make'
## genera archivo ejecutable 'prac', usando todos los .cpp/.cc/.c presentes
##
########################################################################

BIN               = ./bin
INCLUDE           = ./include
OBJ               = ./obj
SRC               = ./src

.SUFFIXES:
.PHONY: start, exec, all, compile, clean

target_name         := prac
opt_dbg_flag        := -g
exit_first          := -Wfatal-errors
warn_all            := -Wall
##warn_all          :=
sources             := $(wildcard  $(SRC)/*.cpp  $(SRC)/*.cc  $(SRC)/*.c)
headers             := $(wildcard $(INCLUDE)/*.hpp $(INCLUDE)/*.hh $(INCLUDE)/*.h)
##units_ext           :=  main practica1 error-ogl

gl_libs_std         := -lglut -lGLU -lGL 
gl_libs_api         := -lglut -lGLU /usr/lib/nvidia-331/libGL.so
gl_libs             := $(gl_libs_std)
##gl_libs           := $(gl_libs_api)
other_ld_libs       := 
gtk_c_flags         := 
gtk_ld_libs         := 

objs                := $(addprefix $(OBJ)/, $(notdir $(sources:.cpp=.o)))
c_flags             := -I $(INCLUDE) $(src_dir) $(opt_dbg_flag) $(exit_first) $(warn_all) $(gtk_c_flags)
ld_libs             := $(gtk_ld_libs) $(gl_libs) $(other_ld_libs)

start:
	@make --no-print-directory exec

exec: $(BIN)/$(target_name)
	@echo "ejecutando " $(BIN)/$(target_name) " ...."
	$(BIN)/$(target_name) img/ant.ply img/helado.ply 11

all:
	make clean
	make compile

compile: $(BIN)/$(target_name)
	@echo "compilando fuentes: " $(SRC)/$(units_ext)
	@make --no-print-directory $(BIN)/$(target_name)

$(BIN)/$(target_name) : $(objs)
	@echo `tput bold`---------------------------------------------------------------
	@echo "Enlazando      :" $(BIN)/$(target_name) 
	@echo "Unidades(ext)  :" $(SRC)/$(units_ext) 
	@echo "Objetos        :" $(objs) 
	@tput sgr0
	g++ -o $(BIN)/$(target_name) $(objs) $(ld_libs) -ljpeg
	@echo ---------------------------------------------------------------
	
	
$(OBJ)/%.o: $(SRC)/%.cpp 
	@echo `tput bold`---------------------------------------------------------------
	@echo Compilando: $(notdir $<) 
	@tput sgr0
	@g++ $(c_flags) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.cc $(headers)
	@echo `tput bold`---------------------------------------------------------------
	@echo Compilando: $(notdir $<) 
	@tput sgr0
	@g++ $(c_flags) -c $< -o $@
	
$(OBJ)/%.o: $(SRC)/%.c
	@echo `tput bold`---------------------------------------------------------------
	@echo Compilando: $(notdir $<) 
	@tput sgr0
	@g++ $(c_flags) -c $< -o $@

clean:
	rm -f $(OBJ)/*.o *~ ./*/*~ $(BIN)/$(target_name)
	


   




