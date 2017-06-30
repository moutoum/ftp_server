/*
** DELE.c for  in /home/moutou_m/c/PSU_2016_myftp/src
** 
** Made by moutoum
** Login   <maxence.moutoussamy@epitech.eu>
** 
** Started on  Wed May 10 18:17:30 2017 moutoum
** Last update Wed May 10 18:17:41 2017 moutoum
*/

#include "ftp.h"

int server_DELE(int cfd, char *const _cmd, struct s_login *login)
{
  char *cmd;
  char *crlf;
  char buff[3096];

  (void)login;
  cmd = _cmd + strlen("DELE");
  if (*cmd == FTP_SP)
    {
      cmd += 1;
      if (((crlf = strstr(cmd, FTP_CRLF)) - cmd) <= 0)
	return (print_code(cfd, 550, NULL), EXIT_SUCCESS);
      bzero(buff, 3096);
      strncpy(buff, cmd, crlf - cmd);
      if (access(buff, R_OK) == -1 || unlink(buff) == -1)
	return (print_code(cfd, 550, NULL), EXIT_SUCCESS);
      return (print_code(cfd, 250, NULL), EXIT_SUCCESS);
    }
  else
    print_code(cfd, 550, NULL);
  return (EXIT_SUCCESS);
}
