#include <stdio.h>
int CreatePassword(char *str){
	int f1,f2,f3,f4,f;
	f1=17*(str[2]-48)+13*(str[7]-48);
	f2=7*(str[3]-48)+11*(str[8]-48);
	f3=23*(str[4]-48)+5*(str[9]-48);
	f4=19*(str[5]-48)+29*(str[6]-48);
	f=256*256*256*f1+256*256*f2+256*f3+f4;
	return(f);
}
int main(){
	char pb[11];
	int g,s;
	printf("Pleast input your student number\n");
	scanf("%s",pb);
	g=CreatePassword(pb);
	printf("%0x\n",g);
	printf("Press 0 to exit\n");
	scanf("%d",&s);
	return(0);
}
