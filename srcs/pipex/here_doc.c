/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:18:54 by minskim2          #+#    #+#             */
/*   Updated: 2022/03/06 22:33:14 by minskim2         ###   ########.fr       */
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

int	create_tmp(char **name)
{
	int	fd;

	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("create_tmp error: %s\n", strerror(errno));
		exit(1);
	}
	return (fd);
}

int read_tmp(void)
{
	int	fd;

	fd = open("tmp", O_RDWR);
	if (fd < 0)
	{
		printf("read_tmp error: %s\n", strerror(errno));
		exit(1);
	}
}

void	here_doc(char *limiter, int input_fd, int output_fd)
{
	int		fd;
	int		fd2;
	int		status;
	char	*str;

	fd = create_tmp("tmp");
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
	close(fd);
	// 이전 명령어로부터 받은 input_fd로 새로 파일 만들어야함
	fd = create_tmp("tmp2");
	status = get_next_line(input_fd, &str);
	while(status > 0)
	{
		if (write(fd, str, ft_strlen(str)) < 0 || write(fd, "\n", 1) < 0)
			exit(1);
		status = get_next_line(input_fd, &str);
	}
	if (write(fd, str, ft_strlen(str)) < 0)
		exit(1);
	// heredoc 저장한 파일을 읽어서 쓰기
	input_fd = read_tmp();
	status = get_next_line(input_fd, &str);
	while(status > 0)
	{
		if (write(fd, str, ft_strlen(str)) < 0 || write(fd, "\n", 1) < 0)
			exit(1);
		status = get_next_line(input_fd, &str);
	}
	if (write(fd, str, ft_strlen(str)) < 0)
		exit(1);
	close(input_fd);

	dup2(fd, STDIN_FILENO);
	close(fd);
	//fd = read_tmp();
	//status = get_next_line(STDIN_FILENO, &str);
	//while (status > 0)
	//{
	//	write(output_fd, str, ft_strlen(str));
	//	status = get_next_line(STDIN_FILENO, &str);
	//}
	//write(output_fd, str, ft_strlen(str));
	//close(fd);
}
