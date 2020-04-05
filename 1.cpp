#include<bits/stdc++.h>
using namespace std; 
string str;         //源程序
int flag=0;         //注释
map<string,int> mmap,guan;      //存放所有关键字和出现的关键字
set<string> vec;                 //错误字符
set<string> v;                   //无符号整数
set<string> biao_zhi;            //标识符
string word[]={
"",
"#",   
"begin",
"end",
"if",
"then",
"else",
"for",
"while",
"do",
"and",
"or",
"not",
"+",
"-",
"*",
"/",
">",
"<",
"=",
":=",
">=",
"<=",
"<>",
"++",
"--",
"(",
")",
";" };

int check(char c){                     //检查是否为数字 字母 下划线
    if(c=='_'||(c>='0'&&c<='9')||((c>='a'&&c<='z')||(c>='A'&&c<='Z')))
        return 1;
    return -1;
}

void init(){        //初始化map（单词符号和种别码一一对应关系）
    for(int q=1;q<=28;q++){
        cout<<word[q]<<" "<<q<<endl;
        mmap.insert(map<string,int>::value_type(word[q],q));
    }
    cout<<mmap[";"]<<endl;
}

void yu_chu_li(){   //预处理，去掉空白符
    string s="";
    for(int q=0;q<str.length();q++){
        if(str[q]=='\n'||str[q]=='\t')
            s+=" ";
        else 
            s+=str[q];
    }
    str.assign(s);
}

bool biao(string s){        //标识符匹配
    bool flag=true;
    if(s[0]=='-'||((s[0]>='a'&&s[0]<='z')||(s[0]>='A'&&s[0]<='Z'))){
        for(int q=1;q<s.length();q++){
            if(s[q]=='-'||((s[q]>='a'&&s[q]<='z')||(s[q]>='A'&&s[q]<='Z'))){}
            else{
                flag=false;
                break;
            }
        }
    }
    else flag=false;
    return flag;
}

bool dfa(string s){         //无符号整数匹配
    bool flag=true;
    for(int q=0;q<s.length();q++){
        if(s[q]>='0'&&s[q]<='9') {}
        else{
            flag=false;
            break;
        }
    }
    return flag;
}

int main(){
    guan.clear();
    vec.clear();
    str="";
    ofstream out("out.txt");
    ifstream data("yuan.txt");
    string line;
    while(!data.eof()){
        getline(data,line);
        for(int q=0;q<line.length();q++){
            if(line[q]=='#') { guan.insert(map<string,int>::value_type("#",mmap["#"])); break; }          //去掉注释并添加#关键字
            str+=line[q];
        }
    }
    yu_chu_li();
    init();
    out<<str<<endl<<endl<<endl;
    string s1="",s2="";
    int in=1;                   //为1识别关键字   -1其他
    for(int q=0;q<str.length();q++){
        if(str[q]==' '){
            goto part;
        }
        if(s1.length()==0){
            if(s2.length()!=0){
                in=check(s2[0]);
                s1+=s2[0];
                s2="";
            }
            else
                in=check(str[q]);
        }
        if(check(str[q])==in){
            s1+=str[q];
        }
        else{
            s2+=str[q];
        }
        part:
        if(in!=check(str[q])){
      //      out<<s1<<endl;
            if(s1.length()>0){
                if(mmap[s1]!=0){        //是否为关键字
                    guan.insert(map<string,int>::value_type(s1,mmap[s1]));
                }
                else if(biao(s1)){      //是否为标识符
                    biao_zhi.insert(s1);
                }
                else if(dfa(s1)){       //是否为无符号整型常量
                    v.insert(s1);
                }
                else{                   //错误字符
                    vec.insert(s1);
                }
            }
            s1="";
        }
    }
    out<<"------关键字------"<<endl;
    cout<<"------关键字------"<<endl;
    for(map<string,int>::iterator it=guan.begin();it!=guan.end();it++){     //关键字输出
        out<<"<"<<it->first<<","<<it->second<<">"<<endl;
        cout<<"<"<<it->first<<","<<it->second<<">"<<endl;
    }
    out<<"------标识符------"<<endl;
    cout<<"------标识符------"<<endl;
    for(set<string>::iterator it=biao_zhi.begin();it!=biao_zhi.end();it++){  //标识符输出
        out<<"<标识符,"<<*it<<">"<<endl;
        cout<<"<标识符,"<<*it<<">"<<endl;
    }
    out<<"------无符号整型常量------"<<endl;
    cout<<"------无符号整型常量------"<<endl;
    for(set<string>::iterator it=v.begin();it!=v.end();it++){            //无符号整数输出
        out<<"<无符号整型常量,"<<*it<<">"<<endl;
        cout<<"<无符号整型常量,"<<*it<<">"<<endl;
    }
    out<<"------错误------"<<endl;
    cout<<"------错误------"<<endl;
    for(set<string>::iterator it=vec.begin();it!=vec.end();it++){        //错误输出
        out<<"<错误,"<<*it<<">"<<endl;
        cout<<"<错误,"<<*it<<">"<<endl;
    }
    out.close();
    return 0;
}