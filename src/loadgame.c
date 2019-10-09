/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadgame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 18:13:26 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/09 13:55:09 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		initsdl(t_doom *doom, t_sdl *sdl)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Surface	*surface;
	sdl->win = SDL_CreateWindow("Doom", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(sdl->win);
	sdl->pix = (int*)surface->pixels;
	doom->player.fall = 0;
	SDL_SetRelativeMouseMode(1);
	return (0);
}

int		calcmouse(t_player *player, float yaw)
{
	int		x;
	int		y;

	SDL_GetRelativeMouseState(&x, &y);
	player->yaw = clamp(yaw + y * 0.01f, -5, 5);
	player->angle += x * 0.003f;
	// if (player->angle > 6.283184)
	// 	player->angle -= 6.283184;
	// else if (player->angle < -6.283184)
	// 	player->angle += 6.283184;
	player->anglesin = sinf(player->angle);
	player->anglecos = cosf(player->angle);
	return (0);
}

int		direction(t_doom *doom, t_player *player, float *move_vec)
{	
	if (doom->wsad[0])
	{
		move_vec[0] += player->anglecos * 0.4f;
		move_vec[1] += player->anglesin * 0.4f;
	}
    if (doom->wsad[1])
	{
		move_vec[0] -= player->anglecos * 0.4f;
		move_vec[1] -= player->anglesin * 0.4f;
	}
    if (doom->wsad[2])
	{
		move_vec[0] += player->anglesin * 0.4f;
		move_vec[1] -= player->anglecos * 0.4f;
	}
    if (doom->wsad[3])
	{
		move_vec[0] -= player->anglesin * 0.4f;
		move_vec[1] += player->anglecos * 0.4f;
	}
	move_vec[0] *= doom->time_frame * 60;
	move_vec[1] *= doom->time_frame * 60;
	return (0);
}

int		calcmove(t_doom *doom, t_player *player)
{
	float move_vec[2] = {0.f, 0.f};
	float acceleration;

	direction(doom, player, move_vec);
	doom->push = doom->wsad[0] || doom->wsad[1] || doom->wsad[2] || doom->wsad[3];
	acceleration = doom->push ? 0.6 : 0.4;
	player->velocity.x = player->velocity.x * (1 - acceleration) + move_vec[0] * acceleration;
	player->velocity.y = player->velocity.y * (1 - acceleration) + move_vec[1] * acceleration;
	if (doom->push == 1)
		player->move = 1;
	return (0);
}

int		overlap(float a0, float a1, float b0, float b1)
{
	return (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1));
}

int		intersectbox(t_xy p, t_xy d, t_xy v1, t_xy v2)
{
	return (overlap(p.x, p.x + d.x, v1.x, v2.x) && overlap(p.y, p.y + d.y, v1.y, v2.y));
}

int		pointside(t_xy p, t_xy d, t_xy v1, t_xy v2)
{
	return (vxs(v1.x - (p.x + d.x), v1.y - (p.y + d.y), p.x - (p.x + d.x), p.y - (p.y + d.y)));
}

//Returns 1 if colliders intersects
int		intersects_collider(t_xy pos, t_xy dest_pos, t_xy col_pos1, t_xy col_pos2)
{
	if ((IntersectBox(pos.x, pos.y, dest_pos.x, dest_pos.y, col_pos1.x, col_pos1.y, col_pos2.x, col_pos2.y) &&
		PointSide(dest_pos.x, dest_pos.y, col_pos1.x, col_pos1.y, col_pos2.x, col_pos2.y) <= 0))
		return (1);
	return (0);
}

int		calcnewsector(float dx, float dy, t_doom *doom, t_player *player)
{
	int			n;
	t_xy		p;
	t_xy		d;
	t_sector	*sect;
	t_xy		*v;

	p = (t_xy){player->where.x, player->where.y};
	d = (t_xy){dx, dy};
	sect = &doom->sector[player->sector];
	v = sect->vert;
	n = 0;
	while (n < sect->npoints)
	{
		if (sect->neighbors[n] >= 0 &&
			intersects_collider(p, v2_add(p, v2_multf(d, 8.0f)), v[n], v[n + 1]))
		{
			player->sector = sect->neighbors[n];
			if (player->where.z != doom->sector[player->sector].floor)
				doom->player.fall = 1;
			break ;
		}
		n++;
	}
	player->where.x += dx;
	player->where.y += dy;
	player->anglesin = sinf(player->angle);
	player->anglecos = cosf(player->angle);
	return (0);
}

int		calciswall(t_doom *doom, t_player *player)
{
	t_sector *sect;
	t_xy	*v;
	t_xy	p = (t_xy){player->where.x, player->where.y};
	t_xy	d = (t_xy){player->velocity.x, player->velocity.y};
	float	hole_low;
	float	hole_high;
	float	xd, yd;
	int		n;
	int		t = 0;

	n = 0;
	sect = &doom->sector[player->sector];
	v = sect->vert;
	while (n < sect->npoints)
	{
		if (PointSide(p.x + d.x * 8.0f, p.y + d.y * 8.0f, v[n].x, v[n].y, v[n + 1].x, v[n + 1].y) < 0)
			t++;
		if (t >= 2)
			return (0);
		n++;
	}
	n = 0;
	while (n < sect->npoints)
	{
		if (intersects_collider(p, v2_add(p, v2_multf(d, 8.0f)), v[n], v[n + 1]))
		{
			player->velocity.x = 0;
			player->velocity.y = 0;
			hole_low  = sect->neighbors[n] < 0 ?  9e9 : max(sect->floor, doom->sector[sect->neighbors[n]].floor);
			hole_high = sect->neighbors[n] < 0 ? -9e9 : min(sect->ceil,  doom->sector[sect->neighbors[n]].ceil);
			if (hole_high < player->where.z + HeadMargin ||
				hole_low  > player->where.z - EyeHeight + KneeHeight)
			{
				xd = v[n + 1].x - v[n].x + (d.x * -8.0f);
				yd = v[n + 1].y - v[n].y + (d.y * -8.0f);
				d.x = xd * (d.x * xd + yd * d.y) / (xd * xd + yd * yd);
				d.y = yd * (d.x * xd + yd * d.y) / (xd * xd + yd * yd);
				break ;
			}
		}
		n++;
	}
	calcnewsector(d.x, d.y, doom, player);
	return (0);
}

int		calcjump(t_doom *doom, t_player *player, t_sector *sectors)
{
	float 	nextz;

	player->ground = !player->fall;
	if (player->fall)
	{
		player->velocity.z -= doom->time_frame * 5.f;
		nextz = player->where.z + player->velocity.z;
        if (player->velocity.z < 0 && nextz  < sectors[player->sector].floor + EyeHeight)
        {
            player->where.z    = sectors[player->sector].floor + EyeHeight;
            player->velocity.z = 0;
            player->fall = 0;
            player->ground  = 1;
        }
        else if (player->velocity.z > 0 && nextz > sectors[player->sector].ceil)
        {
            player->velocity.z = 0;
            player->fall = 1;
        }
        if (player->fall)
        {
            player->where.z += player->velocity.z;
            player->move = 1;
        }
	}
	return (0);
}

int		fps(t_doom *doom)
{
	doom->times[1] = doom->times[0];
	doom->times[0] = SDL_GetTicks();
	doom->time_frame = (doom->times[0] - doom->times[1]) / 1000;
	
	return (0);
}

int		animation(t_doom *doom)
{
	static float	t = 0;

	t += doom->time_frame;
	if (t >= 0.15f)
	{
		doom->a = 1;
		t = 0;
	}	
	return (0);
}

int		doors(t_doom *doom, t_player player)
{
	int		n;
	int		neigh;
	int		j;
	int		a = 0;
	static float t = 0;
	t_sector *s;
	
	j = 0;
	while (j < doom->numsectors)
	{
		s = &doom->sector[j];
		if (s->open)
		{
			t += doom->time_frame;
			if (t >= 1.5f)
			{
				a = 1;
				t = 0;
			}	
		}
		if (s->open && a == 1)
			s->up = 1;
		if (s->up && j == player.sector && s->open)
			return (0);
		if (s->door && s->up && s->open)
		{
			s->ceil -= doom->time_frame * 120.f;
			if (s->ceil <= s->floor)
			{
				s->ceil = s->floor;
				s->up = 0;
				s->open = 0;
				s->close = 1;
			}
		}
		else if (s->door && s->up && s->close)
		{
			s->ceil += doom->time_frame * 120.f;
			if (s->ceil >= s->tmpceil)
			{
				s->ceil = s->tmpceil;
				s->up = 0;
				s->open = 1;
				s->close = 0;
			}
		}
		j++;
	}
	return (0);
}

int		loadgame(t_doom *doom)
{
	SDL_Event	ev;

	initsdl(doom, doom->sdl);
	while (1)
	{	
		fps(doom);
		doors(doom, doom->player);
		enemies_update(doom);
		animation(doom);
		drawscreen(doom);
		calcjump(doom, &doom->player, doom->sector);
		if (doom->player.move == 1)
			calciswall(doom, &doom->player);
		while(SDL_PollEvent(&ev))
			hooks(doom, ev);
		calcmouse(&doom->player, doom->player.yaw);
		calcmove(doom, &doom->player);
		SDL_memset(doom->sdl->pix, 0, WIDTH * 4);
		SDL_UpdateWindowSurface(doom->sdl->win);
		if (doom->a)
			doom->a = 0;
	}
	return (0);
}