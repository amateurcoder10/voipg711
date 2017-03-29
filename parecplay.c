
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/gccmacro.h>

#include "g711mit.c"
#define BUFSIZE 1024

int main(int argc, char*argv[]) {
    /* The sample type to use */
    static const pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE,
        .rate = 8000,
        .channels = 2
    };
    pa_simple *s = NULL;
    pa_simple *s2=NULL;
    int ret = 1;
    int error;
int n;
	//printf("%lu",sizeof(short));

        if (!(s = pa_simple_new(NULL, argv[0], PA_STREAM_RECORD, NULL, "record", &ss, NULL, NULL, &error))) {
        fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
        goto finish;
    }
    //printf("creating recording stream\n");

   if (!(s2 = pa_simple_new(NULL, argv[0], PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error))) {
        fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
        goto finish;
    }


    for (;;) 
	{
        short buf[BUFSIZE];
	unsigned char buf2[BUFSIZE];short buf3[BUFSIZE];
	
	//printf("reading some data\n");
      n=1024;
        if (pa_simple_read(s, buf, sizeof(buf), &error) < 0) {
            fprintf(stderr, __FILE__": pa_simple_read() failed: %s\n", pa_strerror(error));
            goto finish;
        }
	        //printf("record");
	for(int i=0;i<n;i++)
	{
	buf2[i]=linear2alaw(buf[i]);
	//printf("encoding %d %d %d\n",i,buf2[i],buf[i]);
	
	buf3[i]=alaw2linear(buf2[i]);
	//printf("decoding %d %d %d\n",i,buf2[i],buf3[i]);
	}
	usleep(20);

        if (pa_simple_write(s2, buf3, sizeof(buf3), &error) < 0) {
            fprintf(stderr, __FILE__": pa_simple_write() failed: %s\n", pa_strerror(error));
            goto finish;
        }
	//printf("play");
    
	
}
    ret = 0;

finish:

    if (s)
        pa_simple_free(s);

    return ret;

}
