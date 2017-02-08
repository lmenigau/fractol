/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 15:55:29 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/08 19:40:40 by lmenigau         ###   ########.fr       */
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

typedef struct	s_state
{
	void	*mlx_ptr;
	void	*window;
	int		(*buff)[WIN_WIDTH];
	t_cplex		c;
}				t_state;

#endif
