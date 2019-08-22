#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NAME_LEN 100

typedef struct {
  char name[NAME_LEN];
  char surname[NAME_LEN];
  float salary;
  float score;
} Worker;

float compute_bonus(int score, float salary){
	if(score == 0)
		return salary + 0.95 * salary;
	if(score == 1)
		return salary;
	if(score >= 2)
		return salary + (score * 0.015 * salary);
	return -1.0;
}

// void compute_bonus(Worker* w){
// 	if(w->score == 0)
// 		w->salary = w->salary + 0.95 * w->salary;
// 	if(w->score == 1)
// 		return;
// 	if(w->score >= 2)
// 		w->salary = w->salary + (w->score * 0.015 * w->salary);
// }


int main(void) {
  FILE *fp = NULL;
  FILE *output_file = NULL;
  int i = 0;
  int person = 0;
  int k = 0;
  printf("Tell me number of elements\n");
  scanf("%d", &k);
  Worker* data = malloc(k*sizeof(Worker));
  // Worker data[k];

  if ((fp = fopen("workers.txt", "r")) == NULL) {
    printf("Cant open file %s\n", "workers.txt");
    return 1;
  }
  if ((output_file = fopen("output.txt", "w")) == NULL) {
    printf("Cant open file %s\n", "output.txt");
    return 1;
  }
  else {
    for (i = 0; i < k; i++) {
      if (fscanf(fp, "%s %s %f %f", data[person].name, data[person].surname,
                 &data[person].salary, &data[person].score) != 4)
        break;
      person++;
    }
    for (i = 0; i < person; i++){
    	data[i].salary = compute_bonus(data[i].score, data[i].salary);
      printf("%-10s %-10s %5.1f %5.1f\n", data[i].name, data[i].surname,
             data[i].salary, data[i].score);
      fprintf(output_file, "%-10s %-10s %5.1f %5.1f\n", data[i].name, data[i].surname,
             data[i].salary, data[i].score);
    }
    fclose(fp);
    fclose(output_file);
  }
  return 0;
}