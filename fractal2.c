/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 15:29:56 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/15 15:30:09 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		julia(t_state *state, t_cplex s, int iter)
{
	t_cplex	c;
	t_cplex	tmp;
	int		it;

	c = state->c;
	it = -1;
	while (++it < iter && s.real * s.real + s.im * s.im < 4)
	{
		tmp.real = s.real * s.real - s.im * s.im + c.real;
		tmp.im = 2 * s.im * s.real + c.im;
		if (s.real == tmp.real && s.im == tmp.im)
			return (iter);
		s = tmp;
	}
	return (it);
}

int		burning_ship(t_state *state, t_cplex c, int iter)
{
	double	swap;
	t_cplex	z;
	int		it;

	(void)state;
	it = -1;
	z = (t_cplex){0, 0};
	while (z.real * z.real + z.im * z.im < 4 && ++it < iter)
	{
		swap = fabs(z.real * z.real) - fabs(z.im * z.im) + c.real;
		z.im = 2 * fabs(z.im * z.real) + c.im;
		z.real = swap;
	}
	return (it);
}
