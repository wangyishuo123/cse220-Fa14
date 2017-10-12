//Yishuo Wang
//ID:108533945

#include <stdio.h>
#include <stdlib.h>
int isXXX(char c){//is captial letters, punctuation and numerical digits
	int p=0;
	if ((c-'A'>=0 && c-'Z'<=0) || (c-'0'>=0 && c-'9'<=0) ||c =='!' || c =='`' || c =='$' || c =='%' || c =='&' || c =='\'' || c =='.' || c ==':' || c ==';' || c ==',' || c =='?'){
		c=c;
		p=1;
	}
	
	return p;
}
int isXXX2(char c){//is in the A-Z
	int p=0;
	if((c-'A'>=0 && c-'Z'<=0)){
		p=1;
	}
	return p;
}
int ixXXX3(char c){// ` & % & ' . :  , ?
	int p=0;
	if(c =='!' || c =='`' || c =='$' || c =='%' || c =='&' || c =='\'' || c =='.' || c ==':' || c ==';' || c ==',' || c =='?'){
		p=1;
	}
	return p;
}

char toUpper(char *i){
	if(*i-'a'>=0 && *i-'z'<=0){
		*i-=32;
	}
	else if(*i-'A'>=0 && *i-'Z'<=0){
		*i=*i;
	}	
	return *i;
}
char Change(char *i){
	if( ((*(i)=='T'&&*(i+1)=='O') && isXXX2(*(i+2))!=1) || ((*(i)=='T'&&*(i+1)=='O'&&*(i+2)=='O') && isXXX2(*(i+3))!=1) ){
		return '2';	
	}
	else if( *(i)=='A'&&*(i+1)=='N'&&*(i+2)=='D' && isXXX2(*(i+3))!=1 ){
		return '&';
	}
	else if( *(i)=='Y'&&*(i+1)=='O'&&*(i+2)=='U' && isXXX2(*(i+3))!=1 ){
		return 'U';
	}
	else if( *(i)=='F'&&*(i+1)=='O'&&*(i+2)=='R' && isXXX2(*(i+3))!=1 ){
		return '4';
	}
	else if( *(i)=='Q' && *(i+1)=='U' && *(i+2)=='E' && *(i+3)=='S' && *(i+4)=='T' && *(i+5)=='I' && *(i+6)=='O' && *(i+7)=='N' && isXXX2(*(i+8))!=1 ){
		return '?';
	}
	else if( *(i)=='W'&&*(i+1)=='H'&&*(i+2)=='Y' && isXXX2(*(i+3))!=1 ){
		return 'Y';
	}
	else if( *(i)=='A'&&*(i+1)=='T' && isXXX2(*(i+2))!=1 ){
		return '@';
	}
	else if( *(i)=='M'&&*(i+1)=='O'&&*(i+2)=='N'&&*(i+3)=='E'&&*(i+4)=='Y' && isXXX2(*(i+5))!=1 ){
		return '$';
	}
	else if( *(i)=='S'&&*(i+1)=='E'&&*(i+2)=='E'&& isXXX2(*(i+3))!=1){
		return 'C';
	}
	else{
		return toUpper(i);
	}
}
//1:size: 
int Scramble (char* sentence){//same: char *sentence
	 char *p1, *p2;// one start in the beginning, one starts in the end
	 int n = 0;// n is length
	 char *cur = sentence;//*cur is sentence[0] now. same: char* cur=sentence
	 char temp;
	 int t=0;
	 int i=0;
	 
	 while(*cur != '\0') {
	 	n++;
	 	cur++;
	 }
	 p1 = sentence;
	 p2 = sentence + n - 1;
	 while(p1 < p2) {
	 	for(p1;p1 < p2;p1++){
	 		if(isXXX(*p1)){
	 			break;//jump out the for loop
	 		}
	 	}
	 	for(p2;p2 > p1;p2--){
	 		if( isXXX(*p2)){
	 			break;//jump out the for loop
	 		}
	 	}

	 	if(p1==p2) return t;//jump out the Scramble function

	 	temp=*p1;
	 	*p1=*p2;
		*p2=temp;
		t++;

		p1++;
		p2--;

	}
	return t;
}
void buildSentence(char** dictionary, char** newSentence, int numWordsInSentence, int numWordOptions){
	int i=0,j=0;    //char* type array
	for(i=0;i<numWordsInSentence;i++){
		j=(int)(rand() % numWordOptions);
		*( newSentence + i) = *(dictionary+i*numWordOptions+j);//the address of the first char of the i row
	}   //newSentence[i] is an element, same as *(newSentence+i)  //put address of dictionary to the element newsentence
}
int buildSentenceString (char** dictionary, char* newSentence, int numWordsInSentence, int numWordOptions){
	
	char* q;
	int j=0,p=0;
	int length=0;
	char* L=newSentence;
	for(p=0;p<numWordsInSentence;p++){
		j=(int)(rand() % numWordOptions);  //   numWordOptions *rand()/(RAND_MAX+1.0)
		q = *(dictionary+p*numWordOptions+j);
		while(*q!='\0'){
			*L++=*q++;
			length++;
		}
		*(L++)=' ';
		
		length++;
	}
	toUpper(newSentence);//toUpper use pointer, so i dont need to wirte newSentence[0]= this.
	
	*(L-1)='.';	
	*L='\0';
	return length;
}

int AcronymGenerator (char* sentence, char* acronymString, int type){
	int i=0,k=0,h=0;//for type 1
	int j=0,p=0,w=0;//for type 2
	int n=0;//length
	int z=0,x=0,c=0;//for special
	char *p1, *p2;
	char* v=sentence;
	char* _AR=(char*)malloc(50);
	char* AR = _AR;
	
	int jishu=0;

	if(type == 1){
		for(h=0;*(sentence+h)!='\0';h++){
			toUpper(sentence+h);
		}
		while( *(sentence+x) != '\0' ){
			if(isXXX2(*(sentence+x)) || *(sentence+x) == ' '){
				*AR=*(sentence+x);
				AR++;	
			}
			
			x++;
		}
		
		*(acronymString) = *(_AR);
		n++;
		for(i=1,k=1; *(_AR+i)!='\0'; i++){
			if( *(_AR+i) ==' '){
				*(acronymString+k) = *(_AR+i+1);
				k++;
				n++;
			}	
		}
		for(z=0; *v!='\0';z++){// for get two pointer in the beginning and ending
			v++;
		}
		p1=sentence;
		p2=sentence+z-1;

		while(ixXXX3(*p2)){
			p2--;
		}
		p2++;
		while( *p2 != '\0' ){
			*(acronymString+k)=*p2;
			p2++;
			k++;
			n++;
		}
		
		*(acronymString+k)='\0';
	}
	else if(type == 2){
		for(j=0;*(sentence+j)!='\0';j++){
			toUpper(sentence+j);
		}
		while( *(sentence+c) != '\0' ){
			if(isXXX2(*(sentence+c)) || *(sentence+c) == ' '){
				*AR=*(sentence+c);
				AR++;	
			}
			c++;
		}
		*(acronymString)=Change(_AR);
		n++;
		for(p=1,w=1; *(_AR+p)!='\0'; p++){
			if(*(_AR+p) == ' '){
				*(acronymString+w) = Change(_AR+p+1);
				w++;
				n++;
			}
		}
		for(z=0; *v!='\0';z++){
			v++;
		}
		p1=sentence;
		p2=sentence+z-1;

		while(ixXXX3(*p2)){
			p2--;
		}
		p2++;
		while( *p2 != '\0' ){
			*(acronymString+w)=*p2;
			p2++;
			w++;
			n++;
		}
		*(acronymString+w)='\0';
	}
	else{
		printf("Build nothing");
	}
	free(_AR);
	return n;


}





