/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtshekel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 23:23:55 by gtshekel          #+#    #+#             */
/*   Updated: 2017/08/08 14:12:34 by gtshekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"

static t_pair	get_x_pair(t_graphic *g, int row, int pair)
{
	t_pair x_pair;

	x_pair = (t_pair){{0, 0, 0}, {0, 0, 0}};
	x_pair.p1.z = (g->map[row][pair - 1] ? g->zoom + g->map[row][pair - 1] : 0);
	x_pair.p2.z = (g->map[row][pair] ? g->zoom + g->map[row][pair] : 0);
	x_pair.p1.z = x_pair.p1.z * g->dimen.h;
	x_pair.p2.z = x_pair.p2.z * g->dimen.h;
	x_pair.p1.x = (pair - 1) * g->zoom;
	x_pair.p2.x = pair * g->zoom;
	x_pair.p1.y = row * g->zoom;
	x_pair.p2.y = row * g->zoom;
	return (x_pair);
}

static t_pair	get_y_pair(t_graphic *g, int col, int pair)
{
	t_pair y_pair;

	y_pair = (t_pair){{0, 0, 0}, {0, 0, 0}};
	y_pair.p1.z = (g->map[pair - 1][col] ? g->zoom + g->map[pair - 1][col] : 0);
	y_pair.p2.z = (g->map[pair][col] ? g->zoom + g->map[pair][col] : 0);
	y_pair.p1.z = y_pair.p1.z * g->dimen.h;
	y_pair.p2.z = y_pair.p2.z * g->dimen.h;
	y_pair.p1.x = col * g->zoom;
	y_pair.p2.x = col * g->zoom;
	y_pair.p1.y = (pair - 1) * g->zoom;
	y_pair.p2.y = pair * g->zoom;
	return (y_pair);
}

static void		drawline(t_graphic *g, t_pair pair, int col)
{
	float	x1;
	float	x2;
	float	y1;
	float	y2;
	int		steps;

	x1 = pair.p1.x - pair.p1.y + g->dimen.x_off;
	x2 = pair.p2.x - pair.p2.y + g->dimen.x_off;
	y1 = (pair.p1.x + pair.p1.y - pair.p1.z) / 2 + g->dimen.y_off;
	y2 = (pair.p2.x + pair.p2.y - pair.p2.z) / 2 + g->dimen.y_off;
	if (ft_abs(x2 - x1) > ft_abs(y2 - y1))
		steps = ft_abs(x2 - x1) + 1;
	else
		steps = ft_abs(y2 - y1) + 1;
	while (steps--)
	{
		y1 = y1 + (y2 - y1) / (float)steps;
		x1 = x1 + (x2 - x1) / (float)steps;
		mlx_pixel_put(g->mlx, g->win, x1, y1, col);
	}
}

void			draw_rows(t_graphic *g)
{
	t_pair		pair;
	int			row;
	int			pair_num;
	int			pairs;

	pair = (t_pair){{0, 0, 0}, {0, 0, 0}};
	row = 0;
	pairs = g->dimen.cols - 1;
	while (row < g->dimen.rows)
	{
		pair_num = 1;
		while (pair_num <= pairs)
		{
			pair = get_x_pair(g, row, pair_num);
			drawline(g, pair, COL);
			pair_num++;
		}
		row++;
	}
}

void			draw_cols(t_graphic *g)
{
	t_pair		pair;
	int			col;
	int			pair_num;
	int			pairs;

	pair = (t_pair){{0, 0, 0}, {0, 0, 0}};
	col = 0;
	pairs = g->dimen.rows - 1;
	while (col < g->dimen.cols)
	{
		pair_num = 1;
		while (pair_num <= pairs)
		{
			pair = get_y_pair(g, col, pair_num);
			drawline(g, pair, COL);
			pair_num++;
		}
		col++;
	}
}
