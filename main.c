/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtshekel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 16:25:14 by gtshekel          #+#    #+#             */
/*   Updated: 2017/08/08 14:16:07 by gtshekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		redraw_map(t_graphic *g)
{
	mlx_clear_window(g->mlx, g->win);
	drawmap(g);
	return (0);
}

int		config_map(int keycode, t_graphic *g)
{
	if (keycode == 53)
		exit(1);
	else if (keycode == ZOOM_IN || keycode == ZOOM_OUT)
		update_zoom(g, keycode);
	else if (keycode == HEIGHT_INCR || keycode == HEIGHT_DECR)
		update_height(g, keycode);
	else if (keycode == RIGHT || keycode == LEFT)
		update_hori_shift(g, keycode);
	else if (keycode == UP || keycode == DOWN)
		update_verti_shift(g, keycode);
	redraw_map(g);
	return (0);
}

int		main(int argc, char **argv)
{
	t_graphic	g;
	char		*filename;

	g = (t_graphic){NULL, NULL, NULL, 0, 0, {0, 0, 0, 0, 0, 0, 0}};
	if (argc == 2)
	{
		filename = argv[1];
		getdimensions(filename, &g);
		g.dimen.win_x = g.zoom * (g.dimen.cols + g.dimen.rows - 2) + g.scr;
		g.dimen.win_y = g.zoom * (g.dimen.cols + g.dimen.rows - 2) / 2 + g.scr;
		g.dimen.win_x = g.dimen.win_x > 1800 ? 1800 : g.dimen.win_x;
		g.dimen.win_y = g.dimen.win_y > 900 ? 900 : g.dimen.win_y;
		g.mlx = mlx_init();
		g.win = mlx_new_window(g.mlx, g.dimen.win_x, g.dimen.win_y, "my fdf");
		init_map(filename, &g);
		redraw_map(&g);
		mlx_expose_hook(g.win, redraw_map, &g);
		mlx_key_hook(g.win, config_map, &g);
		mlx_loop(g.mlx);
	}
	ft_putendl_fd("Incorrect usage. Supply only map name as argument", 2);
	return (0);
}
