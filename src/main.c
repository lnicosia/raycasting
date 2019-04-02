/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:13:15 by lnicosia          #+#    #+#             */
/*   Updated: 2019/04/02 17:43:32 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include <math.h>

# define min(a,b)             (((a) < (b)) ? (a) : (b))
# define max(a,b)             (((a) > (b)) ? (a) : (b))
# define clamp(a, mi,ma)      min(max(a,mi),ma)

int		quit(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *surface,
		SDL_Texture *texture)
{
	if (window)
		SDL_DestroyWindow(window);
	if (renderer)
		SDL_DestroyRenderer(renderer);
	if (surface)
		SDL_FreeSurface(surface);
	if (texture)
		SDL_DestroyTexture(texture);
	SDL_Quit();
	return (1);
}

int	w = 1000;
int	h = 1000;
int worldMap[24][24] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	clear_img(int *img_str)
{
	int y = 0;
	while (y < h / 2)
	{
		int x = 0;
		while (x < w)
		{
			img_str[x + y * w] = 0x444444FF;
			x++;
		}
		y++;
	}
	y = h / 2;
	while (y < h)
	{
		int x = 0;
		while (x < w)
		{
			img_str[x + y * w] = 0x222222FF;
			x++;
		}
		y++;
	}
}

void	draw_crosshair(int *img_str)
{
	int y = h / 2 - 10;
	int	x = w / 2;
	while (y < h / 2 - 3)
	{
		img_str[x + y * w] = 0xFFFFFFFF;
		y++;
	}
	y = h / 2 + 10;
	while (y > h / 2 + 3)
	{
		img_str[x + y * w] = 0xFFFFFFFF;
		y--;
	}
	y = h / 2;
	x = w / 2 - 10;
	while (x < w / 2 - 3)
	{
		img_str[x + y * w] = 0xFFFFFFFF;
		x++;
	}
	x = w / 2 + 10;
	while (x > w / 2 + 3)
	{
		img_str[x + y * w] = 0xFFFFFFFF;
		x--;
	}
}

unsigned int	get_color(int worldMap[24][24], int mapX, int mapY, int lineHeight)
{
	unsigned int	color;

	//lineHeight = lineHeight * 255 / h;
	lineHeight = clamp(lineHeight, 0, 255);
	//ft_printf("lineHeight = %d\n", lineHeight);
	if (worldMap[mapX][mapY] == 1)
		//color = 16777216 * lineHeight + 255;
		color = lineHeight << 24 | lineHeight << 16 | lineHeight << 8 | 0xFF;
		//color = lineHeight << 24 | 0 << 16 | 0 << 8 | 0xFF;
	if (worldMap[mapX][mapY] == 2)
		color = lineHeight << 16 | 0 << 8 | 0xFF;
		//color = 0xFF00FF;
	if (worldMap[mapX][mapY] == 3)
		color = lineHeight << 8 | 0xFF;
		//color = 0xFFFF;
	if (worldMap[mapX][mapY] == 4)
		color = lineHeight << 24 | lineHeight << 16 | 0 << 8 | 0xFF;
		//color = 0xFFFF00FF;
	if (worldMap[mapX][mapY] == 5)
		color = lineHeight << 24 | lineHeight << 16 | lineHeight << 8 | 0xFF;
		//color = 0xFFFFFFFF;
	//ft_printf("color = %X\n", color);
	return (color);
}

int		raytracing(SDL_Surface *surface, SDL_Texture *texture, SDL_Renderer *renderer, SDL_Window *window, int *img_str, double *planeX, double *planeY, double *dirX, double *dirY, double *posX, double *posY)
{
	int x = 0;
	clear_img(img_str);
	unsigned int currentColor = 0xFF;
	while (x < w)
	{
		double cameraX = 2 * x / (double)w - 1;
		double rayDirX = *dirX + *planeX * cameraX;
		double rayDirY = *dirY + *planeY * cameraX;
		int mapX = *posX;
		int mapY = *posY;

		double sideDistX;
		double sideDistY;

		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (*posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - *posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (*posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - *posY) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		} 
		if (side == 0)
			perpWallDist = (mapX - *posX + (1 - stepX) / 2) / rayDirX;
		else          
			perpWallDist = (mapY - *posY + (1 - stepY) / 2) / rayDirY;
		int lineHeight = (int)(h / perpWallDist);
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)
			drawEnd = h - 1;
		unsigned int color = get_color(worldMap, mapX, mapY, lineHeight);
		int i = drawStart - 1;
		while (++i < drawEnd)
		{
			//if (color == currentColor)
				img_str[x + i * w] = color;
			/*else
				img_str[x + i * w] = 0xFF;*/
		}
		img_str[x + drawStart * w] = 0xFF;
		img_str[x + drawEnd * w] = 0xFF;
		currentColor = color;
		x++;
	}
	draw_crosshair(img_str);
	if (!(texture = SDL_CreateTextureFromSurface(renderer, surface)))
	{
		ft_printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
		return (quit(window, renderer, surface, texture));
	}
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	return (0);
}

int		main(void)
{
	int				running;
	SDL_Window		*window;
	SDL_Event		event;
	SDL_Renderer	*renderer;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	int				*img_str;
	double			posX = 22;
	double			posY = 12;
	double dirX = -1, dirY = 0;
	double planeX = 0, planeY = 0.66;
	int		redraw = 0;
	/*double time = 0;
	  double oldTime = 0;*/

	window = NULL;
	renderer = NULL;
	surface = NULL;
	texture = NULL;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (ft_printf("SDL_Init Error: %s\n", SDL_GetError()));
	running = 1;
	if (!(window = SDL_CreateWindow(
					"Ma fenêtre",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					w,
					h,
					SDL_WINDOW_MOUSE_FOCUS)))
	{
		ft_printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		return (quit(window, renderer, surface, texture));
	}
	if (!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE)))
	{
		ft_printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return (quit(window, renderer, surface, texture));
	}
	if (!(surface = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA8888)))
		//if (!(surface = SDL_CreateRGBSurface(0, 800, 600, 32, 0, 0, 0, 0)))
	{
		ft_printf("SDL_CreateRGBSurface Error: %s\n", SDL_GetError());
		return (quit(window, renderer, surface, texture));
	}
	img_str = surface->pixels;
	clear_img(img_str);
	if (!(texture = SDL_CreateTextureFromSurface(renderer, surface)))
	{
		ft_printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
		return (quit(window, renderer, surface, texture));
	}
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	double moveSpeed = 0.15;
	double rotSpeed = 0.001;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			SDL_CaptureMouse(SDL_TRUE);
			if (event.type == SDL_QUIT
					|| (event.type == SDL_KEYUP
						&& event.key.keysym.sym == SDLK_ESCAPE))
				running = 0;
			else
			{
				if (event.type == SDL_MOUSEMOTION)
				{
					double diff = -(event.motion.xrel) * rotSpeed;
					double oldDirX = dirX;
					dirX = (dirX * cos(diff) - dirY * sin(diff));
					dirY = (oldDirX * sin(diff) + dirY * cos(diff));
					double oldPlaneX = planeX;
					planeX = (planeX * cos(diff) - planeY * sin(diff));
					planeY = (oldPlaneX * sin(diff) + planeY * cos(diff));
				}
				else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP))
				{
					if (worldMap[(int)(posX + dirX * moveSpeed)][(int)posY] == 0)
						posX += dirX * moveSpeed;
					if (worldMap[(int)posX][(int)(posY + dirY * moveSpeed)] == 0)
						posY += dirY * moveSpeed;
				}
				else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN))
				{
					if (worldMap[(int)(posX - dirX * moveSpeed)][(int)posY] == 0)
						posX -= dirX * moveSpeed;
					if (worldMap[(int)posX][(int)(posY - dirY * moveSpeed)] == 0)
						posY -= dirY * moveSpeed;
				}
				/*else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a)
				{
					if (worldMap[(int)(posX - dirX * moveSpeed)][(int)posY] == 0)
						posX -= dirX * moveSpeed;
					if (worldMap[(int)posX][(int)(posY - dirY * moveSpeed)] == 0)
						posY -= dirY * moveSpeed;
				}*/
				redraw = 1;
			}
		}
		if (redraw)
		{
			if (raytracing(surface, texture, renderer, window, img_str, &planeX, &planeY, &dirX, &dirY, &posX, &posY) != 0)
				return (1);
			redraw = 0;
		}
	}
	quit(window, renderer, surface, texture);
	return (0);
}
