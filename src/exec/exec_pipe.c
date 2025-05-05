/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:52:53 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/05/01 19:05:46 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipe(t_tree *root, t_ms *ms)
{
	//open un pfd, le ranger dans la liste de ms.pfd
	//redefinir le outfd de root.left et le infd de root.right avec le pfd.
}