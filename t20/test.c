#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char write_buff[100] = "jeevitha";

int main()
{
    int num, fd, read_bytes, written_bytes, rv;
    char read_data[100];

    printf("Do you want to open: 1 - Yes, 0 - No : ");
    scanf("%d", &num);
    fd = open("/dev/myDev", O_RDWR);

    printf("Do you want to write: 1 - Yes, 0 - No : ");
    scanf("%d", &num);
    written_bytes = write(fd, write_buff, 10);
    if(written_bytes < 0) {
        printf("Error in writting\n");
    }

    printf("Do you want to read: 1 - Yes, 0 - No : ");
    scanf("%d", &num);
    read_bytes = read(fd, read_data, 10);
    printf("%d\n", read_bytes);
    printf("%s\n", read_data);
    if(read_bytes < 0) {
        printf("Error in reading\n");
    }
   /* printf("Do you want to ioctl: 1 - Yes, 0 - No : ");
    scanf("%d", &num);
    rv = ioctl(fd, 0, NULL);*/

    printf("Do you want to close: 1 - Yes, 0 - No : ");
    scanf("%d", &num);
    close(fd);

    return 0;
} 
