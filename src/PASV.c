/*
** PASV.c for  in /home/moutou_m/c/PSU_2016_myftp/src
** 
** Made by moutoum
** Login   <maxence.moutoussamy@epitech.eu>
** 
** Started on  Wed May 10 18:19:49 2017 moutoum
** Last update Wed May 10 18:20:28 2017 moutoum
*/

#include "ftp.h"

int server_PASV(int cfd, char *const _cmd, struct s_login *login)
{
  struct protoent *protocol;
  int port;
  char buff[3096];

  (void)_cmd;
  if (server_init_tcp(&protocol))
    return (print_code(cfd, 530, NULL), EXIT_FAILURE);
  if (server_create_socket(&login->fd, protocol))
    return (print_code(cfd, 530, NULL), EXIT_FAILURE);
  port = 1024;
  while (port < UINT16_MAX && server_bind(login->fd, port))
    port++;
  if (server_listen(login->fd))
    return (server_close_socket(login->fd), print_code(cfd, 530, NULL),
	    EXIT_FAILURE);
  bzero(buff, 3096);
  sprintf(buff, "Entering passive mode (127,0,0,1,%d,%d)",
	  port / 256, port % 256);
  print_code(cfd, 227, buff);
  login->passive = FTP_PASSIVE;
  return (EXIT_SUCCESS);
}
