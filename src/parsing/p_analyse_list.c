/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_analyse_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaisne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:15:21 by jlaisne           #+#    #+#             */
/*   Updated: 2023/05/25 16:13:06 by jlaisne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	key_compare(t_pcub *lst, t_scub *data);
int		open_content_sprites(t_scub *data);
int		check_colors(t_scub *data);

void	analyse_parameters(t_scub *data)
{
	t_pcub	*temp;

	temp = data->cub;
	while (temp)
	{
    	key_compare(temp, data);
		if (duplicate_key(&data->cub, temp) == 1)
			ft_exit("Duplicate textures.", data);
		temp = temp->next;
	}
	if (open_content_sprites(data) == 1)
			ft_exit("Invalid texture path.", data);
	if (check_colors(data) == 1)
			ft_exit("Invalid color RGB code.", data);
	return ;
}

void	key_compare(t_pcub *lst, t_scub *data)
{
	int	key_len;

	key_len = ft_strlen(lst->key);
	if (ft_memcmp(lst->key, "NO", key_len) == 0)
		lst->type = NO;
	else if (ft_memcmp(lst->key, "SO", key_len) == 0)
		lst->type = SO;
	else if (ft_memcmp(lst->key, "WE", key_len) == 0)
		lst->type = WE;
	else if (ft_memcmp(lst->key, "EA", key_len) == 0)
		lst->type = EA;
	else if (ft_memcmp(lst->key, "C", key_len) == 0)
		lst->type = C;
	else if (ft_memcmp(lst->key, "F", key_len) == 0)
		lst->type = F;
	else
		ft_exit("Invalid key identifier.", data);		
}

int	open_content_sprites(t_scub *data)
{
	t_pcub	*temp;

	temp = data->cub;
	while (temp)
	{
		if (temp->type < 5)
		{
			if (check_arg(temp->content, ".xpm") == 1)
				ft_exit("Invalid parameter path.", data);
			if (open_arg(data, temp->content, 0) == 1)		
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	split_and_check(char *content, t_scub *data)
{
	int		i;
	char	**colors;

	i = 0;
	colors = ft_split(content, ',');
	if (!colors)
		ft_exit("Error malloc", data);
	if (colors[3])
		ft_exit("Invalid RGB format", data);
	while (i < 3)
	{
		if (ft_atoll(colors[i]) < 0 || ft_atoll(colors[i]) > 255)
			return (1);
		i++;
	}
	return (0);
}

int	check_colors(t_scub *data)
{
	t_pcub	*floor;
	t_pcub	*ceilling;

	floor = get_node(data->cub, F);
	ceilling = get_node(data->cub, C);
	if (split_and_check(floor->content, data) == 1)
		return (1);
	if (split_and_check(ceilling->content, data) == 1)
		return (1);
	return (0);
}