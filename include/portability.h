/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portability.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:37:10 by pbremond          #+#    #+#             */
/*   Updated: 2022/03/12 14:39:31 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*\ ----------------- Typedefs for portability over Linux ----------------- \*/
# ifdef __linux__

#  define intmax_t		__intmax_t
#  define uintmax_t		__uintmax_t

#  ifndef INTMAX_MAX
#   define INTMAX_MAX	__INTMAX_MAX__
#  endif
#  ifndef UINTMAX_MAX
#   define UINTMAX_MAX	__UINTMAX_MAX__
#  endif

# endif
/* ------------------------------------------------------------------------- */
