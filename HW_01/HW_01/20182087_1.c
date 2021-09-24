#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFF_SIZE 500

int arg_n(char *argv) {
	int num;
	if (strcmp("-a", argv) == 0) { // 옵션 -a 라면 모두 출력
		num = -1;
		return num;
	}

	else {
		num = atoi(argv); //문자열을 숫자로 변환
		//num = (int)(*argv) - '0';
		if (num <= 26 && num >= 1) {
			return num;	 //알파벳이 a~z 까지있기 때문에 범위 적용
		}

		else {
			fprintf(stderr, "wrong arguments\nuse -a or integer 1~26\n");
			exit(1);
		}
	}

}

int main(int argc, char *argv[]) {
	int rfd, n;
	off_t start;
	char buf[BUFF_SIZE];
	rfd = open("abc.txt", O_RDONLY);


	if (rfd == -1) { // read file open err
		fprintf(stderr, "open_err()\n");
		exit(1);
	}

	if (argc == 1) { //argument count err (have to be upper than 1)
		fprintf(stderr, "you have to input -a or integers\n");
		exit(1);
	}

	int line = arg_n(argv[1]); //읽을 줄의 수 (1,2,3 정수)

	if (line == -1) { //읽을 줄의 수가 -1 이라면 모두 출력
		lseek(rfd, 0, SEEK_SET);
		line = BUFF_SIZE;
	}

	else { //아니면 읽을 줄의수 * 6 (5개의 똑같을 알파벳 + \n = 6개의 문자)
		start = lseek(rfd, -(line * 6), SEEK_END);
	}


	n = read(rfd, buf, line * 6);
	write(1, buf, n);

	close(rfd);
	return 0;
}