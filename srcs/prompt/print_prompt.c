/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:14:57 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/13 18:28:26 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_modified_pwd(void)
{
	char	*pwd;
	char	*home;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	home = getenv("HOME");
	if (home && pwd && !ft_strncmp(pwd, home, ft_strlen(home)))
	{
		tmp = ft_strjoin("~", pwd + ft_strlen(home));
		free(pwd);
		pwd = tmp;
	}
	return (pwd);
}

char	*print_prompt(void)
{
	char	*pwd;
	char	*user;
	char	result[1024];

	pwd = get_modified_pwd();
	user = getenv("USER");
	*result = '\0';
	ft_strlcat(result, "\001\033[1;31m", ft_strlen("\001\033[1;31m") + 1);
	ft_strlcat(result, user, ft_strlen(result) + ft_strlen(user) + 1);
	ft_strlcat(result, "\001\033[0m", ft_strlen(result) + ft_strlen("\001\033[0m") + 1);
	ft_strlcat(result, ":", ft_strlen(result) + 2);
	ft_strlcat(result, "\001\033[1;34m", ft_strlen(result) + \
		ft_strlen("\001\033[1;34m") + 1);
	ft_strlcat(result, pwd, ft_strlen(result) + ft_strlen(pwd) + 1);
	ft_strlcat(result, "\001\033[0m", ft_strlen(result) + ft_strlen("\001\033[0m") + 1);
	ft_strlcat(result, "$ ", ft_strlen(result) + 3);
	free(pwd);
	return (ft_strdup(result));
}
