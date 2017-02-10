/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 21:40:53 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/10 20:44:59 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fractol.h"

int		 motion_hook(int x, int y, t_state *state)
{
	state->c.real = (x - WIN_HEIGHT / 2) / (double)WIN_HEIGHT * state->zoom * 2
		+ state->center.real;
	state->c.im = (y - WIN_HEIGHT / 2) / (double)WIN_HEIGHT * state->zoom * 2 +
		state->center.im;
	render(state);
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
		state->iter += 10;
	else if (keycode == 40)
		state->iter -= 10;
	render(state);
	return(0);
}

int		key_hook(int keycode, t_state *state)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 83)
		state->fractol = Mandlebrot;
	else if (keycode == 84)
		state->fractol = Julia;
	else if (keycode == 85)
		state->fractol = Burning_sheep;
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
		zoom = 2.00;
		state->iter -= 5;
	}
	else if (button == 2)
	{
		zoom = 0.50;
		state->iter += 5;
	}
	else
		return (0);
	a.real = (x - WIN_HEIGHT / (double)2) / (double)WIN_HEIGHT * state->zoom *
		2 + state->center.real;
	a.im = (y - WIN_HEIGHT / (double)2) / (double)WIN_HEIGHT * state->zoom * 2
		+ state->center.im;
	state->zoom *= zoom;
	z = state->center;
	z.real = zoom * (z.real - a.real) + a.real;
	z.im  = zoom * (z.im - a.im) + a.im ;
	state->center = z;
	render(state);
	return (0);
}
