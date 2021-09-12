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
            for(int i=0;i<Game::Size;i++){
                this->hr=hr+"-";
                empty=empty+" ";
            }
            empty=empty+"|";
        }
        this->new_game();
    }
    void new_game(){
        int status=0;
        int dir;
        char c;
        this->add_random();
        this->draw_game_screen();
        while (true) {
            c=getch();
            if (c == 'w'| c == 'a'| c == 's'| c == 'd'| c == 65| c == 66| c == 67| c == 68) {
                if(c=='w' | c 65){
                    dir=0;
                }
                else if(c=='s' | c 66){
                    dir=0;
                }
                else if(c=='d' | c 67){
                    dir=0;
                }
                else if(c=='a' | c 68){
                    dir=0;
                }
                this->move(dir);
                this->add_random();
                this->draw_game_screen();
            }
            napms(50);
        }
    }
    bool move(int dir){
        bool ret=false;
        bool sort=true;
        bool tryer;
        if(dir==0){
            //top
            for(int j=0;j<Game::Size;j++){
                for(int i=Game::Size-1; i>0; i--){
                    if(this->grid[i][j]==this->grid[i][j-1]){
                        grid[i][j]++;
                        grid[i][j-1]=0;
                    }
                }
                while(sort){
                    tryer=false;
                    for(int i=N-1;i>0;i--){
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
                for(int i=1; i<Game::Size; i--){
                    if(this->grid[i][j]==this->grid[i][j-1]){
                        grid[i][j]++;
                        grid[i][j-1]=0;
                    }
                }
                while(sort){
                    tryer=false;
                    for(int i=0;i<N-1;i++){
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
        else if(dir==3){
            for(int i=0;i<Game::Size;i++){
                while(sort){
                    tryer=false;
                    for(int j=0;j<N-1;j++){
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
        else if(dir==4){
            for(int i=0;i<Game::Size;i++){
                while(sort){
                tryer=false;
                for(int j=N-1;j>0;j--){
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
        for(int i=0;i<Game::Size*4+1;i++){
            if(i%Game::Size==0){
                mvwprintw(stdscr, i+Game::Top, 0, "%s", this->hr.c_str());
            }
            else if(i%Game::Size==Game::Size/2){
                std::string buf="|";
                for(int j=0;j<Game::Size;j++){
                    level=this->grid[i/Game::Size][j];
                    if(level==0){
                        buf=buf+"    |";
                    }
                    else if(level==1 | level==2 | level==3){
                        buf=buf+"  "+std::to_string((int)pow(2,level))+" |";
                    }
                    else if(level==4 | level==5 | level==6){
                        buf=buf+" "+std::to_string((int)pow(2,level))+" |";
                    }
                    else if(level==7 | level==8 | level==9){
                        buf=buf+std::to_string((int)pow(2,level))+" |";
                    }
                    else if(level==10 | level==11 | level==12){
                        buf=buf+std::to_string((int)pow(2,level))+"|";
                    }
                }
                mvwprintw(stdscr, i+Game::Top, 0, "%s", buf.c_str());
            }
            else{
                mvwprintw(stdscr, i+Game::Top, 0, "%s", this->empty.c_str());
            }
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
        mvwprintw(stdscr, 0, (10 - strlen(std::to_string(this->score).c_str())) / 2, "%s", std::to_string(this->score).c_str());
    }
    void clear_screen(){
        clear();
    }
    private:
    static const int Size=4;
    static const int Top=1;
    int grid[Game::Size][Game::Size];
    std::string hr="-----";
    std::string empty="|";
    int score=0;
    int row;
    int col;
};