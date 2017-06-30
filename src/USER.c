/*
** USER.c for  in /home/moutou_m/c/PSU_2016_myftp/src
** 
** Made by moutoum
** Login   <maxence.moutoussamy@epitech.eu>
** 
** Started on  Wed May 10 18:11:14 2017 moutoum
** Last update Wed May 10 18:11:51 2017 moutoum
*/

#include "ftp.h"

int server_USER(int cfd, char *const _cmd, struct s_login *login)
{
  char *cmd;
  char *crlf;

  if (login->connected)
    return (print_code(cfd, 530, "Can't change from guest user."),
	    EXIT_FAILURE);
  cmd = _cmd + strlen("USER");
  if (*cmd == FTP_SP)
    {
      cmd += 1;
      if (((crlf = strstr(cmd, FTP_CRLF)) - cmd) <= 0)
	return (print_code(cfd, 530, NULL), EXIT_SUCCESS);
      bzero(login, sizeof(struct s_login) - sizeof(char *));
      if (!strncmp(FTP_ANONYM, cmd, strlen(FTP_ANONYM)))
	strcpy(login->login, FTP_ANONYM);
      else
	strncpy(login->login, cmd, crlf - cmd);
      return (print_code(cfd, 331, NULL), EXIT_SUCCESS);
    }
  else
    {
      print_code(cfd, 530, NULL);
      return (EXIT_SUCCESS);
    }
  return (EXIT_SUCCESS);
}
