/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 20:13:42 by gscarama          #+#    #+#             */
/*   Updated: 2022/01/20 08:29:45 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	lendst;
	size_t	lensrc;
	size_t	rest;

	i = 0;
	rest = size;
	while (dst[i] && rest > 0)
	{
		rest--;
		i++;
	}
	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	if (rest == 0)
		return (lensrc + size);
	i = 0;
	while (rest > 1 && src[i] != '\0')
	{
		dst[(lendst + i)] = src[i];
		rest--;
		i++;
	}
	dst[(lendst + i)] = '\0';
	return (lendst + lensrc);
}
