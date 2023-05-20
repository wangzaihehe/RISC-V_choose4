#include <stdint.h>
#include"ImageData.h"
uint32_t ReadController(void); 
void InitializeTimer(void);
int checkwinner(char player, int x_pos);
uint32_t ReadInterrupt(void);
// typedef struct{
//     uint32_t DBlue : 8;
//     uint32_t DGreen : 8;
//     uint32_t DRed : 8;
//     uint32_t DAlpha : 8;
// } SColor, *SColorRef;

typedef struct{
    SColor DColors[256];
} SPalette, *SPaletteRef;

typedef struct{
    uint8_t DData[64][64];
} SLargeData, *SLargeDataRef;

typedef struct{
    uint32_t DPalette : 2;
    uint32_t DXOffset : 10;
    uint32_t DYOffset : 9;
    uint32_t DWidth : 5;
    uint32_t DHeight : 5;
    uint32_t DReserved : 1;
} SLargeSpriteControl, *SLargeSpriteControlRef;
typedef struct{
    uint32_t BPalette :2;
    uint32_t BXOffset : 10;
    uint32_t BYOffset : 10;
    uint32_t BZ : 3;
    uint32_t BReserved : 7;    

} BackgroundControl, *BackgroundControlRef;  
volatile int global = 42;
volatile uint32_t *controller_status = (volatile uint32_t *)(0x40000018);
// volatile uint32_t *interrupt_status = (volatile uint32_t *)(0x40000000);
volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xFE800);
volatile uint32_t *VIDEO_MODE = (volatile uint32_t *)(0x500FF414);
volatile SPalette *SPRITE_PALETTES = (volatile SPalette *)(0x500FD000);
volatile uint8_t *BackGround=(volatile uint8_t *)(0x50000000);
volatile SPalette *BACK_GROUND_PALETTE = (volatile SPalette *)(0x500FC000);
volatile uint8_t *LARGE_SPRITE_DATA_SECOND = (volatile uint8_t *)(0x500B5000);
volatile SLargeSpriteControl *LARGE_SPRITE_CONTROL_SECOND = (volatile SLargeSpriteControl *)(0x500FF118);


volatile uint8_t *LARGE_SPRITE_DATA = (volatile uint8_t *)(0x500B4000);
volatile SLargeSpriteControl *LARGE_SPRITE_CONTROL = (volatile SLargeSpriteControl *)(0x500FF114);
volatile BackgroundControl *BACKGROUND_CONTROL = (volatile BackgroundControl *)(0x500FF100);
volatile int win =0;
volatile int interrupt_activated = 0;


int main() {

    for(int i=0;i<235;i++){
        SPRITE_PALETTES->DColors[i]=Palette[i];
        BACK_GROUND_PALETTE->DColors[i]=Palette[i];
    }
    for(int i=0;i<240;i++){
        for(int j=0;j<280;j++){
           BackGround[i*512+j]=BoardImage[i*280+j];
        }
    }
    for(int v=1;v<=21;v++){
    for(int i=0;i<32;i++){
        for(int j=0;j<32;j++){
            LARGE_SPRITE_DATA[i*64+j]=BluePieceImage[i*32+j];//0
            LARGE_SPRITE_DATA_SECOND[i*64+j]=YellowPieceImage[i*32+j];
        }
    }
    LARGE_SPRITE_DATA=(volatile uint8_t *)(0x500B4000+0x2000*v);
    LARGE_SPRITE_DATA_SECOND=(volatile uint8_t *)(0x500B5000+0x2000*v);
    }
    *VIDEO_MODE = 1;

    // LARGE_SPRITE_CONTROL_SECOND[0].DXOffset=108;
    // LARGE_SPRITE_CONTROL_SECOND[0].DYOffset=156;
    
    LARGE_SPRITE_CONTROL[0].DXOffset=189;
    LARGE_SPRITE_CONTROL[0].DYOffset=76;

    // int l=1;
    // LARGE_SPRITE_CONTROL=(volatile SLargeSpriteControl *)(0x500FF114+0x4*l);
    // LARGE_SPRITE_CONTROL[0].DXOffset=189;
    // LARGE_SPRITE_CONTROL[0].DYOffset=76-7*39;

    // LARGE_SPRITE_CONTROL=(volatile SLargeSpriteControl *)(0x500FF114+0x4*2);

    //     LARGE_SPRITE_CONTROL_SECOND[0].DXOffset=108;
    // LARGE_SPRITE_CONTROL_SECOND[0].DYOffset=116;
    BACKGROUND_CONTROL[0].BXOffset=512;
    BACKGROUND_CONTROL[0].BYOffset=336;
    int a = 4;
    int b = 12;
    int last_global = 42;
    int x_pos = 7;
    int y_pos = 7;
    int delta_x = 1;
    int delta_y = 0;
    char player='X';
    VIDEO_MEMORY[x_pos]='X';
    VIDEO_MEMORY[65]='0';

    VIDEO_MEMORY[128]='|';
    VIDEO_MEMORY[192]='|';
    VIDEO_MEMORY[256]='|';
    VIDEO_MEMORY[320]='|';
    VIDEO_MEMORY[384]='|';
    VIDEO_MEMORY[448]='|';
        VIDEO_MEMORY[67]='1';

    VIDEO_MEMORY[130]='|';
    VIDEO_MEMORY[194]='|';
    VIDEO_MEMORY[258]='|';
    VIDEO_MEMORY[322]='|';
    VIDEO_MEMORY[386]='|';
    VIDEO_MEMORY[450]='|';
            VIDEO_MEMORY[69]='2';

    VIDEO_MEMORY[132]='|';
    VIDEO_MEMORY[196]='|';
    VIDEO_MEMORY[260]='|';
    VIDEO_MEMORY[324]='|';
    VIDEO_MEMORY[388]='|';
    VIDEO_MEMORY[452]='|';
                VIDEO_MEMORY[71]='3';

    VIDEO_MEMORY[134]='|';
    VIDEO_MEMORY[198]='|';
    VIDEO_MEMORY[262]='|';
    VIDEO_MEMORY[326]='|';
    VIDEO_MEMORY[390]='|';
    VIDEO_MEMORY[454]='|';
                VIDEO_MEMORY[73]='4';

    VIDEO_MEMORY[136]='|';
    VIDEO_MEMORY[200]='|';
    VIDEO_MEMORY[264]='|';
    VIDEO_MEMORY[328]='|';
    VIDEO_MEMORY[392]='|';
    VIDEO_MEMORY[456]='|';
                VIDEO_MEMORY[75]='5';

    VIDEO_MEMORY[138]='|';
    VIDEO_MEMORY[202]='|';
    VIDEO_MEMORY[266]='|';
    VIDEO_MEMORY[330]='|';
    VIDEO_MEMORY[394]='|';
    VIDEO_MEMORY[458]='|';
                VIDEO_MEMORY[77]='6';

    VIDEO_MEMORY[140]='|';
    VIDEO_MEMORY[204]='|';
    VIDEO_MEMORY[268]='|';
    VIDEO_MEMORY[332]='|';
    VIDEO_MEMORY[396]='|';
    VIDEO_MEMORY[460]='|';
     VIDEO_MEMORY[142]='|';
    VIDEO_MEMORY[206]='|';
    VIDEO_MEMORY[270]='|';
    VIDEO_MEMORY[334]='|';
    VIDEO_MEMORY[398]='|';
    VIDEO_MEMORY[462]='|';
         VIDEO_MEMORY[143]='5';
    VIDEO_MEMORY[207]='4';
    VIDEO_MEMORY[271]='3';
    VIDEO_MEMORY[335]='2';
    VIDEO_MEMORY[399]='1';
    VIDEO_MEMORY[463]='0';

    uint32_t ControllerStat, LastControllerStat = 0;
    uint32_t interrupt_pointer= 0;
    #define LEFT        0x1
    #define RIGHT       0x8
    #define BUTTON1     0x10
    #define INTERRUPT_ENABLE (*(volatile uint32_t*)0x40000000)
    int controller=0;
    while(1){
        
        // interrupt_pointer = interrupt_status;  
        INTERRUPT_ENABLE=0x4;
        ControllerStat = ReadController();
        if(LastControllerStat!=ControllerStat){
        if(ControllerStat & LEFT && x_pos>1){
            LARGE_SPRITE_CONTROL[0].DXOffset-=40;
            VIDEO_MEMORY[x_pos]=' ';
            x_pos-=2;
            VIDEO_MEMORY[x_pos]=player;
        }
        else if(ControllerStat & RIGHT && x_pos < 13){
            LARGE_SPRITE_CONTROL[0].DXOffset+=40;
            VIDEO_MEMORY[x_pos]=' ';
            x_pos+=2;
            VIDEO_MEMORY[x_pos]=player;
        }
        
        if(ControllerStat & BUTTON1){
            VIDEO_MEMORY[x_pos]=' ';
            for(int w=7;w>=2;w--){
            if(VIDEO_MEMORY[x_pos+w*64]!='X'&&VIDEO_MEMORY[x_pos+w*64]!='O'){
                LARGE_SPRITE_CONTROL[0].DYOffset+=(w-1)*40;
                controller+=1;
                LARGE_SPRITE_CONTROL = (volatile SLargeSpriteControl *)(0x500FF114+0x4*controller);
                LARGE_SPRITE_CONTROL[0].DYOffset=76;             
                LARGE_SPRITE_CONTROL[0].DXOffset=189;
                
                
            VIDEO_MEMORY[x_pos+w*64]=player;
            win=checkwinner(player,x_pos);
            while(win){
                if(interrupt_activated){
                        win =0;
                        player='O';
                        for(int i =0;i<42;i++){
                            LARGE_SPRITE_CONTROL = (volatile SLargeSpriteControl *)(0x500FF114+0x4*i);
                            LARGE_SPRITE_CONTROL[0].DYOffset=0;             
                            LARGE_SPRITE_CONTROL[0].DXOffset=0;
                        }
                        LARGE_SPRITE_CONTROL = (volatile SLargeSpriteControl *)(0x500FF114);
                        LARGE_SPRITE_CONTROL[0].DXOffset=189;
                        LARGE_SPRITE_CONTROL[0].DYOffset=76;
                        interrupt_activated=0;
                        controller=0;
                        break;
                }
            }
            w=2;
            }
            }
            if(player=='X'){
                player='O';                
            }else{
                player='X';
            }
            
            x_pos=7;
            
        }
        VIDEO_MEMORY[x_pos]=player;
        }
       
        LastControllerStat = ControllerStat;
    }

    return 0;
}
int checkwinner(char player, int x_pos){
    int count=0;
    int h_count=0;
    int d_count=0;
    for(int i =7;i>=2;i--){
        if(VIDEO_MEMORY[x_pos+i*64]==player){//check vertically

            for(int v=1;v<=14;v+=2){//check horizontally
                
                if(VIDEO_MEMORY[v+i*64]==player){
                    h_count+=1;
                    if(h_count==4){
                        VIDEO_MEMORY[x_pos+i*64]=player;
                        return 1;
                    }
                }else{
                    h_count=0;
                    break;
                }
            }
                    count+=1;
                    if(count==4){
                        VIDEO_MEMORY[x_pos+i*64]=player;
                       return 1;
                    }
                }else{
                    count=0;
                    break;
                }
    }
    for(int i=2;i<=7;i++){
            for(int v=1;v<=14;v+=2){
            if(VIDEO_MEMORY[v+i*64]==player){
                d_count+=1;
                for(int l=1;l<=4;l++){
                    if(VIDEO_MEMORY[v+l*2+(i+l)*64]==player){
                        d_count+=1;
                        if(d_count==4){
                        VIDEO_MEMORY[v+i*64]=player;
                        return 1;

                    }

                    }else{
                        d_count=0;
                        break;
                    }
                }

            }
            }
    }
    
        for(int i =7;i>=2;i--){
            for(int v=1;v<=14;v+=2){
            if(VIDEO_MEMORY[v+i*64]==player){
                d_count+=1;
                for(int l=1;l<=4;l++){
                    if(VIDEO_MEMORY[v+l*2+(i-l)*64]==player){
                        d_count+=1;
                        if(d_count==4){
                        VIDEO_MEMORY[v+i*64]=player;
                        return 1;    
                    }
                    }else{
                        d_count=0;
                        break;
                    }
                }

            }
            }
    }
    return 0;

}