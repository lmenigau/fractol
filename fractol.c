/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:22:28 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/15 17:18:42 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <unistd.h>

void	pixel(t_state *state, t_vec2 start, t_img buff, int iter)
{
	t_cplex	c;
	t_vec2	xy;
	int		it;
	int		col;
	t_cplex	center;

	center = state->center;
	xy.y = -1;
	while (++xy.y < WIN_HEIGHT / 2)
	{
		xy.x = -1;
		while (++xy.x < WIN_HEIGHT / 2)
		{
			c.im = (start.y + xy.y) / (double)WIN_HEIGHT * state->zoom +
				center.im;
			c.real = (start.x + xy.x) / (double)WIN_HEIGHT * state->zoom +
				center.real;
			it = state->func(state, c, iter);
			col = it * 0xFF / iter;
			if (it != iter)
				buff[xy.y][xy.x] = (col) | (col << 10) | (col << 19);
		}
	}
}

void	render(t_argt *argt)
{
	void	*img;
	t_state	*state;
	int		shit[3];
	t_img	buff;

	state = argt->state;
	img = mlx_new_image(state->mlx_ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	buff = (t_img)mlx_get_data_addr(img, &shit[0],
			&shit[1], &shit[2]);
	pixel(state, argt->start, buff, state->iter);
	pthread_mutex_lock(argt->mutex);
	mlx_put_image_to_window(state->mlx_ptr, state->window, img, argt->start.x,
			argt->start.y);
	mlx_destroy_image(state->mlx_ptr, img);
	pthread_mutex_unlock(argt->mutex);
}

void	mt_render(t_state *state)
{
	pthread_t				t[4];
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	t_argt					args[4];

	args[0] = (t_argt){ &mutex, state, {0, 0}};
	args[1] = (t_argt){ &mutex, state, {WIN_HEIGHT / 2, 0}};
	args[2] = (t_argt){ &mutex, state, {0, WIN_HEIGHT / 2}};
	args[3] = (t_argt){ &mutex, state, {WIN_HEIGHT / 2, WIN_HEIGHT / 2}};
	pthread_create(&t[0], NULL, (void *)render, &args[0]);
	pthread_create(&t[1], NULL, (void *)render, &args[1]);
	pthread_create(&t[2], NULL, (void *)render, &args[2]);
	pthread_create(&t[3], NULL, (void *)render, &args[3]);
	pthread_join(t[0], NULL);
	pthread_join(t[1], NULL);
	pthread_join(t[2], NULL);
	pthread_join(t[3], NULL);
}

void	parse_arg(t_state *state, int argc, char **argv)
{
	int		frac;

	if (argc != 2)
	{
		ft_putstr("1) mandlebrot\n2) julia\n3) burning_ship\n4) cactus\n"
				"5) biomorph\n");
		exit(0);
	}
	frac = ft_atoi(argv[1]);
	if (frac == 1)
		state->func = mandlebrot;
	else if (frac == 2)
		state->func = julia;
	else if (frac == 3)
		state->func = burning_ship;
	else if (frac == 4)
		state->func = cactus;
	else if (frac == 5)
		state->func = biomorph;
	else
	{
		ft_putstr("1) mandlebrot\n2) julia\n3) burning_ship\n4) cactus\n"
				"5) biomorph\n");
		exit(0);
	}
}

int		main(int argc, char **argv)
{
	t_state	state;

	parse_arg(&state, argc, argv);
	state.mlx_ptr = mlx_init();
	state.window = mlx_new_window(state.mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"fractol");
	state.zoom = 3;
	state.center = (t_cplex) {-2, -1.5};
	state.iter = 100;
	state.power = 3;
	mlx_do_key_autorepeaton(state.mlx_ptr);
	mlx_hook(state.window, 6, 0, motion_hook, &state);
	mlx_hook(state.window, 2, 0, key_hook_repeat, &state);
	mlx_mouse_hook(state.window, mouse_hook, &state);
	mlx_key_hook(state.window, key_hook, &state);
	mt_render(&state);
	mlx_loop(state.mlx_ptr);
	return (0);
}
