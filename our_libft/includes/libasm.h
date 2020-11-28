/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:36:10 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/20 12:36:13 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LIBASM_H
# define LIBASM_H

#include <stdlib.h>
#include <unistd.h>

/*
** *********************    WRITTEN IN THE ASSEMBLER   ********************** **
*/
size_t		ft_strlen(char const *str);
char		*ft_strcpy(char * dst, const char * src);
int			ft_strcmp(const char *s1, const char *s2);
ssize_t		ft_write(int fildes, const void *buf, size_t nbyte);
char		*ft_strdup(const char *s1);
ssize_t		ft_read(int fildes, void *buf, size_t nbyte);

# endif
