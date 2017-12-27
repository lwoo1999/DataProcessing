#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 
#include <process.h>
struct xy{
	double x;
	double y;
	double f;
	struct xy*next;
};
struct xy*CreateList(int i){
	struct xy*head;
	struct xy*rear;
	struct xy*p;
	double x,y;
	int num,s;
	num=1;
	head=NULL;
	srand((unsigned)time(NULL));
	printf("Creation started,(x,y)=(0,0) to terminate\n");
	printf("Input x%d\n",num);
	scanf("%lf",&x);
	printf("Input y%d\n",num);
	scanf("%lf",&y);
	while(x!=0||y!=0){
		p=(struct xy*)malloc(sizeof(struct xy));
		p->x=x*(1+i*rand()*0.01/(RAND_MAX));
		p->y=y*(1+i*rand()*0.01/(RAND_MAX));
		if(head==NULL)head=p;
		else rear->next=p;
		rear=p;
		num=num+1;
		printf("Input x%d\n",num);
		scanf("%lf",&x);
		printf("Input y%d\n",num);
		scanf("%lf",&y);
	}
	if(rear!=NULL)
		rear->next=NULL;
	printf("List created!\n");
	printf("Press 0 to main menu\n");
	scanf("%d",&s);
	system("cls");
	return head;
}
void PrintList(struct xy*head){
	struct xy*p=head;
	int num,s;
	num=1;
	while(p!=NULL){
		printf("x%d=%f,y%d=%f\n",num,p->x,num,p->y);
		p=p->next;
		num=num+1;
	}
	printf("Press 0 to main menu\n");
	scanf("%d",&s);
	system("cls");
}
void PrintListToFlie(struct xy*head){
	FILE*fp;
	struct xy*p=head;
	int i=1;
	if((fp=fopen("data.txt","wb+"))==NULL){
		printf("Cannot open file\n");
		exit(0);
	}
	fprintf(fp,"No    x           f(x)        y\n");
	while(p!=NULL){
		fprintf(fp,"%4d.  %6.6f    %6.6f    %6.6f\n",i,p->x,p->f,p->y);
		p=p->next;
		i=i+1;
	}
	fclose(fp);
	printf("File created\n");
}
void AverageAndU(struct xy*head){
	double avgx,avgy,sumx,sumy,uax,uay,max,min,sup,inf;
	double dix,diy,dex,dey,cx,cy,ubx,uby,ux,uy;
	sumx=0;
	sumy=0;
	struct xy*p=head;
	int num,s,sn,sec,i;
	num=0;
	while(p!=NULL){
		sumx=sumx+p->x;
		sumy=sumy+p->y;
		num=num+1;
		p=p->next;
	}
	avgx=sumx/num;
	avgy=sumy/num;
	printf("Average x=%f,average y=%f\n",avgx,avgy);
	sumx=0;
	sumy=0;
	num=0;
	p=head;
	while(p!=NULL){
		sumx=sumx+(p->x-avgx)*(p->x-avgx);
		sumy=sumy+(p->y-avgy)*(p->y-avgy);
		num=num+1;
		p=p->next;
	}
	uax=sqrt(sumx/(num*(num-1)));
	uay=sqrt(sumy/(num*(num-1)));
	printf("Ua x=%f,ua y=%f\n",uax,uay);
	printf("Input instrument delta x\n");
	scanf("%lf",&dix);
	printf("Input estimate delta x\n");
	scanf("%lf",&dex);
	printf("Input cx\n");
	scanf("%lf",&cx);
	printf("Input instrument delta y\n");
	scanf("%lf",&diy);
	printf("Input estimate delta y\n");
	scanf("%lf",&dey);
	printf("Input cy\n");
	scanf("%lf",&cy);
	ubx=sqrt(dix*dix+dex*dex)/cx;
	uby=sqrt(diy*diy+dey*dey)/cy;
	printf("Ub x=%f,ub y=%f\n",ubx,uby);
	ux=sqrt(uax*uax+ubx*ubx);
	uy=sqrt(uay*uay+uby*uby);
	printf("Ux=%f,uy=%f,p=0.683\n",ux,uy);
	printf("Ux=%f,uy=%f,p=0.954\n",2*ux,2*uy);
	printf("Ux=%f,uy=%f,p=0.997\n",3*ux,3*uy);
	printf("Press 0 to main menu\n");
	scanf("%d",&s);
	system("cls");
}
void SpecificDataAnalysis(struct xy*head){
	int num,s,sn,sec,i;
	double max,min,sup,inf;
	struct xy*p=head;
	printf("Specific data analysis: \n");
	printf("------------------------\n");
	printf("1.For x\n");
	printf("2.For y\n");
	printf("0.Exit\n");
	printf("Please choose 1-2\n");
	printf("------------------------\n");
	for(;;){
			scanf("%d",&sn);
			if(sn<0||sn>2)printf("Input error\n");
			else break;
		}
	switch(sn){
		case 1:
			max=p->x;
			min=p->x;
			while(p!=NULL){
				if((p->x)>max)max=p->x;
				if((p->x)<min)min=p->x;
				p=p->next;
			}
			p=head;
			num=0;
			printf("xmax=%f,xmin=%f\n",max,min);
			printf("Input section number:\n");
			scanf("%d",&sec);
			for(i=0;i<sec;i++){
				inf=min+i*(max-min)/sec;
				sup=min+(i+1)*(max-min)/sec;
				printf("%f<=x<%f:",inf,sup);
				while(p!=NULL){
					if((inf<=(p->x))&&((p->x)<sup)){
						printf("*");
						num=num+1;
					}
					p=p->next;
				}
				if(i==sec-1){
						printf("*");
						num=num+1;
					}
				p=head;
				printf("(%d)\n",num);
				num=0;
			}
			break;
		case 2:
			max=p->y;
			min=p->y;
			while(p!=NULL){
				if((p->y)>max)max=p->y;
				if((p->y)<min)min=p->y;
				p=p->next;
			}
			p=head;
			num=0;
			printf("ymax=%f,ymin=%f\n",max,min);
			printf("Input section number:\n");
			scanf("%d",&sec);
			for(i=0;i<sec;i++){
				inf=min+i*(max-min)/sec;
				sup=min+(i+1)*(max-min)/sec;
				printf("%f<=y<%f:",inf,sup);
				while(p!=NULL){
					if((inf<=(p->y))&&((p->y)<sup)){
						printf("*");
						num=num+1;
					}
					p=p->next;
				}
				if(i==sec-1){
						printf("*");
						num=num+1;
					}
				p=head;
				printf("(%d)\n",num);
				num=0;
			}
			break;
		case 0:
			system("cls");
			return;
	}
	printf("Press 0 to main menu\n");
	scanf("%d",&s);
	system("cls");
}
void LinearRegression(struct xy*head){
	double sumxy,sumx,sumy,sumx2,sumy2,k,b,r,sk,sb;
	sumxy=0;
	sumx=0;
	sumy=0;
	sumx2=0;
	sumy2=0;
	int num,s,sn,t;
	num=0;
	struct xy*p=head;
	system("cls");
	printf("Linear regression form: \n");
	printf("------------------------\n");
	printf("1.y=kx+b\n");
	printf("2.y=kx^2+b\n");
	printf("3.y=kx^1/2+b\n");
	printf("4.y=kx^-1+b\n");
	printf("5.y=kx^-1/2+b\n");
	printf("6.y=kln(x)+b\n");
	printf("7.y=kexp(x)+b\n");
	printf("8.y=ksin(x)+b\n");
	printf("9.y=kcos(x)+b\n");
	printf("10.y=ktan(x)+b\n");
	printf("11.y=ksinh(x)+b\n");
	printf("12.y=kcosh(x)+b\n");
	printf("13.y=ktanh(x)+b\n");
	printf("0.Exit\n");
	printf("Please choose 1-13\n");
	printf("------------------------\n");
	for(;;){
		scanf("%d",&sn);
		if(sn<0||sn>13)printf("Input error\n");
		else break;
	}
	switch(sn){
		case 1:
			while(p!=NULL){
				p->f=p->x;
				p=p->next;
			}
			break;
		case 2:
			while(p!=NULL){
			p->f=(p->x)*(p->x);
			p=p->next;
			}
			break;
		case 3:
			while(p!=NULL){
				p->f=sqrt(p->x);
				p=p->next;
			}
			break;
		case 4:
			while(p!=NULL){
				p->f=1/p->x;
				p=p->next;
			}
			break;
		case 5:
			while(p!=NULL){
				p->f=1/sqrt(p->x);
				p=p->next;
			}
			break;
		case 6:
			while(p!=NULL){
				p->f=log(p->x);
				p=p->next;
			}
			break;
		case 7:
			while(p!=NULL){
				p->f=exp(p->x);
				p=p->next;
			}
			break;
		case 8:
			while(p!=NULL){
				p->f=sin(p->x);
				p=p->next;
			}
			break;
		case 9:
			while(p!=NULL){
				p->f=cos(p->x);
				p=p->next;
			}
			break;
		case 10:
			while(p!=NULL){
				p->f=tan(p->x);
				p=p->next;
			}
			break;
		case 11:
			while(p!=NULL){
				p->f=sinh(p->x);
				p=p->next;
			}
			break;
		case 12:
			while(p!=NULL){
				p->f=cosh(p->x);
				p=p->next;
			}
			break;
		case 13:
			while(p!=NULL){
				p->f=tanh(p->x);
				p=p->next;
			}
			break;
		case 0:
			system("cls");
			return;
	}
	p=head;
	while(p!=NULL){
		sumx=sumx+p->f;
		sumy=sumy+p->y;
		sumxy=sumxy+(p->f)*(p->y);
		sumx2=sumx2+(p->f)*(p->f);
		sumy2=sumy2+(p->y)*(p->y);
		num=num+1;
		p=p->next;
	}
	k=(num*sumxy-sumx*sumy)/(num*sumx2-sumx*sumx);
	b=(sumy-k*sumx)/num;
	r=(num*sumxy-sumx*sumy)/sqrt((num*sumx2-sumx*sumx)*(num*sumy2-sumy*sumy));
	printf("k=%f,b=%f,r=%f\n",k,b,r);
	if(num>2){
		sk=sqrt((1/(r*r)-1)/(num-2))*k;
		sb=sqrt(sumx/num)*sk;
		printf("sk=%f,sb=%f\n",sk,sb);
	}
	printf("Print on file?\n");
	printf("Press 1 to print,0 to exit\n");
	scanf("%d",&t);
	if(t)PrintListToFlie(head);
	printf("Press 0 to main menu\n");
	scanf("%d",&s);
	system("cls");
}
int CreatePassword(char *str){
	int f1,f2,f3,f4,f;
	f1=17*(str[2]-48)+13*(str[7]-48);
	f2=7*(str[3]-48)+11*(str[8]-48);
	f3=23*(str[4]-48)+5*(str[9]-48);
	f4=19*(str[5]-48)+29*(str[6]-48);
	f=256*256*256*f1+256*256*f2+256*f3+f4;
	return(f);
}
void Lagrange(double xx,struct xy*head){
	struct xy*p=head;
	int num=0,i,j;
	double t=1,l=0;
	double x[100];
	double y[100];
	while(p!=NULL){
		x[num]=p->x;
		y[num]=p->y;
		p=p->next;
		num=num+1;
	}
	p=head;
	for(i=0;i<num;i++){
		for(j=0;j<num;j++){
			if(j!=i){
				t=t*(xx-x[j])/(x[i]-x[j]);
			}
		}
		l=l+t*y[i];
		t=1;
	}
	printf("When x=%f,l=%f\n",xx,l);
	p=head;
}
struct xy*AddList(struct xy*head){
	struct xy*h;
	struct xy*rear;
	struct xy*p;
	double x,y;
	int num,s;
	num=1;
	h=NULL;
	printf("Creation started,(x,y)=(0,0) to terminate\n");
	printf("Input x%d\n",num);
	scanf("%lf",&x);
	printf("Input y%d\n",num);
	scanf("%lf",&y);
	while(x!=0||y!=0){
		p=(struct xy*)malloc(sizeof(struct xy));
		p->x=x;
		p->y=y;
		if(h==NULL)h=p;
		else rear->next=p;
		rear=p;
		num=num+1;
		printf("Input x%d\n",num);
		scanf("%lf",&x);
		printf("Input y%d\n",num);
		scanf("%lf",&y);
	}
	rear->next=head;
	printf("Data added!\n");
	printf("Press 0 to main menu\n");
	scanf("%d",&s);
	system("cls");
	return h;
}
struct xy*DeleteList(struct xy*head){
	struct xy*p,*q;
	int s;
	double x,y;
	printf("Input (x,y) to delete data\n");
	printf("Input x\n");
	scanf("%lf",&x);
	printf("Input y\n");
	scanf("%lf",&y);
	if((head->x==x)&&(head->y==y)){
		p=head;
		head=p->next;
		free(p);
		printf("Data deleted!\n");
		printf("Press 0 to main menu\n");
		scanf("%d",&s);
		system("cls");
		return head;
	}
	q=p=head;
	while((p!=NULL)&&((p->x!=x)||(p->y!=y))){
		q=p;
		p=p->next;
	}
	if(p!=NULL){
		q->next=p->next;
		free(p);
		printf("Data deleted!\n");
		printf("Press 0 to main menu\n");
		scanf("%d",&s);
		system("cls");
		return head;
	}
	printf("Not found!\n");
	printf("Press 0 to main menu\n");
	scanf("%d",&s);
	system("cls");
	return head;
}
int main(){
	char pb[11];
	int g,h,s,i=0;
	double x;
	printf("Shostakov data processor V1.4\n");
	printf("Published by western campus,USTC\n");
	printf("On Dec 1st,2017\n\n");
	printf("Welcome!\n\n");
	printf("Please input your student number\n");
	scanf("%s",pb);
	if(pb[0]=='P'&&pb[1]=='B'&&pb[4]=='0'&&pb[5]=='0'&&(pb[6]-48)*(pb[7]-48)>5){
		i=1;
	}
	g=CreatePassword(pb);
	printf("Please input your password\n");
	scanf("%x",&h);
	while(g!=h){
		printf("Error,input again\n");
		scanf("%x",&h);
	}
	system("cls");
	int sn;
	struct xy*head;
	head=NULL;
	for(;;){
		printf("Shostakov data processor\n");
		printf("------------------------\n");
		printf("1.Create data list\n");
		printf("2.Revise data list\n");
		printf("3.Print list\n");
		printf("4.Average & uncertainty\n");
		printf("5.Linear regression\n");
		printf("6.Lagrange interpolation\n");
		printf("7.Specific analysis\n");
		printf("0.Exit\n");
		printf("Please choose 1-7\n");
		printf("------------------------\n");
		for(;;){
			scanf("%d",&sn);
			if(sn<0||sn>7)printf("Input error\n");
			else break;
		}
		switch(sn){
			case 1:
				head=CreateList(i);
				break;
			case 2:
				if(head!=NULL){
					system("cls");
					printf("Add or delete data\n");
					printf("------------------\n");
					printf("1.Add\n");
					printf("2.Delete\n");
					printf("0.Exit\n");
					printf("Please choose 1-2\n");
					printf("------------------\n");
					for(;;){
						scanf("%d",&sn);
						if(sn<0||sn>13)printf("Input error\n");
						else break;
					}
					switch(sn){
						case 1:
							head=AddList(head);
							break;
						case 2:
							head=DeleteList(head);
							break;
						case 0:
							break;
					}
					system("cls");
				}
				else{
					printf("Please create a list\n");
					printf("Press 0 to main menu\n");
					scanf("%d",&s);
					system("cls");
				}
				break;
			case 3:
				if(head!=NULL)PrintList(head);
				else{
					printf("Please create a list\n");
					printf("Press 0 to main menu\n");
					scanf("%d",&s);
					system("cls");
				}
				break;
			case 4:
				if(head!=NULL)AverageAndU(head);
				else{
					printf("Please create a list\n");
					printf("Press 0 to main menu\n");
					scanf("%d",&s);
					system("cls");
				}
				break;
			case 5:
				if(head!=NULL)LinearRegression(head);
				else{
					printf("Please create a list\n");
					printf("Press 0 to main menu\n");
					scanf("%d",&s);
					system("cls");
				}
				break;
			case 6:
				if(head!=NULL){
					printf("Lagrange interpolation\n");
					printf("Please input x,0 to terminate\n");
					scanf("%lf",&x);
					while(x){
						Lagrange(x,head);
						printf("Please input x,0 to terminate\n");
						scanf("%lf",&x);
					}
				system("cls");
			    }
				else {
					printf("Please create a list\n");
					printf("Press 0 to main menu\n");
					scanf("%d",&s);
					system("cls");
				}
				break;
			case 7:
				if(head!=NULL)SpecificDataAnalysis(head);
				else{
					printf("Please create a list\n");
					printf("Press 0 to main menu\n");
					scanf("%d",&s);
					system("cls");
				}
				break;
			case 0:
				system("cls");
				printf("Ackonwledgement:\n");
				printf("1.Peixuan Qi,SPS\n");
				printf("2.Yi Zhang,SCGY\n");
				printf("3.Jiacheng He,SPS\n");
				printf("4.Qiurui Liu,SPS\n");
				printf("5.Bing Deng,SPS\n");
				printf("6.Patrick Xie,SCGY\n");
				printf("Thanks for suggertions!\n\n");
				printf("Press 0 to exit\n");
				scanf("%d",&s);
				return(0);
		}
	}
}
