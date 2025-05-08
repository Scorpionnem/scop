NAME := scop

OBJ_DIR := ./obj/
INCLUDE_DIRS := ./includes/ ./GLFW/include/GLFW ./includes/glad/.

GLFWARCHIVE = GLFW/build/src/libglfw3.a

INCLUDE_DIRS := $(addprefix -I, $(INCLUDE_DIRS))

MAKE := @make --no-print-directory

SOURCE_DIR := ./src/

OBJ_DIR := ./obj/

OBJECTS = $(SOURCES:.cpp=.o)

CPP_FILES :=	main \
				glad/glad \
				Window \
				Terminal

CPP_FILES := $(addsuffix .cpp, $(CPP_FILES))

SOURCES := $(addprefix $(SOURCE_DIR), $(CPP_FILES))

OBJECTS := $(addprefix $(OBJ_DIR), $(CPP_FILES:.cpp=.o))
DEPS := $(addprefix $(OBJ_DIR), $(CPP_FILES:.cpp=.d))

CFLAGS = -MP -MMD -Wall -Werror -Wextra -g

GLAD_PATH = libs/glad

all: glfw glad $(NAME)

run: all
	@./$(NAME)

glfw:
	@if ls | grep -q "GLFW"; then \
		echo "\033[32;1;4mGLFW Found\033[0m"; \
	else \
		echo "\033[31;1;4mGLFW Not Found\033[0m"; \
		echo "\033[31;1mDownloading GLFW from github \033[0m"; \
		git clone https://github.com/glfw/glfw.git GLFW; \
		echo "\033[31;1mCompiling GLFW\033[0m"; \
		cmake -S GLFW -B GLFW/build; \
		cmake --build GLFW/build; \
	fi

# pip install glad if it doesnt work
glad:
	@if ls src | grep -q "glad"; then \
		echo "\033[32;1;4mglad Found\033[0m"; \
	else \
		echo "\033[31;1;4mglad Not Found\033[0m"; \
		echo "\033[31;1mDownloading glad from github \033[0m"; \
		git clone https://github.com/Dav1dde/glad.git glad; \
		python -m glad --out-path=glad/build --generator=c; \
		mkdir -p glad2; \
		cp glad/build/include/glad/glad.h glad2/.; \
		cp glad/build/src/glad.c glad2/.; \
		rm -rf glad; \
		mv glad2 glad; \
		mv glad/glad.c glad/glad.cpp; \
		mkdir -p src/glad; \
		mkdir -p includes/glad; \
		mv glad/glad.cpp src/glad/; \
		mv glad/glad.h includes/glad/; \
		rm -rf glad; \
	fi

$(OBJECTS): $(OBJ_DIR)%.o : $(SOURCE_DIR)%.cpp
	@c++ $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(OBJ_DIR):
	@(cd $(SOURCE_DIR) && find . -type d -exec mkdir -p -- $(shell pwd)/$(OBJ_DIR){} \;)

$(NAME): $(OBJ_DIR) $(OBJECTS)
	@c++ $(OBJECTS) $(GLFWARCHIVE) -o $(NAME)
	@echo "\033[0;32mCompiled $(NAME)\033[0m"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;32mCleaned objects\033[0m"

fclean:
	$(MAKE) clean
	@rm -f $(NAME)
	@echo "\033[0;32mCleaned $(NAME)\033[0m"

deepclean: fclean
	@rm -rf src/glad
	@rm -rf includes/glad
	@rm -rf GLFW
	@echo "\033[0;32mCleaned external libraries\033[0m"

re: fclean all

.PHONY: all clean fclean deepclean re GLFW glad run

-include $(DEPS)