#include<fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/gccmacro.h>
#include "g711mit.c"
#include "g711.c"

void main()
{int BUFSIZE=100;	
 short buf[BUFSIZE];
unsigned char buf2[BUFSIZE];short buf3[BUFSIZE];
int n=20;
	for(int i=0;i<n;i++)
	{buf[i]=i;
	buf2[i]=ALaw_Encode(buf[i]);
	printf("%d %d\n",buf2[i],buf[i]);}
	
	for(int i=0;i<n;i++)
	{buf3[i]=ALaw_Decode(buf2[i]);
	printf("%d %d\n",buf2[i],buf3[i]);}

}
