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

release: ${OBJ_FILES_RELEASE}
	g++ $(CXX_FLAGS) -shared $^ -o libgengine.so $(CXX_RELEASE_FLAGS)
	make clean

%_release.o: %.cpp ${HDR_FILES}
	g++ $(CXX_FLAGS) -fPIC -c $< -o $@ $(CXX_RELEASE_FLAGS)

debug: ${OBJ_FILES_DEBUG}
	g++ $(CXX_FLAGS) -shared $^ -o libgengine_debug.so $(CXX_RELEASE_DEBUG)
	make clean

%_debug.o: %.cpp ${HDR_FILES}
	g++ $(CXX_FLAGS) -fPIC -c $< -o $@ $(CXX_RELEASE_DEBUG)

.PHONY: clean
clean:
	find . -name *.o -delete
