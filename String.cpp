// palindromes(i, i) 回文列挙

void palindromes(int a, int b){
  int l = a, u = b;
  while(l >= 0 && u < N){
    if(s[l] != s[u])
      break;
    check[l][u - l + 1] = true;
    l -= 1;
    u += 1;
  }
  l = a, u = b + 1;
  while(l >= 0 && u < N){
    if(s[l] != s[u])
      break;
    check[l][u - l + 1] = true;
    l -= 1;
    u += 1;
  }
}