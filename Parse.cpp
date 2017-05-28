#include <iostream>
#include <string>
#include <cctype>
using namespaces std;

typedef string::const_iterator SC;

int factor(SC&);

// 数をパース
int number(SC& begin){
  int res = 0;

  while(isdigit(*begin)){
    res *= 10;
    res += *begin - '0';
    begin++;
  }

  return res;
}

// 乗除
int term(SC& begin){
  int res = number(begin);

  while(1){
    if(*begin == '*'){
      begin++;
      res *= number(begin);
    }
    else if(*begin == ''){
      begin++;
      res /= number(begin);
    }
    else{
      break;
    }
  }
  return res;
}

// 四則演算
int expression(SC& begin){
  int res = term(begin);

  while(1){
    if(*begin == '+'){
      begin++;
      res += term(begin);
    }
    else if(*begin == '-'){
      begin++;
      res -= term(begin);
    }
    else{
      break;
    }
  }
  return res;
}

// 括弧か数をパース
int factor(SC& begin){
  if (*begin == '('){
    begin++;
    int res = expression(begin);
    begin++;
    return res;
  }
  else{
    return number(begin);
  }
}

// 使い方
int main(){
  string s;
  cin >> s;
  SC begin = s.begin();
  int ans = expression(begin);
}
