#include <stdlib.h>
#include <stdio.h>

#define NAME_LEN 64

typedef struct{/*構造体*/
    char name[NAME_LEN];    /*名前*/
    char surname[NAME_LEN]; /*指名*/
    float salary;   /*給料*/
    float score;    /*スコア*/
}Worker;

/*ボーナス込みの給料を計算する関数*/
float compute_bonus(float score,float salary){

    if(score == 0.0){ /*スコアが０なら給料を０・９倍*/
        return salary * 0.9;
    }
    if(score == 1.0){/*スコアが１なら増減なし*/
        return salary;
    }
    if(score >= 2.0){/*スコアが２なら（salary * score * 0.1）分プラス*/
        return salary + salary * score * 0.1;
    }

    return 1;
}


int main(void){

    FILE *fp = NULL;
    FILE *output_file = NULL;

    printf("Tell me number pf elements\n");
    int k = 0;
    scanf("%d", &k);

    Worker* data = malloc(k * sizeof(Worker));

    if((fp = fopen("workers.txt","r")) == NULL){/*読み込むファイルを開く処理*/
        printf("Can't open file %s\n","workers.txt");/*オープンに失敗したらメッセージ表示*/
        return 1;
    }

    int person = 0;

    if((output_file = fopen("output.txt","w")) == NULL){/*書きこむファイルを開く処理*/
        printf("Can't open file %s\n","output.txt");
        return 1;
    }else{
        for(int i = 0; i < k; i++){
            if(fscanf(fp,"%s %s %f %f",
                data[person].name,data[person].surname,
                &data[person].salary,&data[person].score) != 4){/*読み込んだ項目が4じゃなかったらbreak*/
                    printf("Wrong in number of elements.\n");
                    break;
            }
            person++;
        }

        for(int i = 0;i < person; i++){

            data[i].salary = compute_bonus(data[i].score,data[i].salary);/*ボーナス込みの給料を計算*/

            fprintf(output_file,"%-10s %-10s %5.1f %5.1f\n",/*アウトプットファイルに書き込む*/
            data[i].name,data[i].surname,
            data[i].salary,data[i].score);

            printf("%-10s %-10s %5.1f %5.1f\n",/*コンソールに表示*/
            data[i].name,data[i].surname,
            data[i].salary,data[i].score);

        }

        fclose(fp);/*ファイルを閉じる*/
        fclose(output_file);

    }

    free(data);/*malloc()で確保した領域を解放*/

    return 0;
}