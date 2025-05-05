/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:52:50 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/05/01 19:41:37 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	si node.left ou node.right == redir : chopper le path de la redir
	creer les files si besoin. 
	
	expandre les arguments de la cmd
	
	creer le fork
	
		faire les redirect si besoin (si redir ou si ms.fd_out ou ms.fd_in)
		
		close tous les pfd
		
		checker si builtin, si oui -> builtint si non -> execve

	parent
		penser a remettre les file_in et file_out a 0
	*/

void	exec_cmd(t_tree node, t_ms *ms)
{
}
