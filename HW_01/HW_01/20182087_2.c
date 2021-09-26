#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFF_SIZE 1000

int arg_n(char *argv) {
	int num;
	if (strcmp("-a", argv) == 0) {
		num = -1; //-a 옵션이면 모두 출력
	}

	else {
		num = atoi(argv); //문자열을 정수로 변환
	}
	return num;
}
//2021.09.26 version 2
int main(int argc, char *argv[]) {
	int rfd, n, i = 0;
	int line = 0, line_cnt = 0, read_b = 0;
	off_t end;
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

	end = lseek(rfd, 0, SEEK_END); 
	//ex) 0 ~ 155 => why 156?
	//0~155개의 문자가 있다면 OFFSET은 155를 나타내야하는데 156을 나타낸다 왜일까?

	n = lseek(rfd, 0, SEEK_SET);
	//파일을 읽기위해 다시 OFFSET을 파일의 처음으로

	n = read(rfd, read_all, end);//0 ~ 155 => char buf[156]
	//OFFSET 개수에 맞게 읽어야한다. (end가 155였다면 end + 1이 되어야함)

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
			{	//개행문자가 있을 시 읽어야할 라인 카운트
				line_cnt++; 
			}
			if (line_cnt == line + 1)
			{	//라인카운트가 원하는 조건(출력을 원하는 라인 수)과 맞다면 LOOP_EXIT
				//if SEEK_END == '\n' => line +1
				//if seek_END != '\n' = > line
				//in this problem SEEK_END == '\n'
				break;
			}
			read_b++; //count how many read, 읽을 byte의 수 카운트
		}
		n = lseek(rfd, -read_b, SEEK_END); 
		//파일의 끝에서 읽을 카운트 수만큼 앞으로 땡겨줌
		//SEEK_END가 155였다면,  read_b = read_b - 1 ...?
	}

	//read_b= OFFSET
	//printf("offset :%d\n", n);

	n = read(rfd, buff, read_b);
	write(1, buff, read_b);

	close(rfd);
	return 0;
}