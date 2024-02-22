#include <stdio.h>
#include <unistd.h>


static int my_write(int fd, const void *buf, size_t count) {
    size_t bytes_written = 0;
    size_t bytes_remaining = count;
    const char *buf_addr = buf;

    while (bytes_remaining > 0) {
        bytes_written = write(fd, buf_addr, bytes_remaining);
        if (bytes_written == -1) {
            printf("Error writing to file\n"); 
            return -1;
        }
        bytes_remaining -= bytes_written;
        buf_addr += bytes_written;
    }

    return 0;
}

static int my_strlen(const char *s) {
    int len = 0;
    while (*s != '\0') {
        s++;
        len++;
    }
   return len;
}

int my_print(const char *s) {
    return my_write(1, s, my_strlen(s));
}

int main (int argc, char **argv) {
   
    /* create diff cases for num of arg
    might wanna change this to a switch statement
    with all the different cases
    */
/*ejejre*/
    switch (argc) {
        case 1:
            /*copy first 10 lines of standard input*/
            char buffer[100];
            int i = 0;
            int newline_count=0;//added count
            while (i < 10){
                int n = read(0, buffer, 100);
                if (n == 0){
                    break;
                }
                my_write(1, buffer, n);

                for(int j=0;j<n;j++){
                    if (buffer[j]== '\n'){
                        newline_count++;
                        if(newline_count==10){
                            i=10;
                            break;
                        }
                    }
                i++;
            }
            break;
        case 2:
            /*copy first 10 lines of file*/
            int fd = open(argv[1],O_RDONLY);
            if (fd ==-1){
                my_print("Error opening file\n");
                return -1;
            }
            char buffer[100];
            int line_count2= 0;//renamed the variable i to line_count2
            while (line_count2 < 10){
                int n = read(fd, buffer, 100);
                if (n == 0){
                    break;
                }
                my_write(1, buffer, n);
                i++;
            }
            close(fd);
            
            break;
        case 3:
            /*copy first n lines of file*/
            int fd = open(argv[2],O_RDONLY);
            if(fd == -1){
                my_print("Error opening file\n");
                return -1;
            }
            int n= atoi(argv[1]);
            char buffer[100];
            int line_count3=0;//renamed variable i to line_count3
            while(line_count3 < n){
                int read_bytes = read(fd,buffer,100);
                if(read_bytes==0){
                    break;
                }
                my_write(1,buffer,read_bytes);
                i++;
            }
            close(fd);
            break;
        default:
            my_print("Error: too many arguments\n");
            break;
    }
}

