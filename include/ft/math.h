/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:59:59 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/11 09:30:44 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# include <math.h>

typedef struct s_float2
{
	float	x;
	float	y;
}	t_float2;

typedef struct s_float3
{
	float	x;
	float	y;
	float	z;
}	t_float3;

typedef struct s_float4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_float4;

typedef struct s_float4x4
{
	t_float4	a;
	t_float4	b;
	t_float4	c;
	t_float4	d;
}	t_float4x4;

float		ft_minf(float a, float b);
float		ft_maxf(float a, float b);

float		ft_lerp(float start, float end, float factor);
float		ft_clamp(float value, float min, float max);
float		ft_rad(float deg);
float		ft_deg(float rad);

t_float2	ft_float2_add(t_float2 l, t_float2 r);
t_float2	ft_float2_sub(t_float2 l, t_float2 r);
t_float2	ft_float2_scalar(t_float2 l, float multiplier);
t_float2	ft_float2_lerp(t_float2 start, t_float2 end, float factor);
t_float2	ft_float2_normalize(t_float2 vec);
t_float2	ft_float2_rot(t_float2 l, float rad);

float		ft_float2_dot(t_float2 l, t_float2 r);
float		ft_float2_cross(t_float2 l, t_float2 r);
float		ft_float2_len(t_float2 vector);

t_float3	ft_float3_add(t_float3 l, t_float3 r);
t_float3	ft_float3_sub(t_float3 l, t_float3 r);
t_float3	ft_float3_scalar(t_float3 l, float multiplier);
t_float3	ft_float3_lerp(t_float3 start, t_float3 end, float factor);
t_float3	ft_float3_cross(t_float3 l, t_float3 r);
t_float3	ft_float3_normalize(t_float3 vec);
t_float3	ft_float3_transform(const t_float4x4 *l, t_float3 r);
t_float3	ft_float3_rot_x(t_float3 l, float rad);
t_float3	ft_float3_rot_y(t_float3 l, float rad);
t_float3	ft_float3_rot_z(t_float3 l, float rad);

float		ft_float3_dot(t_float3 l, t_float3 r);
float		ft_float3_len(t_float3 vector);

t_float4x4	ft_float4x4_mul(const t_float4x4 *l, const t_float4x4 *r);
t_float4x4	ft_float4x4_ortho(float size, float aspect, float near, float far);
t_float4x4	ft_float4x4_persp(float fov, float aspect, float near, float far);
t_float4x4	ft_float4x4_view(t_float3 pos, t_float3 x, t_float3 y, t_float3 z);
t_float4x4	ft_float4x4_translation(t_float3 pos);
t_float4x4	ft_float4x4_rotation(t_float3 rot);
t_float4x4	ft_float4x4_scaling(t_float3 scale);

#endif
