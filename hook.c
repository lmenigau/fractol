/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 21:40:53 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/09 16:09:34 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fractol.h"

int	 motion_hook(int x, int y, t_state *state)
{
	state->c.real = (x - WIN_HEIGHT / 2) / (double)WIN_HEIGHT * state->zoom * 2 + state->center.real;
	state->c.im = (y - WIN_HEIGHT / 2) / (double)WIN_HEIGHT * state->zoom * 2 + state->center.im;
	printf("z: %f c : %f, %f\n", state->zoom, state->c.im, state->c.real);
	render(state);
	return (0);
}

int		mouse_hook(int button, int x, int y, t_state *state)
{
	t_cplex a;
	t_cplex z;
	double zoom;

	if (button == 1)
	{
		zoom = 1.5;
	}
	else if (button == 2)
	{
		zoom = 0.5;
	}
	else
		return (0);
	a.real = (x - WIN_HEIGHT / 2) / (double)WIN_HEIGHT * state->zoom * 2 + state->center.real;
	a.im = (y - WIN_HEIGHT / 2) / (double)WIN_HEIGHT * state->zoom * 2 + state->center.im;
	state->zoom *= zoom;
	printf("a : %f, %f\n", a.real, a.im);
	z = state->center;
	z.real = zoom * (z.real - a.real) + a.real;
	z.im  = zoom * (z.im - a.im) + a.im ;
	state->center = z;
	render(state);
	return (0);
}
