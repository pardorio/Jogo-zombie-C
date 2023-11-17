
//BONECOS CONTROLADOS
struct PLAYER
{

int invul,
x,
y,
vidas,
vleft,
vright,
vup,
vdown,
larg_x,
alt_y,


cur,
dir,
disp,
dano,
pontos;

};

struct PLAYER swat={60,400,200,100,2,2,2,2,14,14,0,0,45,100};

//PROJETEIS
struct PROJETEIS
{
    bool ativo;
    int v,
     x,
     y,
     dir;

};

struct PROJETEIS akbala[5];


struct ZOMBIES
{
    bool vivo;
    int x,
        y,

        v,
        larg_x,
        alt_y,
        dir,
        cur,
        dano,
        vidas;


};

struct ZOMBIES zombie1[10];




