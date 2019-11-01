#include <stdio.h>
#include <stdlib.h>

#define NAME_LEN 64

typedef struct{ /*Struct構造体*/
    char name[NAME_LEN]; /*名前*/
    char surname[NAME_LEN]; /*苗字*/
    int score1; /*点数*/
    int score2;
    int score3;
    int score4;
} Student;

float compute_grade(float average){ /*成績を計算*/

    if(average <= 50){ /*50以下は2*/
        return 2.0;
    }else if(average >= 51 && average <= 60){ /*51～60は成績3*/
        return 3.0;
    }else if(average >= 61 && average <= 70){ /*61～70は成績3.5*/
        return 3.5;
    }else if(average >= 71 && average <= 80){ /*71～80は成績4*/
        return 4.0;
    }else if(average >= 81 && average <= 90){ /*81～90は4.5*/
        return 4.5;
    }else{                                    /*91～100は5*/
        return 5.0;
    }

}

int main(void){

    FILE *fp = NULL;
    FILE *output_file = NULL;

    printf("Tell me number of students.\n");

    int k = 0;
    scanf("%d",&k);

    printf("\n");

    Student* data = malloc(k * sizeof(Student)); /*メモリ確保*/

    if((fp = fopen("students.txt","r")) == NULL){ /*データが書いてあるファイルを開く*/
        printf("Can't open file %s.\n","students.txt"); /*ファイルが開けないときにはエラーメッセージ*/
        return 1;
    }

    int person = 0;

    if((output_file = fopen("results.txt","w")) == NULL){   /*書き込みするファイルを開く*/
        printf("Can't open file %s.\n","results.txt");
        return 1;
    }else{

        for(int i = 0; i < k; i++){

            if(fscanf(fp,"%s %s %d %d %d %d",data[person].name,data[person].surname,
            &data[person].score1,&data[person].score2,
            &data[person].score3,&data[person].score4) != 6){ /*読み込んだデータの項目が6個じゃなかったらbreak*/
                printf("Wrong number of elements.\n");
                break;
            }

            person++;
        }

        for(int i = 0; i < person; i++){ /*コンソールに名前と苗字、点数を表示*/
            printf("%-10s %-10s %d %d %d %d\n",data[i].name,data[i].surname,
            data[i].score1,data[i].score2,
            data[i].score3,data[i].score4);
        }

        printf("\n");


        for(int i = 0; i <person; i++){

            float average = (data[i].score1 + data[i].score2 + 
            data[i].score3 + data[i].score4) / 4;  /*平均点を計算*/

            fprintf(output_file,"%-10s %-10s %5.1f\n",
            data[i].name,data[i].surname,compute_grade(average));   /*データを書き込む*/

            printf("%-10s %-10s %5.1f\n",
            data[i].name,data[i].surname,compute_grade(average)); /*名前、苗字、成績をコンソールに表示*/
        }

        fclose(fp); /*ファイルを閉じる*/
        fclose(output_file);
    }

    free(data);/*malloc()で確保した領域を解放*/

    return 0;
}
