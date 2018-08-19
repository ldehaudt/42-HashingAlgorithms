/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 15:21:41 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/07/19 15:21:43 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int g_k[64];
unsigned int g_s[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7,
	12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

void	md5_init(unsigned char *input, t_md5 *t, int i)
{
	t->a_base = 0x67452301;
	t->b_base = 0xefcdab89;
	t->c_base = 0x98badcfe;
	t->d_base = 0x10325476;
	while (i < 64)
	{
		g_k[i] = pow(2, 32) * fabs(sin(i + 1));
		i++;
	}
	t->out_len = find_output_len(input);
	t->out = (unsigned char *)ft_strnew(t->out_len);
	ft_strcpy((char *)t->out, (char *)input);
	t->len = ft_strlen((char *)input) * 8;
	t->out[ft_strlen((char *)input)] = 1 << 7;
	i = 0;
	while (i < 8)
	{
		t->out[t->out_len - 8 + i] = ((char *)&(t->len))[i];
		i++;
	}
}

void	md5_set_m(t_md5 *t, int i)
{
	t->x = 0;
	while (t->x < 16)
	{
		t->m[t->x] = 0;
		t->m[t->x] += t->out[i * 64 + t->x * 4 + 0];
		t->m[t->x] += t->out[i * 64 + t->x * 4 + 1] << 8;
		t->m[t->x] += t->out[i * 64 + t->x * 4 + 2] << 16;
		t->m[t->x] += t->out[i * 64 + t->x * 4 + 3] << 24;
		t->x++;
	}
	t->a = t->a_base;
	t->b = t->b_base;
	t->c = t->c_base;
	t->d = t->d_base;
}

void	md5_main_loop(t_md5 *t, int j)
{
	if (j < 16)
	{
		t->f = (t->b & t->c) | ((~t->b) & t->d);
		t->g = j;
	}
	else if (j < 32)
	{
		t->f = (t->d & t->b) | ((~t->d) & t->c);
		t->g = (5 * j + 1) & 15;
	}
	else if (j < 48)
	{
		t->f = t->b ^ t->c ^ t->d;
		t->g = (3 * j + 5) & 15;
	}
	else
	{
		t->f = t->c ^ (t->b | (~t->d));
		t->g = (7 * j) & 15;
	}
	t->f = t->f + t->a + g_k[j] + t->m[t->g];
	t->a = t->d;
	t->d = t->c;
	t->c = t->b;
	t->b += ((t->f << g_s[j]) | (t->f >> (32 - g_s[j])));
}

void	md5(unsigned char *input)
{
	t_md5			t;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	md5_init(input, &t, i);
	while (i < (t.out_len * 8) / 512)
	{
		md5_set_m(&t, i);
		j = -1;
		while (++j < 64)
			md5_main_loop(&t, j);
		t.a_base += t.a;
		t.b_base += t.b;
		t.c_base += t.c;
		t.d_base += t.d;
		i++;
	}
	t.a_base = reverse(t.a_base);
	t.b_base = reverse(t.b_base);
	t.c_base = reverse(t.c_base);
	t.d_base = reverse(t.d_base);
	ft_printf("%.8x%.8x%.8x%.8x", t.a_base, t.b_base, t.c_base, t.d_base);
	free(t.out);
}
