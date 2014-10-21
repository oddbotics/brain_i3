/*
 * \get_subnet.cpp
 *
 * \author Drew Marschner, CMU - amarschn@andrew.cmu.edu
 * \date October 13, 2014
 * 
 * Returns the subnet of the eth0 connection
 */

#include <oddbot_boot/get_subnet.h>

int get_subnet() {
  int fd;
  struct ifreq ifr;

  fd = socket(AF_INET, SOCK_DGRAM, 0);

  /* I want to get an IPv4 IP address */
  ifr.ifr_addr.sa_family = AF_INET;

  /* I want IP address attached to "subnet" */
  strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);

  ioctl(fd, SIOCGIFADDR, &ifr);

  close(fd);

  char *address = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
  std::stringstream s(address);
  int a, b, c, d;
  char ch;
  s >> a >> ch >> b >> ch >> c >> ch >> d;
  return c;
}