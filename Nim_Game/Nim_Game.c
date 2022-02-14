#include <stdio.h>
#include<stdbool.h>

void Print_stack_size(int arr[])
{
	int temp = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = i + 1; j < 3; j++) {
			if (arr[j] < arr[i]) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	printf("Packet sizes are :");
	for (int i = 0; i < 3; i++)
	{
		printf(" %d ", arr[i]);
	}
	printf("\n");
}
void Player(int arr[]) {
	int index;
	printf("Choose the stack (1 or 2 or 3): \n");
	scanf_s("%d", &index);
	if (arr[0] == 0 || arr[1] == 0) {
		printf("you cant turn this stack!\n");
	}
	while (index != 1 && index != 2 && index != 3) {
			printf("Wrong input , try again : \n");
			printf("Choose the stack (1 or 2 or 3): \n");
			scanf_s("%d", &index);
	}
	int new_stack;
	printf("Turn the stack to :\n");
	scanf_s("%d", &new_stack);
	while (0>new_stack||new_stack >= arr[index - 1]) {
		printf("Wrong input , try again :\n");
		printf("Turn the stack to :\n");
		scanf_s("%d", &new_stack);
	}
	arr[index - 1] = new_stack;
	Print_stack_size(arr);
}

void Comp(int arr[]) {
	if (arr[0] == 0 && arr[1] == 0 && arr[2]>1) {
		printf("I turned %d to 1 :\n", arr[2]);
		arr[2] = 1;
	}
	else if (arr[0] == 0 && arr[1] == 1 && arr[2]>=1) {
		printf("I turned %d to 0 :\n", arr[2]);
		arr[2] = 0;
	}
	else if (arr[0] == 1 && arr[1] == 1 && arr[2] > 1) {
		printf("I turned %d to 1 :\n", arr[2]);
		arr[2] = 1;
	}
	else if (arr[0] == 1 && arr[1] == 1 && arr[2] == 1) {
		Player(arr);
		printf("I turned %d to 0:\n", arr[2]);
		arr[2] =0;
	}
	else if (arr[0] == 0 && arr[1] == 0 && arr[2] == 1) {
		printf("You lost , Game Over:\n");
	}
	else if ((arr[0] == arr[1] || arr[1] == arr[2]) && arr[1] > 1) {
		if (arr[0] == arr[1]) {
			printf("I turned %d to 0:\n", arr[2]);
			arr[2] = 0;
		}
		else {
			printf("I turned %d to 0:\n", arr[1]);
			arr[1] = 0;

		}
	}
	else if (arr[0]+arr[1]<arr[2]) {
		int sum = arr[0] +arr[1];
		printf("I turned %d to %d :\n", arr[2], sum);
		arr[2] = sum;
	}
	else {
		printf("I turned %d to %d :\n", arr[2], (arr[1] - arr[0]));
		arr[2] = arr[1] - arr[0];

	}
	Print_stack_size(arr);
}
int Win(int arr[]) {
	if (arr[0] + arr[1] + arr[2]== 1) {
		printf("Game over! \n");
		return 1;
	}
	else return 0;
}
int main() {
	int x, y, z;
	printf("Please enter 3 numbers \n");
	scanf_s("%d %d %d", &x, &y, &z);
	int arr[] = { x,y,z };
	while (x<0 || y<0 || z<0||isdigit(x)|| isdigit(y)|| isdigit(z)) {
		printf("Wrong input , try again :\n");
		printf("Please enter 3 numbers \n");
		scanf_s("%d %d %d", &x, &y, &z);
		int arr1[] = { x,y,z };

	}
	int check = x + y + z;
	while (check <= 0) {
		printf("Wrong input , try again :\n");
		printf("Please enter 3 numbers \n");
		scanf_s("%d %d %d", &x, &y, &z);
		int arr[] = { x,y,z };
	}
	Print_stack_size(arr);

	if (!(arr[0] + arr[1] == arr[2]))
	{
		 {
			Player(arr);
			while (arr[0] + arr[1] + arr[2] > 1)
			{
				Comp(arr);
				if (Win(arr) == 1)
				{
					printf("You lost!");
					break;
				}
				Player(arr);
				if (Win(arr) == 1)
				{
					printf("You win!");
					break;
				}
			}
		}
	}
	else
	{
		while (arr[0] + arr[1] + arr[2]>1) {
			Player(arr);
			if (Win(arr) == 1)
			{
				printf("You win!");
				break;
			}
			Comp(arr);
			if (Win(arr) == 1)
			{
				printf("You lost!");
				break;
			}
		}
	}

	return 0;
}



