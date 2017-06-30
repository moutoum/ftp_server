/*
** HELP.c for  in /home/moutou_m/c/PSU_2016_myftp/src
** 
** Made by moutoum
** Login   <maxence.moutoussamy@epitech.eu>
** 
** Started on  Wed May 10 18:19:07 2017 moutoum
** Last update Wed May 10 18:19:17 2017 moutoum
*/

#include "ftp.h"

int server_HELP(int cfd, char *const _cmd, struct s_login *login)
{
  int i;
  char buff[3096];
  int ret;

  (void)_cmd;
  (void)login;
  i = 0;
  bzero(buff, 3096);
  strcpy(buff, "Commands :");
  ret = strlen("Commands :");
  while (g_cmds[i].name != NULL)
    {
      if (!(i % 4))
	{
	  strcpy(&(buff[ret]), "\n ");
	  ret += 2;
	}
      ret += sprintf(&(buff[ret]), "%-5s", g_cmds[i].name);
      i++;
    }
  strcat(buff, "\n214 Help OK.");
  print_code(cfd, 214, buff);
  return (EXIT_SUCCESS);
}
