#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 100

/*構造体*/
typedef struct {
  char name[NAME_LEN]; /*名前*/
  char surname[NAME_LEN]; /*苗字*/
  float salary; /*給料*/
  float score; /*スコア*/
} Worker;

/*ボーナスを計算する関数*/
void compute_bonus(Worker* w){
	if(w->score == 0)       /*スコアが0なら給料は（0.95＊給料）*/
		w->salary = 0.95 * w->salary;
	if(w->score == 1)       /*スコアが1なら増減なし*/
		return;
	if(w->score >= 2)       /*2以上ならプラス（給料*0.015*スコア）*/
		w->salary = w->salary + (w->score * 0.015 * w->salary);
}


int main(void) {
  FILE *fp = NULL;
  FILE *output_file = NULL;
  int i = 0;
  int person = 0;
  int k = 0;
  printf("Tell me number of elements\n");
  scanf("%d", &k);
  Worker* data = malloc(k*sizeof(Worker));
  

  if ((fp = fopen("workers.txt", "r")) == NULL) {  /*ファイルを開く処理*/
    printf("Cant open file %s\n", "workers.txt");  /*オープンに失敗したらメッセージ表示*/
    return 1;
  }
  if ((output_file = fopen("output.txt", "w")) == NULL) { /*アウトプットファイルを開く*/
    printf("Cant open file %s\n", "output.txt");
    return 1;
  }
  else {
    for (i = 0; i < k; i++) {
      if (fscanf(fp, "%s %s %f %f", data[person].name, data[person].surname,
                 &data[person].salary, &data[person].score) != 4)
        break; /*読み込んだ項目が4じゃなかったらbreak*/
      person++;
    }
    for (i = 0; i < person; i++){
    	compute_bonus(&data[i]); /*ボーナスを計算する関数*/
      printf("%-10s %-10s %5.1f %5.1f\n", data[i].name, data[i].surname,
             data[i].salary, data[i].score); /*コンソールに表示*/
      fprintf(output_file, "%-10s %-10s %5.1f %5.1f\n", data[i].name, data[i].surname,
             data[i].salary, data[i].score); /*アウトプットファイルに書き込む*/
    }
    fclose(fp); /*ファイルを閉じる*/
    fclose(output_file);
  }
  return 0;
}