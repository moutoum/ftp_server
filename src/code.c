/*
** code.c for  in /home/moutou_m/c/PSU_2016_myftp/src
** 
** Made by moutoum
** Login   <maxence.moutoussamy@epitech.eu>
** 
** Started on  Wed May 10 18:18:05 2017 moutoum
** Last update Wed May 10 22:58:12 2017 moutoum
*/

#include "ftp.h"

static struct s_code codes[] =
  {
    {.code = 120,
     .msg = "Service ready in nnn minutes."},
    {.code = 125,
     .msg = "Data connection already open; transfer starting."},
    {.code = 150,
     .msg = "File status okay; about to open data connection."},
    {.code = 200,
     .msg = "Command okay."},
    {.code = 214,
     .msg = "Help message. On how to use the server or the \
meaning of a particular non-standard command. This reply is \
useful only to the human user."},
    {.code = 220,
     .msg = "Service ready for new user."},
    {.code = 221,
     .msg = "Service closing control connection. Logged out if appropriate."},
    {.code = 226,
     .msg = "Transfer complete."},
    {.code = 227,
     .msg = "Entering Passive Mode (h1,h2,h3,h4,p1,p2)."},
    {.code = 230,
     .msg = "User logged in, proceed."},
    {.code = 250,
     .msg = "Requested file action okay, completed."},
    {.code = 257,
     .msg = "\"PATHNAME\" created."},
    {.code = 331,
     .msg = "User name okay, need password."},
    {.code = 332,
     .msg = "Need account for login."},
    {.code = 425,
     .msg = "Use PORT or PASV first."},
    {.code = 500,
     .msg = "Unknown command."},
    {.code = 503,
     .msg = "Login with USER first."},
    {.code = 530,
     .msg = "Permission denied."},
    {.code = 550,
     .msg = "Failed to change directory."},
    {.code = -1,
     .msg = NULL}};

int print_code(int fd, uint16_t code, const char *msg)
{
  int i;

  i = 0;
  while (codes[i].code != (uint16_t)-1)
    {
      if (codes[i].code == code)
	{
	  dprintf(fd, "%d %s%s",
		  codes[i].code, msg ? msg : codes[i].msg, FTP_CRLF);
	  return (0);
	}
      i++;
    }
  return (0);
}
