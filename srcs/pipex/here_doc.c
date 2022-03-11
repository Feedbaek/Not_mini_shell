/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:18:54 by minskim2          #+#    #+#             */
/*   Updated: 2022/03/11 16:51:29 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
임시 파일을 이용한 here_doc 처리
	1.	O_WRONLY, O_CREAT, O_TRUNC 모드 및 0644 권한으로 임시 파일 생성
	2.	limiter가 나오기 전까지 임시 파일에 기록
	3.	limiter를 만나면 기록을 중지하고 임시 파일을 닫기
	4.	O_RDONLY 모드로 임시 파일 다시 열기
	5.	dup2를 통해 표준 입력을 임시 파일로 돌리기
	6.	임시 파일 닫기
*/

int	create_tmp(char *name)
{
	int	fd;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("create_tmp error: %s\n", strerror(errno));
		exit(1);
	}
	free(name);
	return (fd);
}

int	read_tmp(void)
{
	int	fd;

	fd = open("tmp", O_RDONLY);
	if (fd > 0)
	{
		close(fd);
		printf("read_tmp error: %s\n", strerror(errno));
		exit(1);
	}
}

char	*tmp_naming(void)
{
	int	fd;
	char	*name;
	char	*new_name;

	name = (char *)malloc(sizeof(char) * 5);
	ft_strlcpy(name, "_tmp", 5);
	fd = open(name, O_RDONLY);
	while (fd > 0)
	{
		close(fd);
		new_name = ft_strjoin(name, "_tmp");
		free(name);
		name = new_name;
		fd = open(name, O_RDONLY);
	}
	if (errno != ENOENT)	// 없는 파일의 경우가 아니면
		exit(1);
	return (name);
}

void	here_doc(char *limiter, int write_fd)
{
	int		fd;
	int		status;
	char	*str;
	char	*file_name;

	file_name = tmp_naming();
	fd = create_tmp(file_name);
	status = get_next_line(0, &str);
	if (status < 0)
		exit(1);
	while (ft_strncmp(str, limiter, ft_strlen(str)) != 0)
	{
		if (write(fd, str, ft_strlen(str)) < 0 || write(fd, "\n", 1) < 0)
			exit(1);
		status = get_next_line(0, &str);
		if (status < 0)
			exit(1);
	}
	dup2(fd, write_fd);
	close(fd);
}
