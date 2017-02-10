/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:22:28 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/10 20:22:21 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <unistd.h>

void	mandlebrot(t_state *state, double zoom, double step, int iter)
{
	double	swap;
	t_cplex	c;
	t_cplex	z;
	int		it;

	c.im = state->center.im - zoom - step;
	while ((c.im += step) < state->center.im + zoom)
	{
		c.real = state->center.real - zoom;
		while (c.real < state->center.real + zoom)
		{
			it = -1;
			z = (t_cplex){0, 0};
			while (z.real * z.real + z.im * z.im < 4 && ++it < iter)
			{
				swap = z.real * z.real - z.im * z.im + c.real;
				z.im = z.real * z.im + z.im * z.real + c.im;
				z.real = swap;
			}
			if (iter != it)
				state->buff[WIN((c.im - state->center.im) / step)]
					[WIN((c.real - state->center.real) / step)] = COL;
			c.real += step;
		}
	}
}

void	julia(t_state *state, double zoom, double step, int iter)
{
	double	swap;
	t_cplex	z;
	t_cplex	s;
	int		it;

	z.im = state->center.im - zoom;
	while ((z.im += step) < state->center.im + zoom)
	{
		z.real = state->center.real - zoom;
		while (z.real < state->center.real + zoom)
		{
			it = -1;
			s = z;
			while (s.real * s.real + s.im * s.im < 4 && ++it < iter)
			{
				swap = s.real * s.real - s.im * s.im + state->c.real;
				s.im = s.real * s.im + s.im * s.real + state->c.im;
				s.real = swap;
			}
			if (iter != it)
				state->buff[WIN((z.im - state->center.im) / step)]
				[WIN((z.real - state->center.real) / step)] = COL;
			z.real += step;
		}
	}
}

void	burning_sheep(t_state *state, double zoom, double step, int iter)
{
	double	swap;
	t_cplex	c;
	t_cplex	z;
	int		it;

	c.im = state->center.im - zoom;
	while ((c.im += step) < state->center.im + zoom)
	{
		c.real = state->center.real - zoom;
		while (c.real < state->center.real + zoom)
		{
			it = -1;
			z = (t_cplex){0, 0};
			while (z.real * z.real + z.im * z.im < 4 && ++it < iter)
			{
				swap = ABS(z.real * z.real) - ABS(z.im * z.im) + c.real;
				z.im = ABS(z.real * z.im)+ ABS(z.im * z.real) + c.im;
				z.real = swap;
			}
			if (iter != it)
				state->buff[WIN((c.im - state->center.im) / step)]
				[WIN((c.real - state->center.real) / step)] = COL;
			c.real += step;
		}
	}
}

void	render(t_state *state)
{
	void	*img;
	int		bits;
	int		size;
	int		endian;
	double	step;

	img = mlx_new_image(state->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	state->buff = (int (*)[WIN_WIDTH])mlx_get_data_addr(img, &bits, &size,
			&endian);
	step = 2 * state->zoom / (double)WIN_HEIGHT;
	if (state->fractol == Mandlebrot)
		mandlebrot(state, state->zoom, step, state->iter);
	else if (state->fractol == Julia)
		julia(state, state->zoom, step, state->iter);
	else
		burning_sheep(state, state->zoom, step, state->iter);
	mlx_put_image_to_window(state->mlx_ptr, state->window, img, 0, 0);
	mlx_destroy_image(state->mlx_ptr, img);
	state->buff = NULL;
}

int		main(int argc, char **argv)
{
	t_state	state;

	state.mlx_ptr = mlx_init();
	state.window = mlx_new_window(state.mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"fractol");
	state.zoom = 2;
	state.topleft = (t_cplex) {-state.zoom , -state.zoom};
	state.botright = (t_cplex) {state.zoom, state.zoom};
	state.center = (t_cplex) {0, 0};
	state.fractol = Mandlebrot;
	state.iter = 75;
	mlx_do_key_autorepeaton(state.mlx_ptr);
	mlx_hook(state.window, 6, 0, motion_hook, &state);
	mlx_hook(state.window, 2, 0, key_hook_repeat, &state);
	mlx_mouse_hook(state.window, mouse_hook, &state);
	mlx_key_hook(state.window, key_hook, &state);
	render(&state);
	mlx_loop(state.mlx_ptr);
	return (0);
}
