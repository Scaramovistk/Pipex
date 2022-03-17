/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <gscarama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:10:42 by gscarama          #+#    #+#             */
/*   Updated: 2022/03/17 13:34:33 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			row;
	unsigned char	*ps1;
	unsigned char	*ps2;

	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	row = 0;
	while ((ps1[row] != '\0' || ps2[row] != '\0') && row < n)
	{
		if (ps1[row] != ps2[row])
			return (ps1[row] - ps2[row]);
		row++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t		size;

	size = 0;
	while (str[size] != '\0')
		size++;
	return (size);
}

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

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len;
	char	*nstr;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	nstr = malloc(sizeof(char) * len);
	if (!nstr)
		return (NULL);
	nstr[0] = '\0';
	ft_strlcat(nstr, s1, len);
	ft_strlcat(nstr, s2, len);
	free(s1);
	return (nstr);
}

void	ft_error(int id, char *str)
{
	if (id == -1)
	{
		id = 0;
		while (str[id])
		{
			write(1, &str[id], 1);
			id++;
		}
		write(1, " Failed", 6);
		exit (0);
	}
}
