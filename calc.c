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
	int a=c;
	if((a>64 && a<91) || (a>96 && a<123))
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

int solve(char* expr) //Risolve una qualsiasi espressione contenente somma,sottrazione,moltiplicazione,divisione intera e parentesi (da mettere tutte tonde)
{
	char sign='+';
	int res=0;
	char nxt_sign='+';
	int expr_index=0, num_index=0;
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

char chg_sign(char sign)
{
	if(sign=='+')
		return '-';
	else
		return '+';
}

int digit_counter(int num)
{
	int digit_count=0;

	if(num==0)
		return 1;
	while(num!=0)
	{
		digit_count++;
		num=num/10;
	}
	return digit_count;
}

char* i_to_char(int num)
{
	int digit_count;
	int* digits;
	char* string;
	int index;
	char digit;
	int negative=0;

	digit_count=digit_counter(num);
	digits=(int*)malloc(sizeof(int)*digit_count);
	index=digit_count-1;
	if(num<0)
	{
		negative=1;
		digit_count++;
	}
	while(index>=0)
	{
		if(negative)
			digits[index]=-num%10;
		else
			digits[index]=num%10;
		num=num/10;
		index--;
	}
	string=(char*)malloc(sizeof(char)*(digit_count+1));
	for(index=0;index<digit_count;index++)
	{
		digit=digits[index]+'0';
		string[index]=digit;
	}
	if(negative)
	{
		while(index>0)
		{
			index=digit_count-1;
			string[index]=string[index-1];
			index--;
		}
		string[index]='-';
	}
	return string;
}

char* get_unknown(char* equa, int* equa_index)
{
	int unk_index=0;
	char* unknown;
	int chars=0;

	unknown=(char*)malloc(sizeof(char)*100);
	while(is_letter(equa[(*equa_index)]))
	{
		unknown[unk_index]=equa[(*equa_index)];
		(*equa_index)++;
		unk_index++;
	}
	chars=char_count(unknown);
	unknown=(char*)realloc(unknown,sizeof(char)*(chars+1));
	return unknown;
}

struct unknowns
{
	char* unknown;
	int coeff;
	char sign;
	struct unknowns* next;
};

char* get_pol_unk(char* expr, int* expr_index)
{
	int unk_index=0;
	char* unknown;
	int chars=0;

	unknown=(char*)malloc(sizeof(char)*100);
	while(is_letter(expr[(*expr_index)]))
	{
		unknown[unk_index]=expr[(*expr_index)];
		(*expr_index)++;
		unk_index++;
		if(expr[(*expr_index)]=='^')
		{
			unknown[unk_index]='^';
			(*expr_index)++;
			unk_index++;
			unknown[unk_index]=expr[(*expr_index)];
			(*expr_index)++;
			unk_index++;
		}
	}
	chars=char_count(unknown);
	unknown=(char*)realloc(unknown,sizeof(char)*(chars+1));
	return unknown;
}

void mon_insert(struct unknowns** head, int num, char* unknown,char sign, int is_mon)
{
	struct unknowns* new;

	if((*head)==NULL || strcmp(unknown,(*head)->unknown)>0)
	{
		new=(struct unknowns*)malloc(sizeof(struct unknowns));
		new->coeff=num;
		if(is_mon)
			new->unknown=strdup(unknown);
		else
			new->unknown=strdup("\0");
		new->sign=sign;
		new->next=(*head);
		(*head)=new;
		//printf("Inserito\n");
	}
	else if(strcmp(unknown,(*head)->unknown)==0)
		 {
		 	if((*head)->sign=='-')
		 		(*head)->coeff=-(*head)->coeff;
		 	if(sign=='+')
		 		(*head)->coeff=sum((*head)->coeff,num);
		 	if(sign=='-')
		 		(*head)->coeff=diff((*head)->coeff,num);
		 	if((*head)->coeff>0)
		 	{
		 		(*head)->sign='+';
		 	}
		 	if((*head)->coeff<0)
		 	{
		 		(*head)->sign='-';
		 		(*head)->coeff=-(*head)->coeff;
		 	}
		 }
		 else
		 {
		 	mon_insert(&((*head)->next),num,unknown,sign,is_mon);
		 	//printf("Ritentiamo");
		 }
}

void print_pol(struct unknowns* head)
{
	char* polinomial;
	int char_cont=0;

	polinomial=(char*)malloc(sizeof(char)*100);
	while(head!=NULL)
	{
		if(head->coeff!=0)
		{
			polinomial=strcat(polinomial,(char[2]){(char)head->sign,'\0'});
			polinomial=strcat(polinomial,i_to_char(head->coeff));
			polinomial=strcat(polinomial,head->unknown);
		}
		head=head->next;
	}
	polinomial=strcat(polinomial,"=0");
	char_cont=char_count(polinomial);
	polinomial=(char*)realloc(polinomial,sizeof(char)*(char_cont+1));
	printf("%s\n",polinomial);
}

struct unknowns* polinomial_expr(char* expr)
{
	int expr_index=0;
	char sign='+';
	struct unknowns* monomials=NULL;
	int num=0;
	int chg=0;
	char nxt_sign;
	char* unknown;
	int is_mon;

	while(expr[expr_index]!='\0')
	{
		is_mon=0;
		if(is_sign(expr[expr_index]))
		{
			sign=expr[expr_index];
			expr_index++;
		}
		num=get_num(expr,&expr_index);
		if(num==0 && is_letter(expr[expr_index]))
			num=1;
		unknown=strdup("\0");
		if(is_letter(expr[expr_index]))
		{
			unknown=get_pol_unk(expr,&expr_index);
			is_mon=1;
		}
		nxt_sign=expr[expr_index];
		if(chg)
			sign=chg_sign(sign);
		mon_insert(&monomials,num,unknown,sign,is_mon);
		if(expr[expr_index]=='=')
		{
			chg=1;
			expr_index++;
			sign='+';
		}
		//printf("num: %i\nexpr: %c\nunknown: %s\npolinomial: %s\n",num,expr[expr_index],unknown,monomials->unknown);
	}
	return monomials;
}

char* solve_equation(char* equation)
{
	int coeff=0;
	char* unknown;
	int res=0;
	int equa_index=0;
	char sign='+';
	int num=0;
	int chg=1;
	char nxt_sign;
	int digit_count=0;
	char* answer;
	int temp_res;
	char* mult_unk;
	int is_mon=0,mult_mon=0;
	int grade=0;
	int multiplier=0;

	while(equation[equa_index]!='\0')
	{
		is_mon=0;
		mult_mon=0;
		grade=0;
		if(is_sign(equation[equa_index]))
		{
			sign=equation[equa_index];
			equa_index++;
		}
		num=get_num(equation,&equa_index);
		if(num==0 && is_letter(equation[equa_index]))
			num=1;
		if(is_letter(equation[equa_index]))
		{
			unknown=get_unknown(equation,&equa_index);
			is_mon=1;
			grade++;
		}
		nxt_sign=equation[equa_index];
		//printf("nxt_sign: %c\n",nxt_sign);
		temp_res=num;
		while(nxt_sign=='*' || nxt_sign=='/')
		{
			equa_index++;
			multiplier=get_num(equation,&equa_index);
			if(is_letter(equation[equa_index]))
			{
				mult_mon=1;
				mult_unk=get_unknown(equation,&equa_index);
			}
			if(nxt_sign=='*')
			{
				temp_res=mult(temp_res,multiplier);
				if(mult_mon)
					grade++;
			}
			if(nxt_sign=='/')
			{
				temp_res=divs(temp_res,multiplier);
				if(mult_mon)
					grade--;
			}
			nxt_sign=equation[equa_index];
		}
		//printf("grade: %i\n",grade);
		if(grade>0)
			is_mon=1;
		else
			is_mon=0;
		//printf("sign PRIMA: %c\n",sign);
		if((chg && !is_mon) || (!chg && is_mon))
			sign=chg_sign(sign);
		num=temp_res;
		if(sign=='+')
			if(is_mon)
				coeff=sum(coeff,num);
			else
				res=sum(res,num);
		if(sign=='-')
			if(is_mon)
				coeff=diff(coeff,num);
			else
				res=diff(res,num);
		if(equation[equa_index]=='=')
		{
			chg=0;
			sign='+';
			equa_index++;
		}
		//printf("num: %i\nsign: %c\nmon: %i\nres: %i\n",num,sign,is_mon,res);
	}
	//printf("coeff: %i\n",coeff);
	res=divs(res,coeff);
	//printf("RES: %i\n",res);
	answer=(char*)malloc(sizeof(char)*100);
	answer=strcat(answer,unknown);
	answer=strcat(answer,"=");
	answer=strcat(answer,i_to_char(res));
	digit_count=char_count(answer);
	answer=(char*)realloc(answer,sizeof(char)*(digit_count+1));
	return answer;
}

void main()
{
	//printf("Prova: %s\n",i_to_char(123456789));
	//printf("Risultato: %s\n",solve_equation(get_expr()));
	//printf("Prova: %i\n",digit_counter(-1));
	print_pol(polinomial_expr(get_expr()));
}