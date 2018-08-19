/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 15:08:14 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/07/19 15:08:15 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft/libft.h"
# include "libft/ft_printf.h"
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>

bool g_rev;
bool g_quiet;
bool g_stdin;
bool g_str;
int g_count;
bool g_flag;
bool g_print;
int g_hash;

typedef struct		s_hash
{
	void (*func)(unsigned char*);
	char *name;
	char *out_str;
}					t_hash;

typedef struct		s_md5
{
	unsigned int	a_base;
	unsigned int	b_base;
	unsigned int	c_base;
	unsigned int	d_base;
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;
	unsigned int	x;
	unsigned int	y;
	unsigned int	out_len;
	long long		len;
	unsigned int	f;
	unsigned int	g;
	unsigned char	*out;
	unsigned int	m[16];
}					t_md5;

typedef struct		s_sha256
{
	unsigned int	a_base;
	unsigned int	b_base;
	unsigned int	c_base;
	unsigned int	d_base;
	unsigned int	e_base;
	unsigned int	f_base;
	unsigned int	g_base;
	unsigned int	h_base;
	unsigned int	i;
	long long		len;
	unsigned int	out_len;
	unsigned char	*out;
	unsigned int	x;
	unsigned int	s0;
	unsigned int	s1;
	unsigned int	ch;
	unsigned int	maj;
	unsigned int	tmp1;
	unsigned int	tmp2;
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;
	unsigned int	e;
	unsigned int	f;
	unsigned int	g;
	unsigned int	h;
	unsigned int	j;
}					t_sha256;

void				md5(unsigned char *input);
char				*read_stdin(void);
void				sha256(unsigned char *input);
void				run_hash(char *str);
bool				flag_check(char *str);
char				*ld_stradd(char *a, char *b);
int					reverse(int i);
int					find_output_len(unsigned char *input);

static t_hash g_dispatch[] =
{
	{md5, "md5", "MD5"},
	{sha256, "sha256", "SHA256"},
	{NULL, NULL, NULL}
};

#endif
