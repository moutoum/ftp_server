/*
** STOR.c for  in /home/moutou_m/c/PSU_2016_myftp/src
** 
** Made by moutoum
** Login   <maxence.moutoussamy@epitech.eu>
** 
** Started on  Wed May 10 18:05:20 2017 moutoum
** Last update Wed May 10 18:09:18 2017 moutoum
*/

#include "ftp.h"

static void do_file(int cfd, char *file)
{
  int fd;
  char buff[3096];
  int i;
  int c;

  if ((fd = open(file, O_RDWR | O_CREAT, 0644)) == -1)
    {
      print_code(cfd, 550, "Failed to open file.");
      return;
    }
  while ((c = read(cfd, buff, 3096)) > 0)
    {
      i = 0;
      while (i < c)
	{
	  if (!strncmp(FTP_CRLF, &buff[i], 2)
	      && write(fd, "\n", 1) != -1)
	    i++;
	  else
	    write(fd, &buff[i], 1);
	  i++;
	}
    }
  close(fd);
}

int server_STOR(int cfd, char *const _cmd, struct s_login *login)
{
  struct sockaddr_in client;
  char file[3096];

  bzero(file, 3096);
  if (login->passive == FTP_NOMODE)
    return (print_code(cfd, 425, NULL));
  if (sscanf(_cmd, "STOR %s\r\n", file) != 1)
    return (print_code(cfd, 550, "Failed to open file."),
	    EXIT_SUCCESS);
  if (login->passive == FTP_PASSIVE)
    server_accept(login->fd, &login->cfd, &client);
    else
    {
	if (connect(login->cfd, (const struct sockaddr *)&login->ctmpin,
	      sizeof(struct sockaddr)) == -1)
    	return (print_code(cfd, 530, strerror(errno)), EXIT_SUCCESS);
    }
  print_code(cfd, 150, NULL);
  do_file(login->cfd, file);
  print_code(cfd, 226, NULL);
  close(login->cfd);
  close(login->fd);
  login->passive = FTP_NOMODE;
  return (EXIT_SUCCESS);
}
