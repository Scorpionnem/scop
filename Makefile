NAME :=	scop

###

CXX :=	c++
CXXFLAGS :=	-Wall -Wextra -Werror -g -MP -MMD
LFLAGS :=	-lSDL2 -lGL

###

INCLUDE_DIRS :=	includes/\
				includes/Core\
				includes/Math\
				includes/Scop\
				external/glad

SRCS :=	main\
		Core/Window\
		Math/Vec3\
		Core/Shader\
		Core/Mesh\
		Math/Math

###

INCLUDE_DIRS :=	$(addprefix -I, $(INCLUDE_DIRS))

SRCS :=	$(addprefix src/, $(SRCS))
SRCS :=	$(addsuffix .cpp, $(SRCS))

SRCS +=	external/glad/glad.cpp

###

OBJ_DIR :=	obj

OBJS =	$(SRCS:%.cpp=$(OBJ_DIR)/%.o)
DEPS =	$(SRCS:%.cpp=$(OBJ_DIR)/%.d)

###

compile:
	@@make -j all --no-print-directory

all: $(NAME)

$(NAME): $(OBJS)
	@echo Compiling $(NAME)
	@$(CXX) $(CXXFLAGS) $(LFLAGS) $(INCLUDE_DIRS) -o $@ $^

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

re: fclean all

fclean: clean
	@echo Removed $(NAME)
	@rm -rf $(NAME)

clean:
	@echo Removed $(OBJ_DIR)
	@rm -rf $(OBJ_DIR)

.PHONY: all clean fclean re compile

-include $(DEPS)
