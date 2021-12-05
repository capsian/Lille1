static int t[10];

int main(int argc, char **argv) {
  int i;
  for(i=0;i<10;i++)
    t[i]=49-i;
  
  return t[7];
}
