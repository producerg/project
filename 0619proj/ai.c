#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "data_set.h"
clock_t start, end;

#define FIRSTNUM 3200
#define TSETSET_DATA_NUM 100
#define TESTCNT 1600
#define DATAINDEX_NUM 32
//

static NICE_NUMBER = 0;
#define INPUT_NEURONS 49
#define HIDDEN_NEURONS 10
#define OUTPUT_NEURONS 10

// number of training epochs (iterations)
#define EPOCHS 10
// logistic regression values for backpropagation
const double LR_IH = 0.01;
const double LR_HO = 0.01;
double pattern_error[FIRSTNUM][10];
double rms_error = 0.0;
// vector to store results in hidden layer
double values_hidden_layer[HIDDEN_NEURONS];
double values_out_layer[FIRSTNUM][OUTPUT_NEURONS];
// weight matrices

double weights_HI[HIDDEN_NEURONS][INPUT_NEURONS];
double weights_OH[OUTPUT_NEURONS][HIDDEN_NEURONS];

// arrays to store training data
double input_data[FIRSTNUM][49];
double output_data[FIRSTNUM][OUTPUT_NEURONS]; //10
double get_rand();
int cor_count=0;

void init_data();
void init_weights();
void feed_forward();
void backprop();
void calc_error();

void printOutWeight();


void printOutWeight()
{
	printf("\n");

	for (int i = 0; i < INPUT_NEURONS; i++)
	{
		for (int j = 0; j < HIDDEN_NEURONS; j++)
		{
			printf(" weights_HI[%d][%d] = %f ", j, i, weights_HI[j][i]);
		}
		printf("\n");
	}

	printf("\n");

	for (int k = 0; k < OUTPUT_NEURONS; k++)
	{
		for (int j = 0; j < HIDDEN_NEURONS; j++)
		{
			printf(" weights_OH[%d][%d] = %f ", k, j, weights_OH[k][j]);
		}
		printf("\n");
	}

	printf("\n");
}

void init_data(void)
{
	int temp = 0;
	int count = 0;

	for (int a = 0; a < FIRSTNUM; a++)
	{
		for (int b = 0; b < 10; b++)
		{
			// 아웃풋 데이터 :  
			output_data[a][b] = 0.0;
			//
			pattern_error[a][b] = 0.0;
		}
	}

	for (int a = 0; a < DATAINDEX_NUM; a++)
	{
		for (int b = 0; b < 10; b++)
		{
			for (int c = 0; c < 10; c++)
			{
				output_data[temp][b] = 1.0;
				// weight 수정을 위한 올바른 결과값 저장하기.
				for (int i = 0; i < 7; i++)
				{
					for (int j = 0; j < 7; j++)
					{
						input_data[temp][count] = data_set[a][b][c][i][j];
						count++;
					}
				}
				count = 0;
				temp++;
			}
		}
	}
}

void init_weights(void)
{

	for (int j = 0; j < HIDDEN_NEURONS; j++)
	{
		for (int i = 0; i < INPUT_NEURONS; i++)
		{
			// 입력층~은닉층 사이 웨이트 값 초기화
			weights_HI[j][i] = 0.01;
		}
	}

	for (int k = 0; k < OUTPUT_NEURONS; k++)
	{
		for (int j = 0; j < HIDDEN_NEURONS; j++)
		{
			weights_OH[k][j] = 0.01;
		}
	}
}
// feed the data forward through the neural network
void feed_forward(void)
{
	for (int hidden = 0; hidden < HIDDEN_NEURONS; hidden++)
	{
		values_hidden_layer[hidden] = 0.0;
		// matrix multiplication of inputs and weights
		for (int input = 0; input < INPUT_NEURONS; input++)
		{
			values_hidden_layer[hidden] = values_hidden_layer[hidden] + (input_data[NICE_NUMBER][input] * weights_HI[hidden][input]);
		}
		// activation functioninp
		//printf("values_hidden_layer[%d] = %f\n", hidden,values_hidden_layer[hidden]);
		values_hidden_layer[hidden] = tanh(values_hidden_layer[hidden]);
		//tanh 시그모이드 함수랑 비슷함
	}
	//----------------------------------------------------------------------

	for (int output = 0; output < OUTPUT_NEURONS; output++)
	{
		values_out_layer[NICE_NUMBER][output] = 0.0;
		// matrix multiplication of inputs and weightsa
		for (int hidden = 0; hidden < HIDDEN_NEURONS; hidden++)
		{
			values_out_layer[NICE_NUMBER][output] = values_out_layer[NICE_NUMBER][output] + (values_hidden_layer[hidden] * weights_OH[output][hidden]);
		}
		// activation function
		values_out_layer[NICE_NUMBER][output] = tanh(values_out_layer[NICE_NUMBER][output]);
		//printf("values_out_layer[%d] = %f\n", output, values_out_layer[output]);
	}
	//printf("\n");

	for (int output = 0; output < OUTPUT_NEURONS; output++)
	{
		pattern_error[NICE_NUMBER][output] = values_out_layer[NICE_NUMBER][output] - output_data[NICE_NUMBER][output];
		//printf("pattern_error[%d][%d] = %f\n", NICE_NUMBER,output, pattern_error[NICE_NUMBER][output]);
		//output_data는 기존에 이미 설정해둔 값
		// 0 1 0 0 0 0 0 0 0 0 => 1
	}
	//printf("\n");

} // NICE_NUMBER

  // backpropagation algorithm to update the weights

void backprop(void)
{
	// update weights between hidden and output layer
	for (int output = 0; output < OUTPUT_NEURONS; output++)
	{
		for (int hidden = 0; hidden < HIDDEN_NEURONS; hidden++)
		{
			// update weight matrix
			double weightChange = LR_HO * pattern_error[NICE_NUMBER][output] * values_hidden_layer[hidden];
			weights_OH[output][hidden] = weights_OH[output][hidden] - weightChange;
			// regularisation on the output weights
		}
	}

	// update weights between input and hidden layer
	double sum = 0.0;
	for (int hidden = 0; hidden < HIDDEN_NEURONS; hidden++)
	{
		for (int input = 0; input < INPUT_NEURONS; input++)
		{
			// update weight matrix
			for (int output = 0; output < OUTPUT_NEURONS; output++)
			{
				sum = sum + (weights_OH[output][hidden] * pattern_error[NICE_NUMBER][output]);
			}
			double weightChange = ((1 - (values_hidden_layer[hidden] * values_hidden_layer[hidden])) * sum * LR_IH) * input_data[NICE_NUMBER][input];
			weights_HI[hidden][input] = weights_HI[hidden][input] - weightChange;
		}

	}
} // NICE_NUMBER

  // calculate the overall network error
void calc_error(void)
{
	int max_index = 0;
	for (int i = 0; i < FIRSTNUM; i++)
	{
		double max = values_out_layer[i][0];
		max_index = 0;
		for (int output = 0; output < OUTPUT_NEURONS; output++)
		{
			if (max < values_out_layer[i][output])
			{
				max = values_out_layer[i][output];
				max_index = output;
			}
		}
		//printf("*%d* 현재의 max_index => %d\n", i,max_index);
		if (output_data[i][max_index] == 1)
		{
			//printf("%d. 맞습니다!\n", cor_count);
			cor_count++;
		}
	}
	rms_error = ((double)cor_count / (double)3200);
	printf("인식률은 %.2f입니다.\n", rms_error);

}


int main(void)
{

	// seed random number function
	srand(time(NULL));

	// initialise data set with inputs and target outputs for supervised learning
	init_data();

	// initialise the weights with random values
	init_weights();

	/*
	for (int a = 0; a < FIRSTNUM; a++)
	{
	for (int b = 0; b < 10; b++)
	{
	printf(" #[%d] :output_data[%d][%d] = %f\n", a, a, b, output_data[a][b]);
	}
	printf("\n");
	}
	*/
	/*
	for (int a = 0; a < TSETSET_DATA_NUM; a++)
	{
		printf(" #[%d]\n", a);
		for (int b = 0; b < 49; b++)
		{
			if (b % 7 == 0) printf("\n");
			printf(" %f ", input_data[a][b]);
		}
		printf("\n");
	}

	*/

	/*
	printOutWeight();
	for (int j = 0; j <= 30; j++)
	{
	for (int i = 0; i < 3200; i++)
	{
	// feed the data forward
	feed_forward();

	// update the weights
	backprop();
	//printOutWeight();
	NICE_NUMBER++;
	printf(" NICE = %d \n", NICE_NUMBER);
	}
	NICE_NUMBER = 0;
	}

	printOutWeight();
	*/



	// train the neural network
	for (int j = 0; j <= EPOCHS; j++)
	{
		for (int i = 0; i < TESTCNT; i++)
		{
			// feed the data forward
			feed_forward();

			// update the weights
			backprop();
			NICE_NUMBER++;
			// 0 - FIRSTNUM까지
		}
		NICE_NUMBER = 0;
		// calculate the overall network error
	//	calc_error();

		// display no of epoch and overall error
		// printf("epoch = %d RMS Error = %f\n", j, rms_error);
	}//epoh만큼 돌리기

	 // training has finished, stop timer

	init_data();

	calc_error();

	// display the results
	/*
	printf("---------------------------------- \n");
	for (int i = 0; i < TSETSET_DATA_NUM; i++)
	{
		for (int output = 0; output < OUTPUT_NEURONS; output++)
		{
			printf("values_out_layer[%d] = %.2f, actual output[%d] = %.2f\n", i, values_out_layer[i][output], i, output_data[i][output]);
		}
		printf("\n");
	}
	*/


	return 0;

}