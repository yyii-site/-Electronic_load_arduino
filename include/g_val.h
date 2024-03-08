#ifndef __G_VAL_H_
#define __G_VAL_H_

typedef struct {
    float     voltage;        //V
    float     current;        //A
    float     power;          //W
    float     resistance;     //R
    float     set_current;    //A

    float     voltage_sub;
    float     current_sub;
    float     set_current_sub;

    int       voltage_base;
    int       current_base;
    int       set_current_base;
} LoadTypeDef;
extern LoadTypeDef load;

extern int temputer;


#endif
