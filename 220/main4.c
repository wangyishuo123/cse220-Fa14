int main(){
	char a[]="m?o?n?e?y";
	char b[100];
	int c;
	printf("Enter the type: ");
	scanf("%d",&c);
	c=AcronymGenerator(a, b, c);
	printf("%s ",b);
	printf("%d",c);
	//system("pause");


}

