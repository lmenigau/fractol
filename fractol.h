/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 15:55:29 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/11 04:39:34 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <mlx.h>
# define WIN_WIDTH		800
# define WIN_HEIGHT		800
# define ABS(x)		((x) < 0 ? (-(x)): (x))
# define WIN(x)		(int)(x + WIN_HEIGHT / 2)
# define WHITE		0x00FFFFFF

# define RGB		(0xFF * it /iter)
# define COL		(RGB) | (RGB * 3 << 8) | (RGB * 7<< 16)

typedef struct	s_cplex
{
	double	real;
	double	im;
}				t_cplex;

typedef struct	s_vec2
{
	int		x;
	int		y;
}				t_vec2;

typedef enum	e_fractol
{
	Mandlebrot,
	Julia,
	Burning_sheep
}				t_fractol;

typedef struct	s_state
{
	double		zoom;
	void		*mlx_ptr;
	void		*window;
	int			(*buff)[WIN_WIDTH];
	t_cplex		c;
	t_cplex		center;
	t_fractol	fractol;
	int			iter;
}				t_state;

int		motion_hook(int x, int y, t_state *state);
int		mouse_hook(int button, int x, int y, t_state *state);
void	render(t_state *state);
int		key_hook(int keycode, t_state *state);
int		key_hook_repeat(int keycode, t_state *state);
#endif
