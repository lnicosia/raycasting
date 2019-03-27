/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:13:15 by lnicosia          #+#    #+#             */
/*   Updated: 2019/03/27 15:29:12 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int		quit(SDL_Window *window, SDL_Renderer *renderer)
{
	if (window)
		SDL_DestroyWindow(window);
	if (renderer)
		SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return (1);
}

int		main(int ac, char **av)
{
	int				running;
	SDL_Window		*window;
	SDL_Event		event;
	SDL_Renderer	*renderer;

	(void)ac;
	(void)av;
	window = NULL;
	renderer = NULL;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (ft_printf("SDL_Init Error: %s\n", SDL_GetError()));
	running = 1;
	if (!(window = SDL_CreateWindow(
					"Ma fenetre",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					800,
					600,
					SDL_WINDOW_RESIZABLE)))
	{
		ft_printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		return (quit(window, renderer));
	}
	if (!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE)))
	{
		ft_printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return (quit(window, renderer));
	}
	while (running)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT
				|| (event.type == SDL_KEYUP
					&& event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			running = 0;
	}
	quit(window, renderer);
	return (0);
}
