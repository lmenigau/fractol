/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:22:28 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/08 17:12:57 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define WIN(x)		(int)(x) + WIN_HEIGHT / 2
#define WHITE		0x00FFFFFF

void	mandlebrot(int (*buff)[WIN_WIDTH], double zoom, double step, int iter)
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
				buff[WIN(c.im / step)][WIN(c.real / step)] = WHITE / iter * it;
			c.real += step;
		}
		c.im += step;
	}
}

void	julia(int (*buff)[WIN_WIDTH], double zoom, double step, int iter)
{
	double	swap;
	t_cplex	z;
	t_cplex	c;
	t_cplex	s;
	int		it;

	c = (t_cplex){0.5, 0.5};
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
				swap = s.real * s.real - s.im * s.im + c.real;
				s.im = s.real * s.im + s.im * s.real + c.im;
				s.real = swap;
			}
			if (iter != it)
				buff[WIN(z.im / step)][WIN(z.real / step)] = WHITE / iter * it;
			z.real += step;
		}
		z.im += step;
	}
}

void	render(void *mlx_ptr, void *win)
{
	int		(*buff)[WIN_WIDTH];
	void	*img;
	int		bits;
	int		size;
	int		endian;

	img = mlx_new_image(mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	buff = (int (*)[WIN_WIDTH])mlx_get_data_addr(img, &bits, &size, &endian);
//	mandlebrot(buff, 2, 2 * 2 / (double)WIN_HEIGHT, 100);
	julia(buff, 2, 2 * 2 / (double)WIN_HEIGHT, 100);
	mlx_put_image_to_window(mlx_ptr, win, img, 0, 0);
}

int		main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*window;

	mlx_ptr = mlx_init();
	window = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"fractol");
	mlx_do_key_autorepeaton(mlx_ptr);
	render(mlx_ptr, window);
	mlx_loop(mlx_ptr);
	return (0);
}
