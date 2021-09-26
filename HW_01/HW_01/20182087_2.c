#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFF_SIZE 1000

int arg_n(char *argv) {
	int num;
	if (strcmp("-a", argv) == 0) {
		num = -1;
	}

	else {
		num = atoi(argv);
	}
	return num;
}
//2021.09.26 version 2
int main(int argc, char *argv[]) {
	int rfd, n, end = 0, i = 0;
	int line = 0, line_cnt = 0, read_b = 0;
	off_t start;
	char read_all[BUFF_SIZE], buff[BUFF_SIZE];
	rfd = open("abc2", O_RDONLY);
	//-------------------------------------------------------------------------------
	if (rfd == -1) { // read file open err
		fprintf(stderr, "open_err()\n");
		exit(1);
	}

	if (argc == 1) { //argument count err (have to be upper than 1)
		fprintf(stderr, "you have to input -a or integers\n");
		exit(1);
	}

	//-------------------------------------------------------------------------------

	end = lseek(rfd, 0, SEEK_END); //0 ~ 155 => why 156?
	printf("offset end : %d\n", end);
	int cur;
	n = lseek(rfd, 0, SEEK_SET);
	//------------------------------------------WTF
	n = read(rfd, read_all, end);//0 ~ 155 => char buf[156]
//------------------------------------------WTF

//	printf("read byte : %d\n",n);

	line = arg_n(argv[1]);
	if (line == -1) {
		lseek(rfd, 0, SEEK_SET);
		read_b = end;
	}
	else
	{
		for (i = end - 1; i >= 0; i--)
		{
			if (read_all[i] == '\n')
			{
				line_cnt++;
			}
			if (line_cnt == line + 1)
			{
				//if SEEK_END == '\n' => line +1
				//if seek_END != '\n' = > line
				//in this problem SEEK_END == '\n'
				break;
			}
			read_b++; //count how many read
		}
		n = lseek(rfd, -read_b, SEEK_END);
	}

	//  = OFFSET

	printf("offset :%d\n", n);

	n = read(rfd, buff, read_b);
	write(1, buff, read_b);
	printf("line : %d, line_cnt : %d, read_b : %d\n", line, line_cnt, read_b);

	close(rfd);
	return 0;
}