#include <stdio.h>
#include <stdlib.h> 
#include "data_set.h"		// 비교를 위한 데이터가 들어가는 헤더파일.

#define PER 32					// 전체 데이터 입력한 인공지능 수강자 숫자.
#define MAX 10					// 각 숫자 별 모델 입력 수
#define THERSOLD 0.4		// 배열 인덱스 값의 합을 나누기 330 한것의 판독기준값.

int main(void) {
														
	double  sample_list[10][7][7];	// 숫자별 대표 샘플이 들어가기 위한 자리.
	int thres[10];						// 대표 모델을 만들기 위한 과정에서 문턱치값 만들 변수.
	int example_list[10][7][7];		// 대표 모델 0~9
	int insertarray_Crit[7][7];		// 비교하기 위해 입력받을 배열을 담을 변수.
	
	int a, i, j, l = 0;		// 반복문 돌리기 위한 변수.
	int k = 0;					// 역시 반복문 돌리는 용도의 변수.
	int pers = 0;			// 반복문 돌리는 변수인데, 여기서 데이터 넣은 사람 숫자.
	int num = 0;			// 배열 맨 앞에 숫자를 판독.
	int sum = 0;			// 각각의 배열인덱스값을 더해주기 위한~
	int thres_sum = 0;
	int b = 0;				// 테스트 목적의 변수. 최종 구동 확인되면 지움.

	/*
	printf("0과 1을 만을 활용하여 비교할 숫자 이미지를 입력하십시오. : \n");
	for (l = 0; l < 7; l++) {
		for (k = 0; k < 7; k++) {
			scanf("%d", &insertarray_Crit[l][k]);
		}
	}
	*/
	/*
		여기만 일단 손보면 되네
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
		평균값 필터를 적용하기 위한 셋업작업 : 스레숄드 세팅
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
		위에서 샘플데이터를 만들기 위한 배열값을 더하고 난 것을, 각각 숫자의 샘플데이터 숫자로 나눔.
		이때 스레숄드 값을 지정해서, 대표샘플 배열에 0,1 형태로만 데이터를 남김.
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
	// 여기까지 했으면, 대표샘플 데이터 만드는것까지는 완성됨.

	/* 
		테스트 용도의 출력문 뽑는 반복구문.
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

	return 0;
}