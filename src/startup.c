#include <stdint.h>

extern uint8_t _erodata[];
extern uint8_t _data[];
extern uint8_t _edata[];
extern uint8_t _sdata[];
extern uint8_t _esdata[];
extern uint8_t _bss[];
extern uint8_t _ebss[];

// Adapted from https://stackoverflow.com/questions/58947716/how-to-interact-with-risc-v-csrs-by-using-gcc-c-code
__attribute__((always_inline)) inline uint32_t csr_mstatus_read(void){
    uint32_t result;
    asm volatile ("csrr %0, mstatus" : "=r"(result));
    return result;
}

__attribute__((always_inline)) inline void csr_mstatus_write(uint32_t val){
    asm volatile ("csrw mstatus, %0" : : "r"(val));
}

__attribute__((always_inline)) inline void csr_write_mie(uint32_t val){
    asm volatile ("csrw mie, %0" : : "r"(val));
}

__attribute__((always_inline)) inline void csr_enable_interrupts(void){
    asm volatile ("csrsi mstatus, 0x8");
}

__attribute__((always_inline)) inline void csr_disable_interrupts(void){
    asm volatile ("csrci mstatus, 0x8");
}

#define MTIME_LOW       (*((volatile uint32_t *)0x40000008))
#define MTIME_HIGH      (*((volatile uint32_t *)0x4000000C))
#define MTIMECMP_LOW    (*((volatile uint32_t *)0x40000010))
#define MTIMECMP_HIGH   (*((volatile uint32_t *)0x40000014))
#define CONTROLLER      (*((volatile uint32_t *)0x40000018))

void init(void){
    uint8_t *Source = _erodata;
    uint8_t *Base = _data < _sdata ? _data : _sdata;
    uint8_t *End = _edata > _esdata ? _edata : _esdata;

    while(Base < End){
        *Base++ = *Source++;
    }
    Base = _bss;
    End = _ebss;
    while(Base < End){
        *Base++ = 0;
    }

    csr_write_mie(0x888);       // Enable all interrupt soruces
    csr_enable_interrupts();    // Global interrupt enable
    MTIMECMP_LOW = 1;
    MTIMECMP_HIGH = 0;
}

extern volatile int global;
extern volatile uint32_t controller_status;
extern volatile int win;
extern volatile int interrupt_activated;
#define INT_PENDING (*(volatile uint32_t*) 0x40000004)
#define VIDEO_MEMORY ((volatile char*) 0x500FE800)
#define VIDEO_NUM_ROWS 36
#define VIDEO_NUM_COLS 64

void c_interrupt_handler(uint32_t cause){
    if(cause==0x80000007){
    uint64_t NewCompare = (((uint64_t)MTIMECMP_HIGH)<<32) | MTIMECMP_LOW;
    NewCompare += 100;
    MTIMECMP_HIGH = NewCompare>>32;
    MTIMECMP_LOW = NewCompare;
    global++;
    controller_status = CONTROLLER;
    }
    if(cause==0x8000000B){  
        interrupt_activated=1;
                            VIDEO_MEMORY[7]='X';
                        VIDEO_MEMORY[65]='0';

                        VIDEO_MEMORY[129]=' ';
                        VIDEO_MEMORY[193]=' ';
                        VIDEO_MEMORY[257]=' ';
                        VIDEO_MEMORY[321]=' ';
                        VIDEO_MEMORY[385]=' ';
                        VIDEO_MEMORY[449]=' ';
                            VIDEO_MEMORY[67]='1';

                        VIDEO_MEMORY[131]=' ';
                        VIDEO_MEMORY[195]=' ';
                        VIDEO_MEMORY[259]=' ';
                        VIDEO_MEMORY[323]=' ';
                        VIDEO_MEMORY[387]=' ';
                        VIDEO_MEMORY[451]=' ';
                                VIDEO_MEMORY[69]='2';

                        VIDEO_MEMORY[133]=' ';
                        VIDEO_MEMORY[197]=' ';
                        VIDEO_MEMORY[261]=' ';
                        VIDEO_MEMORY[325]=' ';
                        VIDEO_MEMORY[389]=' ';
                        VIDEO_MEMORY[453]=' ';
                                    VIDEO_MEMORY[71]='3';

                        VIDEO_MEMORY[135]=' ';
                        VIDEO_MEMORY[199]=' ';
                        VIDEO_MEMORY[263]=' ';
                        VIDEO_MEMORY[327]=' ';
                        VIDEO_MEMORY[391]=' ';
                        VIDEO_MEMORY[455]=' ';
                                    VIDEO_MEMORY[73]='4';

                        VIDEO_MEMORY[137]=' ';
                        VIDEO_MEMORY[201]=' ';
                        VIDEO_MEMORY[265]=' ';
                        VIDEO_MEMORY[329]=' ';
                        VIDEO_MEMORY[393]=' ';
                        VIDEO_MEMORY[457]=' ';
                                    VIDEO_MEMORY[75]='5';

                        VIDEO_MEMORY[139]=' ';
                        VIDEO_MEMORY[203]=' ';
                        VIDEO_MEMORY[267]=' ';
                        VIDEO_MEMORY[331]=' ';
                            VIDEO_MEMORY[395]=' ';
                            VIDEO_MEMORY[459]=' ';
                        VIDEO_MEMORY[77]='6';
    INT_PENDING =0x4;
    }


}

