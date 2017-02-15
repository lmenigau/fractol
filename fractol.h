/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 15:55:29 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/15 06:15:41 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <pthread.h>
# include <math.h>
# include <mlx.h>
# define WIN_WIDTH		1000
# define WIN_HEIGHT		1000
# define ABS(x)			((x) < 0 ? (-(x)): (x))

typedef struct	s_cplex
{
	double		real;
	double		im;
}				t_cplex;

typedef struct	s_vec2
{
	int			x;
	int			y;
}				t_vec2;

typedef struct	s_quad
{
	t_vec2		start;
	t_vec2		end;
}				t_quad;


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
	int			(*func)();
	int			iter;
}				t_state;

typedef	struct	s_argt
{
	pthread_mutex_t *mutex;
	t_state		*state;
	t_vec2		start;
}				t_argt;


int				motion_hook(int x, int y, t_state *state);
int				mouse_hook(int button, int x, int y, t_state *state);
void			render(t_argt *argt);
int				key_hook(int keycode, t_state *state);
int				key_hook_repeat(int keycode, t_state *state);
void			mt_render(t_state *state);
int				mandlebrot(t_state *state, t_cplex c, int iter);
int				julia(t_state *state, t_cplex c, int iter);
int				burning_ship(t_state *state, t_cplex c, int iter);
#endif
