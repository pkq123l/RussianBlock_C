/* 下落的方块 */
int ges[20][10] = {0};

/* 落实不动的方块 */
int shiKuais[20][10] = {0};

/* 下落方块的颜色 */
int color;

/* 消掉行的得分 */
int fen = 0;


/**/
void xinKuai();

void showBG();

void showXiaLuo();

void showLuoShi();

void showFen();


int nengZuo();
int nengZuoBuDang();
void zuoYi();

int nengYou();
int nengYouBuDang();
void youYi();

void heBing();

int nengXiao(int hang[]);
int xiaoHang();

void deFen(int xhs);

int nengXia();
int nengXiaBuDang();
void xiaYi();
int nengShu();