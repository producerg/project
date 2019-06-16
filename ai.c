#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "data_set.h"

// to measure runtime
/*
	이건 원 소스코드 저자가 측정 시간을 테스트하기위해 넣은 함수
	우리는 사용하지 않아도 됨.
*/
clock_t start, end;
double cpu_time_used;

// number of input neurons(입력층 개수)
#define NO_INPUT_NEURONS 3
// number of neurons in hidden layer(은닉층 개수)
#define NO_HIDDEN_NEURONS 8
// 4 sets of inputs paired with their target outputs in XOR problem(출력층 개수)
#define NO_PATTERNS 4

// number of training epochs (iterations)
/*
	epochs : 전체 데이터 이용, 한 바퀴 돌며 학습하는 것을 말함.
	여기서 epochs의 no를 200으로 설정하였으니 전체 데이터셋을 200바퀴 돌아 학습.
*/
const int no_epochs = 200;

// logistic regression values for backpropagation
// 역전파 로지스틱 회귀 웨이트
const double LR_IH = 0.7;
const double LR_HO = 0.07;

// single output neuron
double actual_output = 0.0;
// other variables
int pattern_no = 0;
double pattern_error = 0.0;
double rms_error = 0.0;

// vector to store results in hidden layer
// 입력층->은닉층 순서로 갔을 때 결과값 저장할 내용.
double values_hidden_layer[NO_HIDDEN_NEURONS];

// weight matrices
// 웨이트 값 저장되는 배열
double weights_IH[NO_INPUT_NEURONS][NO_HIDDEN_NEURONS];
// 입력층~은닉층 사이 웨이트(이차원)
double weights_HO[NO_HIDDEN_NEURONS];
// 은닉층~입력층 사이 웨이트

// arrays to store training data
// 학습 데이터를 저장할 배열 선언
int input_data[NO_PATTERNS][NO_INPUT_NEURONS];
int output_data[NO_PATTERNS];				// 출력층 데이터 0~9까지 입력되도록 함.

											// ann functions
/*
	함수 선언
*/
double get_rand();
void init_data();
void init_weights();
void feed_forward();
void backprop();
void calc_error();

// random number for first init of matrices
double get_rand(void)
{
	return ((double)rand()) / (double)RAND_MAX;
}

// init input and output data to learn XOR problem
// 기존 소스코드는 xor 문제를 풀어나가는 방식으로 해결함. 인풋데이터는 2차원 배열 방식이였음
void init_data(void)
{	// 초기 데이터, 즉 목표하려는 데이터 입력함.
	printf("initialising data... \n");

	// 0 XOR 0 = 0
	input_data[0][0] = -1;	// input x
	input_data[0][1] = -1; 	// input y
	input_data[0][2] = 1;  	// additional bias neuron
	output_data[0] = -1;	// target output

							// 0 XOR 1 = 1
	input_data[1][0] = -1;
	input_data[1][1] = 1;
	input_data[1][2] = 1;
	output_data[1] = 1;

	// 1 XOR 0 = 1
	input_data[2][0] = 1;
	input_data[2][1] = -1;
	input_data[2][2] = 1;
	output_data[2] = 1;

	// 1 XOR 1 = 0
	input_data[3][0] = 1;
	input_data[3][1] = 1;
	input_data[3][2] = 1;
	output_data[3] = -1;
}

// init weights with random values
// 각 웨이트를 랜덤값으로 정의함.(초기화)
void init_weights(void)
{
	for (int j = 0; j < NO_HIDDEN_NEURONS; j++)
	{	// 은닉층~출력층 사이의 웨이트.
		weights_HO[j] = (get_rand() - 0.5) / 2;

		for (int i = 0; i < NO_INPUT_NEURONS; i++)
		{	/* 
				입력층~은닉층 사이 웨이트
			*/
			weights_IH[i][j] = (get_rand() - 0.5) / 5;
		}
	}
}

// feed the data forward through the neural network
// 정방향으로 신경망에 데이터를 입력.
void feed_forward(void)
{
	int i = 0;
	for (i = 0; i < NO_HIDDEN_NEURONS; i++)
	{
		values_hidden_layer[i] = 0.0;

		// matrix multiplication of inputs and weights
		// 인풋과 웨이트의 행렬곱.
		for (int j = 0; j < NO_INPUT_NEURONS; j++)
		{
			values_hidden_layer[i] += input_data[pattern_no][j] * weights_IH[j][i];
		}

		// activation function
		values_hidden_layer[i] = tanh(values_hidden_layer[i]);
	}

	// value of output neuron
	actual_output = 0.0;

	for (i = 0; i < NO_HIDDEN_NEURONS; i++)
	{
		actual_output += values_hidden_layer[i] * weights_HO[i];
	}
	// calculate error for this pattern
	// 입력 패턴에 대한 에러 계산.
	pattern_error = actual_output - output_data[pattern_no];
}

// backpropagation algorithm to update the weights
// 웨이트 갱신을 위한 역전파 알고리즘
void backprop(void)
{
	// update weights between hidden and output layer
	// 은닉층~출력층 사이의 웨이트 수정.
	for (int m = 0; m < NO_HIDDEN_NEURONS; m++)
	{
		// update weight matrix
		// 웨이트에 해당하는 행렬 데이터 값 갱신
		double weightChange = LR_HO * pattern_error * values_hidden_layer[m];
		weights_HO[m] -= weightChange;

		// regularisation on the output weights
		if (weights_HO[m] < -5)
		{
			weights_HO[m] = -5;
		}
		else if (weights_HO[m] > 5)
		{
			weights_HO[m] = 5;
		}
	}

	// update weights between input and hidden layer
	// 입력층~은닉층의 웨이트 값 갱신
	for (int i = 0; i < NO_HIDDEN_NEURONS; i++)
	{
		for (int k = 0; k < NO_INPUT_NEURONS; k++)
		{
			// update weight matrix
			/*
				웨이트 행렬값 갱신
			*/
			double weightChange = ((1 - (values_hidden_layer[i] * values_hidden_layer[i])) * weights_HO[i] * pattern_error * LR_IH) * input_data[pattern_no][k];
			weights_IH[k][i] -= weightChange;
		}
	}
}

// calculate the overall error 
void calc_error(void)
{
	rms_error = 0.0;

	// calculate error for each pattern
	for (int i = 0; i < NO_PATTERNS; i++)
	{
		pattern_no = i;
		feed_forward();
		rms_error += pattern_error * pattern_error;
	}

	// square root error
	rms_error = sqrt(rms_error / NO_PATTERNS);
}


int main(void)
{
	// seed random number function
	srand(time(NULL));

	// initialise data set with inputs and target outputs for supervised learning
	init_data();

	// initialise the weights with random values
	init_weights();

	// start timer
	start = clock();

	// train the neural network
	// 신경망에 학습 시킴
	for (int j = 0; j <= no_epochs; j++)
	{
		for (int i = 0; i < NO_PATTERNS; i++)
		{
			// select one of the patterns as input and target output
			pattern_no = rand() % NO_PATTERNS;

			// feed the data forward
			feed_forward();

			// update the weights
			backprop();
		}

		// calculate the overall network error
		calc_error();

		// display no of epoch and overall error
		printf("epoch = %d RMS Error = %f\n", j, rms_error);
	}

	// training has finished, stop timer
	end = clock();

	// display the results
	printf("---------------------------------- \n");
	for (int i = 0; i < NO_PATTERNS; i++)
	{
		pattern_no = i;
		feed_forward();
		printf("target output = %d, actual output = %f\n", output_data[pattern_no], actual_output);
	}
	// 이건 쌩까도 되는거 : 측정(학습 시간) 계산 함수 
	// display time elapsed for training
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("----------------------------------\n");
	printf("time: %f sec \n", cpu_time_used);
	printf("----------------------------------\n");

	return 0;
}