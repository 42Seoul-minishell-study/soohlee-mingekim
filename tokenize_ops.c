#include "minishell.h"

char	*split_ops(char *str, char **op_out)
{
	int		len_op;
	int		len_filename;
	char	*temp;
	char	*filename;

	temp = str;
	len_filename = 0;
	len_op = 0;
	if (ft_strncmp(temp, "<<", 2) == 0)
	{
		temp += 2;
		len_op = 2;
		temp = pass_space(temp);
		filename = temp;
		temp = find_next_word(temp);
		len_filename = temp - filename;
		printf("%s\n", str);
	}
	else if (ft_strncmp(temp, "<", 1) == 0)
	{
		temp += 1;
		len_op = 1;
		temp = pass_space(temp);
		filename = temp;
		temp = find_next_word(temp);
		len_filename = temp - filename;
	}
	else if (ft_strncmp(temp, ">>", 2) == 0)
	{
		temp += 2;
		len_op = 2;
		temp = pass_space(temp);
		filename = temp;
		temp = find_next_word(temp);
		len_filename = temp - filename;
	}
	else if (ft_strncmp(temp, ">", 1) == 0)
	{
		temp += 1;
		len_op = 1;
		temp = pass_space(temp);
		filename = temp;
		temp = find_next_word(temp);
		len_filename = temp - filename;
	}
	*op_out = malloc(sizeof(char) * (len_op + 1 + len_filename + 1));
	if (*op_out == NULL)
	{
		perror("malloc");
		return (str);
	}
	ft_memcpy(*op_out, str, len_op);
	(*op_out)[len_op] = ' ';
	ft_memcpy(*op_out + len_op + 1, filename, len_filename);
	(*op_out)[len_op + 1 + len_filename] = '\0';
	return (temp);
}