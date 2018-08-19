/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 15:21:18 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/07/19 15:21:19 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		reverse(int i)
{
	int new;

	new = 0;
	new += i << 24 & 0xff000000;
	new += i << 8 & 0xff0000;
	new += i >> 8 & 0xff00;
	new += i >> 24 & 0xff;
	return (new);
}

char	*ld_stradd(char *a, char *b)
{
	char	*new;
	size_t	i;

	i = 0;
	new = ft_strnew(ft_strlen(a) + ft_strlen(b));
	while (i < ft_strlen(a) + ft_strlen(b))
	{
		if (i < ft_strlen(a))
		{
			new[i] = a[i];
		}
		else
		{
			new[i] = b[i - ft_strlen(a)];
		}
		i++;
	}
	free(a);
	free(b);
	return (new);
}

bool	flag_check(char *str)
{
	if (g_flag && ft_strcmp(str, "-r") == 0)
	{
		g_rev = true;
		g_count++;
		return (true);
	}
	if (g_flag && ft_strcmp(str, "-p") == 0)
	{
		g_stdin = true;
		g_count++;
		return (true);
	}
	if (g_flag && ft_strcmp(str, "-q") == 0)
	{
		g_quiet = true;
		g_count++;
		return (true);
	}
	if (g_flag && ft_strcmp(str, "-s") == 0)
	{
		g_str = true;
		g_count++;
		return (true);
	}
	return (false);
}

int		find_output_len(unsigned char *input)
{
	int len;
	int new_len;

	len = ft_strlen((char *)input);
	new_len = ((len + 8) / 64) * 64 + 64;
	return (new_len);
}
