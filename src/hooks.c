/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 18:28:42 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/05 20:17:52 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		finddoor(t_doom *doom, t_player player)
{
	t_sector	*s;
	t_xy		*v;
	int			n;
	float		dx = player.anglecos * 10;
	float		dy = player.anglesin * 10;
	float		px = player.where.x;
	float		py = player.where.y;

	s = &doom->sector[player.sector];
	v = s->vert;
	n = 0;	
	while (n < s->npoints)
	{
		if (s->neighbors[n] >= 0 &&
		IntersectBox(px, py, px + dx, py + dy, v[n].x, v[n].y, v[n + 1].x, v[n + 1].y) &&
		PointSide(px + dx, py + dy, v[n].x, v[n].y, v[n + 1].x, v[n + 1].y) < 0)
		{
			doom->sector[s->neighbors[n]].up = 1;
			break ;
		}
		n++;
	}
	
	return (0);
}

int		keydown(t_doom *doom, SDL_Event ev)
{
	if (ev.key.keysym.sym == '\033')
	{
		SDL_Quit();
		exit(0);
	}
	if (ev.key.keysym.sym == 'w')
		doom->wsad[0] = 1;
	if (ev.key.keysym.sym == 's')
		doom->wsad[1] = 1;
	if (ev.key.keysym.sym == 'a')
		doom->wsad[2] = 1;
	if (ev.key.keysym.sym == 'd')
		doom->wsad[3] = 1;
	if (ev.key.keysym.sym == 'e')
	{
		finddoor(doom, doom->player);
	}
	if (ev.key.keysym.sym == SDLK_SPACE)
	{
		doom->player.velocity.z = 3.f;
		doom->player.fall = 1;
	}
	if (ev.key.keysym.sym == 'p')
		profile_output(doom);
	if (ev.key.keysym.sym == 'm')
		doom->sector[doom->player.sector].light += 0.1f;
	if (ev.key.keysym.sym == 'n')
		doom->sector[doom->player.sector].light -= 0.1f;
	return (0);
}

int		keyup(t_doom *doom, SDL_Event ev)
{
	if (ev.key.keysym.sym == 'w')
		doom->wsad[0] = 0;
	if (ev.key.keysym.sym == 's')
		doom->wsad[1] = 0;
	if (ev.key.keysym.sym == 'a')
		doom->wsad[2] = 0;
	if (ev.key.keysym.sym == 'd')
		doom->wsad[3] = 0;
	return (0);
}

int		hooks(t_doom *doom, SDL_Event ev)
{
	if (ev.type == SDL_KEYDOWN)
		keydown(doom, ev);
	if (ev.type == SDL_KEYUP)
		keyup(doom, ev);
	return (0);
}
