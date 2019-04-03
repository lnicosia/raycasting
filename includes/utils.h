/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:26:43 by lnicosia          #+#    #+#             */
/*   Updated: 2019/04/03 17:58:05 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <SDL.h>
# include "libft.h"

typedef struct	s_v2
{
	double	x;
	double	y;
}				t_v2;

typedef struct	s_sector
{
	double			floor;
	double			ceiling;
	struct s_wall	*walls;
}				t_sector;

typedef struct	s_wall
{
	int			x;
	int			y;
	t_sector	*next;
}				t_wall;

typedef struct	s_player
{
	t_v2		pos;
	t_v2		dir;
	t_v2		plane;
	t_sector	sector;
}				t_player;

typedef struct	s_map
{
	t_sector	*sectors;
	t_wall		*walls;
}				t_map;

typedef struct	s_sdl
{
	SDL_Window		*window;
	SDL_Event		event;
	SDL_Renderer	*renderer;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	unsigned int	*img_str;
}				t_sdl;

typedef struct	s_env
{
	t_sdl			sdl;
	int				w;
	int				h;
	int				running;
}				t_env;

void			free_all(t_env *env);
void			clear_image(t_env *env);
int				init_sdl(t_env *env);
void			init_map(t_env *env);

#endif
