/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:22:28 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/15 06:21:32 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <unistd.h>


# define RGB		(0xFF * it / iter)
# define COL
void	pixel(t_state *state, t_vec2 start, int (*buff)[WIN_WIDTH/2], int iter)
{
	t_cplex	c;
	t_vec2	xy;
	int		it;
	int		col;

	xy.y = -1;
	while (++xy.y < WIN_HEIGHT /2)
	{
		xy.x = -1;
		while (++xy.x < WIN_HEIGHT /2)
		{
			c.im = (start.y + xy.y) / (double)WIN_HEIGHT * state->zoom + state->center.im;
			c.real = (start.x + xy.x) / (double)WIN_HEIGHT * state->zoom + state->center.real;
			it = state->func(state, c, iter);
			col = 0xFF * it / iter;
			if (it != iter)
				buff[xy.y][xy.x] = (col) | (col << 10) | (col << 17);
		}
	}
}

int	 mandlebrot(t_state *state, t_cplex c, int iter)
{
	double	swap;
	t_cplex	z;
	int		it;

	it = -1;
	z = (t_cplex){0, 0};
	while (z.real * z.real + z.im * z.im < 4 && ++it < iter)
	{
		swap = z.real * z.real - z.im * z.im + c.real;
		z.im = z.real * z.im + z.im * z.real + c.im;
		z.real = swap;
	}
	return (it);
}

int	julia(t_state *state, t_cplex s, int iter)
{
	double	swap;
	t_cplex	c;
	int		it;

	c = state->c;
	it = -1;
	while (++it < iter && s.real * s.real + s.im * s.im < 4)
	{
		swap = s.real * s.real - s.im * s.im + c.real;
		s.im = s.real * s.im + s.im * s.real + c.im;
		s.real = swap;
	}
	return (it);
}

int	 burning_ship(t_state *state, t_cplex c, int iter)
{
	double	swap;
	t_cplex	z;
	int		it;

	it = -1;
	z = (t_cplex){0, 0};
	while (z.real * z.real + z.im * z.im < 4 && ++it < iter)
	{
		swap = ABS(z.real * z.real) - ABS(z.im * z.im) + c.real;
		z.im = ABS(z.real * z.im) + ABS(z.im * z.real) + c.im;
		z.real = swap;
	}
	return (it);
}

void	render(t_argt *argt)
{
	void	*img;
	t_state	*state;
	int		shit[3];
	int		(*buff)[WIN_WIDTH/2];

	state = argt->state;
	img = mlx_new_image(state->mlx_ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	buff = (int (*)[WIN_WIDTH/2])mlx_get_data_addr(img, &shit[0],
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
	pthread_t	*t;
	static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	t_argt		*args;

	t = malloc(sizeof(pthread_t) * 4);
	args = malloc(sizeof(t_argt) * 4);
	args[0] = (t_argt){ &mutex, state, {0, 0}};
	args[1] = (t_argt){ &mutex, state, {WIN_HEIGHT/2, 0}};
	args[2] = (t_argt){ &mutex, state, {0, WIN_HEIGHT/2}};
	args[3] = (t_argt){ &mutex, state, {WIN_HEIGHT/2, WIN_HEIGHT/2}};
	pthread_create(&t[0], NULL, (void *)render, &args[0]);
	pthread_create(&t[1], NULL, (void *)render, &args[1]);
	pthread_create(&t[2], NULL, (void *)render, &args[2]);
	pthread_create(&t[3], NULL, (void *)render, &args[3]);
	pthread_join(t[0], NULL);
	pthread_join(t[1], NULL);
	pthread_join(t[2], NULL);
	pthread_join(t[3], NULL);
}

int		main(void)
{
	t_state	state;

	state.mlx_ptr = mlx_init();
	state.window = mlx_new_window(state.mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"fractol");
	state.zoom = 3;
	state.center = (t_cplex) {-2, -1.5};
	state.fractol = Mandlebrot;
	state.func = mandlebrot;
	state.iter = 100;
	mlx_do_key_autorepeaton(state.mlx_ptr);
	mlx_hook(state.window, 6, 0, motion_hook, &state);
	mlx_hook(state.window, 2, 0, key_hook_repeat, &state);
	mlx_mouse_hook(state.window, mouse_hook, &state);
	mlx_key_hook(state.window, key_hook, &state);
	mt_render(&state);
	mlx_loop(state.mlx_ptr);
	return (0);
}
