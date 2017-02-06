/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:22:28 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/06 19:16:41 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
# define WIN_WIDTH		1300
# define WIN_HEIGHT		1300

#include <math.h>

# define ABS(x)		((x) < 0 ? (-(x)): (x))
typedef struct	s_cplex
{
	double	real;
	double	im;
}				t_cplex;

void	mandlebrot(void *mlx_ptr, void *win)
{
	void	*img;
	int		bits;
	int		size;
	int		endian;
	int		(*buff)[WIN_WIDTH];
	int		it;
	double	step;
	double	swap;
	t_cplex	c;
	t_cplex	z;
	img = mlx_new_image(mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	buff = (int (*)[WIN_WIDTH])mlx_get_data_addr(img, &bits, &size, &endian);

	step = 4 / (double)WIN_HEIGHT;
	c.im = -2;
	while (c.im < 2)
	{
		c.real = -2;
		while (c.real < 2)
		{
			it = 0;
			z = (t_cplex){0, 0};
			while (z.real * z.real + z.im * z.im < 4 && it < 10)
			{
				swap = z.real * z.real - z.im * z.im + c.real;
				z.im = z.real * z.im + z.im * z.real + c.im;
				z.real = swap;
				it++;
			}
			if (it != 10)
				buff[(int)(c.im / step) + WIN_HEIGHT/ 2][(int)(c.real / step) + (WIN_HEIGHT/2)] = 0x00FFFFFF / 10 * it;
			c.real += step;
		}
		c.im += step;
	}
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
	mandlebrot(mlx_ptr, window);
	mlx_loop(mlx_ptr);
	return (0);
}
