void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}


int R_ldr[5]={0,1,2,3,Red_max};
int G_ldr[5]={0,1,2,3,Green_max};
int B_ldr[5]={0,1,2,3,Blue_max};

int R_F[5]={0,1,2,3,255};
int G_F[5]={0,1,2,3,255};
int B_F[5]={0,1,2,3,255};

int mapping(val,Array_C,Array_F)
{
  int i = 0;
  while(1)
  {
    if (val <= Array_C[i] || i>4)
    {
      break;
    }
    i++;
  }
  int Sample_f = map(val,Array_C[i-1],Array_C[i]_,Array_F[i-1],Array_F[i]);
  return Sample_f;
}











