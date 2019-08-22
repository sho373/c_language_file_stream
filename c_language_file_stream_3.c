#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{     /*Student構造体*/
	char name[100]; /*名前*/
	char surname[100]; /*苗字*/
	int score1; /*点数*/
	int score2;
	int score3;
	int score4;
}Student;


float grade(int average){         /*成績を計算*/

	if(average<=50) /*50以下は2*/
		return 2.0;
	if(average>=51 && average<=60) /*51～60は成績3*/
		return 3.0;
	if(average>=61 && average<=70) /*61～70は成績3.5*/
		return 3.5;
	if(average>=71 && average<=80) /*71～80は成績4*/
		return 4.0;
	if(average>=81 && average<=90) /*81～90は4.5*/
		return 4.5;
	if(average>=91 && average<=100) /*91～100は*/
		return 5;
	return 0;
}

int main(void){

	FILE *fp = NULL;
	FILE *outputfile=NULL;

	int i = 0;
	int person =0;
	int average = 0;
	int k = 8; /*今回は8人分まで*/

	Student* data=malloc(k*sizeof(Student)); /*メモリ確保*/


	if((fp=fopen("students.txt","r"))==NULL){    /*ファイルを開く*/
		printf("cant open file");
		return 0;
		}

	if((outputfile=fopen("results.txt","w"))==NULL){   /*アウトプットファイルを開く*/
		printf("cant open file");
		return 0;
		}
	else{
		for(i=0;i<k;i++){
			if(fscanf(fp,"%s %s %d %d %d %d",data[person].name,data[person].surname,
				&data[person].score1, &data[person].score2, &data[person].score3,
				&data[person].score4)!=6)
				break; /*読み込んだ項目が6じゃなかったらbreak*/
			person++;
		}

		for(i=0;i<person;i++){ /*コンソールに名前と苗字、点数を表示*/
			printf("%-10s %-10s %d %d %d %d\n",data[i].name,data[i].surname,
			data[i].score1,data[i].score2,data[i].score3,data[i].score4);
		}
		printf("\n");

		for(i=0;i<person;i++){
			average=((data[i].score1+data[i].score2+data[i].score3+data[i].score4)/4); /*平均を計算*/

			printf("%-10s %-10s %5.1f\n",data[i].name,data[i].surname,grade(average)); /*名前、苗字、成績を表示*/
      /*データを書き込み*/
			fprintf(outputfile,"%-10s %-10s %5.1f\n",data[i].name,data[i].surname,grade(average));
		}

	fclose(fp);       /*ファイルをとじる*/
	fclose(outputfile);
	}
	return 0;
}