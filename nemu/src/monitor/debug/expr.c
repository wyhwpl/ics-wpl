#include "nemu.h"
#include <stdlib.h>
#include <elf.h>
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>
uint32_t expr_value(char *args);
enum {
	NOTYPE =256, EQ, NUMD, NUMH, REG, NEQ, NS, NB, S, B, LM, RM, AND, OR, EOR, NOT, DAND, DOR, DNOT, NEG, POINT, VAR

	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */ 

	{" +", NOTYPE},				    // spaces
	{"\\+", '+'},					// plus
	{"-",'-'},                      // minus
	{"\\*",'*'},                    // mutiply
	{"/",'/'},                      // division
	{"%",'%'},                      // complementation
	{"\\(",'('},                    // left-braket
	{"\\)",')'},                    // right-braket
	{"==", EQ},						// equal
	{"!=", NEQ},                    // notequal
	{">=", NS},                     
	{"<=", NB},
	{">>", RM},                     // right-move
	{"<<", LM},                     // left-move
	{">", B},
	{"<", S},
	{"&&", DAND},                     // and
	{"~", NOT},                     // bit-not
	{"\\^", EOR},                   // bit-exclusive or
    {"&", AND},                   // bit- and
	{"\\|\\|", DOR},                  // or
	{"\\|", OR},                     //bit-or
	{"!", DNOT},                    // not
	{"0x[0-9a-fA-F]{1,8}",NUMH},    // hexadecimal
	{"[0-9]{1,10}",NUMD},            //decimal
	{"(\\$)[a-z]{1,3}",REG},            // register
	{"[_a-zA-Z]+",VAR},               //varibale
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			Assert(ret == 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
 		}
 	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

  	while(e[position] != '\0') {
		/* Try all rules one by one. */
 		for(i = 0; i < NR_REGEX; i ++) {
 			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;
				int t=0;
				char substr[100];
				while(t<substr_len)
				{
					substr[t]=substr_start[t];
					t++;
				}
				substr[t]='\0';

				Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array ``tokens''. For certain 
				 * types of tokens, some extra actions should be performed.
				 */

				switch(rules[i].token_type) {
					case NOTYPE:tokens[nr_token].type=NOTYPE;break;
					case NUMD:{tokens[nr_token].type=rules[i].token_type;strcpy(tokens[nr_token].str,substr);nr_token++;}break;
					case NUMH:{tokens[nr_token].type=rules[i].token_type;strcpy(tokens[nr_token].str,substr);nr_token++;}break;
					case REG:{tokens[nr_token].type=rules[i].token_type;strcpy(tokens[nr_token].str,substr);nr_token++;}break;
					case '+':{tokens[nr_token].type='+';nr_token++;}break;
					case '-':{tokens[nr_token].type='-';nr_token++;}break;
					case '*':{tokens[nr_token].type='*';nr_token++;}break;
					case '/':{tokens[nr_token].type='/';nr_token++;}break;
					case '%':{tokens[nr_token].type='%';nr_token++;}break;
					case '(':{tokens[nr_token].type='(';nr_token++;}break;
					case ')':{tokens[nr_token].type=')';nr_token++;}break;
					case AND:{tokens[nr_token].type=AND;nr_token++;}break;
				    case OR:{tokens[nr_token].type=OR;nr_token++;}break;
					case NOT:{tokens[nr_token].type=NOT;nr_token++;}break;
					case EOR:{tokens[nr_token].type=EOR;nr_token++;}break;
					case DAND:{tokens[nr_token].type=DAND;nr_token++;}break;
					case DOR:{tokens[nr_token].type=DOR;nr_token++;}break;
				    case DNOT:{tokens[nr_token].type=DNOT;nr_token++;}break;
					case EQ:{tokens[nr_token].type=EQ;nr_token++;}break;
					case NEQ:{tokens[nr_token].type=NEQ;nr_token++;}break;
					case NS:{tokens[nr_token].type=NS;nr_token++;}break;
					case NB:{tokens[nr_token].type=NB;nr_token++;}break;
				    case S:{tokens[nr_token].type=S;nr_token++;}break;
	 				case B:{tokens[nr_token].type=B;nr_token++;}break;
					case LM:{tokens[nr_token].type=LM;nr_token++;}break;
					case RM:{tokens[nr_token].type=RM;nr_token++;}break;
					case VAR:{tokens[nr_token].type=VAR;strcpy(tokens[nr_token].str,substr);nr_token++;}break;
					default: panic("please implement me");
     				}

				break;
    			}
    		}

  		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
		/*if(tokens[nr_token].type!=N0TYPE) nr_token++;*/
    	}

	return true; 
}
uint32_t eval(int p,int q);
uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) { 
		*success = false;
		return 0;
	}
	int i;
    for(i=0;i<nr_token;i++)
    	{
		if(tokens[i].type=='-')
  		{
			if(i==0||(tokens[i-1].type!=DAND&&tokens[i-1].type!=DOR&&tokens[i-1].type!=DNOT&&tokens[i-1].type!=')'&&tokens[i-1].type!=NUMD&&tokens[i-1].type!=NUMH&&tokens[i-1].type!=REG)) tokens[i].type=NEG;
   		}
		if(tokens[i].type=='*')
		{
			if(i==0||(tokens[i-1].type!=DAND&&tokens[i-1].type!=DOR&&tokens[i-1].type!=DNOT&&tokens[i-1].type!=')'&&tokens[i-1].type!=NUMD&&tokens[i-1].type!=NUMH&&tokens[i-1].type!=REG)) tokens[i].type=POINT;
  		}
  	}
   uint32_t Result=eval(0,nr_token-1);
     

	/* TODO: Insert codes to evaluate the expression. */
//	panic("please implement me");
	return Result;
}
bool check_parentheses(int p,int q)
{
	int Type[q-p+1];
	int i;
	for(i=0;i<q-p+1;i++) Type[i]=tokens[p+i].type;
	if(Type[0]=='('&&Type[q-p]==')')
	{
	  i=1;
	  int j;
      while(i<q-p)
	   {
		  if(Type[i]==')')
	 	  {
			j=i-1;
		  while(j>0)
	 	  {
		   if(Type[j]=='(')
	 	   {
            if(j==i-1) return false;
            else
			{
	          Type[j]=0;
              Type[i]=0;
              break;
            }
           }
            j--;
		  }
           if(j==0) return false;
 		  }
           i++;
 	  }
 	}	  
	else return false;
 return true;
}
int Precede(int ty)
{
	switch(ty)
	{
		case DOR:return 0;
		case DAND:return 1;
		case OR:return 2;
		case EOR:return 3;
	    case AND:return 4;
		case EQ:return 5;
		case NEQ:return 5;
		case NS:return 6;
		case NB:return 6;
	    case S:return 6;
		case B:return 6;
		case LM:return 7;
		case RM:return 7;
		case '+':return 8;
		case '-':return 8;
		case '*':return 9;
		case '/':return 9;
		case '%':return 9;
		case DNOT:return 10;
		case NOT:return 10;
		default:return ty;
	}
	return ty;
}
int find_dominant_operator(int p,int q)
{
  int op=0;
  int Type[q-p+1];
  int i;
  for(i=0;i<q-p+1;i++)  Type[i]=Precede(tokens[p+i].type);
  for(i=0;i<q-p+1;i++)
  {
	if(Type[i]>=0&&Type[i]<=10)
	{
	 int r=i+1,l=i-1;
     while(l>=0)
	 {
	   if(Type[l]=='(')
	   {
		   Type[i]=100;
		   break;
   	    }
	   if(Type[l]==')')
 	    {
		   while(r<q-p+1)
 		   {
			   if(Type[r]=='(') break;
			   if(Type[r]==')')
 			   {
				   Type[i]=100;
				   break;
  	 		   }
			   r++;
  	 	   }
		   break;
  	   }
       l--;
   	  }
   	}
     }
    int mtype=100;
   for(i=0;i<q-p+1;i++)
    {
	 if(Type[i]>=0&&Type[i]<=10)
 	 {
	  if(Type[i]<=mtype)
	  {
	   mtype=Type[i];
	   op=i;
  	  }
   	 }
      }
   return op+p;   
}
uint32_t eval(int p,int	q)
{
	if(p>q)
	{
 		printf("Bad expression!\n");
		uint32_t value=0;
		return value;
  	}
	else if(q==p)
 	{
		if(tokens[p].type==NUMD)
 		{
			unsigned long number=strtoul(tokens[p].str,NULL,10);
			uint32_t value=(uint32_t)number;
			return value;
  	 	}		
		else if(tokens[p].type==NUMH)
  	 	{
			unsigned long number=strtoul(tokens[p].str,NULL,16);
			uint32_t value=(uint32_t)number;
			return value;
 		}
		else if(tokens[p].type==VAR)
        {
			uint32_t value;
			value=expr_value(tokens[p].str);
//			printf("value:%x\n",value);
			return value;
 		}
		else if(tokens[p].type==REG)
  		{
			int k;
			for(k=0;k<8;)
 			{
				if(strcmp(tokens[p].str,regsl[k])) return reg_l(k);
				else if(strcmp(tokens[p].str,regsw[k])) return reg_w(k);
				else if(k<4)
				{
				 int n=k+4;
				 if(strcmp(tokens[p].str,regsb[k])) return reg_b(k);
				 else if(strcmp(tokens[p].str,regsb[n])) return reg_b(n);
				 else k++;
  	  			}
				else k++;
     			}
   	 	}
   	    }
    else if(check_parentheses(p,q)==true)
 	{ 
        return eval(p+1,q-1);
 	}
	else
          	{ 
		int op_type;
		op_type=find_dominant_operator(p,q);
    	uint32_t value1=eval(p,op_type-1);
    	uint32_t value2=eval(op_type+1,q);
		switch(tokens[op_type].type)
		{
		 case NEG:return (-1)*value2;
		 case POINT:return swaddr_read(value2,4);
         case '+':return value1+value2;
		 case '-':return value1-value2;
		 case '*':return value1*value2;
		 case '/':return value1/value2;
		 case '%':return value1%value2;
		 case EQ:return value1==value2;
		 case NEQ:return value1!=value2;
		 case NS:return value1>=value2;
		 case NB:return value1<=value2;
		 case S:return value1<value2;
		 case B:return value1>value2;
		 case DAND:return value1&&value2;
		 case DOR:return value1||value2;
		 case DNOT:return !value2;
		 case AND:return value1&value2;
		 case OR:return value1|value2;
		 case NOT:return ~value2;
		 case LM:return value1<<value2;
		 case RM:return value1>>value2;
		 case EOR:return value1^value2;
		default:panic("please implement me");
        	 	}
   	}
	return 0;
}
