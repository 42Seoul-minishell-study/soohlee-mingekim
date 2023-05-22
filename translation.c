/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soohlee <soohlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:53:16 by soohlee           #+#    #+#             */
/*   Updated: 2023/05/22 21:45:56 by soohlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	temp_make_data(char *****out_data);
void	temp_data_print(char *****out_data);

int	translation(char *****out_data, char **envp)
{	
//	tokenization(out_str, out_data);	//thursday minkeun
//	temp_make_data(out_data);
	shell_expansions(out_data, envp);	//thursday sooha
	temp_data_print(out_data);
	if (envp)
		;
	return (0);
}

void	temp_make_data(char *****out_data)
{
	*out_data = (char ****)malloc(sizeof(char ***) * 4);
	char	**cmd1;
	char	**cmd2;
	char	**rider1;
	char	**rider2;
	(*out_data)[0] = (char ***)malloc(sizeof(char **) * 3);
	rider1 = ft_split("   << \'\"$END   $END,< \"   $AAA  \",< infile2,>> outfile1,> outfile2", ',');
	cmd1 = ft_split("\'\"$envcmd, $envfile$envarg", ',');
	(*out_data)[0][0] = rider1;
	(*out_data)[0][1] = cmd1;
	(*out_data)[0][2] = NULL;

	(*out_data)[1] = (char ***)malloc(sizeof(char **) * 3);
	rider2 = ft_split("<< $END,< infile4,< infile5,>> outfile3,> outfile4", ',');
	cmd2 = ft_split("cat, $BBB  $CCC$DDD", ',');
	(*out_data)[1][0] = rider2;
	(*out_data)[1][1] = cmd2;
	(*out_data)[1][2] = NULL;

	(*out_data)[2] = NULL;
}

void	temp_data_print(char *****out_data)
{
	int	pipe;
	int	i;
	int	j;

	pipe = -1;
	printf("---------------------------expantion-----------------------------\n");
	while ((*out_data)[++pipe])
	{
		i = -1;
		while ((*out_data)[pipe][++i])
		{
			j = -1;
			while ((*out_data)[pipe][i][++j])
				printf("%d %d %d: %s\n", pipe, i, j, (*out_data)[pipe][i][j]);
		}
	}
// //node 1
// 	printf("\n-----<node 1>--------------------\nredir : %s\n", (*out_data)[0][0][0]);
// 	printf("redir : %s\n", (*out_data)[0][0][1]);
// 	printf("redir : %s\n", (*out_data)[0][0][2]);
// 	printf("redir : %s\n", (*out_data)[0][0][3]);
// 	printf("redir : %s\n", (*out_data)[0][0][4]);
// 	printf("redir : %s\n", (*out_data)[0][0][5]);

// 	printf("\ncmd : %s\n", (*out_data)[0][1][0]);
// 	printf("cmd : %s\n", (*out_data)[0][1][1]);
// 	printf("cmd : %s\n", (*out_data)[0][1][2]);

// //node 2
// 	printf("\n-----<node 2>--------------------\nredir : %s\n", (*out_data)[1][0][0]);
// 	printf("redir : %s\n", (*out_data)[1][0][1]);
// 	printf("redir : %s\n", (*out_data)[1][0][2]);
//  	printf("redir : %s\n", (*out_data)[1][0][3]);
//  	printf("redir : %s\n", (*out_data)[1][0][4]);
//  	printf("redir : %s\n", (*out_data)[1][0][5]);

//  	printf("\ncmd : %s\n", (*out_data)[1][1][0]);
//  	printf("cmd : %s\n", (*out_data)[1][1][1]);
//  	printf("cmd : %s\n", (*out_data)[1][1][2]);

//  	printf("\narray_end : %s\n", (char *)(*out_data)[2]);
}

//출력폼
// -----<node 1>--------------------
// redir : << $END
// redir : < $AAA
// redir : < infile2
// redir : >> outfile1
// redir : > outfile2
// redir : (null)

// cmd : $envcmd
// cmd : $envfile$envarg
// cmd : (null)

// -----<node 2>--------------------
// redir : << END2
// redir : < infile4
// redir : < infile5
// redir : >> outfile3
// redir : > outfile4
// redir : (null)

// cmd : cat
// cmd : $BBB$CCC$DDD
// cmd : (null)

// array_end : (null)