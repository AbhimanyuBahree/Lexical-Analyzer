#include<stdio.h>
#include<stdbool.h>
#include<string.h>
char * buf[234];
int dou=0;
FILE * gin;
struct token
{
char * lexemename;
int index;
unsigned int row,col; 
char * type;
};
// getNextToken()
int sindex=0;
int maxlimit;
char arr[123][1000];
void fillToken(char * filename)
{

FILE * fin=fopen(filename,"r");

char buf[1000];
int linenumber=0;
while(fscanf(fin,"%[^\n]s",buf)==1)
  {
      //printf("%s\n",buf);
      int i=0;
     while(i<strlen(buf))
     {
     arr[linenumber][i]=buf[i];
      i++;
     }
      fseek(fin,1,SEEK_CUR);
      linenumber++;
  }
  maxlimit=linenumber;
fclose(fin);
}

char * getNextToken()
{
   if(sindex== maxlimit) return " ";  
return arr[sindex++];
}
// getNextToken
FILE * foutput(char * filename)
{
FILE * fin=fopen(filename,"w");
 if(fin == NULL) {printf("Can't open file\n"); return;}
 return fin;
}
void printToken(struct token * tk){printf("<%s,%d,%d,%s>\n",tk->lexemename,tk->row,tk->col,tk->type);}
struct token * createToken(char * lexemename,int row,int col,char * type)
{
struct token * tk=(struct token *)malloc(sizeof(struct token *));
tk->lexemename=lexemename;
tk->row=row;
tk->col=col;
tk->type=type;
return tk;
}

void printUpperCase (char *word) {
	int l = strlen(word);
	char z;
	int i;
	for (i = 0; i < l; ++i) {
		z = word[i];
		printf("%c", z > 96 ? z - 32 : z);
	}
	printf("\n");
}

void fprintToken(struct token * tk){
 fprintf(gin,"<%s,%d,%d,%s>\n",tk->lexemename,tk->row,tk->col,tk->type);
 
}

bool isDelimiter(char ch) 
{ 
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||  
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||  
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||  
        ch == '[' || ch == ']' || ch == '{' || ch == '}'||ch=='\n'||ch =='"'||ch=='!') 
        return (true); 
    return (false); 
} 
 
bool isOperator(char ch) 
{ 
    if (ch == '+' || ch == '-' || ch == '*' ||  
        ch == '/' || ch == '>' || ch == '<' ||  
        ch == '=' || ch == '%' || ch =='!') 
        return (true); 
    return (false); 
} 
  
 
bool validIdentifier(char* str) 
{ 
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' || 
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||  
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||  
        str[0] == '9' || isDelimiter(str[0]) == true) 
        return (false); 
    return (true); 
} 

bool isKeyword(char* str) 
{ 
    if (!strcmp(str, "if") || !strcmp(str, "else") || 
        !strcmp(str, "while") || !strcmp(str, "do") ||  
        !strcmp(str, "break") ||  
         !strcmp(str, "continue") || !strcmp(str, "int") 
        || !strcmp(str, "double") || !strcmp(str, "float") 
        || !strcmp(str, "return") || !strcmp(str, "char") 
        || !strcmp(str, "case") || !strcmp(str, "char") 
        || !strcmp(str, "sizeof") || !strcmp(str, "long") 
        || !strcmp(str, "short") || !strcmp(str, "typedef") 
        || !strcmp(str, "switch") || !strcmp(str, "unsigned") 
        || !strcmp(str, "void") || !strcmp(str, "static") 
        || !strcmp(str, "struct") || !strcmp(str, "goto")) 
        return (true); 
    return (false); 
} 
bool isInteger(char* str) 
{ 
    int i, len = strlen(str); 
  
    if (len == 0) 
        return (false); 
    for (i = 0; i < len; i++) { 
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0)) 
            return (false); 
    } 
    return (true); 
} 
bool isRealNumber(char* str) 
{ 
    int i, len = strlen(str); 
    bool hasDecimal = false; 
  
    if (len == 0) 
        return (false); 
    for (i = 0; i < len; i++) { 
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' ||  
            (str[i] == '-' && i > 0)) 
            return (false); 
        if (str[i] == '.') 
            hasDecimal = true; 
    } 
    return (hasDecimal); 
} 
char* subString(char* str, int left, int right) 
{ 
    int i; 
    char* subStr = (char*)malloc( 
                  sizeof(char) * (right - left + 2)); 
  
    for (i = left; i <= right; i++) 
        subStr[i - left] = str[i]; 
    subStr[right - left + 1] = '\0'; 
    return (subStr); 
} 
void parse(char* str) 
{ 
    int linenumber=1;
    int save=-1;
    int left = 0, right = 0; 
    int len = strlen(str); 
    while (right <= len && left <= right) { 
        if(str[right]=='\n') {linenumber++; save=right;}
        if(str[right]=='"') dou++;
        if(str[right]=='('){
            char ch=str[right];
                   char * p=malloc(sizeof(char));
                   *p=ch;
        struct token * tk=createToken(p,0,0,"LB");
                    tk->row=linenumber;
                    tk->col=left-save;
                  printToken(tk); 
                    fprintToken(tk); 
        }
        if(str[right]==')'){
            char ch=str[right];
                   char * p=malloc(sizeof(char));
                   *p=ch;
        struct token * tk=createToken(p,0,0,"RB");
                    tk->row=linenumber;
                    tk->col=left-save;
                 printToken(tk);
                     fprintToken(tk); 
        }

        if(str[right]=='{'){
            char ch=str[right];
                   char * p=malloc(sizeof(char));
                   *p=ch;
        struct token * tk=createToken(p,0,0,"LC");
                    tk->row=linenumber;
                    tk->col=left-save;
                 printToken(tk);
                     fprintToken(tk); 
        }

        if(str[right]=='}'){
            char ch=str[right];
                   char * p=malloc(sizeof(char));
                   *p=ch;
        struct token * tk=createToken(p,0,0,"RC");
                    tk->row=linenumber;
                    tk->col=left-save;
                  printToken(tk); 
                    fprintToken(tk); 
        }
        if(str[right]==';'){
            char ch=str[right];
                   char * p=malloc(sizeof(char));
                   *p=ch;
        struct token * tk=createToken(p,0,0,"SS");
                    tk->row=linenumber;
                    tk->col=left-save;
                 printToken(tk); 
                    fprintToken(tk); 
        }
        if (isDelimiter(str[right]) == false) 
            right++; 
  
        if (isDelimiter(str[right]) == true && left == right) {
           
            if (isOperator(str[right]) == true) 
               { //printf("'%c' IS AN OPERATOR\n", str[right]);

if((str[right]=='<')|(str[right]=='>')|(str[right]=='!')|(str[right]=='=')){
   if(str[right+1]=='=')
             {
              char* su = subString(str, right, right + 1);
               struct token * tk=createToken(su,0,0,"RELATIONAL OPERATOR");
                    tk->row=linenumber;
                    tk->col=left-save;
                    printToken(tk);
                     fprintToken(tk);
                     right++;

             }
         else if(str[right]=='='){
            char ch=str[right];
                   char * p=malloc(sizeof(char));
                   *p=ch;
        struct token * tk=createToken(p,0,0,"ASSIGNMENT OPERATOR");
                    tk->row=linenumber;
                    tk->col=left-save;
                    printToken(tk);
                     fprintToken(tk); 
        }
        else
        {
             char ch=str[right];
                   char * p=malloc(sizeof(char));
                   *p=ch;
        struct token * tk=createToken(p,0,0,"RELATIONAL OPERATOR");
                    tk->row=linenumber;
                    tk->col=left-save;
                    printToken(tk); 
                    fprintToken(tk);
        }
     
             }    
        else if((str[right]=='*')|(str[right]=='+')|(str[right]=='-')|(str[right]=='/')){
     
             if(str[right+1]=='=')
             {
              char* su = subString(str, right, right + 1);
               struct token * tk=createToken(su,0,0,"ARITHMETIC OPERATOR");
                    tk->row=linenumber;
                    tk->col=left-save;
                    printToken(tk);
                     fprintToken(tk);
                     right++;

             }
          else {                  
            char ch=str[right];
                   char * p=malloc(sizeof(char));
                   *p=ch;
        struct token * tk=createToken(p,0,0,"ARITHMETIC OPERATOR");
                    tk->row=linenumber;
                    tk->col=left-save;
                    printToken(tk); 
                    fprintToken(tk);} 
                  }
        
       
               } 
        
            right++; 
            left = right; 
        } else if (isDelimiter(str[right]) == true && left != right 
                   || (right == len && left != right)) { 
            char* subStr = subString(str, left, right - 1); 
              
            if (isKeyword(subStr) == true) 
                {

                   printf("'%s' IS A KEYWORD\n", subStr);
                    struct token * tk=createToken(subStr,0,0,"KEYWORD");
                    tk->row=linenumber;
                    tk->col=left-save;
                    printToken(tk);
                     fprintToken(tk);
                 } 
  
            else if (isInteger(subStr) == true) 
                {
                   printf("'%s' IS AN INTEGER\n", subStr);
                   struct token * tk=createToken(subStr,0,0,"NUMBER");
                   tk->row=linenumber;
                   tk->col=left-save;
                      printToken(tk);
                       fprintToken(tk); 
                }
            else if (isRealNumber(subStr) == true) 
              {  printf("'%s' IS A REAL NUMBER\n", subStr); 
                  struct token * tk=createToken(subStr,0,0,"NUMBER");
                      tk->row=linenumber;
                      tk->col=left-save;
                   printToken(tk); 
                   fprintToken(tk);
              }
            else if (validIdentifier(subStr) == true
                     && isDelimiter(str[right - 1]) == false) 
               {
                 
                      
                      if(dou!=0 && dou%2 != 0)
                      {
                              
                printf("'%s' IS A STRING LITERAL\n", subStr);
                      struct token * tk=createToken(subStr,0,0,"STRING LITERAL");
                    tk->row=linenumber;
                    tk->col=left-save;
                       printToken(tk); 
                       fprintToken(tk);
                      }
                      else
                      {
                printf("'%s' IS A VALID IDENTIFIER\n", subStr);
                      struct token * tk=createToken(subStr,0,0,"IDENTIFIER");
                    tk->row=linenumber;
                    tk->col=left-save;
                       printToken(tk); 
                       fprintToken(tk);
                       } 
                } 
  
            else if (validIdentifier(subStr) == false
                     && isDelimiter(str[right - 1]) == false) 
               printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr); 
            left = right;
             
        } 
    } 
    return; 
} 
int checkDelimiter(char * filename,char ch)
{
FILE * fin=fopen(filename,"r");
if(fin == NULL) {printf("Can't open file\n"); return 0;}
fseek(fin,-1,SEEK_END);
char d=(char)getc(fin);
if(ch==d) {fclose(fin); return 1;}
	else {fclose(fin);return 0;}
}
void appendch(char * filename,char ch)
{
	if(checkDelimiter(filename,ch)) return;

FILE * fin=fopen(filename,"a");
if(fin == NULL) {printf("Can't open file\n"); return 0;}
fprintf(fin,"%c",ch);
fclose(fin);
}

char * concatstr(char * str1,char * str2)
{
char * str3 = (char *)malloc(1+strlen(str1)+strlen(str2));
strcpy(str3,str1);
strcat(str3,str2);	
return str3;
}

char * concatchar(char * str1,char ch)
{
	char * str=(char *)malloc(1+1+strlen(str1));
	strcpy(str,str1);
	str[strlen(str1)]=ch;
	str[strlen(str1)+1]='\0';
	return str;
}
void readDocument(char * filename,char * delimiter){
FILE * fi=fopen(filename,"r");
if(fi == NULL) {printf("Can't open file\n"); return; }
char * str4=concatstr(concatchar("%[^",delimiter),"]%*c");
fscanf(fi,str4,buf);
fclose(fi);
return buf;
}

char * preprocess(char * filename)
{

char * str="q4out.c";
FILE * fa=fopen(filename,"r");
if(fa == NULL){printf("can't open file in preprocessing\n"); return str;}
FILE * fb=fopen(str,"w");
// for single and multiline comments
int ca,cb;
ca = getc(fa);
while (ca != EOF)
{
if (ca=='/')
{
cb = getc(fa);
if (cb == '/')
{
while(ca != '\n')
ca = getc(fa);
}
else if (cb == '*')
{
do
{
while(ca != '*')
ca = getc(fa);
ca = getc(fa);
} while (ca != '/');
}
else
{
putc(ca,fb);
putc(cb,fb);
}
}
else putc(ca,fb);
ca = getc(fa);
}
fclose(fa);
fclose(fb);
//
// for reducing spaces and tabs to a single space
FILE * fin;
FILE * fout;
char * str2="q4out2.c";
fout=fopen(str2,"w");
fin=fopen("q4out.c","r");
if(fin == NULL)
{
printf("Can't open file\n");
exit(0);
}

ca=getc(fin);
while(ca!= EOF)
{
if(ca==' ')
{
    putc(ca,fout);
    while(ca==' ')
	ca=getc(fin);
  
}
else if(ca=='	')
{
	putc(' ',fout);
	while(ca=='	')
	ca=getc(fin);
}
else
{
putc(ca,fout);
ca=getc(fin);
}

}
fclose(fin);
fclose(fout);
//
// discarding preprocessor directives

fin=fopen(str2,"r");
if(fin == NULL)
{
printf("Can't open file");
exit(0);
}
char * str3="q4out3.c";
fout=fopen(str3,"w");


ca = getc(fin);
while(ca!=EOF)
{
if(ca == '#')
  {
	while(ca!='\n')
	ca = getc(fin);
	putc(ca,fout);
  }

else
{
 putc(ca,fout);
}
ca=getc(fin);
}

fclose(fin);
fclose(fout);

//

return str3;
}
int main()
{
char * filename1="uin.c";
char delimiter='@';
//preprocessing
char * filename=preprocess(filename1);
 appendch(filename,delimiter);
 readDocument(filename,delimiter);
printf("%s",buf);
printf("\ndone\n");
   gin=foutput("output.c");
 parse(buf);
 fclose(gin);
 fillToken("output.c");
 printf("----------------------------------------------------------------------------------------\n");
while(1)
{
  printf("Do you want next token(y/n)?\n");
  char ch; scanf(" %c",&ch);
  if(ch == 'n') break;
  char * str=getNextToken();
  printf("%s\n",str);
}
	return 0;
}
