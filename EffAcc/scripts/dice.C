#include <math.h>
#include <algorithm>
#include <list>
#include <iostream>

void vout(int ndice,int dice,int add,int maxi, int mini){
  std::cout<<ndice<<"d"<<dice<<"+"<<add<<" range:"<<mini<<"-"<<maxi<<std::endl;

  
}

void conciseout(int ndice,int dice,int add){
  std::cout<<ndice<<"d"<<dice<<"+"<<add<<std::endl;
}

void dice(int lvl,int maxD,int mxdice,int vbose){
  // if(maxD==-1)maxD==99999;
  int ave=lvl+8;
  int dice[10]={12,10,8,6,4,2,0};
  double adice[10]={6.5,5.5,4.5,3.5,2.5,1.5,0.5};
  int ndice[10]={1,2,3,4,5,6,7,8,9,10};
  int diceblock[100][15];
  
  for(int b=0;b<100;b++)
    for(int b2=0;b2<15;b2++)
      diceblock[b][b2]=-99;
  
  for(int j=0;ndice[j]<mxdice+1;j++){
    if(vbose<3)     std::cout<<ndice[j]<<" Dice:"<<std::endl;
    for(int i=0;dice[i]>0;i++){
      
      int add,maxi,mini;
      add=(int)(ave-(int)(ndice[j]*adice[i]));
      if(add < 0) continue;
      maxi=dice[i]*ndice[j]+add;
      if(maxi > (maxD+2))continue;
      mini=ndice[j]+add;
      if (vbose==0)conciseout(ndice[j],dice[i],add);
      if(vbose==1)vout(ndice[j],dice[i],add,maxi,mini);
      if(vbose==2)vout(ndice[j],dice[i],add,maxi-mini,maxi);
      
      diceblock[add][ndice[j]]=dice[i];
    }//j
    
    if(vbose<3)   std::cout<<""<<std::endl;
  }//i
  
  if(vbose==3){
    for(int b=0;b<maxD+1;b++){
      for(int b2=0;b2<15;b2++)
	if(diceblock[b][b2]>0)
	  conciseout(b2,diceblock[b][b2],b);
      std::cout<<""<<std::endl;
    }
  }
  if(vbose>3){
    for(int j=0;ndice[j]<mxdice+1;j++){
      for(int i=0;dice[i]>0;i++){
	int lvl=((int)(ndice[j]*adice[i]))-8;
       diceblock[lvl][ndice[j]]=dice[i];
	if(vbose==4)	conciseout(ndice[j],dice[i],lvl);
      }//i
    }//j
    if(vbose==5){
      for(int b=0;b<60;b++)
	for(int b2=0;b2<15;b2++)
	  if(diceblock[b][b2]>-20)
	    conciseout(b2,diceblock[b][b2],b);
      std::cout<<""<<std::endl;}
  }//if 4
  
}//end dice.C


#ifdef NEED_MAIN

int main(int argc, char* argv[]) {
  if (argc<4) {
    printf("?????? [lvl] [maximum damage] [maximum dice]  [0,1,verbose]");
    return 1;
  }

    int ave=atoi(argv[1]);
    int max =atoi(argv[2]);
    int mxd=atoi(argv[3]);
    int vb=atoi(argv[4]);
    
    dice(ave,max,mxd,vb);
  
  std::cout<<"@@@@20"<<std::endl;
  return 0;
}

// gcc -o dice.exe dice.C -DNEED_MAIN -O `root-config --cflags --libs`
// ./dice.exe
//

#endif



