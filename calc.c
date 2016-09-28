#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sum(int a, int b) //somma 2 numeri
{
	return a+b;
}

int diff(int a, int b) //sottrae b da a
{
	return a-b;
}

int mult(int a, int b) //moltiplica 2 numeri
{
	return a*b;
}

int divs(int a, int b) //compie la divisione a/b
{
	return a/b;
}

int is_num(char c) //ritorna TRUE se il carattere inserito e un numero
{				   //ritorna FALSE se il carattere non e un numero
	int a=c;
	if (a>47 && a<58)
		return 1;
	else
		return 0;
}

int is_sign(char c) //ritorna TRUE se il carattere inserito e un operatore matematico
{					//ritorna FALSE se il carattere inserito non e un operatore matematico
 	if (c=='+' || c=='-' || c=='*' || c=='/')
		return 1;
	else
		return 0;
}

int is_letter(char c) //ritorna TRUE se il carattere inserito e una lettera
{					  //ritorna FALSE se il carattere inserito non e una lettera
	if (!is_sign(c) && !is_num(c))
		return 1;
	else
		return 0;
}

int char_count(char* string) //Ritorna il numero di caratteri contenuti nel parametro string
{
	int i=0,cont=0;
	while(string[i]!='\0')
	{
		cont++;
		i++;
	}
	return cont;
}

char* get_expr() //prende in input una espressione da tastiera
{
	char* expr, *temp;
	int cont=0;
	
	temp=(char*)malloc(sizeof(char)*100);
	printf("Inserisci un'espressione: \n");
	scanf("%s",temp);
	cont=char_count(temp);
	expr=(char*)malloc(sizeof(char)*cont);
	expr=strdup(temp);
	free(temp);
	return expr;
}

int get_num(char* expr, int* expr_index) //ritorna il primo numero all'interno di expr, a partire da expr_index
{
	int num_index=0;
	char* temp_num;
	int digit_count=0;
	int num;
	temp_num=(char*)malloc(sizeof(char)*100);
	while(is_num(expr[*expr_index]))
		{
			temp_num[num_index]=expr[*expr_index];
			(*expr_index)++;
			num_index++;
		}
		digit_count=char_count(temp_num);
		temp_num=(char*)realloc(temp_num,sizeof(char)*(digit_count+1));
		num=atoi(temp_num);
		return num;
}

char* get_expr_par(char* expr, int* expr_index)
{
	char* temp_num;
	int num_index;
	int par_cont=0, par_ide=0;
	int digit_count=0;

	(*expr_index)++;
	temp_num=(char*)malloc(sizeof(char)*100);
	num_index=*expr_index;
	while(expr[*expr_index]!=')')
	{
		if(expr[*expr_index]=='(')
			par_cont++;
		(*expr_index)++;
	}
	*expr_index=num_index;
	num_index=0;
	while(expr[*expr_index]!=')' || par_ide!=par_cont)
	{
		if(expr[*expr_index]==')')
			par_ide++;
		temp_num[num_index]=expr[*expr_index];
		num_index++;
		(*expr_index)++;
	}
	(*expr_index)++;
	digit_count=char_count(temp_num);
	temp_num=(char*)realloc(temp_num,sizeof(char)*(digit_count+1));
	return temp_num;
}

int solve(char* expr) //Risolve una qualsiasi espressione contenente somma,sottrazione,moltiplicazione,divisione e parentesi (da mettere tutte tonde)
{
	char sign='+';
	int res=0;
	char nxt_sign='+';
	int expr_index=0, num_index=0;
	int digit_count=0;
	int num,multiplier;
	int temp_res=0;

	while(expr[expr_index]!='\0')
	{
		if (is_sign(expr[expr_index]))
			{
				sign=expr[expr_index];
				expr_index++;
			}
		num=get_num(expr,&expr_index);
		nxt_sign=expr[expr_index];
		temp_res=num;
		if(expr[expr_index]=='(')
		{
			temp_res=solve(get_expr_par(expr,&expr_index));
		}
		while(nxt_sign=='*' || nxt_sign=='/')
		{
			expr_index++;
			multiplier=get_num(expr,&expr_index);
			if(expr[expr_index]=='(')
			{
				multiplier=solve(get_expr_par(expr,&expr_index));
			}
			if(nxt_sign=='*')
				temp_res=mult(temp_res,multiplier);
			if(nxt_sign=='/')
				temp_res=divs(temp_res,multiplier);
			nxt_sign=expr[expr_index];
		}
		num=temp_res;
		if(sign=='+')
			res=sum(res,num);
		if(sign=='-')
			res=diff(res,num);
		num_index=0;
	}
	return res;
}

void main()
{
	printf("Risultato: %i\n",solve(get_expr()));
}