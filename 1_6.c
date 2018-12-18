#include "./lib/unp.h"
#include"myerr.h"

int main(int arcgc, char **argv)
{
  int sockfd, n;
  char reciveline[MAXLINE + 1];
  struct sockaddr_in6 servadde;

  if (arcgc != 2)
    err_quit("usgae : a.out <IPAddress>");
  if ((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
      err_sys("socket error!");
  bzero(&servadde, sizeof(servadde));
  servadde.sin6_family = AF_INET6;
  servadde.sin6_port = htons(13);
  if (inet_pton(AF_INET6, argv[1], &servadde.sin6_addr) < 0)
    err_quit("inet_pton error for %s", argv[1]);
  if ((n = connect(sockfd, (SA*)&servadde, sizeof(servadde))) < 0)
    err_sys("connect error");
  while ( (n = read(sockfd, reciveline, MAXLINE)) > 0) {
    reciveline[n] = 0;
    if (fputs(reciveline, stdout) == EOF)
      err_sys("fputs error");
  }
  if (n < 0)
    err_sys("read error");
  exit(0);
}
