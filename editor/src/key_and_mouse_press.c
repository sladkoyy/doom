/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_mouse_press.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohelly <ohelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 22:12:24 by ohelly            #+#    #+#             */
/*   Updated: 2019/10/01 19:14:38 by ohelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_editor.h"

void	kek(t_doom *doom)
{
	int i = -1;
	while (++i < doom->walls->count)
		printf("i = %d  sect = %d  vert1 = %d  vert2 = %d  portal = %d\n", i, doom->walls->wall[i].sectors, doom->walls->wall[i].vert_one, doom->walls->wall[i].vert_two, doom->walls->wall[i].portal);
	i = -1;
	while (++i < doom->verts->count)
		printf("x = %d   y = %d  i = %d\n", doom->verts->list[i].pos.x, doom->verts->list[i].pos.y, i);
}

void	key_and_mouse_press(t_doom *doom)
{
	while (SDL_PollEvent(&doom->sdl->ev))
	{
		if (doom->sdl->ev.type == SDL_KEYDOWN)
		{
			if (doom->sdl->ev.key.keysym.sym == '\033')
				exit (0);
			if (doom->sdl->ev.key.keysym.sym == ' ')
				build_sector(doom);
			if (doom->sdl->ev.key.keysym.sym == 'e')
				save(doom);
			if (doom->sdl->ev.key.keysym.sym == 'w')
				find_portal(doom);
			if (doom->sdl->ev.key.keysym.sym == 's')
				get_closest_sector(doom);
			if (doom->sdl->ev.key.keysym.sym == 'k')
				kek(doom);
			if (doom->sdl->ev.key.keysym.sym == '\r')
			{
				if (doom->walls->selected_wall != -1)
					build_portal(doom);
				//else if (doom->sects->selected_sector != -1)
				//	config_sector(doom);
			}
			if (doom->sdl->ev.key.keysym.sym == 'v')
				split_wall(doom);
			if (doom->sdl->ev.key.keysym.sym == 'l')
				split_sectors(doom);
			if (doom->sdl->ev.key.keysym.sym == 'c')
				remove_built_sector(doom);
			if (doom->sdl->ev.key.keysym.sym == SDLK_LEFT)
				doom->move_vector = (t_v2){-1, doom->move_vector.y};
			else if (doom->sdl->ev.key.keysym.sym == SDLK_RIGHT)
				doom->move_vector = (t_v2){1, doom->move_vector.y};
			else
				doom->move_vector = (t_v2){0, doom->move_vector.y};
			if (doom->sdl->ev.key.keysym.sym == SDLK_UP)
				doom->move_vector = (t_v2){doom->move_vector.x, -1};
			else if (doom->sdl->ev.key.keysym.sym == SDLK_DOWN)
				doom->move_vector = (t_v2){doom->move_vector.x, 1};
			else
				doom->move_vector = (t_v2){doom->move_vector.x, 0};
			
		}
		if (doom->sdl->ev.type == SDL_MOUSEMOTION)
		{
			*doom->mouse = (t_mouse){ doom->sdl->ev.motion.x, doom->sdl->ev.motion.y, 0 , 0 };
			doom->move_vector = (t_v2){0, 0};
		}
		output(doom);
	}
}