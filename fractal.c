/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 06:48:22 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/15 11:02:58 by lmenigau         ###   ########.fr       */
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

int		mandlebrot(t_state *state, t_cplex c, int iter)
{
	t_cplex	z;
	t_cplex	tmp;
	int		it;

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

	it = -1;
	z = (t_cplex){0, 0};
	while (z.real * z.real + z.im * z.im < 4 && ++it < iter)
	{
		swap = ABS(z.real * z.real) - ABS(z.im * z.im) + c.real;
		z.im = 2 * ABS(z.im * z.real) + c.im;
		z.real = swap;
	}
	return (it);
}
