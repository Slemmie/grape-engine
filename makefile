all: release

CXX_FLAGS = -Wshadow -Wall -std=c++17
CXX_RELEASE_FLAGS = -O2
CXX_DEBUG_FLAGS = -g -fsanitize=undefined,address -D_GLIBCXX_DEBUG -D_GE_DEBUG
#CXX_DEBUG_FLAGS = -g -fsanitize=undefined -D_GLIBCXX_DEBUG -D_GE_DEBUG

SRC_FILES =             \
$(wildcard ./src/*.cpp)

HDR_FILES =             \
$(wildcard ./src/*.h)   \
$(wildcard ./src/*.hpp)

OBJ_FILES_RELEASE = ${SRC_FILES:.cpp=_release.o}
OBJ_FILES_DEBUG = ${SRC_FILES:.cpp=_debug.o}

GEPCH = ./src/pch/gepch.h

LINKS = -lpthread

release: ${OBJ_FILES_RELEASE}
	g++ $(CXX_FLAGS) -shared $^ -o libgengine.so $(CXX_RELEASE_FLAGS) $(LINKS)
	make clean

%_release.o: %.cpp gepch ${HDR_FILES}
	g++ $(CXX_FLAGS) -fPIC -c $< -o $@ $(CXX_RELEASE_FLAGS) -include ./src/pch/gch/gepch.h

debug: ${OBJ_FILES_DEBUG}
	g++ $(CXX_FLAGS) -shared $^ -o libgengine_debug.so $(CXX_DEBUG_FLAGS) $(LINKS)
	make clean

%_debug.o: %.cpp gepch_debug ${HDR_FILES}
	g++ $(CXX_FLAGS) -fPIC -c $< -o $@ $(CXX_DEBUG_FLAGS) -include ./src/pch/gch/gepch_debug.h

gepch:
	g++ $(CXX_FLAGS) -fPIC -c $(GEPCH) -o ./src/pch/gch/gepch.h.gch $(CXX_RELEASE_FLAGS)

gepch_debug:
	g++ $(CXX_FLAGS) -fPIC -c $(GEPCH) -o ./src/pch/gch/gepch_debug.h.gch $(CXX_DEBUG_FLAGS)

.PHONY: clean
clean:
	find . -name *.o -delete
	find . -name *.gch -delete
