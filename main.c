/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchampli <rchampli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:10:25 by rchampli          #+#    #+#             */
/*   Updated: 2021/11/11 15:10:39 by rchampli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

char    *get_next_line(int fd);

int    main(void)
{
    int        fd1;
    int        i;
    char    *ret;

    fd1 = open("bible.txt", 0);
    while ((ret = get_next_line(fd1)))
    {
        printf("%s", ret);
    }
}