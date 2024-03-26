#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>
#include<string.h>

struct list {
	double data;
	struct list* next;
};

void push(struct list** head, double data) {
	struct list* new;
	new = (struct list*)malloc(sizeof(struct list));
	if (new == NULL) {
		printf("error malloc");
		exit(-1);
	}
	new->data = data;
	new->next = *head;
	*head = new;
}

double pop(struct list** head) {
	if (*head != NULL) {
		double data = (*head)->data;
		struct list* del = *head;
		*head = (*head)->next;
		free(del);
		return data;
	}
	exit(-1);
}

struct listch {
	char data;
	struct listch* next;
};

void pushchup(struct listch** head, char data) {
	struct listch* new;
	new = (struct listch*)malloc(sizeof(struct listch));
	if (new == NULL) {
		printf("error malloc");
		exit(-1);
	}
	new->data = data;
	new->next = *head;
	*head = new;
}

void pushch(struct listch** head, char data) {
	struct listch* end = *head;
	if (end != NULL) {
		while (end->next != NULL) {
			end = end->next;
		}
	}
	struct listch* new;
	new = (struct listch*)malloc(sizeof(struct listch));
	if (new == NULL) {
		printf("error malloc");
		exit(-1);
	}
	new->data = data;
	new->next = NULL;
	if (*head != NULL) {
		end->next = new;
	}
	else {
		*head = new;
	}
}

void put(struct listch** head, char data) {
	struct listch* end = *head;
	if (end != NULL) {
		while (end->next != NULL) {
			end = end->next;
		}
	}
	struct listch* new;
	new = (struct listch*)malloc(sizeof(struct listch));
	if (new == NULL) {
		printf("error malloc");
		exit(-1);
	}
	new->data = data;
	new->next = NULL;
	if (*head != NULL) {
		end->next = new;
	}
	else {
		*head = new;
	}
}

char get(struct listch** head) {
	if (*head != NULL) {
		char data = (*head)->data;
		struct listch* del = *head;
		*head = (*head)->next;
		free(del);
		return data;
	}
	exit(-1);
}

char popch(struct listch** head) {
	if (*head != NULL) {
		char data = (*head)->data;
		struct listch* del = *head;
		*head = (*head)->next;
		free(del);
		return data;
	}
	exit(-1);
}

void sort(char* f, struct listch** queue, struct listch** stack) {
	int i = 0;
	char c;
	while (i < strlen(f)) {
		if (f[i] == '(') {
			pushchup(stack, f[i]);
		}
		else if (f[i] == ')') {

			c = popch(stack);
			while (c != '(') {
				pushch(queue, c);
				c = popch(stack);
			}
		}
		else if (checkint(f[i])) {
			pushch(queue, f[i]);
		}
		else if (checkop(f[i])) {
			pushch(queue, ' ');
			while (*stack != NULL && priorit(f[i]) <= priorit((*stack)->data)&& (*stack)->data!='(') {
				pushch(queue, popch(stack));
			}
			pushchup(stack, f[i]);
		}
		i++;
	}
	while (*stack != NULL) {
		pushch(queue, popch(stack));
	}
}

void calc(struct listch** queue, struct list** stack) {
	struct listch* temp = NULL;
	double k = 0;
	double tempd = 0, x, y;
	while (*queue != NULL) {
		if (checkint((*queue)->data)) {
			temp = *queue;
			k = 0;
			tempd = 0;
			while (checkint(temp->data)) {
				k++;
				temp = temp->next;
				if (temp->data == '.') {
					break;
				}
			}
			k--;
			while (checkint((*queue)->data)) {
				if ((*queue)->data != '.') {
					tempd += ((*queue)->data - '0') * pow(10, k);
					k--;
				}
				*queue = (*queue)->next;
			}
			push(stack, tempd);
		}
		if ((*queue)->data == '+') {
			x = pop(stack);
			y = pop(stack);
			push(stack, x + y);
		}
		if ((*queue)->data == '-') {
			x = pop(stack);
			if (*stack != NULL) {
				y = pop(stack);
				push(stack, y - x);
			}
			else {
				push(stack, (-1) * x);
			}
		}
		if ((*queue)->data == '*') {
			x = pop(stack);
			y = pop(stack);
			push(stack, x * y);
		}
		if ((*queue)->data == '/') {
			x = pop(stack);
			y = pop(stack);
			if (x == 0) {
				printf("error Del 0");
				exit(-1);
			}
			push(stack, y / x);
		}
		if ((*queue)->data == '^') {
			x = pop(stack);
			y = pop(stack);
			if (x == 0 && y == 0) {
				push(stack, 1);
			}
			push(stack, pow(y, x));
		}
		if ((*queue)->data == '%') {
			x = pop(stack);
			y = pop(stack);
			push(stack, fmod(y,x));
		}
		if ((*queue)->data == '_') {
			x = pop(stack);
			push(stack, (-1) * x);
		}
		*queue = (*queue)->next;
	}
	printf("%.2f", pop(stack));
}

int checkint(char c) {
	if (c >= '0' && c <= '9' || c == '.') return 1;
	return 0;
}

int checkop(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^' || c == '_') return 1;
	return 0;
}

int priorit(char c) {
	if ((c == '+')|| (c == '-')) return 1;
	else if ((c == '*')|| (c == '/') || (c == '%')) return 2;
	else if (c == '^') return 3;
	else if (c == '_') return 4;
	else return 0;
}

void main(int argc, char* argv[]) {
	struct listch* queue = NULL;
	struct listch* stack = NULL;
	char* f = NULL;
	char c;
	int k = 0;
	if (argc == 2) {
		f = (char*)realloc(f, strlen(argv[1])* sizeof(char));
		strncpy(f, argv[1], strlen(argv[1]));
	}
	else {
		while (fread(&c, sizeof(char), 1, stdin) != '\0') {
			if (c == '\n') {
				break;
			}
			f = (char*)realloc(f, (k + 1) * sizeof(char));
			if (f == NULL) {
				printf("error realloc");
				exit(-1);
			}
			f[k] = c;
			k++;
		}
	}
	

	f[k] = '\0';
	int flper = 0, kk = 0;
	char* temp1 = NULL, * temp2 = NULL, in[50], * ff;
	temp2 = (char*)malloc(strlen(f));
	if (temp2 == NULL) {
		printf("error malloc");
		exit(-1);
	}
	strcpy(temp2, f);

	int flag = 0;
	for (int i = 0; i < strlen(f) - 1; i++) {
		if (f[i] == '(' && f[i + 1] == '-') {
			flag = 0;
			for (int j = i + 2; j < strlen(f); j++) {
				if (f[j] == ')') {
					break;
				}
				if (checkint(f[j]))
				{
					break;
				}
				else if (!checkint(f[j])) {
					flag = 1;
					break;
				}
			}
			if (flag == 0) {
				f[i + 1] = '_';
			}
		}
	}

	sort(f, &queue, &stack);
	struct listch* jh = queue, * hh = queue;
	while (jh != NULL) {
		printf("%c", jh->data);
		jh = jh->next;
	}
	printf("\n");
	struct list* stackd = NULL;
	calc(&queue, &stack);
}