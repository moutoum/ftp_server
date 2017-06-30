/*
** LIST.c for  in /home/moutou_m/c/PSU_2016_myftp/src
** 
** Made by moutoum
** Login   <maxence.moutoussamy@epitech.eu>
** 
** Started on  Wed May 10 18:27:35 2017 moutoum
** Last update Wed May 10 18:27:44 2017 moutoum
*/

#include "ftp.h"

static void do_ls(int cfd, const char *file)
{
  char buff[3096];
  FILE *f;
  int i;
  int c;

  sprintf(buff, "/bin/ls -l %s", file);
  f = popen(buff, "r");
  bzero(buff, 3096);
  while ((c = fread(buff, 1, 3096, f)) > 0)
    {
      i = 0;
      while (i < c)
	{
	  if (buff[i] == '\n')
	    write(cfd, "\r\n", 2);
	  else
	    write(cfd, &buff[i], 1);
	  i++;
	}
      bzero(buff, 3096);
    }
  fclose(f);
}

int server_LIST(int cfd, char *const _cmd, struct s_login *login)
{
  struct sockaddr_in client;
  char file[3096];

  bzero(file, 3096);
  if (login->passive == FTP_NOMODE)
    return (print_code(cfd, 425, NULL), EXIT_SUCCESS);
  if (sscanf(_cmd, "LIST %s\r\n", file) == 1 && !opendir(file))
    return (print_code(cfd, 550, "Failed to open file."), EXIT_SUCCESS);
  if (login->passive == FTP_PASSIVE)
    server_accept(login->fd, &login->cfd, &client);
    else
    {
	if (connect(login->cfd, (const struct sockaddr *)&login->ctmpin,
	      sizeof(struct sockaddr)) == -1)
    	return (print_code(cfd, 530, strerror(errno)), EXIT_SUCCESS);
    }
  print_code(cfd, 150, NULL);
  do_ls(login->cfd, file);
  print_code(cfd, 226, NULL);
  close(login->cfd);
  close(login->fd);
  login->passive = FTP_NOMODE;
  return (EXIT_SUCCESS);
}
