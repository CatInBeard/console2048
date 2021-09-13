class Game{
    public:
    Game(){
        initscr();
        cbreak();
        noecho();
        getmaxyx(stdscr, this->row, this->col); 
    }
    ~Game(){
        endwin();
    }
    void init(){
        char c;
        bool stopper=true;
        while(stopper){
            if((this->row<22) | (this->col<21)){
                this->alert("Screen must be 21x22 sumbols or more, Press Q to exit, R to retry.");
                c=getch();
                if(c=='q' | c=='Q'){
                    endwin();
                    exit(0);
                }
                getmaxyx(stdscr, this->row, this->col); 
            }
            else{
                stopper=false;
            }
        }
        for(int i=0;i<Game::Size;i++){
            for(int j=0;j<Game::Size;j++){
                this->grid[i][j]=0;
            }
        }
        this->alert("Use more than 2 colors: Y/N?");
        c=getch();
        if(c=='Y' | c=='y'){
            start_color();
            this->color=true;
            init_pair(1,  COLOR_WHITE,   COLOR_BLACK);
            init_pair(2,  COLOR_GREEN,   COLOR_BLACK);
            init_pair(3,  COLOR_YELLOW,  COLOR_BLACK);
            init_pair(4,  COLOR_BLUE,    COLOR_BLACK);
            init_pair(5,  COLOR_MAGENTA, COLOR_BLACK);
            init_pair(6,  COLOR_CYAN,    COLOR_BLACK);
            init_pair(7,  COLOR_BLUE,    COLOR_WHITE);
            init_pair(8,  COLOR_WHITE,   COLOR_RED);
            init_pair(9,  COLOR_BLACK,   COLOR_GREEN);
            init_pair(10, COLOR_BLUE,    COLOR_YELLOW);
            init_pair(11, COLOR_WHITE,   COLOR_BLUE);
            init_pair(12, COLOR_WHITE,   COLOR_MAGENTA);
            init_pair(13, COLOR_BLACK,   COLOR_CYAN);
        }
        this->new_game();
    }
    void new_game(){
        int status=0;
        int dir;
        char c;
        this->add_random();
        this->add_random();
        this->draw_game_screen();
        
        while (true) {
            c=getch();
            if (c == 'w'| c == 'a'| c == 's'| c == 'd'| c == 65| c == 66| c == 67| c == 68) {
                if(c=='w' | c ==65 ){
                    dir=0;
                }
                else if(c=='s' | c ==66 ){
                    dir=1;
                }
                else if(c=='d' | c == 67){
                    dir=2;
                }
                else if(c=='a' | c == 68){
                    dir=3;
                }
                this->move(dir);
                this->add_random();
                this->draw_game_screen();
            }
            else if(c=='Q' or c=='q'){
                endwin();
                exit(0);
            }
            else if(c==8 | c=='B' | c=='b'){
                for(int i=0;i<Game::Size;i++){
                    for(int j=0;j<Game::Size;j++){
                        this->grid[i][j]=this->grid_backup[i][j];
                    }
                }
                this->draw_game_screen();
            }
            napms(30);
        }
    }
    bool move(int dir){
        for(int i=0;i<Game::Size;i++){
            for(int j=0;j<Game::Size;j++){
                this->grid_backup[i][j]=this->grid[i][j];
            }
        }
        bool ret=false;
        bool sort=true;
        bool tryer;
        if(dir==0){
            //top
            for(int j=0;j<Game::Size;j++){
                sort=true;
                while(sort){
                    tryer=false;
                    for(int i=Game::Size-1;i>0;i--){
                        if(this->grid[i-1][j]==0 & this->grid[i][j]>0){
                            this->grid[i-1][j]=this->grid[i][j];
                            this->grid[i][j]=0;
                            tryer=true;
                        }
                    }
                    if(!tryer){
                        sort=false;
                    }
                }
                for(int i=Game::Size; i>0; i--){
                    if(this->grid[i][j]==this->grid[i-1][j] & this->grid[i][j]!=0){
                        grid[i][j]=0;
                        grid[i-1][j]++;
                        this->score+=(int)pow(2,grid[i-1][j]);
                    }
                }
                sort=true;
                while(sort){
                    tryer=false;
                    for(int i=Game::Size-1;i>0;i--){
                        if(this->grid[i-1][j]==0 & this->grid[i][j]>0){
                            this->grid[i-1][j]=this->grid[i][j];
                            this->grid[i][j]=0;
                            tryer=true;
                        }
                    }
                    if(!tryer){
                        sort=false;
                    }
                }
            }
        }
        else if(dir==1){
            //bottom
            for(int j=0;j<Game::Size;j++){
                sort=true;
                while(sort){
                    tryer=false;
                    for(int i=0;i<Game::Size-1;i++){
                        if(this->grid[i][j]>0 & this->grid[i+1][j]==0){
                            this->grid[i+1][j]=this->grid[i][j];
                            this->grid[i][j]=0;
                            tryer=true;
                        }
                    }
                    if(!tryer){
                        sort=false;
                    }
                }

                for(int i=0; i<Game::Size-1; i++){
                    if(this->grid[i][j]==this->grid[i+1][j] & this->grid[i][j]!=0){
                        grid[i][j]++;
                        grid[i+1][j]=0;
                        this->score+=(int)pow(2,grid[i][j]);
                    }
                }
                sort=true;  
                while(sort){
                    tryer=false;
                    for(int i=0;i<Game::Size-1;i++){
                        if(this->grid[i][j]>0 & this->grid[i+1][j]==0){
                            this->grid[i+1][j]=this->grid[i][j];
                            this->grid[i][j]=0;
                            tryer=true;
                        }
                    }
                    if(!tryer){
                        sort=false;
                    }
                }
            }
        }
        else if(dir==2){
            //right
            for(int i=0;i<Game::Size;i++){
                sort=true;
                while(sort){
                    tryer=false;
                    for(int j=0;j<Game::Size-1;j++){
                        if(this->grid[i][j]>0 & this->grid[i][j+1]==0){
                            this->grid[i][j+1]=this->grid[i][j];
                            this->grid[i][j]=0;
                            tryer=true;
                        }
                    }
                    if(!tryer){
                        sort=false;
                    }
                }
                
                for(int j=Game::Size; j>0; j--){
                    if(this->grid[i][j]==this->grid[i][j-1] & this->grid[i][j]!=0){
                        this->score+=(int)pow(2,grid[i][j-1]);
                        grid[i][j]=0;
                        grid[i][j-1]++;
                    }
                }
                sort=true;
                while(sort){
                    tryer=false;
                    for(int j=0;j<Game::Size-1;j++){
                        if(this->grid[i][j]>0 & this->grid[i][j+1]==0){
                            this->grid[i][j+1]=this->grid[i][j];
                            this->grid[i][j]=0;
                            tryer=true;
                        }
                    }
                    if(!tryer){
                        sort=false;
                    }
                }
            }
        }
        else if(dir==3){
            for(int i=0;i<Game::Size;i++){
                sort=true;
                while(sort){
                    tryer=false;
                    for(int j=Game::Size-1;j>0;j--){
                        if(this->grid[i][j-1]==0 & this->grid[i][j]>0){
                            this->grid[i][j-1]=this->grid[i][j];
                            this->grid[i][j]=0;
                            tryer=true;
                        }
                    }
                    if(!tryer){
                        sort=false;
                    }
                }
                
                for(int j=0; j<Game::Size-1; j++){
                    if(this->grid[i][j]==this->grid[i][j+1] & this->grid[i][j]!=0){
                        this->score+=(int)pow(2,grid[i][j]);
                        grid[i][j]++;
                        grid[i][j+1]=0;
                    }
                }
                sort=true;
                while(sort){
                    tryer=false;
                    for(int j=Game::Size-1;j>0;j--){
                        if(this->grid[i][j-1]==0 & this->grid[i][j]>0){
                            this->grid[i][j-1]=this->grid[i][j];
                            this->grid[i][j]=0;
                            tryer=true;
                        }
                    }
                    if(!tryer){
                        sort=false;
                    }
                }
            }
        }
        return ret;
    }
    void add_random(){
        bool stopper=true;
        int myrand;
        int num;
        int i;
        int j;
        myrand=std::rand()%10;
        if(myrand>5){
            num=2;
        }
        else{
            num=1;
        }
        if(this->checkEmpty()){
            while(stopper){
                i=std::rand()%Game::Size;
                j=std::rand()%Game::Size;
                if(this->grid[i][j]==0){
                    this->grid[i][j]=num;
                    stopper=false;
                }
            }
        }
    }
    bool checkEmpty(){
        for(int i=0;i<Game::Size;i++){
            for(int j=0;j<Game::Size;j++){
                if(this->grid[i][j]==0){
                    return true;
                }
            }
        }
        return false;
    }
    void draw_game_screen(){
        this->base_screen();
        int level;
        if(this->color){
            color_set(1, NULL);
        }
        for(int i=0;i<Game::Size*4+1;i++){
            for(int j=0;j<Game::Size*5+1;j++){
                if(i%Game::Size==0){
                    mvwprintw(stdscr, i+Game::Top, j, "%s", "-");
                }
                else{
                    if(j%(Game::Size+1)==0){
                        mvwprintw(stdscr, i+Game::Top, j, "%s", "|");
                    }
                    if(j==Game::Size*5+1){
                        mvwprintw(stdscr, i+Game::Top, j, "%s", "|");
                    }
                }
            }
        }
        for(int i=0;i<Game::Size;i++){
            for(int j=0;j<Game::Size;j++){
                level=this->grid[i][j];
                if(level!=0){
                    if(this->color){
                        color_set(level+1, NULL);
                    }
                    std::string str= std::to_string(level);
                    int len=str.length();
                    int left=(this->field_size-len)/2;
                    mvwprintw(stdscr, this->field_size*i+1+2+Game::Top, 1+(this->field_size+1)*j, "%s", (std::to_string((int)pow(2,level))).c_str());
                }
            }
        }
        if(this->color){
            color_set(1, NULL);
        }
    }
    void drow_central_text(std::string textbuf){
        mvwprintw(stdscr, row / 2, (col - strlen(textbuf.c_str())) / 2, "%s", textbuf.c_str());
    }
    void alert(std::string textbuf){
        this->base_screen();
        this->drow_central_text(textbuf);
    }
    void base_screen(){
        this->clear_screen();
        if(this->color){
            color_set(1, NULL);
        }
        mvwprintw(stdscr, 0, (10 - strlen(std::to_string(this->score).c_str())) / 2, "%s", std::to_string(this->score).c_str());
    }
    void clear_screen(){
        clear();
    }
    private:
    static const int Size=4;
    static const int Top=1;
    bool color=false;
    int grid[Game::Size][Game::Size];
    int grid_backup[Game::Size][Game::Size];
    int field_size=4;
    int score=0;
    int row;
    int col;
};