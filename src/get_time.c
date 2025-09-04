/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:18:28 by moaljazz          #+#    #+#             */
/*   Updated: 2025/09/04 19:18:30 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

time_t get_time_ms(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) == -1)
    {
        write(2, "gettimeofday() error\n", 22);
        return -1;
    }
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
