/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalih <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 05:41:14 by mmalih            #+#    #+#             */
/*   Updated: 2023/02/17 04:35:41 by mmalih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sshell.h"

void	pwd_builtin(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		panic("getcwd() error");
}
