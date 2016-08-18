/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 19:15:59 by bjanik            #+#    #+#             */
/*   Updated: 2016/08/14 23:24:35 by rjaguene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#define BLOC_NUMBER(i,j) (3 * (i / 3) + j/3)

int g_sudoku[9][9];
int g_exist_in_line[9][10];
int g_exist_in_col[9][10];
int g_exist_in_bloc[9][10];
int g_save_solution[9][9];
int g_nb_solutions;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	print_sudoku(void)
{
	int	i;
	int j;

	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			ft_putchar(g_save_solution[i][j] + 48);
			if (j != 8)
				ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

/*
**This function allows us to read from the command line arguments the data
**inside the argv character strings. If at least one of the arguments doesn't
**satisfy the conditions, or if the number of arguments is not equal to 10
**(program name + 9 sudoku lines), then the function returns a negativ, and
**the main program will display an error message.
*/

int		fill_tab(int argc, char **argv)
{
	int		i;
	int		j;
	char	*ligne;

	i = 0;
	if (argc != 10)
		return (-1);
	while (i < argc - 1 && i < 9)
	{
		ligne = argv[i + 1];
		j = 0;
		while (ligne[j])
		{
			g_sudoku[i][j] = (ligne[j] == '.') ? 0 : ligne[j] - 48;
			if (g_sudoku[i][j] < 0 || g_sudoku[i][j] > 9 || j > 9)
				return (-1);
			j++;
		}
		if (j != 9)
			return (-1);
		i++;
	}
	return (1);
}

/*
**This function allows to save the first solution found in an array which is a
**copy.By this way, we can refill the first array with possibly other solutions
*/

int		save_solution(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			g_save_solution[i][j] = g_sudoku[i][j];
			j++;
		}
		i++;
	}
	g_nb_solutions++;
	return (g_nb_solutions);
}
