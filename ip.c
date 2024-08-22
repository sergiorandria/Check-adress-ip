#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOT_VALID 1
#define VALID 0

int check(char *ip);
int numeric_value(char *s);
char **split_ip_value(char *ip);
int *check_ip_content(char **ip_val);
void get_ip(char ip[]);
void check_ip_range(int *ip);

int main()
{
	char ip[15];
	int *_ip_val = NULL;
	char **ip_val = NULL;
	
	get_ip(ip);
	
	ip_val = split_ip_value(ip);
	
	_ip_val = check_ip_content(ip_val);	
	check_ip_range(_ip_val);
	
	return EXIT_SUCCESS;
}

void get_ip(char ip[])
{
	printf("IP:");
	scanf("%s", ip);
}

int check(char *ip)
{
	int n, value;
	
	n = 0;
	for(size_t i = 0; ip[i] != '\0'; ++i)
	{
		if(ip[i] == '.')	
			++n;
	}
	
	value = (n != 3) ?  NOT_VALID: VALID;
	return value;
}

char **split_ip_value(char *ip)
{
	int n = 0;
	char **ip_val = NULL;

	ip_val = (char **)malloc(4 * sizeof(char *));
	if (!ip_val)
		exit(EXIT_FAILURE);
		
	for(size_t i = 0; i < 4; ++i){
		ip_val[i] = (char *)malloc(10 * sizeof(char));
		if (!ip_val)
			exit(EXIT_FAILURE);
		}
	if (check(ip)){
		printf("Adresse ip non valide");
		exit(EXIT_FAILURE);
	}
	
	char *token = strtok(ip, ".");
	
	strcpy(ip_val[n], token);
	while(token != NULL){
		strcpy(ip_val[n++], token);
		token = strtok(NULL, ".");
		}
	
	return ip_val;
}

int *check_ip_content(char **ip_val)
{
	int err = 0;
	int *_ip_val = NULL;
	
	_ip_val = (int *)malloc(4 * sizeof(int));
	if (!_ip_val)
		exit(EXIT_FAILURE);
	
	for(size_t i = 0; i < 4; ++i){
		if(numeric_value(ip_val[i])){
			err = 1;
			break;
		}
	}
	
	if (!err){
		for(size_t i = 0; i < 4; ++i) 
			_ip_val[i] = atoi(ip_val[i]);
	
		return _ip_val;
	}
	else{
		printf("Adresse IP non valide");
		exit(EXIT_FAILURE);
	}
}

int numeric_value(char *s)
{
	int value = VALID;
	
	for(size_t i = 0; i < strlen(s); ++i){	
			if ((s[i] > '9') || (s[i] < '0')){
				value = NOT_VALID;
				break;
			}
	}

	return value;
}

void check_ip_range(int *ip)
{
	int err = 0;
	
	for(size_t i = 0; i < 4; ++i)
	{
		if (ip[i] > 255 || ip[i] < 0){
			printf("Adresse ip non valide"); 
			err = 1;
			break;
			}
	}
	
	if (!err){
		if (ip[0] <= 127 && ip[0] >= 0)
			printf("La classe est A");
		else if (ip[0] <= 191 && ip[0] >= 128)
			printf("La classe est B");
		else if (ip[0] <= 223 && ip[0] >= 192)
			printf("La classe est C");
		else if (ip[0] <= 239 && ip[0] >= 224)
			printf("La classe est D");
		else if (ip[0] <= 255 && ip[0] >= 240)
			printf("La classe est E");
	}
}

