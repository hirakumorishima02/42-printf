/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digits_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorishi <hmorishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:03:23 by hmorishi          #+#    #+#             */
/*   Updated: 2021/05/19 16:07:51 by hmorishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	digits_d(int d)
{
	int	i;

	i = 0;
	while (d)
	{
		d /= 10;
		i++;
	}
	return (i);
}
