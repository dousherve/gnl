NAME    = libgnl.a

CC      = cc
AR		= ar rcs
CFLAGS  = -O3 -Wall -Wextra -Werror
RM      = rm -rf

SRC_DIR = .
OBJ_DIR = obj
INC_DIRS = .

SRC     = $(SRC_DIR)/gnl.c $(SRC_DIR)/buffer.c 
OBJ     = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(filter $(SRC_DIR)/%.c,$(SRC)))

INCLUDES = $(addprefix -I, $(INC_DIRS))

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR) $(NAME)

re: clean all

.PHONY: all clean re

