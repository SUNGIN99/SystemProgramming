#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFF_SIZE 1000

int arg_n(char *argv) {
	int num;
	if (strcmp("-a", argv) == 0) {
		num = -1; //-a �ɼ��̸� ��� ���
	}

	else {
		num = atoi(argv); //���ڿ��� ������ ��ȯ
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
	//0~155���� ���ڰ� �ִٸ� OFFSET�� 155�� ��Ÿ�����ϴµ� 156�� ��Ÿ���� ���ϱ�?

	n = lseek(rfd, 0, SEEK_SET);
	//������ �б����� �ٽ� OFFSET�� ������ ó������

	n = read(rfd, read_all, end);//0 ~ 155 => char buf[156]
	//OFFSET ������ �°� �о���Ѵ�. (end�� 155���ٸ� end + 1�� �Ǿ����)

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
			{	//���๮�ڰ� ���� �� �о���� ���� ī��Ʈ
				line_cnt++; 
			}
			if (line_cnt == line + 1)
			{	//����ī��Ʈ�� ���ϴ� ����(����� ���ϴ� ���� ��)�� �´ٸ� LOOP_EXIT
				//if SEEK_END == '\n' => line +1
				//if seek_END != '\n' = > line
				//in this problem SEEK_END == '\n'
				break;
			}
			read_b++; //count how many read, ���� byte�� �� ī��Ʈ
		}
		n = lseek(rfd, -read_b, SEEK_END); 
		//������ ������ ���� ī��Ʈ ����ŭ ������ ������
		//SEEK_END�� 155���ٸ�,  read_b = read_b - 1 ...?
	}

	//read_b= OFFSET
	//printf("offset :%d\n", n);

	n = read(rfd, buff, read_b);
	write(1, buff, read_b);

	close(rfd);
	return 0;
}