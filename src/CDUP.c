/*
** CDUP.c for  in /home/moutou_m/c/PSU_2016_myftp/src
** 
** Made by moutoum
** Login   <maxence.moutoussamy@epitech.eu>
** 
** Started on  Wed May 10 18:14:44 2017 moutoum
** Last update Wed May 10 18:14:58 2017 moutoum
*/

#include "ftp.h"

int server_CDUP(int cfd, char *const _cmd, struct s_login *login)
{
  (void)login;
  (void)_cmd;
  if (chdir("..") == -1)
    return (print_code(cfd, 550, NULL), EXIT_SUCCESS);
  return (print_code(cfd, 250, NULL), EXIT_SUCCESS);
}