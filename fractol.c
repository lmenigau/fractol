/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:22:28 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/08 21:20:21 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

# define ABS(x)		((x) < 0 ? (-(x)): (x))
# define WIN(x)		(int)(x) + WIN_HEIGHT / 2
# define WHITE		0x00FFFFFF

# define RGB		(0xFF * it /iter)
# define COL		(RGB) | (RGB * 2 << 8) | (RGB * 6<< 16)

void	mandlebrot(t_state state, double zoom, double step, int iter)
{
	double	swap;
	t_cplex	c;
	t_cplex	z;
	int		it;

	c.im = - zoom;
	while (c.im < zoom)
	{
		c.real = -zoom;
		while (c.real < zoom)
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
				state.buff[WIN(c.im / step)][WIN(c.real / step)] = COL;
			c.real += step;
		}
		c.im += step;
	}
}

void	julia(t_state state, double zoom, double step, int iter)
{
	double	swap;
	t_cplex	z;
	t_cplex	s;
	int		it;

	z.im = - zoom;
	while (z.im < zoom)
	{
		z.real = -zoom;
		while (z.real < zoom)
		{
			it = -1;
			s = z;
			while (s.real * s.real + s.im * s.im < 4 && ++it < iter)
			{
				swap = s.real * s.real - s.im * s.im + state.c.real;
				s.im = s.real * s.im + s.im * s.real + state.c.im;
				s.real = swap;
			}
			if (iter != it)
				state.buff[WIN(z.im / step)][WIN(z.real / step)] = COL;
			z.real += step;
		}
		z.im += step;
	}
}

void	burning_sheep(t_state state, double zoom, double step, int iter)
{
	double	swap;
	t_cplex	c;
	t_cplex	z;
	int		it;

	c.im = - zoom;
	while (c.im < zoom)
	{
		c.real = -zoom;
		while (c.real < zoom)
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
				state.buff[WIN(c.im / step)][WIN(c.real / step)] = COL;
			c.real += step;
		}
		c.im += step;
	}
}

void	render(t_state state)
{
	void	*img;
	int		bits;
	int		size;
	int		endian;

	img = mlx_new_image(state.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	state.buff = (int (*)[WIN_WIDTH])mlx_get_data_addr(img, &bits, &size, &endian);
//	mandlebrot(state, 1, 1 * 2 / (double)WIN_HEIGHT, 100);
	state.c = (t_cplex){0.3, 0.3};
//	julia(state, 2, 2 * 2 / (double)WIN_HEIGHT, 100);
	burning_sheep(state, 2, 2 * 2 / (double)WIN_HEIGHT, 200);
	mlx_put_image_to_window(state.mlx_ptr, state.window, img, 0, 0);
}

int		main(int argc, char **argv)
{
	t_state	state;

	state.mlx_ptr = mlx_init();
	state.window = mlx_new_window(state.mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"fractol");
	mlx_do_key_autorepeaton(state.mlx_ptr);
	render(state);
	mlx_loop(state.mlx_ptr);
	return (0);
}
