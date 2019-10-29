/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:24:41 by njacobso          #+#    #+#             */
/*   Updated: 2019/10/29 04:02:49 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
**	Возвращает 1, если стена i ближе чем player.col_size
*/

int		intersect_walls(t_doom *doom, t_xy pl, int i)
{
	t_xy		pos1;
	t_xy		pos2;
	t_sectors	*sect;

	sect = &doom->sectors[doom->player.sector];
	pos1 = sect->vert[i];
	pos2 = sect->vert[i + 1];
	if (line_distance(pos1, pos2, pl) < doom->player.col_size)
		return (1);
	return (0);
}

/*
** returns 0 if circle pl + pl->col_size intersects with a wall
*/

int		walls_collision(t_doom *doom, t_xy pl)
{
	t_sectors	*sect;
	t_xy		*v;
	int			n;
	t_xy		hole;
	float		height;

	sect = &doom->sectors[doom->player.sector];
	v = sect->vert;
	n = 0;
	height = doom->player.sit ? DUCKHEIGHT : EYEHEIGHT;
	while (n < sect->npoints)
	{
		if (intersect_walls(doom, pl, n) == 1)
		{
			hole.x = sect->neighbors[n] < 0 ? 9e9 :
			MAX(sect->floor, doom->sectors[sect->neighbors[n]].floor);
			hole.y = sect->neighbors[n] < 0 ? -9e9 :
			MIN(sect->ceil, doom->sectors[sect->neighbors[n]].ceil);
			if (hole.y < doom->player.where.z + HEADMARGIN ||
				hole.x > doom->player.where.z - height + KNEEHEIGHT)
				return (0);
		}
		n++;
	}
	return (1);
}

/*
** returns 0 if quad pl1-pl2 intersected with obj collider
*/

int		player_move(t_doom *doom, t_xy delta)
{
	t_xy		player;
	t_xy		move_pos;
	t_xy		pl;

	if (doom->player.velocity.x == 0 || doom->player.velocity.y == 0)
		return (0);
	player = (t_xy){doom->player.where.x, doom->player.where.y};
	pl = v2_add(player, (t_xy){delta.x, 0});
	delta.x *= walls_collision(doom, pl);
	pl = v2_add(player, (t_xy){0, delta.y});
	delta.y *= walls_collision(doom, pl);
	pl = v2_add(player, (t_xy){delta.x, 0});
	delta.x *= obj_collision(doom, pl);
	pl = v2_add(player, (t_xy){0, delta.y});
	delta.y *= obj_collision(doom, pl);
	doom->player.where.x = player.x + delta.x;
	doom->player.where.y = player.y + delta.y;
	doom->player.psin = sinf(doom->player.angle);
	doom->player.pcos = cosf(doom->player.angle);
	return (1);
}

/*
** returns 1 if found interactable obj in closest proximity
*/

int		player_blood_update(t_doom *doom)
{
	int		i;
	int		size;
	float	intensity;

	intensity = doom->player.flash_duration;
	if (intensity <= 0)
		return (0);
	size = WIDTH * HEIGHT;
	i = 0;
	while (i < size)
	{
		doom->sdl->pix[i] = rgb_mix(doom->player.flash_color, doom->sdl->pix[i], intensity);
		i++;
	}
	doom->player.flash_duration -= doom->fps.time_frame;
	doom->player.flash_duration = CLAMP(doom->player.flash_duration, 0.0f, 1.0f);
	return (1);
}

int		player_take_damage(t_doom *doom, int damage)
{
	t_player *pl;

	pl = &doom->player;
	if (pl->hp < 0)
		return (0);
	pl->flash_duration = 0.4f;
	pl->hp -= damage;
	if (!pl->dead)
		play_sound(doom, SOUND_DAMAGE);
	if (pl->hp <= 0)
	{
		if (!pl->dead)
			play_sound(doom, SOUND_SCREAM);
		pl->flash_duration = 1.0f;
		pl->flash_color = 0xff0000;
		pl->dead = 1;
		pl->where.z = doom->sectors[pl->sector].floor + 2;
	}
	return (1);
}
