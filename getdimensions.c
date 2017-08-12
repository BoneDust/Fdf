/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getdimensions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtshekel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 08:36:55 by gtshekel          #+#    #+#             */
/*   Updated: 2017/08/12 11:03:12 by gtshekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		print_err(char *s)
{
	if (ft_strequ("Error : Invalid map", s))
		ft_putendl_fd(s, 2);
	else
		perror("Error ");
	exit(1);
}

static void	compare_cols(char *line, int columns)
{
	char	**array;
	int		cols;

	cols = 0;
	array = ft_strsplit(line, ' ');
	while (array[cols])
		cols++;
	array = (char**)ft_destroy_2d((void**)array);
	if (cols != columns)
		print_err("Error : Invalid map");
}

static void	get_other_dimen(t_graphic *g)
{
	int		prod;

	prod = g->dimen.cols * g->dimen.rows;
	g->dimen.h = 5;
	g->scr = 260;
	if (prod <= 400)
		g->zoom = 16;
	else if (prod <= 800)
		g->zoom = 8;
	else if (prod <= 1200)
		g->zoom = 4;
	else
		g->zoom = 2;
}

void		getdimensions(char *filename, t_graphic *g)
{
	int		fd;
	char	*line;
	char	**array;

	line = NULL;
	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		print_err("");
	while (get_next_line(fd, &line) > 0)
	{
		if (g->dimen.cols == 0)
		{
			array = ft_strsplit(line, ' ');
			while (array[g->dimen.cols])
				g->dimen.cols++;
			array = (char**)ft_destroy_2d((void**)array);
		}
		compare_cols(line, g->dimen.cols);
		g->dimen.rows++;
	}
	get_other_dimen(g);
	g->dimen.x_off = g->zoom * (g->dimen.rows - 1) + g->scr / 2;
	g->dimen.y_off = g->scr / 2;
	close(fd);
	free(line);
}
