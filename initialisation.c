/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtshekel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 08:11:30 by gtshekel          #+#    #+#             */
/*   Updated: 2017/08/08 14:31:58 by gtshekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		is_color_valid(char *s)
{
	char	**sp;
	char	**sp2;
	char	x;
	int		ret;

	sp = ft_strsplit(s, ',');
	x = ft_contains(sp[1], 'x') ? 'x' : '\0';
	x = ft_contains(sp[1], 'X') && x != 'x' ? 'X' : x;
	ret = ft_is_number(sp[0]) ? 1 : 0;
	if (x != '\0' && ret)
	{
		sp2 = ft_strsplit(sp[1], x);
		if (ft_htoi(sp2[0]) != 0)
			ret = 0;
		if (ret && (ft_htoi(sp2[1]) < 0 || ft_htoi(sp2[1]) > WHITE))
			ret = 0;
		sp2 = (char**)ft_destroy_2d((void**)sp2);
	}
	if (ret && x == '\0' && (ft_htoi(sp[1]) < 0 || ft_htoi(sp[1]) > WHITE))
		ret = 0;
	sp = (char**)ft_destroy_2d((void**)sp);
	return (ret);
}

static void		verify_map(int fd)
{
	char	**split;
	char	*line;
	int		index;

	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		index = 0;
		while (split[index])
		{
			if (!ft_is_number(split[index]))
			{
				if (!ft_contains(split[index], ','))
					print_err("Error : Invalid map");
				if (!is_color_valid(split[index]))
					print_err("Error : Invalid map");
			}
			index++;
		}
		split = (char**)ft_destroy_2d((void**)split);
	}
	if (line)
		free(line);
}

static void		read_file(int fd, t_graphic *g)
{
	char	*line;
	char	**split;
	int		row;
	int		col;

	row = 0;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		col = 0;
		if (!(split = ft_strsplit(line, ' ')))
			print_err("");
		while (split[col])
		{
			g->map[row][col] = ft_atoi(split[col]);
			col++;
		}
		split = (char**)ft_destroy_2d((void**)split);
		row++;
	}
	free(line);
}

static void		allocate_mem(t_graphic *g)
{
	int		row;

	row = 0;
	if (!(g->map = (int**)malloc(sizeof(int*) * g->dimen.rows)))
		print_err("");
	while (row < g->dimen.rows)
	{
		if (!(g->map[row] = (int*)malloc(sizeof(int) * g->dimen.cols)))
			print_err("");
		row++;
	}
}

void			init_map(char *filename, t_graphic *g)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_err("");
	verify_map(fd);
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_err("");
	allocate_mem(g);
	read_file(fd, g);
	close(fd);
}
