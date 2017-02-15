/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 06:48:22 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/15 15:48:15 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		cactus(t_state *state, t_cplex c, int iter)
{
	t_cplex	z;
	t_cplex	tmp;
	int		it;
	int		pow;

	pow = state->power;
	it = -1;
	z = (t_cplex){0, 0};
	while (z.real * z.real + z.im * z.im < 4 && ++it < iter)
	{
		tmp = sub(add(power(z, pow), mult(sub(c, (t_cplex){1, 0}), z)), c);
		if (z.real == tmp.real && z.im == tmp.im)
			return (iter);
		z = tmp;
	}
	return (it);
}

int		mandlebrot_pow(t_state *state, t_cplex c, int iter)
{
	t_cplex	z;
	t_cplex	tmp;
	int		it;

	it = -1;
	z = (t_cplex){0, 0};
	while (z.real * z.real + z.im * z.im < 4 && ++it < iter)
	{
		tmp = add(power(z, state->power), c);
		if (z.real == tmp.real && z.im == tmp.im)
			return (iter);
		z = tmp;
	}
	return (it);
}

int		biomorph(t_state *state, t_cplex s, int iter)
{
	t_cplex	c;
	int		it;

	c = state->c;
	it = -1;
	while (++it < iter && (fabs(s.real) < 2 && fabs(s.im) < 2))
	{
		s = add(power(s, state->power), c);
	}
	return (4 / fabs(s.im * s.real) * it);
}

int		mandlebrot(t_state *state, t_cplex c, int iter)
{
	t_cplex	z;
	t_cplex	tmp;
	int		it;

	(void)state;
	it = -1;
	z = (t_cplex){0, 0};
	while (z.real * z.real + z.im * z.im < 4 && ++it < iter)
	{
		tmp.real = z.real * z.real - z.im * z.im + c.real;
		tmp.im = 2 * z.real * z.im + c.im;
		if (z.real == tmp.real && z.im == tmp.im)
			return (iter);
		z = tmp;
	}
	return (it);
}

int		fract0(t_state *state, t_cplex c, int iter)
{
	t_cplex	z;
	t_cplex	tmp;
	int		it;

	(void)state;
	it = -1;
	z = (t_cplex){0, 0};
	while (z.real * z.real + z.im * z.im < 5 && ++it < iter)
	{
		tmp.real = z.real * z.real - z.im * z.im - z.real + c.real;
		tmp.im = 2 * z.real * z.im - z.im + c.im;
		if (z.real == tmp.real && z.im == tmp.im)
			return (iter);
		z = tmp;
	}
	return (it);
}
