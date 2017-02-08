/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 15:55:29 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/08 15:55:54 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <mlx.h>
# define WIN_WIDTH		1300
# define WIN_HEIGHT		1300

# define ABS(x)		((x) < 0 ? (-(x)): (x))

typedef struct	s_cplex
{
	double	real;
	double	im;
}				t_cplex;


#endif
