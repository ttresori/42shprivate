/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_newline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:29:01 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/06 01:03:03 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		get_newline(t_42sh *sh)
{
	add_token(sh, "!newline!", NEWLINE, NONE);
	sh->token_nbr++;
	sh->lex_pos++;
}
