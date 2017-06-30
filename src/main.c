/*
** main.c for  in /home/moutou_m/c/PSU_2016_myftp/src
** 
** Made by moutoum
** Login   <maxence.moutoussamy@epitech.eu>
** 
** Started on  Wed May 10 18:18:21 2017 moutoum
** Last update Wed May 10 22:56:26 2017 moutoum
*/

#include "ftp.h"

static void usage()
{
  printf("USAGE: ./server <port> <path>\n");
  printf("\tPORT\tPort of connection.\n");
  printf("\tPATH\tServer location.\n");
}

static int get_line(int cfd, char *buff)
{
  int i;
  int ret;

  i = 0;
  while (!strstr(buff, FTP_CRLF))
    {
      if ((ret = read(cfd, buff + i, 3096 - i)) <= 0)
	return (EXIT_FAILURE);
      i += ret;
    }
  return (EXIT_SUCCESS);
}

int server_to_client(int cfd, const char *ip)
{
  char buff[3096];
  struct s_command *cmd;
  struct s_login login;

  printf("Connection from %s begin.\n", ip);
  login.ip = strdup(ip);
  print_code(cfd, 220, NULL);
  bzero(buff, 3096);
  bzero(&login, sizeof(struct s_login) - sizeof(char *));
  while (1)
    {
      if (get_line(cfd, buff)) return (EXIT_SUCCESS);
      cmd = g_cmds;
      while (cmd->name && strncmp(cmd->name, buff, strlen(cmd->name)))
	cmd++;
      if (cmd->name && (!cmd->connected || login.connected))
	cmd->callback(cfd, buff, &login);
      else if (!login.connected)
	print_code(cfd, 530, "Please login with USER and PASS.");
      else
	print_code(cfd, 500, NULL);
      bzero(buff, 3096);
    }
  return (EXIT_SUCCESS);
}

int go_accept(int fd)
{
	struct sockaddr_in client;
	int client_fd;
	pid_t child;

	if (server_accept(fd, &client_fd, &client) || (child = fork()) == -1)
		return (server_close_socket(fd), EXIT_FAILURE);
	if (child)
		server_close_socket(client_fd);
	else
	{
		server_close_socket(fd);
		server_to_client(client_fd, inet_ntoa(client.sin_addr));
		printf("Client exited.\n");
		exit(0);
	}
	return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
	struct protoent *protocol;
	int fd;

	if (ac == 3)
	{
		chdir(av[2]);
		if (server_init_tcp(&protocol))
			return (EXIT_FAILURE);
		if (server_create_socket(&fd, protocol))
			return (EXIT_FAILURE);
		if (server_bind(fd, atoi(av[1])) || server_listen(fd))
			return (server_close_socket(fd), EXIT_FAILURE);
		while (!go_accept(fd));
		server_close_socket(fd);
	}
	else
		return (usage(), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
