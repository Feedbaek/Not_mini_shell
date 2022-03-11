/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:47:24 by minskim2          #+#    #+#             */
/*   Updated: 2022/03/11 18:20:20 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redirect_in(const char *file, int input_fd)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("redirect_in error: %s\n", strerror(errno));
		exit(1);
	}
	dup2(fd, input_fd);
	close(fd);
}

void	redirect_out(const char *file, int output_fd)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("redirect_out error: %s\n", strerror(errno));
		exit(1);
	}
	dup2(fd, output_fd);
	close(fd);
}

void	redirect_out_add(const char *file, int output_fd)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
	{
		printf("redirect_out error: %s\n", strerror(errno));
		exit(1);
	}
	dup2(fd, output_fd);
	close(fd);
}

//void	redirect_in(const char *file)
//{
//	int	fd;

//	fd = open(file, O_RDWR);
//	if (fd < 0)
//	{
//		printf("redirect_in error: %s\n", strerror(errno));
//		exit(1);
//	}
//	dup2(fd, STDIN_FILENO);
//	close(fd);
//}

//void	redirect_out(const char *file)
//{
//	int	fd;

//	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
//	if (fd < 0)
//	{
//		printf("redirect_out error: %s\n", strerror(errno));
//		exit(1);
//	}
//	dup2(fd, STDOUT_FILENO);
//	close(fd);
//}
