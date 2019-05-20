#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include "data_set.h"		// 비교를 위한 데이터가 들어가는 헤더파일.

#define PER 32				// 전체 데이터 입력한 인공지능 수강자 숫자.
#define MAX 10				// 각 숫자 별 모델 입력 수
#define PIXELNUM 49			// 7x7행렬의 픽셀 수

int main(void) {

	double  sample_list[10][7][7];	// 숫자별 대표 샘플이 들어가기 위한 자리.
	double avg[10];				// 대표 모델을 만들기 위한 과정에서 문턱치값 만들 변수.
	double var[10];					// 전체 샘플데이터의 분산.
	double sdv_sample[10];			// 샘플데이터의 전체 표준편차값 담은 변수.
	int example_list[10][7][7];		// 대표 모델 0~9

	int a, i, j, l = 0;		// 반복문 돌리기 위한 변수.
	int k = 0;				// 역시 반복문 돌리는 용도의 변수.
	int pers = 0;			// 반복문 돌리는 변수인데, 여기서 데이터 넣은 사람 숫자.
	int num = 0;			// 배열 맨 앞에 숫자를 판독.
	int sum = 0;			// 각각의 배열인덱스값을 더해주기 위한~
	double avg_sum = 0;	// 평균 구하기 위한 변수
	double var_sum = 0;		// 분산 구하기 위한 변수
	double dif_sum = 0;
	double differ_vector[10];	// 차이벡터 평균값
	double difvec_sum = 0;		// 차이벡터 구하는 과정에서 더하는 변수를 담는 변수.
	double difvec_var[10];
	double difvec_sdv[10];	// 차이벡터값의 표준편차
	double difvec_var_sum = 0;
	int b = 0;				// 테스트 목적의 변수. 최종 구동 확인되면 지움.
	int cnt = 0;			// 판독률 판정을 위한 변수.

	// 전체 입력받은 데이터 샘플 중 그걸 일단 전체를 더해볼거임.
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
	위에서 샘플데이터를 만들기 위한 배열값을 더하고 난 것을, 각각 숫자의 샘플데이터 숫자로 나눔.
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
	// 여기까지 했으면, 대표샘플 데이터 만드는것까지는 완성됨.

	/*
	평균값 필터를 적용하기 위한 셋업작업 : 평균값 구하기
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
		printf("%d(%.2f) ", num, avg[num]);	// 멀쩡히 값 들어가는거 확인하면 지운다.
		num++;
		if (num >= 10) break;
	}
	/*
	 통계적 보정을 위해 : 분산값과 표준편차값 사용
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
	 전체 샘플들의 입력 상태를 고려, 표본오차 범위 내에 존재하는 픽셀값들만 표본에 남김.
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
	 각 숫자별 차이벡터 평균값 출력.
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
	 차이벡터값의 분산 및 표준 출력
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
	테스트 용도의 출력문 뽑는 반복구문.
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
	테스트 용도의 출력문 뽑는 반복구문.
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
	// 소스코드 종료
	return 0;
}