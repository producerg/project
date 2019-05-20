#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include "data_set.h"		// �񱳸� ���� �����Ͱ� ���� �������.

#define PER 32				// ��ü ������ �Է��� �ΰ����� ������ ����.
#define MAX 10				// �� ���� �� �� �Է� ��
#define PIXELNUM 49			// 7x7����� �ȼ� ��

int main(void) {

	double  sample_list[10][7][7];	// ���ں� ��ǥ ������ ���� ���� �ڸ�.
	double avg[10];				// ��ǥ ���� ����� ���� �������� ����ġ�� ���� ����.
	double var[10];					// ��ü ���õ������� �л�.
	double sdv_sample[10];			// ���õ������� ��ü ǥ�������� ���� ����.
	int example_list[10][7][7];		// ��ǥ �� 0~9

	int a, i, j, l = 0;		// �ݺ��� ������ ���� ����.
	int k = 0;				// ���� �ݺ��� ������ �뵵�� ����.
	int pers = 0;			// �ݺ��� ������ �����ε�, ���⼭ ������ ���� ��� ����.
	int num = 0;			// �迭 �� �տ� ���ڸ� �ǵ�.
	int sum = 0;			// ������ �迭�ε������� �����ֱ� ����~
	double avg_sum = 0;	// ��� ���ϱ� ���� ����
	double var_sum = 0;		// �л� ���ϱ� ���� ����
	double dif_sum = 0;
	double differ_vector[10];	// ���̺��� ��հ�
	double difvec_sum = 0;		// ���̺��� ���ϴ� �������� ���ϴ� ������ ��� ����.
	double difvec_var[10];
	double difvec_sdv[10];	// ���̺��Ͱ��� ǥ������
	double difvec_var_sum = 0;
	int b = 0;				// �׽�Ʈ ������ ����. ���� ���� Ȯ�εǸ� ����.
	int cnt = 0;			// �ǵ��� ������ ���� ����.

	// ��ü �Է¹��� ������ ���� �� �װ� �ϴ� ��ü�� ���غ�����.
	for (num = 0; num<10; num++) {
		for (j = 0; j < 7; j++) {
			sum = 0;
			for (i = 0; i<7; i++) {
				sum = 0;
				for (pers = 0; pers<PER; pers++) {
					for (k = 0; k < MAX; k++) {
						sum += data_set[pers][num][k][j][i];
						sample_list[num][j][i] = sum;
					}
				}
			}
		}
	}
	/*
	������ ���õ����͸� ����� ���� �迭���� ���ϰ� �� ����, ���� ������ ���õ����� ���ڷ� ����.
	*/
	for (num = 0; num<10; num++) {
		// printf("%d",num);
		for (j = 0; j < 7; j++) {
			for (i = 0; i<7; i++) {
				// printf("[%d][%d][%d][%d] ",num,k, j, i);
				sample_list[num][j][i] = sample_list[num][j][i] / PER;
			}
		}
	}
	// ������� ������, ��ǥ���� ������ ����°ͱ����� �ϼ���.

	/*
	��հ� ���͸� �����ϱ� ���� �¾��۾� : ��հ� ���ϱ�
	*/
	num = 0;
	while (1) {
		for (j = 0; j < 7; j++) {
			for (i = 0; i < 7; i++) {
				avg_sum += sample_list[num][j][i];
				avg[num] = avg_sum / PIXELNUM;
			}
		}
		avg_sum = 0;
		printf("%d(%.2f) ", num, avg[num]);	// ������ �� ���°� Ȯ���ϸ� �����.
		num++;
		if (num >= 10) break;
	}
	/*
	 ����� ������ ���� : �л갪�� ǥ�������� ���
	*/
	num = 0;
	while (1) {
		for (j = 0; j < 7; j++) {
			for (i = 0; i < 7; i++) {
				var_sum+=pow(sample_list[num][j][i] - avg[num], 2.0);
				var[num]=var_sum / PIXELNUM;
			}
		}
		var_sum = 0;
		sdv_sample[num]=sqrt(var[num]);
		printf("%d model's var : %.2f\n ", num, var[num]);
		printf("%d model's sdv : %.2f\n ", num, sdv_sample[num]);
		num++;
		if (num >= 10) break;
	}
	/*
	 ��ü ���õ��� �Է� ���¸� ���, ǥ������ ���� ���� �����ϴ� �ȼ����鸸 ǥ���� ����.
	*/
	for (num = 0; num<10; num++) {
		for (j = 0; j < 7; j++) {
			for (i = 0; i<7; i++) {
				if (sample_list[num][j][i] >= avg[num]-sdv_sample[num] && sample_list[num][j][i] <= avg[num]+sdv_sample[num])
					example_list[num][j][i] = 1;
				else example_list[num][j][i] = 0;
			}
		}
	}
	/*
	 �� ���ں� ���̺��� ��հ� ���.
	*/
	for (num = 0; num<10; num++) {
		difvec_sum = 0;
		for (j = 0; j < 7; j++) {
			for (i = 0; i<7; i++) {
				for (pers = 0; pers<PER; pers++) {
					for (k = 0; k < MAX; k++) {
						dif_sum = pow(example_list[num][j][i] - data_set[pers][num][k][j][i], 2.0);
						difvec_sum += sqrt(dif_sum);
						// printf("%.2f ", difvec_sum);
						differ_vector[num] = difvec_sum / (PER*MAX);
						dif_sum = 0;
					}
				}
			}
		}
	}
	/*
	 ���̺��Ͱ��� �л� �� ǥ�� ���
	*/
	dif_sum = 0;
	num = 0;
	while (1) {
		for (j = 0; j < 7; j++) {
			for (i = 0; i<7; i++) {
				for (pers = 0; pers<PER; pers++) {
					for (k = 0; k < MAX; k++) {
						dif_sum = pow(example_list[num][j][i] - data_set[pers][num][k][j][i], 2.0);
						difvec_sum = sqrt(dif_sum);
						difvec_var_sum += pow(difvec_sum-differ_vector[num], 2.0);
						difvec_var[num]= difvec_var_sum / (PER*MAX);
						dif_sum = 0;
						difvec_sum = 0;
					}
				}
			}
		}
		difvec_var_sum = 0;
		difvec_sdv[num] = sqrt(difvec_var[num]);
		printf("%d model's var : %.2f\n ", num, difvec_var[num]);
		printf("%d model's sdv : %.2f\n ", num, difvec_sdv[num]);
		num++;
		if (num >= 10) break;
	}
	for (num = 0; num < 10; num++) {
		printf("%.2f ", differ_vector[num]);
	}
	/*
	�׽�Ʈ �뵵�� ��¹� �̴� �ݺ�����.
	*/
	for (num = 0; num<10; num++) {
		printf("\n");
		for (a = 0; a < 7; a++) {
			printf("\n");
			for (b = 0; b < 7; b++) {
				printf("%.2f ", sample_list[num][a][b]);
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
	// �ҽ��ڵ� ����
	return 0;
}