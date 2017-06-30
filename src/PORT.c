/*
** PORT.c for  in /home/moutou_m/c/PSU_2016_myftp/src
** 
** Made by moutoum
** Login   <maxence.moutoussamy@epitech.eu>
** 
** Started on  Wed May 10 18:21:13 2017 moutoum
** Last update Wed May 10 18:21:47 2017 moutoum
*/

#include "ftp.h"

int server_PORT(int cfd, char *const _cmd, struct s_login *login)
{
  struct protoent *protocol;
  char buff[3096];
  int tab[6];

  (void)_cmd;
  if (sscanf(_cmd, "PORT %d,%d,%d,%d,%d,%d", &tab[0], &tab[1], &tab[2],
  &tab[3], &tab[4], &tab[5]) != 6)
	 {
		 return (print_code(cfd, 550, "scanf failed"), EXIT_SUCCESS);
	 }
  if (server_init_tcp(&protocol))
    return (print_code(cfd, 530, NULL), EXIT_FAILURE);
  if (server_create_socket(&login->cfd, protocol))
    return (print_code(cfd, 530, NULL), EXIT_FAILURE);
  login->passive = FTP_ACTIVE;
  login->ctmpin.sin_family = AF_INET;
  login->ctmpin.sin_port = htons(tab[4] * 256 + tab[5]);
  sprintf(buff, "%d.%d.%d.%d", tab[0], tab[1], tab[2], tab[3]);
  login->ctmpin.sin_addr.s_addr = inet_addr(buff);
  return (print_code(cfd, 200, NULL), EXIT_SUCCESS);
}
