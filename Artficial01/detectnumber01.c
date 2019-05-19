#include <stdio.h>
#include <stdlib.h> 
#include "data_set.h"		// �񱳸� ���� �����Ͱ� ���� �������.

#define PER 32					// ��ü ������ �Է��� �ΰ����� ������ ����.
#define MAX 10					// �� ���� �� �� �Է� ��
#define THERSOLD 0.4		// �迭 �ε��� ���� ���� ������ 330 �Ѱ��� �ǵ����ذ�.

int main(void) {
														
	double  sample_list[10][7][7];	// ���ں� ��ǥ ������ ���� ���� �ڸ�.
	int thres[10];						// ��ǥ ���� ����� ���� �������� ����ġ�� ���� ����.
	int example_list[10][7][7];		// ��ǥ �� 0~9
	int insertarray_Crit[7][7];		// ���ϱ� ���� �Է¹��� �迭�� ���� ����.
	
	int a, i, j, l = 0;		// �ݺ��� ������ ���� ����.
	int k = 0;					// ���� �ݺ��� ������ �뵵�� ����.
	int pers = 0;			// �ݺ��� ������ �����ε�, ���⼭ ������ ���� ��� ����.
	int num = 0;			// �迭 �� �տ� ���ڸ� �ǵ�.
	int sum = 0;			// ������ �迭�ε������� �����ֱ� ����~
	int thres_sum = 0;
	int b = 0;				// �׽�Ʈ ������ ����. ���� ���� Ȯ�εǸ� ����.

	/*
	printf("0�� 1�� ���� Ȱ���Ͽ� ���� ���� �̹����� �Է��Ͻʽÿ�. : \n");
	for (l = 0; l < 7; l++) {
		for (k = 0; k < 7; k++) {
			scanf("%d", &insertarray_Crit[l][k]);
		}
	}
	*/
	/*
		���⸸ �ϴ� �պ��� �ǳ�
	*/
	for(num=0; num<10; num++) {
		// printf("%d",num);
		for (j = 0; j < 7; j++) {
			sum = 0;
				for (i=0; i<7; i++){
					sum = 0;
					for(pers=0; pers<PER; pers++) {
						for (k = 0; k < MAX; k++) {
							sum += data_set[pers][num][k][j][i]; 
							sample_list[num][j][i]=sum;
						}
				}
				}
			}
	}
	/*
		��հ� ���͸� �����ϱ� ���� �¾��۾� : ������� ����
	*/
	for (num = 0; num<10; num++) {
		for (j = 0; j < 7; j++) {
			for (i = 0; i<7; i++) {
				thres_sum += sample_list[num][j][i];
				thres[num] = thres_sum;
			}
		}
	}
	/*
		������ ���õ����͸� ����� ���� �迭���� ���ϰ� �� ����, ���� ������ ���õ����� ���ڷ� ����.
		�̶� ������� ���� �����ؼ�, ��ǥ���� �迭�� 0,1 ���·θ� �����͸� ����.
	*/
	for (num = 0; num<10; num++) {
		// printf("%d",num);
		for (j = 0; j < 7; j++) {
			for (i = 0; i<7; i++) {
					// printf("[%d][%d][%d][%d] ",num,k, j, i);
					sample_list[num][j][i] = sample_list[num][j][i]/PER;
					if (sample_list[num][j][i] >= (thres[num]/49))
						example_list[num][j][i] = 1;
					else example_list[num][j][i] = 0;
			}
		}
	}
	// ������� ������, ��ǥ���� ������ ����°ͱ����� �ϼ���.

	/* 
		�׽�Ʈ �뵵�� ��¹� �̴� �ݺ�����.
	*/
	for(num=0; num<10; num++) {
		printf("\n");
	for (a = 0; a < 7; a++) {
		printf("\n");
		for (b = 0; b < 7; b++) {	
			printf("%.2f ",sample_list[num][a][b]);
		}
	}
	}
	/*
	�׽�Ʈ �뵵�� ��¹� �̴� �ݺ�����.
	*/
	for (num = 0; num<10; num++) {
		printf("\n");
		for (a = 0; a < 7; a++) {
			printf("\n");
			for (b = 0; b < 7; b++) {
				printf("%d ", example_list[num][a][b]);
			}
		}
	}

	return 0;
}