#pragma warning( disable : 4996) 
#pragma warning( disable : 4101)
#pragma warning( disable : 4715) 

#include<stdio.h>   
#include <memory.h>   
#include <time.h>  
#include <stdlib.h>  

//��ʼ�û���IP   
int IP_Table[64] = {   57,49,41,33,25,17, 9,1,   
                       59,51,43,35,27,19,11,3, 
                       61,53,45,37,29,21,13,5, 
                       63,55,47,39,31,23,15,7,
                       56,48,40,32,24,16, 8,0,  
                       58,50,42,34,26,18,10,2, 
					   60,52,44,36,28,20,12,4, 
                       62,54,46,38,30,22,14,6};    
//���ʼ�û���IP^-1   
int IP_1_Table[64] = {39,7,47,15,55,23,63,31,   
                      38,6,46,14,54,22,62,30,   
                      37,5,45,13,53,21,61,29,   
                      36,4,44,12,52,20,60,28,   
                      35,3,43,11,51,19,59,27,   
                      34,2,42,10,50,18,58,26,   
                      33,1,41,9,49,17,57,25,   
                      32,0,40,8,48,16,56,24};   
  
//�����û���E   
int E_Table[48] = {31, 0, 1, 2, 3, 4,   
                  3,  4, 5, 6, 7, 8,   
                  7,  8,9,10,11,12,   
                  11,12,13,14,15,16,   
                  15,16,17,18,19,20,   
                  19,20,21,22,23,24,   
                  23,24,25,26,27,28,   
                  27,28,29,30,31, 0};   
  
//�û�����P   
int P_Table[32] = {15,6,19,20,28,11,27,16,   
                  0,14,22,25,4,17,30,9,   
                  1,7,23,13,31,26,2,8,   
                  18,12,29,5,21,10,3,24};   
  //S��   
int S[8][4][16] =//S1   
            {{{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},   
              {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},   
              {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0}, 
              {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},   
                //S2   
             {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},  
              {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},   
              {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},   
              {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},  
                //S3   
              {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},  
               {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},   
               {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7}, 
               {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},  
			   //S4   
              {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},  
               {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},   
               {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},   
               {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},  
                //S5   
              {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},  
               {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},   
              {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},   
              {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},  
               //S6   
              {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},  
               {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},   
              {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},   
              {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},  
               //S7   
              {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},  
               {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},   
              {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},   
              {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},  
               //S8   
              {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},  
               {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},   
              {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},   
              {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}}; 
//�û�ѡ��1   
int PC_1[56] = {56,48,40,32,24,16,8,   
              0,57,49,41,33,25,17,   
              9,1,58,50,42,34,26,   
              18,10,2,59,51,43,35,   
              62,54,46,38,30,22,14,   
              6,61,53,45,37,29,21,   
              13,5,60,52,44,36,28,   
              20,12,4,27,19,11,3};   
 //�û�ѡ��2   
int PC_2[48] = {13,16,10,23,0,4,2,27,   
              14,5,20,9,22,18,11,3,   
              25,7,15,6,26,19,12,1,   
              40,51,30,36,46,54,29,39,   
              50,44,32,46,43,48,38,55,   
              33,52,45,41,49,35,28,31};   
//�����ƴ����Ĺ涨   
int MOVE_TIMES[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};  

void  ByteToBit(char ch,char bit[8]);   
void  BitToByte(char bit[8],char *ch);   
void  Char8ToBit64(char ch[8],char bit[64]);   
void  Bit64ToChar8(char bit[64],char ch[8]);   
void  DES_MakeSubKeys(char key[64],char subKeys[16][48]);   
void  DES_PC1_Transform(char key[64], char tempbts[56]);   
void  DES_PC2_Transform(char key[56], char tempbts[48]);   
void  DES_ROL(char data[56], int time);   
void  DES_IP_Transform(char data[64]);   
void  DES_IP_1_Transform(char data[64]);   
void  DES_E_Transform(char data[48]);   
void  DES_P_Transform(char data[32]);   
void  DES_SBOX(char data[48]);   
void  DES_XOR(char R[48], char L[48],int count);   
void  DES_Swap(char left[32],char right[32]);   
void  DES_E_D_Block(char plainBlock[8], char subKeys[16][48], char cipherBlock[8]);   
int  DES_Encrypt(char *plainFile, char *keyStr,char *cipherFile);   
int  DES_Decrypt(char *cipherFile, char *keyStr,char *plainFile); 
//�ֽ�ת���ɶ�����   
void ByteToBit(char ch, char bit[8])
{   int cnt;   
    for(cnt = 0;cnt < 8; cnt++)
		*(bit+cnt) = (ch>>cnt)&1;
}   
//������ת�����ֽ�   
void  BitToByte(char bit[8],char *ch)
{   int cnt;   
    for(cnt = 0;cnt < 8; cnt++)
		*ch |= *(bit + cnt)<<cnt;
}   
//������Ϊ8���ַ���תΪ������λ��   
void  Char8ToBit64(char ch[8],char bit[64]) 
{   
    int cnt;   
    for(cnt = 0; cnt < 8; cnt++)
		ByteToBit(*(ch+cnt),bit+(cnt<<3));
}   
//��������λ��תΪ����Ϊ8���ַ���   
void  Bit64ToChar8(char bit[64],char ch[8])
{   int cnt;   
    memset(ch,0,8);   
    for(cnt = 0; cnt < 8; cnt++)
		BitToByte(bit+(cnt<<3),ch+cnt);  
}   
//��������λ��תΪ����Ϊ6���ַ���   
void  Bit48ToChar6(char bit[48],char ch[6])
{   int cnt;   
    memset(ch,0,6);   
    for(cnt = 0; cnt < 6; cnt++)
		BitToByte(bit+(cnt<<3),ch+cnt); 
} 
//��������Կ   
void  DES_MakeSubKeys(char key[64],char subKeys[16][48])
{   
    char temp[56];
	char ch[6];
    int cnt; 
	int i;
	printf("\n����������Կ��\n");
    DES_PC1_Transform(key,temp);//PC1�û�   
    for(cnt = 0; cnt < 16; cnt++)
	{//16�ֵ���������16������Կ   
        DES_ROL(temp,MOVE_TIMES[cnt]);//ѭ������   
        DES_PC2_Transform(temp,subKeys[cnt]);//PC2�û���
        Bit48ToChar6(subKeys[cnt],ch);
        for(i=0;i<6;i++)
		{printf("%2X  ",(unsigned char)ch[i]);}
		printf("\n");
//��������Կ   
   }   
}   
//��Կ�û�1   
void  DES_PC1_Transform(char key[64], char tempbts[56])
{   
    int cnt;       
    for(cnt = 0; cnt < 56; cnt++)
        tempbts[cnt] = key[PC_1[cnt]];   
 }   
 //��Կ�û�2   
void  DES_PC2_Transform(char key[56], char tempbts[48])
{   
    int cnt;   
    for(cnt = 0; cnt < 48; cnt++)
        tempbts[cnt] = key[PC_2[cnt]];   
}   
//ѭ������   
void  DES_ROL(char data[56], int time)
{      
    char temp[4];   
    //���潫Ҫѭ���ƶ����ұߵ�λ   
    memcpy(temp,data,time);   
    memcpy(temp+time,data+28,time);   
    //ǰ28λ�ƶ�   
    memcpy(data,data+time,28-time);   
    memcpy(data+28-time,temp,time);   
    //��28λ�ƶ�   
    memcpy(data+28,data+28+time,28-time);   
    memcpy(data+56-time,temp+time,time);       
 }   
//IP�û�   
void  DES_IP_Transform(char data[64])
{   int cnt;   
    char temp[64];   
    for(cnt = 0; cnt < 64; cnt++)
        temp[cnt] = data[IP_Table[cnt]];   
    memcpy(data,temp,64);   
 }   
//IP���û�   
void  DES_IP_1_Transform(char data[64])
{   
    int cnt;   
    char temp[64];   
    for(cnt = 0; cnt < 64; cnt++)   
        temp[cnt] = data[IP_1_Table[cnt]];      
    memcpy(data,temp,64);   
 }   
//��չ�û�   
void  DES_E_Transform(char data[48])
{   int cnt;   
    char temp[48];   
    for(cnt = 0; cnt < 48; cnt++) 
        temp[cnt] = data[E_Table[cnt]];         
    memcpy(data,temp,48);   
}   
//P�û�   
void  DES_P_Transform(char data[32])
{   int cnt;   
    char temp[32];   
    for(cnt = 0; cnt < 32; cnt++) 
        temp[cnt] = data[P_Table[cnt]];     
    memcpy(data,temp,32);   
 }   
 //���   
void  DES_XOR(char R[48], char L[48] ,int count)
{  
    int cnt;   
    for(cnt = 0; cnt < count; cnt++)
        R[cnt] ^= L[cnt];   
}   
//S���û�   
void  DES_SBOX(char data[48])
{   
    int cnt;   
    int line,row,output;   
    int cur1,cur2;   
    for(cnt = 0; cnt < 8; cnt++){   
        cur1 = cnt*6;   
        cur2 = cnt<<2;   
        //������S���е�������   
        line = (data[cur1]<<1) + data[cur1+5];   
        row = (data[cur1+1]<<3) + (data[cur1+2]<<2)   
            + (data[cur1+3]<<1) + data[cur1+4];   
        output = S[cnt][line][row];   
        //��Ϊ2����   
        data[cur2] = (output&0X08)>>3;   
        data[cur2+1] = (output&0X04)>>2;   
        data[cur2+2] = (output&0X02)>>1;   
        data[cur2+3] = output&0x01;   
    }      
}   
//����   
void  DES_Swap(char left[32], char right[32])
{   
    char temp[32];   
    memcpy(temp,left,32);      
    memcpy(left,right,32);     
    memcpy(right,temp,32);   
 }   
//�ӽ��ܵ�������   
void  DES_E_D_Block(char plainBlock[8], char subKeys[16][48], char cipherBlock[8])
{   
    char plainBits[64],copyRight[48],zjjg[8];
	int i,cnt; 
	printf("\n\n������16���м�����16����ֵ:\n");
    Char8ToBit64(plainBlock,plainBits);//Char8ToBit64(char ch[8],char bit[64]);
    DES_IP_Transform(plainBits); //��ʼ�û���IP�û���        
    for(cnt = 0; cnt < 16; cnt++){ //16�ֵ���      
        memcpy(copyRight,plainBits+32,32);             
        DES_E_Transform(copyRight); //���Ұ벿�ֽ�����չ�û�����32λ��չ��48λ        
        DES_XOR(copyRight,subKeys[cnt],48); //���Ұ벿��������Կ����������              
        DES_SBOX(copyRight); //���������S�У����32λ���   
        DES_P_Transform(copyRight); //P�û�          
        DES_XOR(plainBits,copyRight,32); //��������벿�����Ұ벿�ֽ������   
        if(cnt != 15){//����������Ҳ��Ľ���   
            DES_Swap(plainBits,plainBits+32); }
		Bit64ToChar8(plainBits,zjjg);
		for(i=0;i<8;i++)
		{printf("%2X  ",(unsigned char)zjjg[i]);}
		printf("\n");}   
    //���ʼ�û���IP^1�û���   
    DES_IP_1_Transform(plainBits);   
    Bit64ToChar8(plainBits,cipherBlock); 
	Bit64ToChar8(plainBits,zjjg);
     printf("�������û������16���ƽ����\n");
	for(i=0;i<8;i++)
		{printf("%2X  ",(unsigned char)zjjg[i]);}
		printf("\n");
}   
//�����ļ�   
int DES_Encrypt(char *plainFile, char *keyFile,char *cipherFile)
{   
    FILE *plain,*cipher,*key;   
    int count,i;   
    char plainBlock[8],cipherBlock[8],keyBlock[8],bKey[64],subKeys[16][48];   
     printf("************����************\n");
	if((plain = fopen(plainFile,"rb")) == NULL){ 
		printf("\n�򿪡����ġ��ļ�ʱ����\n"); system("pause"); return 0;}  
    if((key = fopen(keyFile,"rb")) == NULL){   
        printf("\n�򿪡���Կ���ļ�ʱ����\n"); system("pause"); return 0;}
    if((cipher = fopen(cipherFile,"wb")) == NULL){   
        printf("\n�򿪡����ġ��ļ�ʱ����\n"); system("pause"); return 0;} 
	
	//������Կ   
   count=fread(keyBlock,sizeof(char),8,key);
    if(count<8)
	{memset(keyBlock+count,'\0',7-count);
	keyBlock[7]=8-count;}
		printf("��Կ��16���Ʊ�ʾ:\n");
		for(i=0;i<8;i++)
		{printf("%2X  ",(unsigned char)keyBlock[i]);}
		printf("\n");
    //����Կת��Ϊ��������   
    Char8ToBit64(keyBlock,bKey);   
    //��������Կ   
    DES_MakeSubKeys(bKey,subKeys);   

       while(!feof(plain)){//ÿ�ζ�8���ֽڣ������سɹ���ȡ���ֽ���   
        if((count = fread(plainBlock,sizeof(char),8,plain)) == 8){   
            DES_E_D_Block(plainBlock,subKeys,cipherBlock); 
		    fwrite(cipherBlock,sizeof(char),8,cipher);}}

    if(count<8&&count>0){//���   
        memset(plainBlock + count,'\0',7 - count);   
        //���һ���ַ�����������һ���ַ����ڵ��������ַ�����   
        plainBlock[7] = 8 - count;   
        DES_E_D_Block(plainBlock,subKeys,cipherBlock);   
        fwrite(cipherBlock,sizeof(char),8,cipher);}

    fclose(plain);   
    fclose(cipher);  
	fclose(key); 
 }   
 //�����ļ�   
int DES_Decrypt(char *cipherFile, char *keyFile,char *plainFile)
{   
    FILE *plain, *cipher,*key;   
    int count,i,times = 0;   
    long fileLen;   
    char plainBlock[8],cipherBlock[8],keyBlock[8],bKey[64],subKeys[16][48],temp[48];
    printf("************����************\n");
	if((cipher = fopen(cipherFile,"rb")) == NULL){
		 printf("\n�򿪡����ġ��ļ�ʱ����\n"); system("pause"); return 0;}
	if((key = fopen(keyFile,"rb")) == NULL){   
         printf("\n�򿪡���Կ���ļ�ʱ����\n"); system("pause"); return 0;}
    if((plain = fopen(plainFile,"wb")) == NULL){ 
		 printf("\n�򿪡����Ļ�ԭ���ļ�ʱ����\n"); system("pause"); return 0;}   
     //������Կ   
    count=fread(keyBlock,sizeof(char),8,key); 
	if(count<8)
	{memset(keyBlock+count,'\0',7-count);
	keyBlock[7]=8-count;}
    printf("��Կ��16���Ʊ�ʾ:\n");
    for(i=0;i<8;i++)
		{printf("%2X  ",(unsigned char)keyBlock[i]);}
		printf("\n");
	//����Կת��Ϊ��������   
    Char8ToBit64(keyBlock,bKey);   
	//��������Կ   
    DES_MakeSubKeys(bKey,subKeys); 
	//ת��Ϊ������Կ

	for(i=0;i<8;i++){
	 memcpy(temp,subKeys[i],48);
     memcpy(subKeys[i],subKeys[15-i],48);
     memcpy(subKeys[15-i],temp,48);}

	//ȡ�ļ�����    
    fseek(cipher,0,SEEK_END);   //���ļ�ָ����β   
    fileLen = ftell(cipher);    //ȡ�ļ�ָ�뵱ǰλ��   
    rewind(cipher);             //���ļ�ָ����ָ���ļ�ͷ 
    	while(1){   
        //���ĵ��ֽ���һ����8��������   
        fread(cipherBlock,sizeof(char),8,cipher);   
        DES_E_D_Block(cipherBlock,subKeys,plainBlock);                        
        times += 8;   
        if(times < fileLen)
			fwrite(plainBlock,sizeof(char),8,plain);   
        else break;}

    //�ж�ĩβ�Ƿ����   
    if(plainBlock[7] < 8){   
        for(count = 8 - plainBlock[7]; count < 7; count++)
			if(plainBlock[count] !='\0') break;}
    if(count == 7){//�����   
		fwrite(plainBlock,sizeof(char),8 - plainBlock[7],plain);}   
    else{//�����   
        fwrite(plainBlock,sizeof(char),8,plain);}   
  
    fclose(plain);   
    fclose(cipher);
	fclose(key);
}  
void main()   
{   
     int i,x,a,b;

	printf("��ѡ������Ҫ�ķ���\n");
        printf("1.�ļ�����.\n");
        printf("2.�ļ�����.\n");
        printf("3.�˳�����.\n");
   printf("��������ѡ��:");
   scanf("%x",&x);
        
	switch(x)
	{
	case 1:  
		   system("cls");
           DES_Encrypt("����.txt","��Կ.txt","����.txt");   
		   break;
    case 2:
		   system("cls");
           DES_Decrypt("����.txt","��Կ.txt","���ܺ�.txt");   
		   break;
    case 3:
		exit(0);
    default:{printf("����������������룺\n");}
	}
}