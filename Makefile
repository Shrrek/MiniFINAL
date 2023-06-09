S = srcs/
O = objs/
M = mandatory/

NAME = minishell

SRCS =  $M$Sbuiltins.c\
		$M$Scd.c\
		$M$Scompare.c\
		$M$Sconvert_utils.c\
		$M$Sconvert.c\
		$M$Scopy.c\
		$M$Secho.c\
		$M$Senv.c\
		$M$Sexit.c\
		$M$Sexport_utils.c\
		$M$Sexport.c\
		$M$Sfree.c\
		$M$Smain.c\
		$M$Smemory.c\
		$M$Sparse_pipes_utils.c\
		$M$Sparse_pipes.c\
		$M$Sparse_quotes_utils.c\
		$M$Sparse_quotes_utils2.c\
		$M$Sparse_quotes.c\
		$M$Sparse_redir.c\
		$M$Sprint.c\
		$M$Sprocess_cmds_utils.c\
		$M$Sprocess_expand_utils.c\
		$M$Sprocess_expand.c\
		$M$Sprocess_final.c\
		$M$Sprocess_here_doc.c\
		$M$Sprocess_input.c\
		$M$Sprocess_multiple_cmds.c\
		$M$Sprocess_one_cmd.c\
		$M$Sprocess_one_cmd2.c\
		$M$Sprocess_redir_utils.c\
		$M$Sprocess_redir.c\
		$M$Ssearch.c\
		$M$Ssignals.c\
		$M$Ssize.c\
		$M$Sstrings_utils.c\
		$M$Sstrings.c\
		$M$Streat_fds.c\
		$M$Streat_infd.c\
		$M$Streat_outfd.c\
		$M$Sunset.c\
		
OBJS =  $M$Obuiltins.o\
		$M$Ocd.o\
		$M$Ocompare.o\
		$M$Oconvert_utils.o\
		$M$Oconvert.o\
		$M$Ocopy.o\
		$M$Oecho.o\
		$M$Oenv.o\
		$M$Oexit.o\
		$M$Oexport_utils.o\
		$M$Oexport.o\
		$M$Ofree.o\
		$M$Omain.o\
		$M$Omemory.o\
		$M$Oparse_pipes_utils.o\
		$M$Oparse_pipes.o\
		$M$Oparse_quotes_utils.o\
		$M$Oparse_quotes_utils2.o\
		$M$Oparse_quotes.o\
		$M$Oparse_redir.o\
		$M$Oprint.o\
		$M$Oprocess_cmds_utils.o\
		$M$Oprocess_expand_utils.o\
		$M$Oprocess_expand.o\
		$M$Oprocess_final.o\
		$M$Oprocess_here_doc.o\
		$M$Oprocess_input.o\
		$M$Oprocess_multiple_cmds.o\
		$M$Oprocess_one_cmd.o\
		$M$Oprocess_one_cmd2.o\
		$M$Oprocess_redir_utils.o\
		$M$Oprocess_redir.o\
		$M$Osearch.o\
		$M$Osignals.o\
		$M$Osize.o\
		$M$Ostrings_utils.o\
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
	$(CC) $(CFLAGS) $(COMPILE) -g3 $^ -o $(NAME)
#	$(CC) $(CFLAGS) $(SANITIZE) $(COMPILE) -g3 $^ -o $(NAME)
#	$(CC) $(CFLAGS) $(shell pkg-config --cflags readline) $(SANITIZE) $^ -o $(NAME) -lreadline
	@echo "Mandatory compiled"

clean:
	$(RM) $(OBJS) $M$O

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:  fclean clean all
