#include <stdio.h>
#include "data_set.h"

#define PER 32			// 데이터 입력 인원
#define MAX 10			// 측정 숫자 개수

void main() {
	double vertical_vec[10];			// 0~9 각각의 종축벡터값(특징 1.)
	double horizontal_vec[10];		// 0~9 각각의 횡축벡터값(특징 2.)
	int cnt = 0;									// 종, 횡축 벡터값 측정을 위한 변수.

	/*
		이하 : 반복문 돌리는 개별변수
	*/
	int i = 0;
	int j = 0;
	int k = 0;
	// 함수

	/*
		VERTICAL 벡터 연산. (특징 1)
	*/

	/*
		HORIZONTAL 벡터 연산. (특징 2)
	*/

	/*
		구획을 나누어 영역별로 가중치 값 따로 연산(특징 3)
	*/
}