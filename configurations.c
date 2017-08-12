/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configurations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtshekel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 13:58:33 by gtshekel          #+#    #+#             */
/*   Updated: 2017/08/08 14:01:02 by gtshekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			update_zoom(t_graphic *g, int keycode)
{
	g->zoom = keycode == ZOOM_IN ? g->zoom + 2 : g->zoom - 2;
	g->zoom = g->zoom < 0 ? 0 : g->zoom;
}

void			update_height(t_graphic *g, int keycode)
{
	g->dimen.h = keycode == HEIGHT_INCR ? g->dimen.h + 1 : g->dimen.h - 1;
}

void			update_hori_shift(t_graphic *g, int keycode)
{
	if (keycode == LEFT)
		g->dimen.x_off -= 20;
	else
		g->dimen.x_off += 20;
}

void			update_verti_shift(t_graphic *g, int keycode)
{
	g->dimen.y_off = keycode == UP ? g->dimen.y_off - 20 : g->dimen.y_off + 20;
}
