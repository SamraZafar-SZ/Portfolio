

#include <iostream>
#include <cstring>
using namespace std;
class Roman{
  char r[30];
  int length;
  public:
  Roman(char []);
  int romtoint();
  void int_roman(int);
  bool operator==(Roman& R2);
  bool operator!=(Roman& R2);
  bool operator>(Roman& R2);
  bool operator<(Roman& R2);
  void operator+( Roman&);
  void operator-( Roman&);
  void operator*( Roman&);
  void operator/( Roman&);
  void operator++();
  void operator--();
  void operator++(int);
  void operator--(int);
};
Roman::Roman(char roman[]){
    int len=strlen(roman); int i;
    for(i=0;i<len;i++){
        r[i]=roman[i];
    }
    r[i]='\0';
}
//In roman system, a character of less value can't come two times before a greater one. Like: XL is valid for 40 
//but XXL is not valid for 30. Also, only selected smaller digits can come before the larger ones. Like: IV is 
//valid for 4 but VL is not valid for 45. Rather 45 is XLV. //*****All of these are tackled.*****//
int Roman::romtoint(){ //following standard roman numeral subtractive order//
    int ans=0;
    for(int i=0;i<strlen(r);i++){
        if(r[i]==r[i+1]&&r[i+1]==r[i+2]&&r[i+2]==r[i+3]){
        cout<<"invalid roman notation\nEnter again a valid numeral to run program\n"; exit(0);}
        if(r[i]=='I'){
            if(r[i+1]=='V'||r[i+1]=='X')
            ans=ans;
            else if(r[i+1]=='L'||r[i+1]=='C'||r[i+1]=='D'||r[i+1]=='M'){
            cout<<"invalid roman notation\nEnter again a valid numeral to run program\n"; exit(0);}
            else
            ans=ans+1;
        }
        else if(r[i]=='V'){
            if(r[i+1]=='X'||r[i+1]=='L'||r[i+1]=='C'||r[i+1]=='D'||r[i+1]=='M'){
            cout<<"invalid roman notation\nEnter again a valid numeral to run program\n"; exit(0);}
            else if(r[i-1]=='I'&&r[i-2]!='I')
            ans=ans+4;
            else if(r[i-1]=='I'&&r[i-2]=='I'&&r[i-3]=='I'){
            cout<<"invalid roman notation\nEnter again a valid numeral to run program\n"; exit(0);}
            else if(r[i-1]=='I'&&r[i-2]=='I'){
            cout<<"invalid roman notation\nEnter again a valid numeral to run program\n"; exit(0);}
            else
            ans=ans+5;
        
    }
        else if(r[i]=='X'){
        if(r[i+1]=='L'||r[i+1]=='C')
            ans=ans;
            else if(r[i+1]=='D'||r[i+1]=='M'){
            cout<<"invalid roman notation\nEnter again a valid numeral to run program\n"; exit(0);}
            else if(r[i-1]=='I'&&r[i-2]!='I')
            ans=ans+9;
            else if(r[i-1]=='I'&&r[i-2]=='I'&&r[i-3]=='I'){
            cout<<"invalid roman notation\nEnter again a valid numeral to run program\n"; exit(0);}
            else if(r[i-1]=='I'&&r[i-2]=='I'){
            cout<<"invalid roman notation\nEnter again a valid numeral to run program\n"; exit(0);}
            else
            ans=ans+10;
        }
        else if(r[i]=='L'){
             if(r[i+1]=='C'||r[i+1]=='D'||r[i+1]=='M'){
            cout<<"invalid roman notation\nEnter again a valid numeral to run program\n"; exit(0);}
            else if(r[i-1]=='X'&&r[i-2]!='X')
            ans=ans+40;
            else if(r[i-1]=='X'&&r[i-2]=='X'&&r[i-3]=='X'){
            cout<<"invalid roman notation\nEnter again a valid numeral to run program\n"; exit(0);}
            else if(r[i-1]=='X'&&r[i-2]=='X'){
            cout<<"invalid roman notation\nEnter again a valid numeral to run program\n"; exit(0);}
            else
            ans=ans+50;
        }
        else if(r[i]=='C'){
            if(r[i+1]=='D'||r[i+1]=='M')
            ans=ans;
            else if(r[i-1]=='X'&&r[i-2]!='X')
            ans=ans+90;
            else if(r[i-1]=='X'&&r[i-2]=='X'&&r[i-3]=='X'){
            cout<<"invalid roman notation\nEnter again a valid numeral to run program\n"; exit(0);}
            else if(r[i-1]=='X'&&r[i-2]=='X'){
            cout<<"invalid roman notation\nEnter again a valid numeral to run program\n"; exit(0);}
            else
            ans=ans+100;
        }
        else if(r[i]=='D'){
            if(r[i+1]=='M'){
            cout<<"invalid roman notation\nEnter again a valid numeral to run program\n"; exit(0);}
            else if(r[i-1]=='C'&&r[i-2]!='C')
            ans=ans+400;
            else if(r[i-1]=='C'&&r[i-2]=='C'){
            cout<<"invalid roman notation\nEnter again a valid numeral to run program\n"; exit(0);}
            else if(r[i-1]=='C'&&r[i-2]=='C'&&r[i-3]=='C'){
            cout<<"invalid roman notation\nEnter again a valid numeral to run program\n"; exit(0);}
            else
            ans=ans+500;
        }
        else if(r[i]=='M'){
        if(r[i-1]=='C'&&r[i-2]!='C')
            ans=ans+900;
            else if(r[i-1]=='C'&&r[i-2]=='C'&&r[i-3]=='C'){
            cout<<"invalid roman notation\nEnter again a valid numeral to run program\n"; exit(0);}
            else if(r[i-1]=='C'&&r[i-2]=='C'){
            cout<<"invalid roman notation\nEnter again a valid numeral to run program\n"; exit(0);}
            else
            ans=ans+1000;
        }
    }
    //cout<<"in integer: "<<ans<<endl;
    return ans;
}
//The roman system is only for 1-3999. in case a number greater than or equal to 4000 is given, a bar is unsed 
//to represent 1000. Like VI(bar) means 6000. 10800 is X(bar),DCCC. This case has been tackled. 
//***In case of many thousands, output comes in two lines (with bar and remainder)***//
void Roman::int_roman(int num){
  char a[]={'M','D','C','L','X','V','I'};
  int n[]={1000,500,100,50,10,5,1};
  char result[30]={'\0'}; int i=0;
  if(num==0||num<=0)
  cout<<"---\nzero OR -ve integers are invalid in roman"<<endl;
  if(num>=4000){
      int thousands, remain, c;
      thousands=num/1000;
      cout<<" (with bar) ";
      int_roman(thousands);
      remain=num-(thousands*1000);
      num=remain;
      if(num==0)
      cout<<"remainder -"<<endl;
      else
      cout<<"remiander ";
  }
  while(num>0){
    if(num/1000>=1){
        result[i]='M'; i++; num=num-1000;
    }
    else if(num/500>=1){
        if(num>=900){
        result[i]='C'; result[i+1]='M'; num=num-900; i=i+2;}
        else if(num>=800){
        result[i]='D'; result[i+1]='C'; result[i+2]='C'; result[i+3]='C'; num=num-800; i=i+4;}
        else if(num>=700){
        result[i]='D'; result[i+1]='C'; result[i+2]='C'; num=num-700; i=i+3;}
        else if(num>=600){
        result[i]='D'; result[i+1]='C';  num=num-600; i=i+2;}
        else if(num>=500){
        result[i]='D'; num=num-500; i=i+1;}
    }
    else if(num/100>=1){
        if(num>=400){
        result[i]='C'; result[i+1]='D'; num=num-400; i=i+2;}
        else if(num>=300){
        result[i]='C'; result[i+1]='C'; result[i+2]='C'; num=num-300; i=i+3;}
        else if(num>=200){
        result[i]='C'; result[i+1]='C'; num=num-200; i=i+2;}
        else if(num>=100){
        result[i]='C'; num=num-100; i=i+1;}
    }
    else if(num/50>=1){
        if(num>=90){
        result[i]='X'; result[i+1]='C'; num=num-90; i=i+2;}
        else if(num>=80){
        result[i]='L'; result[i+1]='X'; result[i+2]='X'; result[i+3]='X'; num=num-80; i=i+4;}
        else if(num>=70){
        result[i]='L'; result[i+1]='X'; result[i+2]='X'; num=num-70; i=i+3;}
        else if(num>=60){
        result[i]='L'; result[i+1]='X';  num=num-60; i=i+2;}
        else if(num>=50){
        result[i]='L'; i=i+1; num=num-50;}
    }
    else if(num/10>=1){
        if(num>=40){
        result[i]='X'; result[i+1]='L'; num=num-40; i=i+2;}
        else if(num>=30){
        result[i]='X'; result[i+1]='X'; result[i+2]='X'; num=num-30; i=i+3;}
        else if(num>=20){
        result[i]='X'; result[i+1]='X'; num=num-20; i=i+2;}
        else if(num>=10){
        result[i]='X'; i=i+1; num=num-10;}
    }
    else if(num/5>=1){
        if(num==9){
        result[i]='I'; result[i+1]='X'; num=num-9; i=i+2;}
        else if(num==8){
        result[i]='V'; result[i+1]='I'; result[i+2]='I'; result[i+3]='I'; num=num-8; i=i+4;}
        else if(num==7){
        result[i]='V'; result[i+1]='I'; result[i+2]='I'; num=num-7; i=i+3;}
        else if(num==6){
        result[i]='V'; result[i+1]='I';  num=num-6; i=i+2;}   
        else if(num==5){
        result[i]='V'; num=num-5; i=i+1;}
        
    }
    else if(num/1>=1){
        if(num==4){
        result[i]='I'; result[i+1]='V'; num=num-4; i=i+2;}
        else if(num==3){
        result[i]='I'; result[i+1]='I'; result[i+2]='I'; num=num-3; i=i+3;}
        else if(num==2){
        result[i]='I'; result[i+1]='I'; num=num-2; i=i+2;}
        else if(num==1)
        result[i]='I'; num=num-1;
    }
  }
   cout<<"in roman: "<<result<<endl;
}
void Roman::operator+(Roman& R){
    int sum; int a,b;
    a=R.romtoint();
    b=romtoint();
    sum=a+b;
    cout<<"***sum is***"<<endl;
    cout<<sum<<"/";
    int_roman(sum);
}
void Roman::operator-(Roman& R){
    int diff; int a,b;
    a=R.romtoint();
    b=romtoint();
    diff=b-a;
    cout<<"***difference is***"<<endl;
    cout<<diff<<"/";
    int_roman(diff);
}
void Roman::operator*(Roman& R){
    int mul; int a,b;
    a=R.romtoint();
    b=romtoint();
    mul=a*b;
    cout<<"***multiplied answer is***"<<endl;
    cout<<mul<<"/";
    int_roman(mul);
}
void Roman::operator/(Roman& R){
    int div1; int a,b;
    a=R.romtoint();
    b=romtoint();
    div1=b/a;
    if(b<a)
    cout<<"second roman is smaller than first one"<<endl;
    cout<<"***division is***"<<endl;
    cout<<div1<<"/";
    int_roman(div1);
}
bool Roman::operator==(Roman& R2){
     bool flag;
     if(R2.romtoint()==romtoint())
     flag=true;
     return flag;
}
bool Roman::operator!=(Roman& R2){
     bool flag;
     if(R2.romtoint()!=romtoint())
     flag=true;
     return flag;
}
bool Roman::operator<(Roman& R2){
     bool flag;
     if(R2.romtoint()>romtoint())
     flag=true;
     return flag;
}
bool Roman::operator>(Roman& R2){
     bool flag;
     if(R2.romtoint()<romtoint())
     flag=true;
     return flag;
}
void Roman::operator++(){
    int a=romtoint();
    a++;
    cout<<"*****pre increment*****"<<endl;
    int_roman(a);
    cout<<a<<endl;
}
void Roman::operator--(){
    int a=romtoint();
    a--;
    cout<<"*****pre decrement*****"<<endl;
    int_roman(a);
    cout<<a<<endl;
}
void Roman::operator++(int){
    int a=romtoint();
    cout<<"*****post increment*****"<<endl;
    cout<<"before: "<<endl;
    int_roman(a);
    cout<<a<<endl;
    cout<<"after: "<<endl;
    a++;
    int_roman(a);
    cout<<a<<endl;
}
void Roman::operator--(int){
    int a=romtoint();
    cout<<"*****post deccrement*****"<<endl;
    cout<<"before: "<<endl;
    int_roman(a);
    cout<<a<<endl;
    cout<<"after: "<<endl;
    a--;
    int_roman(a);
    cout<<a<<endl;
}
int main()
{
    char r[30]; int r1, r2;
    cout<<"enter number in roman and capital letters: ";
    cin>>r;
    Roman R1(r);
    cout<<"enter number in roman and capital letters: ";
    cin>>r;
    Roman R2(r);
    cout<<endl<<endl;
    r1=R1.romtoint();
    cout<<"NUM1 in integer: "<<r1<<endl;
    R1.int_roman(r1);  
    r2=R2.romtoint();
    cout<<"NUM2 in integer: "<<r2<<endl;
    R2.int_roman(r2);
    cout<<endl<<endl;
    R1+R2;
    cout<<endl<<endl;
    R1-R2;
    cout<<endl<<endl;
    R1/R2;
    cout<<endl<<endl;
    R1*R2;
    bool a;
    
    cout<<"*******for NUM1<NUM2 ******"<<endl;
    a=R1<R2;
    if(a==1)
    cout<<"true"<<endl;
    else
    cout<<"false"<<endl;
    
    cout<<"*******for NUM1>NUM2 ******"<<endl;
    a=R1>R2;
    if(a==1)
    cout<<"true"<<endl;
    else
    cout<<"false"<<endl;
    cout<<"NUM1 pre-incrementation"<<endl;
    ++R1;
    cout<<"NUM2 pre-decrementation"<<endl;
    --R2;
    cout<<"NUM2 post-incrementation"<<endl;
    R2++;
    cout<<"NUM1 post-deccrementation"<<endl;
    R1--;
    return 0;
}









