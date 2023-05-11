S = srcs/
O = objs/
M = mandatory/

NAME = minishell

SRCS =  $M$Sbuiltins.c\
		$M$Scd.c\
		$M$Scompare.c\
		$M$Scopy.c\
		$M$Sconvert.c\
		$M$Secho.c\
		$M$Senv.c\
		$M$Sexport.c\
		$M$Sexport_utils.c\
		$M$Sfree.c\
		$M$Smain.c\
		$M$Sparse_quotes_aux.c\
		$M$Sprocess_input.c\
		$M$Sparse_quotes.c\
		$M$Sparse_pipes_aux.c\
		$M$Sparse_pipes.c\
		$M$Sprocess_expand.c\
		$M$Sprocess_expand_aux.c\
		$M$Sprocess_here_doc.c\
		$M$Smemory.c\
		$M$Sprocess_cmds_utils.c\
		$M$Sprocess_one_cmd.c\
		$M$Sprocess_multiple_cmds.c\
		$M$Sprocess_redir_utils.c\
		$M$Sprocess_redir.c\
		$M$Ssize.c\
		$M$Ssplit.c\
		$M$Sstrings.c\
		$M$Streat_fds.c\
		$M$Streat_infd.c\
		$M$Streat_outfd.c\
		$M$Sunset.c\

OBJS =  $M$Obuiltins.o\
		$M$Ocd.o\
		$M$Ocompare.o\
		$M$Oconvert.o\
		$M$Ocopy.o\
		$M$Oecho.o\
		$M$Oenv.o\
		$M$Oexport_utils.o\
		$M$Oexport.o\
		$M$Ofree.o\
		$M$Omain.o\
		$M$Omemory.o\
		$M$Oprocess_here_doc.o\
		$M$Oparse_pipes_aux.o\
		$M$Oparse_pipes.o\
		$M$Oparse_quotes_aux.o\
		$M$Oparse_quotes.o\
		$M$Oparse_redir.o\
		$M$Oprocess_cmds_utils.o\
		$M$Oprocess_input.o\
		$M$Oprocess_expand.o\
		$M$Oprocess_expand_aux.o\
		$M$Oprocess_one_cmd.o\
		$M$Oprocess_multiple_cmds.o\
		$M$Oprocess_redir_utils.o\
		$M$Oprocess_redir.o\
		$M$Osize.o\
		$M$Osplit.o\
		$M$Ostrings.o\
		$M$Otreat_fds.o\
		$M$Otreat_infd.o\
		$M$Otreat_outfd.o\
		$M$Ounset.o\

CC = gcc
CFLAGS = -Wall -Werror -Wextra
SANITIZE = -g3 -fsanitize=address

READLINE_DIR = ${HOME}/.brew/opt/readline
F_READLINE = -I$(READLINE_DIR)/include
COMPILE = -lreadline -L$(READLINE_DIR)/lib

RM = -rm -rf

all: mandatory

mandatory: $(NAME)

$M$O:
	@echo "Creating Objects Folder...."
	mkdir $@
	@echo "Folder created."

$(OBJS): | $M$O

$(OBJS): $M$O%.o: $M$S%.c
#	$(CC) $(CFLAGS) $(shell pkg-config --cflags readline) $(SANITIZE) -c $< -o $@
	$(CC) $(CFLAGS) $(F_READLINE) -g3 -c $< -o $@

$(NAME): $(OBJS)
	@echo "Objects successfully created"
	@echo "Compiling mandatory...."
#	$(CC) $(CFLAGS) $(COMPILE) -g3 $^ -o $(NAME)
	$(CC) $(CFLAGS) $(SANITIZE) $(COMPILE) -g3 $^ -o $(NAME)
#	$(CC) $(CFLAGS) $(shell pkg-config --cflags readline) $(SANITIZE) $^ -o $(NAME) -lreadline
	@echo "Mandatory compiled"

clean:
	$(RM) $(OBJS) $M$O

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:  fclean clean all
