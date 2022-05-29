all: glfw glew
	make init_submodules

.PHONY: init_submodules
init_submodules:
	git submodule deinit -f ./glfw/
	git submodule update --init ./glfw/
	
	git submodule deinit -f ./glew/
	git submodule update --init ./glew/

.PHONY: glfw
glfw:
	git submodule deinit -f ./glfw/
	git submodule update --init ./glfw/
	
	if [ -d "./glfw/build/" ]; then rm -rf ./glfw/build/; fi;
	mkdir ./glfw/build/ && cmake -S ./glfw/ -B ./glfw/build/
	cd ./glfw/build/ && make glfw
	
	if [ ! -d "./bin/glfw/" ]; then mkdir -p ./bin/glfw/; fi;
	
	cp ./glfw/build/src/libglfw3.a ./bin/glfw/libglfw3.a
	cp ./glfw/include/GLFW/glfw3.h ./bin/glfw/glfw3.h

.PHONY: glew
glew:
	git submodule deinit -f ./glew/
	git submodule update --init ./glew/
	
	cd ./glew/auto/ && make
	cd ./glew/ && make
	
	if [ ! -d "./bin/glew/" ]; then mkdir -p ./bin/glew/; fi;
	
	cp ./glew/lib/libGLEW.a ./bin/glew/libGLEW.a
	cp ./glew/include/GL/glew.h ./bin/glew/glew.h
