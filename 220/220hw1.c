//Yishuo Wang
//108533945
//part1:1: Big endian
//      2: Because Yish is from left to right, so it is Big endian.
//      3: Enter your first name: Yishuo
//		   First Memory Word: Yish
//		   Hexadecimal Memory Word
//		    59 69 73 68
//		   Details of Memory Word
//		   Byte Address: 4290772064        Value: 59       Char: Y
//		   Byte Address: 4290772065        Value: 69       Char: i
//		   Byte Address: 4290772066        Value: 73       Char: s
//		   Byte Address: 4290772067        Value: 68       Char: h
//
//         output of opposite endianess: hsiY

#include <stdio.h>
int main(void){
	int x=33554431;
	float y=33554431;
	printf("%d\n%f\n",x,y);
	printf("%.1f\n",y);
	char my_string[] = "CSE220 and C are so much fun!!!\0";
	printf("%.12s", my_string);
	char a[]="CSE220";
	printf("\n%12s",a);
	int len=sizeof(my_string);
	
	printf("\n%.*s", len,my_string+(len-4));
	float N[] = {0.125, 0.25, 0.5, 0.75, 1, 1.5, 2, 2.5, 3, 5, 10, 20, 50, 100};
	printf("\n%-15s\t%-15s\t%-15s\t%-15s\t\%-15s\n","Inches","Millimeters","Centimeters","Meters","Kilometers");
	int i;
	int lenOfFloat=sizeof(N)/sizeof(float);
	
	for(i=0;i<lenOfFloat;i++){
		printf("%-15.6g\t%-15.6g\t%-15.6g\t%-15.6g\t%-15.6f\n",N[i],N[i]*25.40,N[i]*2.54,N[i]*0.0254,N[i]*0.0000254);
	}
}
