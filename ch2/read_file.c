#include <stdio.h>

int main(void){
    FILE* pFile = fopen("C:\\Users\\jea5158\\Desktop\\DataStructure\\ch2\\test.txt", "r"); //read mode 
    if(pFile == NULL)
    {
        //r�� ���� ���� ������ ���� �� �ֱ� ������ �̷��� ��üũ�� ���־���մϴ�.
        //������ ������ FILE*�� NULL �Դϴ�.
        //������ ������ ������ ����� ó���� �ϴ��� ���α׷��� �°� ¥��˴ϴ�.
        //���⼭�� ���α׷��� ���� �ϰڽ��ϴ�.
        printf("������ �����ϴ�. ���α׷��� �����մϴ�.");
        return 0;
    }
    //������� �Դٴ°� read ���� ������ ������ �Դϴ�.
    char str[50];
    fgets(str, 50, pFile);  //���Ͽ� �ִ°� �о����
    
    fclose(pFile);          //���� �ݱ�
    printf("%s\n", str);    //�͹̳ο� ���

    return 0;
}