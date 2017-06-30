/*
** NOOP.c for  in /home/moutou_m/c/PSU_2016_myftp/src
** 
** Made by moutoum
** Login   <maxence.moutoussamy@epitech.eu>
** 
** Started on  Wed May 10 18:16:04 2017 moutoum
** Last update Wed May 10 18:16:13 2017 moutoum
*/

#include "ftp.h"

int server_NOOP(int cfd, char *const _cmd, struct s_login *login)
{
  (void)login;
  (void)_cmd;
  print_code(cfd, 200, NULL);
  return (EXIT_SUCCESS);
}
