/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrital- <mrital-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:48:31 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/12 20:46:26 by mrital-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <term.h>
# include <curses.h>
# include <termios.h>
# include <stdint.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include <readline/readline.h>
# include "libft/libft.h"
# include <string.h> // must removed
# include <fcntl.h>

# define SUCCESS 0
# define FAILURE 1
# define MAX_PATH_LENGTH 4096

typedef struct s_tokenizer	t_tokenizer;
typedef enum	e_type	t_type;

enum	e_type
{
	STRING,
	ENV_VARIABLE,
	CMD,
	BUILTIN,
	PIPE,
	RED_OUT_TRUNC, // >
	RED_OUT_APPEND, // >>
	RED_IN,			// <
	HEREDOC 		// <<
};

struct	s_tokenizer
{
	int to_free;
	int i;
	int check;
	char *dup;
	int len;
	char *var;
	char *id;
	char *identify;
	char		*content;
	t_type		type;
	t_tokenizer	*next;
};

typedef struct s_data
{
	char			**env;
	char			*pwd; 
	t_list			*lst;   
	t_tokenizer		*tokenizer; 
}				t_data;

typedef struct s_pipe
{
	int		pipe_fd[2];
	int		prev_in;
	int		pid;
	int		cmd_nb;
	char	**cmd;
	char 	*cmd_name;
}				t_pipe;
int	ft_hundling(t_tokenizer *s, char *data, char *string,char **env);
char	*ft_free_new_str(t_tokenizer *s);
char *get_new_string(int len,char *content,char **env);
void ft_help_get_str(char *content,t_tokenizer *token,char **env);
void ft_go(t_tokenizer *token,char *content);
void expand(t_data *data);
void ft_get_len(t_tokenizer *token,char *data,char **env);
int get_str_len(char* content,char **env);
char *get_expand(char *content,char **env);
void ft_mini_expen(t_tokenizer *token,char **env);
int	ft_valid(char c);
char	*get_index(char *string);
char *get_var(char *id, char **env);

void	ft_export(char **args, t_data *data);
void	export_alone(t_data *data);
char	**export_env(char **old_env, char *export);
void	replace_var(char *new_var, t_data *data, int index);
int		var_index(char *name, t_data *data);
int		check_export(char *str);
int		print_export(char **env);
char	**dup_env(char **env);

void	ft_unset(char **args, t_data *data);
char	**delete_env_var(char **old_env, int index);
void	free_env(char **env);

void	ft_echo(char **args);

void	ft_pwd(t_data *data);

void	ft_exit(char **args);

void	ft_env(char **env);
int		envlen(char **env);

void	ft_cd(char **args, t_data *data);
int		cd_path(char **args, t_data *data);
int		cd_alone(t_data *data);
int		cd_minus(t_data *data);
int		change_pwd(t_data *data, char *input);
void	change_env_oldpwd(t_data *data);
void	change_env_pwd(t_data *data);

void	error_sentence(char *str);

// int	analylizer_redi(t_data	*data);
// int	analylizer_pipe(t_data	*data);
int check_quotes(char* line);
int	analylizer(t_list *list);

// void expand(t_data *data);

// void printerr(int i);

t_tokenizer *new_node(char *content, t_type type);
void		printEnumName(enum e_type value);
void		printList(t_tokenizer *head);
void 		ft_create_node(t_tokenizer **head, char *content, t_type type);
void		ft_redirection(t_list *, t_data *data);
void		tokenizer(t_data *data);
void		free_token_list(t_tokenizer **head);
int			builtin_check(char *cmd);
void		free_double_pointer(char **arr);

void		execute(t_data *data);
void		execute_compound_command(t_data *data);
void		execute_simple_cmd(t_data *data);
void		setup_redirections(t_tokenizer *head);
char		*get_absolute_path( char *command_name, t_data *da);
int			check_pipe(t_tokenizer *lst);
int			count_cmds(t_tokenizer *lst);
void		exec_builtin(char **cmd, t_data *data);

void	setup_pipes(int *p1, int *p2, int i, int cmd_nbr);
void	setup_nchild_pipes(int *p1, int *p2, int i);
void	close_all_pipes(int *p1, int *p2);
void	exec_cmd(t_data *data, char **cmd, char *cmd_name);
void	child_exec(t_data *data, t_pipe p, int i, t_tokenizer *curr);
void	parent_exec(t_pipe p, int i);

void	ft_red_out_trunc(t_tokenizer *head);
void	ft_red_out_append(t_tokenizer *head);
void	ft_red_in(t_tokenizer *head);

#endif
