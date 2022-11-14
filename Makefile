CC = gcc
CFLAGS += -Wall -Werror -Wextra
CFLAGS_DEBUG = $(CFLAGS)
MAIN = my_blockchain
SRCS = blocks.c formating.c init_chain.c main.c node_handles.c parsing.c ui.c
OBJS = $(SRCS:.c=.o) 

all: $(MAIN)

$(MAIN): $(OBJS)
		$(CC) $(CFLAGS) -o $@ $(LINKERFLAG) $^

clean:
		$(RM) -f $(OBJS)

fclean: clean
		$(RM) -f $(MAIN) $(DEBUG)

re: fclean all