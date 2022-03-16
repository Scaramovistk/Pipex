/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <gscarama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:10:42 by gscarama          #+#    #+#             */
/*   Updated: 2022/03/16 15:01:26 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

size_t	ft_freesplit(char **strsplit, int i)
{
	if (!strsplit[i])
	{
		while (i >= 0)
		{
			free(strsplit[i]);
			i--;
		}
		free(strsplit);
		return (1);
	}
	return (0);
}

static size_t	ft_findsize(const char *s, char c)
{
	size_t	size;
	size_t	row;

	size = 0;
	row = 0;
	while (s[row])
	{
		if (s[row] != c)
		{
			while (s[row] != c && s[row + 1])
				row++;
			size++;
		}
		row++;
	}
	return (size);
}

char	*ft_strndup(char const *src, size_t size)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * size + 1);
	if (dest == NULL)
		return (NULL);
	while (src[i] && i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	ft_wrtmtx(char **strsplit, char const *s, char c, size_t i)
{
	size_t	row;
	size_t	size;
	size_t	tmp;

	row = 0;
	while (s[row])
	{
		if (s[row] != c)
		{
			size = row;
			while (s[size] != c && s[size + 1])
				size++;
			tmp = size - row;
			if (s[size + 1] == '\0' && s[size] != c)
				tmp++;
			strsplit[i] = ft_strndup(&s[row], tmp);
			row = ft_freesplit(strsplit, i);
			if (row == 1)
				return ;
			row = size;
			i++;
		}
		row++;
	}
	strsplit[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	size_t		row;
	size_t		i;
	char		**strsplit;

	if (!s)
		return (NULL);
	row = ft_findsize(s, c);
	strsplit = malloc(sizeof(char **) * (row + 1));
	if (!strsplit)
		return (NULL);
	i = 0;
	ft_wrtmtx(strsplit, s, c, i);
	return (strsplit);
}

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
