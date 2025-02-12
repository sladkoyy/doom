/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawceilandfloor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:20:00 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/29 06:06:55 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			check_light(int color, t_sectors *s)
{
	static int	prev_light;
	static int	prev_color;

	if (color != prev_color)
	{
		prev_light = rgb_multiply(color, s->light);
		prev_color = color;
	}
	return (prev_light);
}

int			is_sky(t_cf *p, t_cood *cood, t_doom *doom, t_sectors *s)
{
	p->hei = cood->y < cood->cy.a ? cood->yceil : cood->yfloor;
	p->x = cood->x;
	p->y = cood->y;
	if (s->sky == 1 && p->hei == cood->yceil)
	{
		doom->visible[cood->y][cood->x] = 1;
		return (0);
	}
	return (1);
}

int			render_ceil_floor(t_doom *doom, t_sectors *s,
t_cood *cood, t_player player)
{
	t_xyz	map;
	t_xyz	txt;
	t_cf	p;
	int		color;
	t_img	img;

	if (!(is_sky(&p, cood, doom, s)))
		return (0);
	to_map_coordinates(&p, &map, player);
	txt.x = (map.x * 4);
	txt.z = (map.z * 4);
	img = cood->y < cood->cy.a - 1 ? doom->img[doom->ceils[s->txtc].image] :
	doom->img[doom->floors[s->txtf].image];
	color = img.data[((int)txt.z % img.h) * img.w + ((int)txt.x % img.w)];
	if (cood->y != cood->cy.b)
		doom->sdl->pix[cood->y * WIDTH + cood->x] = check_light(color, s);
	if (!color)
	{
		doom->visible[cood->y][cood->x] = 1;
		return (0);
	}
	return (1);
}

int			draw_ceil_floor(t_doom *doom, t_sectors *s,
t_cood *cood, t_player player)
{
	int		y;

	y = doom->ytop[cood->x];
	while (y <= doom->ybot[cood->x])
	{
		if (y >= cood->cy.a - 1 && y < cood->cy.b)
		{
			y = cood->cy.b;
			y++;
			continue ;
		}
		cood->y = y;
		if (!(render_ceil_floor(doom, s, cood, player)))
		{
			y++;
			continue ;
		}
		y++;
	}
	return (0);
}
