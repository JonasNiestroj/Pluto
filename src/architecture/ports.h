#ifndef _PORTS_H__
#define _PORTS_H__

unsigned char inportbyte(unsigned short port);

void outportbyte(unsigned short port, unsigned char val);

unsigned short inportshort(unsigned short port);

void outportshort(unsigned short port, unsigned short val);

unsigned int inportint(unsigned short port);

void outportint(unsigned short port, unsigned int val);

#endif