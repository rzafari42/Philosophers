/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:45:55 by rzafari           #+#    #+#             */
/*   Updated: 2021/03/31 12:55:38 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

char		*ft_inttochar(int n)
{
	int		l;
	int		mem;
	char	*s;

	l = 0;
	mem = n;
	while (n != 0)
	{
		n = n / 10;
		l++;
	}
	if (!(s = (char *)malloc(sizeof(char *) * (l + 1))))
	{
		printf("Malloc in ft_inttochar failed, sorry\n");
		return (NULL);
	}
	if (mem == 0)
		return ("0");
	s[l--] = '\0';
	while (mem != 0)
	{
		s[l--] = '0' + (mem % 10);
		mem = mem / 10;
	}
	return (s);
}

size_t		ft_strlen(const char *s)
{
	unsigned int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char		*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	calc;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	calc = ft_strlen(s1) + ft_strlen(s2);
	if (!(res = (char *)malloc(sizeof(char) * (calc + 1))))
		return (NULL);
	while (*s1)
	{
		res[i] = *(s1++);
		i++;
	}
	while (*s2)
	{
		res[i] = *(s2++);
		i++;
	}
	res[i] = '\0';
	return (res);
}

size_t		ft_strcpy(char *dst, const char *src)
{
	size_t i;
	size_t j;

	i = ft_strlen(src);
	j = 0;
	while (j < i)
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (0);
}
