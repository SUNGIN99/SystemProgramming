#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>


int main(int argc, char *argv[]) {
	DIR *dp; //디렉토리
	struct dirent *dirp; //디렉토리 구조체
	struct stat buf; //파일정보 구조체

	int file = 0, dir = 0, u = 0;
	char file_path[256]; //파일경로 이름

	if (argc != 2) { 
		fprintf(stderr, "usage : 20182087_2 directory_name\n");
		exit(1);
	}

	if ((dp = opendir(argv[1])) == NULL) { //존재하지 않는 파일명 전달시 오류
		fprintf(stderr, "can't open %s\n", argv[1]);
		exit(1);
	}

	while ((dirp = readdir(dp)) != NULL) {
		strcpy(file_path, argv[1]); //파일경로 복사
		if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0) {
			continue; //부모 디렉토리와 현재 디렉토리 제외
		}
		strcat(file_path, "/"); // 파일경로 밑에 디렉토리 이름 설정
		strcat(file_path, dirp->d_name);// 파일경로 밑에 있는 디렉토리 이름 추가
		lstat(file_path, &buf);// 파일의 정보를 buf구조체에 저장
		//printf("%s\n", file_path);
		//printf("%s : %d\n %o\n\n", file_path, dirp->d_type, buf.st_mode);

		if (S_ISREG(buf.st_mode)) file++; //파일타입이 regular file 일때 개수 증가
		else if (S_ISDIR(buf.st_mode)) dir++; //파일타입이 directory일때 개수 증가
		else u++; //unknown type
	}

	printf("n dirs : %d\n", dir);
	printf("n files : %d\n", file);
	//printf("u : %d\n", u);
	return 0;

}