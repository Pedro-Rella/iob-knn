#include "system.h"
#include "periphs.h"
#include <iob-uart.h>
#include "iob_timer.h"
#include "iob_knn.h"
#include "random.h" //random generator for bare metal

//uncomment to use rand from C lib 
//#define cmwc_rand rand

#define S 12  //random seed
#define N 100  //data set size


#define INFINITE ~0

///////////////////////////////////////////////////////////////////
int main() {

  int x[100], y[100], y_ant=0, media=0;

  //init uart and timer
  uart_init(UART_BASE, FREQ/BAUD);


  //generate random seed 
  random_init(S);

  for (int i=0; i<N; i++){
    x[i] = (short) cmwc_rand();
    y[i] = x[i] + 2*y_ant;
    y_ant=y[i];
    uart_printf("n=%d, x(%d)=%d, y(%d)=%d\n", i, i, x[i], i, y[i]);
    uart_txwait();
    media += x[i];
  }
  media = media/N;
  uart_printf("media_x=%d\n", media);
  uart_txwait();
}


