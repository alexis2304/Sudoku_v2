/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 18:11:04 by bjanik            #+#    #+#             */
/*   Updated: 2016/08/14 23:22:39 by rjaguene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BLOC_NUMBER(i,j) (3 * (i / 3) + j/3)
#define TRUE 1
#define FALSE 0

int		g_sudoku[9][9];
int		g_digit_to_find[82];
int		g_nb_solutions;

int		fill_tab(int argc, char **argv);
int		try(int *g_digit_to_find);
void	init(void);
void	print_sudoku(void);
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	save_solution(void);

int		main(int argc, char **argv)
{
	if (fill_tab(argc, argv) == -1)
	{
		ft_putstr("Erreur\n");
		return (0);
	}
	init();
	try(g_digit_to_find);
	if (g_nb_solutions == 1)
		print_sudoku();
	else
		ft_putstr("Erreur\n");
	return (0);
}
