/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadfonts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:05:50 by glormell          #+#    #+#             */
/*   Updated: 2019/10/25 19:40:02 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		loadfonts(t_hud *hud)
{
	char *env;

	env = ft_strjoin(getenv("HOME"), "/Documents/DoomNukem");
	env = ft_strjoinc(env, "/DooM.ttf");
	hud->font = TTF_OpenFont(env, 20);
	free(env);
	return (1);
}
