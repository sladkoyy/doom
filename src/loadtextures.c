/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadtextures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:53:36 by dtoy              #+#    #+#             */
/*   Updated: 2019/09/29 19:59:30 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		new_image(t_doom *doom, char *texture_name)
{
	t_img		img;
	SDL_Surface	*surface;

	surface = IMG_Load(texture_name);
	img.data = (int*)surface->pixels;
	img.w = surface->w;
	img.h = surface->h;
	
	doom->images[doom->images_count] = img;
	doom->images_count++;
	printf("Image %s loaded.\n", texture_name);
	return (doom->images_count - 1);
}

int		loadtextureobjs(t_doom *doom, t_obj *obj, t_player player)
{
	SDL_Surface *surface;
	int a;

	//	N NE E SE S SW W WN

	obj[0].images[0][0] = new_image(doom, "textures/obj/head2/headN.png");
	obj[0].images[1][0] = new_image(doom, "textures/obj/head2/headNE.png");
	obj[0].images[2][0] = new_image(doom, "textures/obj/head2/headE.png");
	obj[0].images[3][0] = new_image(doom, "textures/obj/head2/headSE.png");
	obj[0].images[4][0] = new_image(doom, "textures/obj/head2/headS.png");
	obj[0].images[5][0] = new_image(doom, "textures/obj/head2/headSW.png");
	obj[0].images[6][0] = new_image(doom, "textures/obj/head2/headW.png");
	obj[0].images[7][0] = new_image(doom, "textures/obj/head2/headNW.png");
	obj[0].images[8][0] = new_image(doom, "textures/obj/head2/headDead.png");
	doom->enemy = create_enemy(doom, &obj[0]);

	/*
	obj[0].images[0][0] = new_image(doom, "textures/obj/bar/BAR1A0.png");
	obj[0].images[0][1] = new_image(doom, "textures/obj/bar/BAR1B0.png");
	obj[0].images[0][2] = new_image(doom, "textures/obj/bar/BAR1C0.png");
	obj[0].images[0][3] = new_image(doom, "textures/obj/bar/BAR1D0.png");
	obj[0].images[0][4] = new_image(doom, "textures/obj/bar/BAR1E0.png");
	obj[0].images[0][5] = new_image(doom, "textures/obj/bar/BAR1F0.png");
	obj[0].images[0][6] = new_image(doom, "textures/obj/bar/BAR1G0.png");
	obj[0].images[0][7] = new_image(doom, "textures/obj/bar/BAR1H0.png");
	obj[0].images[0][8] = new_image(doom, "textures/obj/bar/BAR1I0.png");
	obj[0].images[0][9] = new_image(doom, "textures/obj/bar/BAR1J0.png");
	obj[0].images[0][10] = new_image(doom, "textures/obj/bar/BAR1K0.png");
	obj[0].images[0][11] = new_image(doom, "textures/obj/bar/BAR1L0.png");
	obj[0].images[0][12] = new_image(doom, "textures/obj/bar/BAR1M0.png");

	doom->enemy = create_enemy(doom, &obj[0]);
	a = new_image(doom, "textures/obj/head/HEADA1.png");
	obj[0].images[1][0] = a;
	obj[0].images[2][0] = a;
	obj[0].images[3][0] = a;
	obj[0].images[4][0] = a;
	obj[0].images[5][0] = a;
	obj[0].images[6][0] = a;
	obj[0].images[7][0] = a;
	*/
	obj[1].images[0][0] = new_image(doom, "textures/obj/people/devka/devka.png");
	obj[1].images[0][1] = new_image(doom, "textures/obj/people/devka/devka1.png");

	obj[2].images[0][0] = new_image(doom, "textures/obj/head/HEADA1.png");
	obj[2].images[0][1] = new_image(doom, "textures/obj/head/HEADB1.png");
	obj[2].images[0][2] = new_image(doom, "textures/obj/head/HEADC1.png");
	obj[2].images[0][3] = new_image(doom, "textures/obj/head/HEADD1.png");
	obj[2].images[0][4] = new_image(doom, "textures/obj/head/HEADE1.png");
	obj[2].images[0][5] = new_image(doom, "textures/obj/head/HEADF1.png");

	obj[3].images[0][0] = new_image(doom, "textures/obj/people/svidetel/svidetel.png");
	return (0);
}

int		loadtextures(t_doom *doom)
{
	loadtextureobjs(doom, doom->obj, doom->player);
	return (0);
}
