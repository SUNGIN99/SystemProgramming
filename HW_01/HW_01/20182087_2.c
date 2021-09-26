#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>


int main(int argc, char *argv[]) {
	DIR *dp; //���丮
	struct dirent *dirp; //���丮 ����ü
	struct stat buf; //�������� ����ü

	int file = 0, dir = 0, u = 0;
	char file_path[256]; //���ϰ�� �̸�

	if (argc != 2) { 
		fprintf(stderr, "usage : 20182087_2 directory_name\n");
		exit(1);
	}

	if ((dp = opendir(argv[1])) == NULL) { //�������� �ʴ� ���ϸ� ���޽� ����
		fprintf(stderr, "can't open %s\n", argv[1]);
		exit(1);
	}

	while ((dirp = readdir(dp)) != NULL) {
		strcpy(file_path, argv[1]); //���ϰ�� ����
		if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0) {
			continue; //�θ� ���丮�� ���� ���丮 ����
		}
		strcat(file_path, "/"); // ���ϰ�� �ؿ� ���丮 �̸� ����
		strcat(file_path, dirp->d_name);// ���ϰ�� �ؿ� �ִ� ���丮 �̸� �߰�
		lstat(file_path, &buf);// ������ ������ buf����ü�� ����
		//printf("%s\n", file_path);
		//printf("%s : %d\n %o\n\n", file_path, dirp->d_type, buf.st_mode);

		if (S_ISREG(buf.st_mode)) file++; //����Ÿ���� regular file �϶� ���� ����
		else if (S_ISDIR(buf.st_mode)) dir++; //����Ÿ���� directory�϶� ���� ����
		else u++; //unknown type
	}

	printf("n dirs : %d\n", dir);
	printf("n files : %d\n", file);
	//printf("u : %d\n", u);
	return 0;

}