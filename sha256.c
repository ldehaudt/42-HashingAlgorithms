/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 15:22:02 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/07/19 22:15:41 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int g_m[64];
unsigned int g_k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

unsigned int	rightrot(unsigned int num, unsigned int rot)
{
	unsigned int i;
	unsigned int r;

	i = 0;
	while (i < rot)
	{
		r = num & 1;
		num = num >> 1;
		num += r << 31;
		i++;
	}
	return (num);
}

void			init(t_sha256 *t, unsigned char *input)
{
	t->a_base = 0x6a09e667;
	t->b_base = 0xbb67ae85;
	t->c_base = 0x3c6ef372;
	t->d_base = 0xa54ff53a;
	t->e_base = 0x510e527f;
	t->f_base = 0x9b05688c;
	t->g_base = 0x1f83d9ab;
	t->h_base = 0x5be0cd19;
	t->out_len = find_output_len(input);
	t->out = (unsigned char*)ft_strnew(t->out_len);
	ft_strcpy((char *)t->out, (char *)input);
	t->len = ft_strlen((char *)input) * 8;
	t->out[ft_strlen((char *)input)] = 1 << 7;
	t->i = 0;
	while (t->i < 8)
	{
		t->out[t->out_len - 8 + t->i] = ((unsigned char *)&(t->len))[7 - t->i];
		t->i++;
	}
	t->i = 0;
}

void			setup(t_sha256 *t)
{
	t->x = 0;
	while (t->x < 16)
	{
		g_m[t->x] = 0;
		g_m[t->x] += t->out[t->i * 64 + t->x * 4 + 0] << 24;
		g_m[t->x] += t->out[t->i * 64 + t->x * 4 + 1] << 16;
		g_m[t->x] += t->out[t->i * 64 + t->x * 4 + 2] << 8;
		g_m[t->x] += t->out[t->i * 64 + t->x * 4 + 3] << 0;
		t->x++;
	}
	while (t->x < 64)
	{
		t->s0 = rightrot(g_m[t->x - 15], 7) ^ rightrot(g_m[t->x - 15],\
		18) ^ (g_m[t->x - 15] >> 3);
		t->s1 = rightrot(g_m[t->x - 2], 17) ^ rightrot(g_m[t->x - 2],\
		19) ^ (g_m[t->x - 2] >> 10);
		g_m[t->x] = g_m[t->x - 16] + t->s0 + g_m[t->x - 7] + t->s1;
		t->x++;
	}
	t->a = t->a_base;
	t->b = t->b_base;
	t->c = t->c_base;
	t->d = t->d_base;
}

void			main_loop(t_sha256 *t)
{
	t->j = 0;
	while (t->j < 64)
	{
		t->s1 = rightrot(t->e, 6) ^ rightrot(t->e, 11) ^ rightrot(t->e, 25);
		t->ch = (t->e & t->f) ^ ((~t->e) & t->g);
		t->tmp1 = t->h + t->s1 + t->ch + g_k[t->j] + g_m[t->j];
		t->s0 = rightrot(t->a, 2) ^ rightrot(t->a, 13) ^ rightrot(t->a, 22);
		t->maj = (t->a & t->b) ^ (t->a & t->c) ^ (t->b & t->c);
		t->tmp2 = t->s0 + t->maj;
		t->h = t->g;
		t->g = t->f;
		t->f = t->e;
		t->e = t->d + t->tmp1;
		t->d = t->c;
		t->c = t->b;
		t->b = t->a;
		t->a = t->tmp1 + t->tmp2;
		t->j++;
	}
}

void			sha256(unsigned char *input)
{
	t_sha256 t;

	init(&t, input);
	while (t.i < (t.out_len * 8) / 512)
	{
		setup(&t);
		t.e = t.e_base;
		t.f = t.f_base;
		t.g = t.g_base;
		t.h = t.h_base;
		main_loop(&t);
		t.a_base = t.a_base + t.a;
		t.b_base = t.b_base + t.b;
		t.c_base = t.c_base + t.c;
		t.d_base = t.d_base + t.d;
		t.e_base = t.e_base + t.e;
		t.f_base = t.f_base + t.f;
		t.g_base = t.g_base + t.g;
		t.h_base = t.h_base + t.h;
		t.i++;
	}
	ft_printf("%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x", t.a_base, t.b_base,\
	t.c_base, t.d_base, t.e_base, t.f_base, t.g_base, t.h_base);
	free(t.out);
}
