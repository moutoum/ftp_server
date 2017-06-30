/*
** PWD.c for  in /home/moutou_m/c/PSU_2016_myftp/src
** 
** Made by moutoum
** Login   <maxence.moutoussamy@epitech.eu>
** 
** Started on  Wed May 10 18:16:38 2017 moutoum
** Last update Wed May 10 18:16:47 2017 moutoum
*/

#include "ftp.h"

int server_PWD(int cfd, char *const _cmd, struct s_login *login)
{
  char *msg;
  char *pwd;

  (void)login;
  (void)_cmd;
  pwd = getcwd(NULL, 0);
  asprintf(&msg, "\"%s\"", pwd);
  print_code(cfd, 257, msg);
  free(msg);
  return (EXIT_SUCCESS);
}
