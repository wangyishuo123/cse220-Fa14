// new one
// replace return???
#include <stdio.h>
//#include <unistd.h>   
#include <stdlib.h>
#include <string.h>

extern int opterr;
extern int optind;
extern int optopt;
extern char *optarg;
extern int getopt(int argc, char **argv, char *opts);
int isXXX(char* c){
   int i=0;
   if(c[0]=='I', c[1]=='\0'){
      return 0;
   }
   while(c[i]!='\0'){
      if ((c[i]-'A'>=0 && c[i]-'Z'<=0) || (c[i]-'0'>=0 && c[i]-'9'<=0)){}
      else{
         return 0;
      }
      i++;
   } 
   return 1;
}

struct pNode{ 
char phrase[30]; //string to hold the phrase (at most 29 chars) 
struct pNode* next; // pointer to next phrase in linked list 
 
// statistic about usage of phrase from dictionary file 
int freq; 
}; 

struct dNode { 

char a[5]; //acronyms can be at most 5 letters 
int num_children; //# of acronyms below node in tree 
int num_phrases; //# of phrases associated w/this acronym 
 
//linked list of other acronyms with this dNode as a parent 
struct dNode *siblings; 
 
struct dNode *children; //pointer to acronyms children 
 
//linked list of possible phrases which acronym map to 
struct pNode *phrases; 
};
struct dNode *mallocArray[1000];
int index=0;
void set_dstart(struct dNode *n){
   strcpy(n->a, NULL);
   n->num_children=0;
   n->num_phrases=0;
   n->siblings=NULL;
   n->children=NULL;
}
void set_pstart(struct pNode *n){
   strcpy(n->phrase, NULL);
   n->next=NULL;
   n->freq=0;
}

void addPhrase(struct dNode *n, int freq, char phra[]){
   struct pNode *pp = n->phrases;
   struct pNode prev_Node;
   struct pNode *prev_pNode = &prev_Node;

   struct pNode *temp;
   strcpy(prev_pNode->next->phrase,n->phrases->phrase);
   do{
      if(prev_pNode->next == NULL || prev_pNode->next->freq < freq){
         struct pNode *New_pNode1=(struct pNode*)malloc(50);
         set_pstart(New_pNode1);
         temp = prev_pNode->next;
         prev_pNode->next = New_pNode1;
         New_pNode1->next=temp;
         strcpy(New_pNode1->phrase, phra);
      }
      else{//n->phrases->freq >= freq
         prev_pNode = prev_pNode->next;
      }
   }while( prev_pNode->next != NULL);

   if( prev_pNode->freq > freq || prev_pNode->next == NULL){
      struct pNode *New_pNode2=(struct pNode*)malloc(50);
      set_pstart(New_pNode2);
      temp = prev_pNode->next;
      prev_pNode->next = New_pNode2;
      New_pNode2->next=temp;
      strcpy(New_pNode2->phrase, phra);
   }
}

void replace(struct dNode root, char s[]){
   int length = 0;
   int level = 0;
   struct dNode *cur = &root;
   struct dNode* dest;
   struct dNode *temp;
   char ph[]="";
   int found_string = 0;
   for(length=0;s[length]!=NULL;length++){}
   while(level < length){
      struct dNode *subcur = cur->children;
      if (subcur == NULL || subcur->a[level] > s[level]) {//LB>LA
         struct dNode *_newNode=(struct dNode*)malloc(50);
         set_dstart(_newNode);
         //struct dNode* newNode=_newNode;
         //putinto a empty new node first, then add information into this empty new node.
         temp = subcur;
         subcur = _newNode;
         _newNode->siblings=temp;
       strncpy(_newNode->a, s, level+1); 
      }
     else{
        struct dNode prevNode;
        struct dNode *prev = &prevNode;
        int found = 0;
          prev->siblings = subcur;
         while( prev->siblings!=NULL && prev->siblings->a[level] <= s[level]){
            if( prev->siblings->a[level] == s[level] ){
               cur = prev->siblings;
                   if(level = length){
                  dest = prev->siblings;
                  found_string = 1;
                   }
               found = 1;
                   break; 
            }
            else{
               prev = prev->siblings;
            }
         }
         if( !found ){
            struct dNode *NEWNODE=(struct dNode*)malloc(50);
            struct dNode *temp = prev->siblings;
            set_dstart(NEWNODE);
            prev->siblings = NEWNODE;
            NEWNODE->siblings=temp;
            strncpy(NEWNODE->a, s, level+1);
         }
     }
     level++;
   }
   printf("\"%s\"\n",s);
   if(found_string){
      printf("Replace %s with\n",s);
      int i = 1;
      int k=1;
      struct pNode *tem = dest->phrases;
      struct pNode *Tem = dest->phrases;
      while(tem!=NULL){
         printf("%d: \"%s\"\n",i,tem->phrase);
         i++;
         tem = tem->next;
      }
      printf("%d: Enter new phrase: \n",i);
      printf("Choice (1-%d)?",i);
      scanf("%d",&k);
      if(k==i){
         scanf("%s",ph);
         addPhrase(dest, 1, ph);
         return ph;
      }
      else{
         
         while(--k){
            Tem = Tem->next;
         }
         s=Tem->phrase;
         return s;
      }

   }
   else{
      printf("%s is not found.\n",s);
      printf("Enter a new phrase for %s:",s);
      scanf("%s",ph);
      addPhrase(dest, 1, ph);
      return ph;
   }
   
}

void insertElement(struct dNode root, char Cap[], int freq, char phra[]){
   int i=0;
   int length=0;//the length of the string 
   struct dNode *cur = &root;//cur is a pointer that exist in the tree
   int level = 0;           //phrase is the new Node we want to add
   struct dNode* dest;
   struct dNode *temp;
   for(length=0; Cap[length]!=NULL; length++){}
   while (level < length) {
      struct dNode *subcur = cur->children;
      //if the insert position is the head
      if (subcur == NULL || subcur->a[level] > Cap[level]) {//LB>LA
         struct dNode *_newNode=(struct dNode*)malloc(50);
         set_dstart(_newNode);
         //struct dNode* newNode=_newNode;
         //putinto a empty new node first, then add information into this empty new node.
         temp = subcur;
         subcur = _newNode;
         _newNode->siblings=temp;

         strncpy(_newNode->a, Cap, level+1);
      }

      else {//subcur->acronym[level] <= phrase[level]-----LB<=LO
         struct dNode prevNode;
         struct dNode *prev = &prevNode;
       int found = 0;
         prev->siblings = subcur;
         
         while( prev->siblings!=NULL && prev->siblings->a[level] <= Cap[level]){
            //subcur is not null, and the node in the same level of the tree, the first one biger than phrase, is the position to add
            if( prev->siblings->a[level] == Cap[level] ){  //cur->acronym[level] = *(cur).acronym[level]
               cur = prev->siblings;
               
               if(level = length){
                  dest = prev->siblings;
               }
               
               found = 1;
               break;
            }
            else{
               prev = prev->siblings;
            }
         }
         if( !found ){
            struct dNode *NEWNODE=(struct dNode*)malloc(50);
            struct dNode *temp = prev->siblings;
            set_dstart(NEWNODE);
            prev->siblings = NEWNODE;
            NEWNODE->siblings=temp;
            strncpy(NEWNODE->a, Cap, level+1);
         }        
      }
      level++;
   }
   addPhrase(dest, freq, phra);
}

int main(int argc, char *argv[]){
   int opt;
   char *fd = "AcroDict.txt";
   char *fi = NULL;
   char *fo = "output.txt";
   FILE *in_put;
   FILE *out_put;
   FILE *our_dic;
   struct dNode root;
   char Cap[100];
   int freq_int=0;
   char freq[100];
   char phra[100];
   char line[100];  
   int p=0,q=0,w=0,e=0;
   opt = getopt(argc, argv, "d:i:o:");
   while(opt != -1){
      switch(opt){
         case 'd':
            if (optarg!=NULL)
            fd=optarg;
            break;
         case 'i':
            fi=optarg;
            break;
         case 'o':
            if (optarg!=NULL)
            fo=optarg;
            break;
         case '?':
            printf("invalid input");
            break;
         default:
            break;
      }
   }

   //read dictionary file and make the tree in the computer
   
 
   our_dic = fopen(fd,"r");
   if( our_dic == NULL){
      fprintf(stderr, "Cannot open input file.\n");
      return 1;
   }
   else{
      while( fgets(line, 100, our_dic)!=NULL ){
         while(line[p]!='\n'){
            if(line[p]!=' '){
               Cap[q]=line[p];
               p++,q++;
            }
            else{
               p++;
               break;
            }  
         }
         while(line[p]!='\n'){
            if(line[p]!=' '){
               freq[w]=line[p];
               p++,w++;
            }
            else{
               freq_int=atoi(freq);
               p++;
               break;
            }  
         }
         while(line[p]!='\n'){
            phra[e]=line[p];
            p++,e++;
         }
         insertElement(root, Cap, freq_int, phra);
      }
   }
   fclose(our_dic);

  //read input file
   in_put = fopen(fi,"r");
   if( in_put ==NULL ){
      fprintf(stderr, "Cannot open input file.\n");
      return 1;
   }
   else{
      while( fgets(line, 100,in_put)!=NULL ){
         char *delim = " ";
         char *s = strtok(line,delim);
         while(s){ 
            if(isXXX(s)){
               replace(root, s);
            }
            s = strtok(NULL, delim);
       }
     }
   }
}
     /*
   //write output file
   out_put = fopen(*fo,"w");
   if(out_put == NULL){
      
   }

   //build a tree
   

   
   


   //for each line
   if ( fi != NULL) {
      replace(root, freq, phrase);
   }else {
      for(scanf){
      //
      replace(root, freq, phrase);      
   }
   */
  

   
  


    /*
    double a = 1234567.23456789, b = 4567890123.56789012;
    stream = fopen("a.txt", "w");//open the file, and just write in it.
    fprintf(stream, "%16.6f ", a);
    fprintf(stream, "%16.6f ", b);
    fclose(stream);
    
    stream = fopen("a.txt", "r");//open the file, and just read it.
    fscanf(stream, "%lf", &a);
    fscanf(stream, "%lf", &b);
    fclose(stream);
    printf("%f %f\n", a, b);
}

   
   free(_AR);*/

