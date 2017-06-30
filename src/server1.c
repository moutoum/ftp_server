/*
** server1.c for  in /home/moutou_m/c/PSU_2016_myftp/src
** 
** Made by moutoum
** Login   <maxence.moutoussamy@epitech.eu>
** 
** Started on  Wed May 10 18:08:38 2017 moutoum
** Last update Wed May 10 18:09:01 2017 moutoum
*/

#include "ftp.h"

int server_init_tcp(struct protoent **protocol_addr)
{
  if (!(*protocol_addr = getprotobyname("TCP")))
    return (perror("getprotobyname"), EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int server_create_socket(int *fd_addr, const struct protoent *protocol)
{
  int iSetOption;

  iSetOption = 1;
  if ((*fd_addr = socket(AF_INET, SOCK_STREAM, protocol->p_proto)) == -1)
    return (perror("socket"), EXIT_FAILURE);
  setsockopt(*fd_addr, SOL_SOCKET, SO_REUSEADDR, (char *)&iSetOption,
	     sizeof(iSetOption));
  return (EXIT_SUCCESS);
}

int server_close_socket(int fd)
{
  if (close(fd) == -1)
    return (perror("close"), EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int server_bind(int fd, int port)
{
  struct sockaddr_in sockinfo;

  sockinfo.sin_family = AF_INET;
  sockinfo.sin_port = htons(port);
  sockinfo.sin_addr.s_addr = INADDR_ANY;
  if (bind(fd, (const struct sockaddr *)&sockinfo,
	   sizeof(struct sockaddr)) == -1)
    return (perror("bind"), EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int server_listen(int fd)
{
  if (listen(fd, 1024) == -1)
    return (perror("listen"), EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
