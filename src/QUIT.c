/*
** QUIT.c for  in /home/moutou_m/c/PSU_2016_myftp/src
** 
** Made by moutoum
** Login   <maxence.moutoussamy@epitech.eu>
** 
** Started on  Wed May 10 18:15:32 2017 moutoum
** Last update Wed May 10 18:15:41 2017 moutoum
*/

#include "ftp.h"

int server_QUIT(int cfd, char *const _cmd, struct s_login *login)
{
  (void)login;
  (void)_cmd;
  print_code(cfd, 221, NULL);
  close(cfd);
  return (EXIT_SUCCESS);
}
