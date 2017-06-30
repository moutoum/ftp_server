/*
** PASS.c for  in /home/moutou_m/c/PSU_2016_myftp/src
** 
** Made by moutoum
** Login   <maxence.moutoussamy@epitech.eu>
** 
** Started on  Wed May 10 18:12:44 2017 moutoum
** Last update Wed May 10 18:13:05 2017 moutoum
*/

#include "ftp.h"

int server_PASS(int cfd, char *const _cmd, struct s_login *login)
{
  (void)_cmd;
  if (!login->connected && !strlen(login->login))
    return (print_code(cfd, 503, NULL), EXIT_SUCCESS);
  else if (login->connected)
    return (print_code(cfd, 530, "Already logged in."));
  if (!strcmp(login->login, FTP_ANONYM))
    {
      login->connected = 1;
      return (print_code(cfd, 230, NULL), EXIT_SUCCESS);
    }
  print_code(cfd, 530, "Login incorrect.");
  return (EXIT_SUCCESS);
}
