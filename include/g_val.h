#ifndef __G_VAL_H_
#define __G_VAL_H_


typedef struct {
    int     voltage;        //mV
    int     current;        //mA

    int     set_current;    //mA
} LoadTypeDef;
extern LoadTypeDef load;


#endif
