#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <grp.h>

typedef struct event_t {
 struct timeval time;
 unsigned short type;
 unsigned short code;
 unsigned int value;
} event;

int main(int argc, char *argv[])
{
    int timeout_ms = 5000;
    char input_dev[] = "/dev/input/event0\0";
    int st;
    int ret;
    struct pollfd fds[1];

    fds[0].fd = open(input_dev, O_RDONLY|O_NONBLOCK);

    if(fds[0].fd<0)
    {
        printf("error unable open for reading '%s'\n",input_dev);
        return(0);
    }

    const int input_size = sizeof(event);
    unsigned char input_data[input_size];
    memset(input_data,0,input_size);

    fds[0].events = POLLIN;

    while(1){
        ret = poll(fds, 1, timeout_ms);
        if(ret>0){
            if(fds[0].revents){
                ssize_t r = read(fds[0].fd,input_data,input_size);

                if(r<0){
                    printf("error %d\n",(int)r);
                    break;
                }
                else{
                    event* e = (event*)input_data;
		    //printf("type=%u code=%u value=%d\n",e->type,e->code,e->value);

		    if (e->type == 1 && e->code == 425 && e->value == 0) {
			if (fork() == 0) {
			  printf("%d\n",execl("/usr/sbin/termshortcutrunner","/usr/sbin/termshortcutrunner",(void*)NULL));
                          return 0;
                        }
		    }

                    memset(input_data,0,input_size);
                }
            } else {
                printf("error\n");
            }
        }
    }

    close(fds[0].fd);
    return 0;
}
