/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoy <dtoy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 19:45:10 by dtoy              #+#    #+#             */
/*   Updated: 2019/10/28 20:13:21 by glormell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H
# include "libft.h"
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <SDL_mixer.h>
# include <get_next_line.h>

# define WIDTH 1280
# define HEIGHT 720
# define NEARZ 1e-4f
# define FARZ 5
# define NEARSIDE 1e-5f
# define FARSIDE 20.f
# define EyeHeight  15
# define DuckHeight 4.5
# define HeadMargin 1
# define KneeHeight 2
# define HFOV (0.73f * HEIGHT / WIDTH)
# define VFOV (0.2f)
# define min(a,b)             (((a) < (b)) ? (a) : (b))
# define max(a,b)             (((a) > (b)) ? (a) : (b))
# define clamp(a, mi,ma)      min(max(a,mi),ma)
# define Overlap(a0,a1,b0,b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
# define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3) (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))
# define PointSide(px,py, x0,y0, x1,y1) vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0))

# define SOUND_SHOOT			0
# define SOUND_PICKUP			1
# define SOUND_DEATH			2
# define SOUND_INTERACT			3
# define SOUND_E_ATTACK			4
# define SOUND_LOSS				5
# define SOUND_WEAPON_PICKUP	6
# define SOUND_RELOAD			7
# define SOUND_SCREAM			8
# define SOUND_JUMP				9
# define SOUND_DAMAGE			10
# define SOUND_PISTOL			11
# define SOUND_SHOTGUN			12
# define SOUND_RIPPER			13
# define SOUND_FOOT				14
# define SOUND_EXPLOSIVE		15
# define SOUND_CRASH			16

# define ENEMY_STATE_IDLE	0
# define ENEMY_STATE_DEAD	8
# define ENEMY_STATE_HIT	9
# define ENEMY_STATE_ATTACK	10

# define OBJ_TYPE_BOX			0
# define OBJ_TYPE_BREAKABLE		1
# define OBJ_TYPE_EXPLOSIVE		2
# define OBJ_TYPE_ENEMY_REG		10
# define OBJ_TYPE_PISTOL		20
# define OBJ_TYPE_SHOTGUN		21
# define OBJ_TYPE_SMG			22
# define OBJ_TYPE_AMMO_P		23
# define OBJ_TYPE_AMMO_SH		24
# define OBJ_TYPE_AMMO_SMG		25
# define OBJ_TYPE_MED_SMALL		26
# define OBJ_TYPE_MED_MEDIUM	27
# define OBJ_TYPE_MED_BIG		28
# define OBJ_TYPE_KEY			29

# define PIC_TYPE_DECOR			0
# define PIC_TYPE_SWITCH		1
# define PIC_TYPE_END			2

# define WEAPON_FOOT			0
# define WEAPON_PISTOL			1
# define WEAPON_SHOTGUN			2
# define WEAPON_RIPPER			3

# define SHOTS_NUM				128

typedef struct	s_scaler
{
	int 		result;
	int			bop;
	int			fd; 
	int			ca;
	int			cache; 
}				t_scaler;

typedef struct	s_be
{
	int			x;
	int			begin;
	int			end;
}				t_be;

typedef struct	s_py_i
{
	int			y1;
	int			y2;
}				t_py_i;

typedef struct	s_xy
{
	float		x;
	float		y;
}				t_xy;

typedef	struct 	s_xyz
{
	float		x;
	float		y;
	float		z;
}				t_xyz;

typedef	struct 	s_ab_i
{
	int			a;
	int			b;
}				t_ab_i;

typedef struct	s_img
{
	int			*data;
	int			w;
	int			h;
}				t_img;

typedef struct	s_texture
{
	int			image; //0
}				t_texture;

typedef struct	s_obj
{
	int			id;
	int			n;
	int			enabled;
	t_xy		p;
	int			sector;
	int			type;
	int			**images;
	int			*anim_count;
	int			anim_frame;
	int			states_count;
	int			states_frame;
	float		col_size;
	int			col_passable;
	float		scale;
	void		(*on_collision)(struct s_doom *doom, struct s_obj *obj);
	void		(*on_interaction)(struct s_doom *doom, struct s_obj *obj);
	void		(*on_hit)(struct s_doom *doom, struct s_obj *obj);
	void		(*on_anim_end)(struct s_obj *obj);
}				t_obj;

typedef struct	s_data
{
	int			type;
	int			**images;
	int			*anim_count;
	int			states_count;
}				t_data;

typedef	struct	s_cood
{
	int			x;
	int			y;
	int			n;
	int			neighbor;
	int			beginx;
	int			endx;
	float		u0;
	float		u1;
	float		yceil;
	float		yfloor;
	float		nyceil;
	float		nyfloor;
	int			txtx;
	int			num;
	t_xyz		v1;
	t_xyz		v2;
	t_xyz		t1;
	t_xyz		t2;
	t_xy		org1; 
	t_xy		org2;
	t_xy		scale1;
	t_xy		scale2;
	int			w1x; //left point
	int			w2x; //right point
	t_ab_i		wy; 
	t_ab_i		wx; //current point
	t_ab_i		cy;
	t_ab_i		w1y;
	t_ab_i		w2y;
	t_ab_i		ny;
	t_ab_i		nx;
	t_ab_i		cny;
	t_ab_i		n1y;
	t_ab_i		n2y;
}				t_cood;

typedef struct	s_pics
{
	t_xyz		p;
	t_xy		p1;
	t_xy		p2;
	int			neighbor;
	int			sector;
	int			type;
	int			wall;
	int			**images;
	int			*anim_count;
	int			anim_frame;
	int			states_count;
	int			states_frame;
	t_cood		pcood;
	int			vis;
}				t_pics;

typedef struct		s_player
{
	float		angle;
	float		psin;
	float		pcos;
	float		yaw; //look up/down
	t_xyz		where;
	t_xyz		velocity;
	int			sector;
	int			move; // player moving
	int			sit; // crouch
	int			sprint; // crouch
	int			stand; 
	int			fall; // jump or fall
	int			ground; // player on the ground (fall = !ground)
	int			start;
	int			end;
	int			weapon;
	int			allweapons[4];
	int			hp;
	float		blood; //intensity of blood on the screen
	float		col_size;
	int			reload;
	int			shoots;
	int			wall;
	int			key;
	int			dead;
}				t_player;
	float			col_size;



typedef struct	s_sectors
{
	t_xy		*vert; //vertices
	float		constceil; //constceil for door/elevator
	//float		constfloor; //constfloor for elevator
	float		ceil;
	float		floor;
	float		light;
	int			type; //door or elevator
	int			active; //door or elevetor going up/down (open/close)
	int			open; //for elevator top position
	int			close; //bottom
	int			npoints; //vertices count
	int			*neighbors; //neighbour sectors
	int			txtf; //floor
	int			txtc; //ceil
	int			*txtw; //wall
	int			sky;
}				t_sectors;

typedef struct	s_line
{
	int			y0;
	int			y1;
	int			x0;
	int			x1;
	int			dx;
	int			dy;
	int			color;
}				t_line;

typedef struct	s_sdl
{
	SDL_Window	*win;
	int			*pix;
	t_line		line;
}				t_sdl;

typedef struct	s_num
{
	int     	vertexes;
	int			weapons;
    int     	sectors;
	int			objs;
	int			pics;
	int			txts;
	int			enemies;
}				t_num;

typedef struct	s_weapon
{
	int			type;
	float		delay;
	int			**images;
	int			*anim_count;
	int			anim_frame;
	int			states_count;
	int			states_frame;
	int			ammo;
	int			damage;
	int			scatterx;
	int			scattery;
}				t_weapon;

typedef struct	s_fps
{
	float		times[64];
	float		time_frame;
	float		fps_total;
	float		fps_count;
}				t_fps;

typedef struct 	s_item
{
	int			sx;
	int			ex;
	int			sector;
	int			*ytop;
	int			*ybot;
}				t_item;

typedef struct	s_hudel
{
	TTF_Font	*f; // Font
	char		*t; // Title
	SDL_Surface	*s; // Surface
	unsigned char		*p; // Pixels
	int			w; // Width
	int			h; // Height
	int			x; // Offset X
	int			y; // Offset Y
	int			c; // Color
	int			b; // Border Color
}				t_hudel;

typedef struct	s_hud
{
	TTF_Font	*font;
	t_hudel		health;
	t_hudel		ammo;
	t_obj		*key;
}				t_hud;

typedef struct	s_music
{
	Mix_Music	*music;
	int			volume;
}				t_music;

typedef struct	s_sound
{
	Mix_Chunk	*sound;
	id_t		volume;
}				t_sound;

typedef struct	s_doom
{
	t_img		img[512];
	t_weapon	*weapon;
	t_hud		*hud;
	t_texture	*sky;
	t_texture	*walls;
	t_texture	*floors;
	t_texture	*ceils;
	t_texture	*bullet;
	t_obj		*objs;
	t_data		*objs_data;
	t_pics		*pics;
	t_pics		shot_pics;
	int			num_shots;
	int			isshoot;
	t_data		*pics_data;
	t_sectors	*sectors;
	t_sdl		*sdl;
	t_player	player;
	t_num		num;
	t_fps		fps;
	t_item 		queue[64];
	t_item		*head;
	t_item		*tail;
	t_item		*item;
	t_item		now;
	t_cood		cood;
	int			wsad[4];
	int			visible[HEIGHT][WIDTH];
	int			ytop[WIDTH];
	int			ybot[WIDTH];
	int			push;
	int			a;
	int			lkey;
	int			rkey;
	float		*len;
	int			shakex;
	int			shakey;
	int			shaketmp;
	int			*lookwall;
	float		wall_col_size;
	//int			weapon_change;
	int			change_y;
	//int			change_tmp;
	int			pic_interaction[64];
	int			*obj_ind;
	int			*order;
	int			obj_num;
	int			maplines;
	struct s_enemy		*enemies;
	t_music		music[2];
	t_sound		sound[17];
}				t_doom;

typedef struct		s_enemy
{
	t_obj			*obj;
	//direction vector
	t_xy			dir;
	//rotation is stored in radians
	float			rot;
	//0 - wandering, 1 - attacking
	float			view_distance;
	float			move_speed;
	int				state;
	int				health;
	float			attack_speed;
	float			attack_cd;
	int				attack_damage;
	void			(*on_attack)(t_doom *doom, struct s_enemy *enemy);
	void			(*on_hit)(t_doom *doom, struct s_enemy *enemy);
	void			(*on_framestart)(t_doom *doom, struct s_enemy *enemy);
}					t_enemy;

int		findpicpoints(t_doom *doom, t_pics *pic, float w);

int		load_all(t_doom *doom, char **av);
char	**load_map(t_doom *doom, char *av);
int		load_texture_data(char **map, t_doom *doom);
int		load_weapon_data(char **map, t_doom *doom);
int		load_obj_data(char **map, t_doom *doom);
int		load_pic_data(char **map, t_doom *doom);
int		load_params(t_doom *doom, char **map);
int		load_image(char *map, int *image, t_img *img);
int		new_image(char *str, t_img *img, int w, int h);
int		drawobj(t_doom *doom, t_obj *obj, t_xy pos);
void	obj_anim_next(t_obj *obj);
int		check_light(int color, t_sectors *s);
int		calc_move(t_doom *doom, t_player *player);
int		calc_is_wall(t_doom *doom, t_player *player);
int		calc_jump(t_doom *doom, t_player *player, t_sectors *sectors, t_fps fps);
int		doors(t_doom *doom, t_player player, t_fps fps);
int		animation(t_doom *doom, t_fps fps);
int		intersect(t_xyz *t1, t_xyz *t2, t_cood *cood);
int		point_side(t_xy d, t_xy v1, t_xy v2);
int		intersect_box(t_xy p, t_xy d, t_xy v1, t_xy v2);
int		find_scales(t_doom *doom, t_cood *cood, t_player player);
int		find_yceil_yfloor(t_doom *doom, t_sectors *s, t_cood *cood, t_player player);
int		calc_pics(t_doom *doom, t_pics *pic, t_player player);
void	render_walls(t_doom *doom, t_sectors *s, t_cood *cood, t_player player);
void	drawsky(t_doom *doom, t_player player, t_texture *sky, t_img *img);
int		draw_walls(t_doom *doom, t_player player);
t_img	wpn_get_image(t_doom *doom, t_weapon *wpn);
void	wpn_anim_next(t_doom *doom, t_player *player, t_weapon *wpn, t_fps fps);
void	wpn_state_change(t_weapon *wpn, int state);
int		render_weapon(t_doom *doom, t_weapon *wpn);
void	vline2(int x, t_ab_i wy, t_scaler ty, t_doom *doom);
void	vline3(int x, t_ab_i wy, t_scaler ty, t_doom *doom);
void	vlineobj(t_be px, t_ab_i wy, t_obj *obj, t_doom *doom);
int		render_pics(t_doom *doom, t_pics *pics, int x) ;
t_scaler	scaler_init(t_ab_i wy, int cya, int u0, int u1);
void	to_map_coordinates(float mapY, t_cood *cood, t_xyz *map, t_player player);
int		scaler_next(t_scaler* i);
int		draw_ceil_floor(t_doom *doom, t_sectors *s, t_cood *cood, t_player player);
int		calc_sector(t_doom *doom, t_sectors *s, t_cood *cood, t_player player);
void	draw_scope(t_sdl *sdl);
int		countall(t_doom *doom, char **map);
int		loadvertexes(t_xy *v, char *str);
int		loadsectors(t_sectors *s, t_xy *v, char *str);
char	*todigit(char *str, float *data);
int		loadobjs(t_doom *doom, char *str);
int		shoot(t_doom *doom);
int		loadpics(t_doom *doom, t_pics *pic, t_data *pics_data, char *str);
t_img	pic_get_image(t_doom *doom, t_pics *pic);
void	pic_anim_next(t_pics *pic);
int		loadplayer(t_player *player, char *str);
int		load_hud(t_doom *doom);
int		loadfonts(t_hud *hud);
int		load_game(t_doom *doom);
int		hooks(t_doom *doom, SDL_Event ev);
int		profile_output(t_doom *doom);
int		draw_screen(t_doom *doom);
int		draw_walls(t_doom *doom, t_player player);
int		rgb_multiply(int color, float value);
float	vxs(float x0, float y0, float x1, float y1);
float	yaw(float y, float z, t_player player);
void	drawweapon(t_doom *doom, t_weapon *weapon);
void	drawhud(t_doom *doom);
int     drawsprites(t_doom *doom, t_obj *obj, t_player player);
t_img	weapon_get_image(t_doom *doom, t_weapon *weapon);
int		player_move(t_doom *doom, t_xy move_pos);
int		player_take_damage(t_doom *doom, int damage);
int		player_blood_update(t_doom *doom);
char	*ft_strjoinc(char *s1, char const *s2);
//objects
int		objects_update(t_doom *doom);
void	on_collision_key(t_doom *doom, t_obj *obj);
int		find_obj_interaction(t_doom *doom);
t_img	obj_get_image(t_doom *doom, t_obj *obj);
//enemies
void	enemies_update(t_doom *doom);
t_enemy	*create_enemy_default(t_doom *doom, t_obj *obj);
void	enemy_on_framestart(t_doom *doom, t_enemy *enemy);
void	enemy_on_attack(t_doom *doom, t_enemy *enemy);
void	enemy_on_hit(t_doom *doom, t_enemy *enemy);
void	enemy_obj_on_hit(t_doom *doom, t_obj *obj);
//collisions
int		collision_box(t_xy p1, t_xy p2, t_xy v1, t_xy v2);
int		collision_circle(t_xy pos1, float rad1, t_xy pos2, float rad2);
int		collision_box_dir(t_xy pos1, t_xy pos2, t_xy col_pos1, t_xy col_pos2);
int		overlap(float a0, float a1, float b0, float b1);
//sounds
int		sound_free_everything(t_doom *doom);
int		play_music(t_doom *doom, int index);
int		play_sound(t_doom *doom, int index);
void	load_music(t_doom *doom);
//math
t_xy	rot_to_v2(float rot);
float	v2_to_rot(t_xy v2);
t_xy	v2_add(t_xy v1, t_xy v2);
t_xy	v2_addf(t_xy v2, float f);
t_xy	v2_subtract(t_xy v1, t_xy v2);
t_xy	v2_multf(t_xy v2, float f);
t_xy	v2_normalize(t_xy v2);
float	distance(t_xy p1, t_xy p2);
float	rad_to_deg(float rad);

void	close_program(SDL_Event ev, t_doom *doom);
void	jump_sprint_crouch(t_doom *doom, SDL_Event ev,
t_player *player, t_sectors *s);
void	reload_pistol(SDL_Event ev, t_doom *doom,
t_weapon weapon, t_player *player);
void	change_all_weapons(t_weapon *weapon, SDL_Event ev,
t_player *player, int *allweapons);
void	change_weapon(t_player *player, t_weapon *weapon, int n);
int		find_on_hit_obj(t_doom *doom);
int		find_pic_interaction(t_doom *doom, t_player player, t_pics *pics);
int		find_door(t_doom *doom, t_player player);
int		shoot_wall(t_doom *doom, t_player player, t_sectors *sect, t_pics *pic);
void	left_mouse_keydown(t_doom *doom, SDL_Event ev,
t_weapon *weapon, t_player *player);

#endif
