/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:22:28 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/08 16:19:35 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define WIN(x)		(int)(x) + WIN_HEIGHT / 2
#define WHITE		0x00FFFFFF

void	mandlebrot(int		(*buff)[WIN_WIDTH], double zoom, int iter)
{
	double	step;
	double	swap;
	t_cplex	c;
	t_cplex	z;
	int		it;

	step = zoom * 2 / (double)WIN_HEIGHT;
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

void	render(void *mlx_ptr, void *win)
{
	int		(*buff)[WIN_WIDTH];
	void	*img;
	int		bits;
	int		size;
	int		endian;

	img = mlx_new_image(mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	buff = (int (*)[WIN_WIDTH])mlx_get_data_addr(img, &bits, &size, &endian);
	mandlebrot(buff, 2, 100);
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
