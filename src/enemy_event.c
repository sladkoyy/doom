/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 19:39:30 by glormell          #+#    #+#             */
/*   Updated: 2019/10/28 20:55:16 by dtoy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	enemy_on_attack(t_doom *doom, t_enemy *enemy)
{
	enemy->attack_damage = (int)random_range(doom->difficult * 4,
												doom->difficult * 7);
	enemy->attack_cd = enemy->attack_speed;
	player_take_damage(doom, enemy->attack_damage);
	play_sound(doom, SOUND_E_ATTACK);
}

void	enemy_on_hit(t_doom *doom, t_enemy *enemy)
{
	if (enemy->health <= 0)
		return ;
	obj_state_change(enemy->obj, ENEMY_STATE_HIT);
	enemy->health -= doom->weapon[doom->player.weapon].damage /
		sqrt(pow(enemy->obj->p.x - doom->player.where.x, 2) +
		pow(enemy->obj->p.y - doom->player.where.y, 2));
	if (enemy->health <= 0)
	{
		obj_state_change(enemy->obj, ENEMY_STATE_DEAD);
		play_sound(doom, SOUND_DEATH);
	}
}

void	enemy_obj_on_hit(t_doom *doom, t_obj *obj)
{
	t_enemy *enemy;

	enemy = get_enemy_by_obj_id(doom, obj->n);
	enemy->on_hit(doom, enemy);
}
