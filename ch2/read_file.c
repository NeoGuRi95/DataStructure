#include <stdio.h>

int main(void){
    FILE* pFile = fopen("C:\\Users\\jea5158\\Desktop\\DataStructure\\ch2\\test.txt", "r"); //read mode 
    if(pFile == NULL)
    {
        //r로 읽을 때는 파일이 없을 수 있기 때문에 이렇게 널체크를 해주어야합니다.
        //파일이 없으면 FILE*가 NULL 입니다.
        //파일이 없을때 파일을 만드는 처리를 하던지 프로그램에 맞게 짜면됩니다.
        //여기서는 프로그램을 종료 하겠습니다.
        printf("파일이 없습니다. 프로그램을 종료합니다.");
        return 0;
    }
    //여기까지 왔다는건 read 모드로 파일이 열린것 입니다.
    char str[50];
    fgets(str, 50, pFile);  //파일에 있는거 읽어오기
    
    fclose(pFile);          //파일 닫기
    printf("%s\n", str);    //터미널에 출력

    return 0;
}