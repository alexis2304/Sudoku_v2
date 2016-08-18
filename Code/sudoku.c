/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sudoku.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agougaut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 12:53:36 by agougaut          #+#    #+#             */
/*   Updated: 2016/08/14 23:24:18 by rjaguene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BLOC_NUMBER(i,j) (3 * (i / 3) + j/3)
#define TRUE 1
#define FALSE 0

int		g_sudoku[9][9];
int		g_digit_to_find[82];
int		g_exist_in_line[9][10];
int		g_exist_in_col[9][10];
int		g_exist_in_bloc[9][10];
int		g_save_solution[9][9];
int		g_nb_solutions = 0;

int		save_solution(void);
void	print_sudoku(void);
/*
**Function tests if for a specific digit there is not the same digit in
**the same line, column and block.
*/

int		valid_position(int digit, int i, int j)
{
	return (!(g_exist_in_line[i][digit] || g_exist_in_col[j][digit]
				|| g_exist_in_bloc[BLOC_NUMBER(i, j)][digit]));
}

/*
** If the digit checks the valid condition, then we fill the empty case with
**the digit and we fill the booleans arrays with the same digit.
*/

void	set_digit(int digit, int i, int j)
{
	g_exist_in_line[i][digit] = digit;
	g_exist_in_col[j][digit] = digit;
	g_exist_in_bloc[BLOC_NUMBER(i, j)][digit] = digit;
	g_sudoku[i][j] = digit;
}

/*
** Function sets the digit to 0 if all digits were tested and did not verified
**the condition (valid_position)
*/

void	unset_digit(int digit, int i, int j)
{
	g_exist_in_line[i][digit] = 0;
	g_exist_in_col[j][digit] = 0;
	g_exist_in_bloc[BLOC_NUMBER(i, j)][digit] = 0;
	g_sudoku[i][j] = 0;
}

/*
**Main function of the program, we use the backtracking way to solve the
**problem. We put as argument of the function the array we created with the
**previous function.
**For each empty square, we test every digit until one can be put in the case.
**Then we go to the next empty case. If all the digit were tested, the function
**returns.
*/

int		try(int *position)
{
	int	i;
	int	j;
	int	digit;

	i = *position / 9;
	j = *position % 9;
	digit = 1;
	while (digit <= 9)
	{
		if (valid_position(digit, i, j))
		{
			set_digit(digit, i, j);
			if (*(position + 1) >= 0)
			{
				if (try(position + 1))
					return (TRUE);
			}
			else if (save_solution() > 1)
				return (TRUE);
			unset_digit(digit, i, j);
		}
		digit++;
	}
	return (FALSE);
}

/*
**With the following function we fill an array containing the position of each
**empty square, according to its column number, line number and block number.
**We will use this array for our recursive function.
*/

void	init(void)
{
	int	i;
	int	j;
	int	k;
	int	digit;

	i = 0;
	k = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			if (g_sudoku[i][j] == 0)
				g_digit_to_find[k++] = i * 9 + j;
			digit = g_sudoku[i][j];
			g_exist_in_line[i][digit] = digit;
			g_exist_in_col[j][digit] = digit;
			g_exist_in_bloc[BLOC_NUMBER(i, j)][digit] = digit;
			j++;
		}
		i++;
	}
	g_digit_to_find[k] = -1;
}
