/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtshekel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 22:56:19 by gtshekel          #+#    #+#             */
/*   Updated: 2017/08/11 11:05:48 by gtshekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# define COL 0X00FFFFFF
# define WHITE 16777215
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define HEIGHT_INCR 75
# define HEIGHT_DECR 67
# define ZOOM_IN 69
# define ZOOM_OUT 78

typedef struct	s_dimensions
{
	int			rows;
	int			cols;
	int			win_x;
	int			win_y;
	int			h;
	int			x_off;
	int			y_off;
}				t_dimen;

typedef struct	s_graphic
{
	void		*mlx;
	void		*win;
	int			**map;
	int			scr;
	int			zoom;
	t_dimen		dimen;
}				t_graphic;

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
}				t_point;

typedef struct	s_pair
{
	t_point		p1;
	t_point		p2;
}				t_pair;

void			getdimensions(char *filename, t_graphic	*g);
void			draw_cols(t_graphic *g);
void			draw_rows(t_graphic *g);
void			drawmap(t_graphic *g);
void			init_map(char *filname, t_graphic *g);
void			update_zoom(t_graphic *g, int keycode);
void			update_height(t_graphic *g, int keycode);
void			update_hori_shift(t_graphic *g, int keycode);
void			update_verti_shift(t_graphic *g, int keycode);
void			print_err(char *str);

#endif
