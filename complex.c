/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 09:00:08 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/15 11:21:26 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_cplex	add(t_cplex a, t_cplex b)
{
	return ((t_cplex){a.real + b.real, a.im + b.im});
}

t_cplex	sub(t_cplex a, t_cplex b)
{
	return ((t_cplex){a.real - b.real, a.im - b.im});
}

t_cplex	mult(t_cplex a, t_cplex b)
{
	return ((t_cplex){a.real * b.real - a.im * b.im,
			a.im * b.real + a.real * b.im});
}

t_cplex	power(t_cplex a, int b)
{
	t_cplex res;

	res = a;
	while (--b > 0)
	{
		res = (t_cplex){a.real * res.real - a.im * res.im,
			a.im * res.real + a.real * res.im};
	}
	return (res);
}
