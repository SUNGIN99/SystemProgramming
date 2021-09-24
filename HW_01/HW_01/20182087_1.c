#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFF_SIZE 500

int arg_n(char *argv) {
	int num;
	if (strcmp("-a", argv) == 0) { // �ɼ� -a ��� ��� ���
		num = -1;
		return num;
	}

	else {
		num = atoi(argv); //���ڿ��� ���ڷ� ��ȯ
		//num = (int)(*argv) - '0';
		if (num <= 26 && num >= 1) {
			return num;	 //���ĺ��� a~z �����ֱ� ������ ���� ����
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

	int line = arg_n(argv[1]); //���� ���� �� (1,2,3 ����)

	if (line == -1) { //���� ���� ���� -1 �̶�� ��� ���
		lseek(rfd, 0, SEEK_SET);
		line = BUFF_SIZE;
	}

	else { //�ƴϸ� ���� ���Ǽ� * 6 (5���� �Ȱ��� ���ĺ� + \n = 6���� ����)
		start = lseek(rfd, -(line * 6), SEEK_END);
	}


	n = read(rfd, buf, line * 6);
	write(1, buf, n);

	close(rfd);
	return 0;
}