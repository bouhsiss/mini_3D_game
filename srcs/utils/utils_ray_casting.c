/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray_casting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:32:28 by omeslall          #+#    #+#             */
/*   Updated: 2022/11/03 17:33:01 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    free_linked_list(t_lst **head)
{
    t_lst *tmp;

    while (*head)
    {
        tmp = *head;
        *head = (*head)->next;
        free(tmp->content);
        free(tmp);
    }
}

t_lst	*new_node(void *content)
{
    t_lst	*new;

    new = malloc(sizeof(t_lst));
    if (!new)
        return (NULL);
    new->content = content;
    new->next = NULL;
    new->previous = NULL;
    return (new);
}

void	add_node_back(t_lst **lst, t_lst *new)
{
    t_lst	*tmp;

    if (!*lst)
    {
        *lst = new;
        return ;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    new->previous = tmp;
}

t_lst    *get_last_node(t_lst *lst)
{
    while (lst->next)
        lst = lst->next;
    return (lst);
}

float normalize_angle(float angle)
{   
    angle = fmod(angle, (2 * PI));
    if (angle < 0)
    {
        angle = (2 * PI) + angle;
    }
    return (angle);
}

t_ray    *init_t_ray(float ray_angle)
{
    t_ray *ray;
    
    ray = malloc(sizeof(t_ray));
    if (!ray)
        return (NULL);
    ray->ray_angle = normalize_angle(ray_angle);
    ray->wallhit_x  = 0;
    ray->wallhit_y  = 0;
    ray->distance = 0;
    if(ray->ray_angle > 0 && ray->ray_angle < PI)
        ray->if_down = 1;
    else
        ray->if_down = 0;
    ray->if_up = !ray->if_down;
    if(ray->ray_angle < 0.5 * PI || ray->ray_angle > 1.5 * PI)
        ray->if_R = 1;
    else
        ray->if_R = 0;
    ray->if_L = !ray->if_R;
    return(ray);
}
