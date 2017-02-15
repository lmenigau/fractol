/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 21:40:53 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/15 06:10:48 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		motion_hook(int x, int y, t_state *state)
{
	state->c.real = x / (double)WIN_HEIGHT * state->zoom + state->center.real;
	state->c.im = y / (double)WIN_HEIGHT * state->zoom + state->center.im;
	if (state->func == julia)
		mt_render(state);
	return (0);
}

int		key_hook_repeat(int keycode, t_state *state)
{
	if (keycode == 123)
		state->center.real -= state->zoom / 4;
	else if (keycode == 124)
		state->center.real += state->zoom / 4;
	else if (keycode == 125)
		state->center.im += state->zoom / 4;
	else if (keycode == 126)
		state->center.im -= state->zoom / 4;
	else if (keycode == 38)
		state->iter += log2(state->iter);
	else if (keycode == 40 && state->iter > 4)
		state->iter -= log2(state->iter);
	else
		return (0);
	mt_render(state);
	return (0);
}

int		key_hook(int keycode, t_state *state)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 83)
		state->func = mandlebrot;
	else if (keycode == 84)
		state->func = julia;
	else if (keycode == 85)
		state->func = burning_ship;
	else if (keycode == 49)
	{
		state->zoom = 3;
		state->center = (t_cplex) {-2, -1.5};
		state->iter = 100;
	}
	else
		return (0);
	mt_render(state);
	return (0);
}

int		mouse_hook(int button, int x, int y, t_state *state)
{
	t_cplex		a;
	t_cplex		z;
	double		zoom;

	if ((button == 1 || button == 4) && state->iter > 4)
	{
		zoom = 2.00;
		state->iter -= log2(state->iter);
	}
	else if (button == 2 || button == 5)
	{
		zoom = 0.50;
		state->iter += log2(state->iter);
	}
	else
		return (0);
	a.real = (x) / (double)WIN_HEIGHT * state->zoom + state->center.real;
	a.im = (y) / (double)WIN_HEIGHT * state->zoom + state->center.im;
	state->zoom *= zoom;
	z = state->center;
	z.real = zoom * (z.real - a.real) + a.real;
	z.im = zoom * (z.im - a.im) + a.im;
	state->center = z;
	mt_render(state);
	return (0);
}
