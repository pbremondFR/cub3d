/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:39:54 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/27 21:27:40 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

// Returns distance between two points
float	c_math_get_dist(float x1, float x2, float y1, float y2)
{
	return (sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2)));
}

// Returns squared distance between two points
float	c_math_get_sq_dist(float x1, float x2, float y1, float y2)
{
	return (powf(x2 - x1, 2) + powf(y2 - y1, 2));
}

// int Fast_Distance_2D(int x, int y) {
// 	// this function computes the distance from 0,0 to x,y with 3.5% error

// 	// first compute the absolute value of x,y  
// 	x = abs(x);
// 	y = abs(y);

// 	// compute the minimum of x,y
// 	int mn = min(x,y);  

// 	// return the distance
// 	// fyi: pow(2,4) is the same as 2^4
// 	return ( x + y -
// 		( mn / pow(2, 1) ) - ( mn / pow(2, 2) ) + ( mn / pow(2, 4) ) );
// }

void	c_math_rotate_vector(float *x, float *y, float angle)
{
	float	new_x;
	float	new_y;

	new_x = *x * cosf(angle) - *y * sinf(angle);
	new_y = *x * sinf(angle) + *y * cosf(angle);
	*x = new_x;
	*y = new_y;
}

int	c_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
