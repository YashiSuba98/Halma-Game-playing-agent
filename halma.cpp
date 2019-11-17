#include<bits/stdc++.h>
using namespace std;
string player,opponent;
int final_from=-1,final_to=-1;
float epsilon=0.0001;
//vector<vector<int> >previous_moves;
float get_score1(char board[16][16],string color){
    float score=0;
    vector<int> outside_coins;
    vector<int> blank_places;
    if(color[0]=='B'){
        for(int i=0;i<16;i++){
            for(int j=0;j<16;j++){
                int location=16*i+j;
                if((location>=251 && location<=255) || (location>=235 && location<=239) || (location>=220 && location<=223) || (location>=205 && location<=207) || location==190 || location==191){
                    if(board[i][j]=='.')
                        blank_places.push_back(location);
                }
                else{
                    if(board[i][j]=='B')
                       outside_coins.push_back(location);
                }
            }
        }
        for(int i=0;i<outside_coins.size();i++){
            int x=outside_coins[i]/16;
            int y=outside_coins[i]%16;
            for(int j=0;j<blank_places.size();j++){
                int x1=blank_places[j]/16;
                int y1=blank_places[j]%16;
                score=score+sqrt(pow(abs(x-x1),2)+pow(abs(y-y1),2));
            }
        }
    }
    else{
        for(int i=0;i<16;i++){
            for(int j=0;j<16;j++){
                int location=16*i+j;
                if((location>=0 && location<=4) || (location>=16 && location<=20) || (location>=32 && location<=35) || (location>=48 && location<=50) || location==64 || location==65){
                        if(board[i][j]=='.')
                        blank_places.push_back(location);
                }
                else{
                    if(board[i][j]=='W')
                       outside_coins.push_back(location);
                }
            }
        }
        for(int i=0;i<outside_coins.size();i++){
            int x=outside_coins[i]/16;
            int y=outside_coins[i]%16;
            for(int j=0;j<blank_places.size();j++){
                int x1=blank_places[j]/16;
                int y1=blank_places[j]%16;
                score=score+sqrt(pow(abs(x-x1),2)+pow(abs(y-y1),2));
            }
        }
    }
    return 500-score;
}

float get_score(char board[16][16],string color){
    float score=0;
    if(color[0]=='B'){
        for(int i=0;i<16;i++){
            for(int j=0;j<16;j++){
                if(board[i][j]=='B'){
                    score=score+sqrt(pow(abs(15-i),2)+pow(abs(15-j),2));
                }
            }
        }
    }
    else{
        for(int i=0;i<16;i++){
            for(int j=0;j<16;j++){
                if(board[i][j]=='W'){
                    score=score+sqrt(pow(abs(i-0),2)+pow(abs(j-0),2));
                }
            }
        }
    }
    return 500-score;
}

vector <int> directions(char board[16][16],int location){
    int x,y;
    vector <int>to_locations;
    bool visited[16][16];
    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++)
        visited[i][j]=false;
    }
    int k=0;
    vector <int> from_location;
    vector <int> jump_location;
    from_location.push_back(location);
    jump_location.push_back(location);

    while(k<jump_location.size()){
        x=jump_location[k]/16;
        y=jump_location[k]%16;
        visited[x][y]=true;
        //north-west
        if(x>1 && y>1){
        if(board[x-1][y-1]=='B' || board[x-1][y-1]=='W'){
            if(board[x-2][y-2]=='.' && visited[x-2][y-2]!=true){
                from_location.push_back(x*16+y);
                jump_location.push_back((x-2)*16+(y-2));
                visited[x-2][y-2]=true;
            }
        }
        }
        //north-east
        if(x>1 && y<14){
        if(board[x-1][y+1]=='B' || board[x-1][y+1]=='W'){
            if(board[x-2][y+2]=='.' && visited[x-2][y+2]!=true){
                from_location.push_back(x*16+y);
                jump_location.push_back((x-2)*16+(y+2));
                visited[x-2][y+2]=true;
            }
        }
        }
        //south-east
        if(x<14 && y<14){
        if(board[x+1][y+1]=='B' || board[x+1][y+1]=='W'){
            if(board[x+2][y+2]=='.' && visited[x+2][y+2]!=true){
                from_location.push_back(x*16+y);
                jump_location.push_back((x+2)*16+(y+2));
                visited[x+2][y+2]=true;
            }
        }
        }
        //south-west
        if(x<14 && y>1){
        if(board[x+1][y-1]=='B' || board[x+1][y-1]=='W'){
            if(board[x+2][y-2]=='.' && visited[x+2][y-2]!=true){
                from_location.push_back(x*16+y);
                jump_location.push_back((x+2)*16+(y-2));
                visited[x+2][y-2]=true;
            }
        }
        }
        //north
        if(x>1){
        if(board[x-1][y]=='B' || board[x-1][y]=='W'){
            if(board[x-2][y]=='.' && visited[x-2][y]!=true){
                from_location.push_back(x*16+y);
                jump_location.push_back((x-2)*16+y);
                visited[x-2][y]=true;
            }
        }
        }
        //west
        if(y>1){
        if(board[x][y-1]=='B' || board[x][y-1]=='W'){
            if(board[x][y-2]=='.' && visited[x][y-2]!=true){
                from_location.push_back(x*16+y);
                jump_location.push_back((x)*16+(y-2));
                visited[x][y-2]=true;
            }
        }
        }
        //east
        if(y<14){
        if(board[x][y+1]=='B' || board[x][y+1]=='W'){
            if(board[x][y+2]=='.' && visited[x][y+2]!=true){
                from_location.push_back(x*16+y);
                jump_location.push_back((x)*16+(y+2));
                visited[x][y+2]=true;
            }
        }
        }
        //south
        if(x<14){
        if(board[x+1][y]=='B' || board[x+1][y]=='W'){
            if(board[x+2][y]=='.' && visited[x+2][y]!=true){
                from_location.push_back(x*16+y);
                jump_location.push_back((x+2)*16+y);
                visited[x+2][y]=true;
            }
        }
        }

        k++;
    }
    for(int k=1;k<jump_location.size();k++){
        to_locations.push_back(jump_location[k]);
    }
    int step_location=location;
    x=location/16;
    y=location%16;
    //north-west
    if(x!=0 && y!=0){
        if(board[x-1][y-1]!='B' && board[x-1][y-1]!='W'){
            step_location=(x-1)*16+y-1;
            to_locations.push_back(step_location);
        }
    }
    //south-east
    if(x!=15 && y!=15){
        if(board[x+1][y+1]!='B' && board[x+1][y+1]!='W'){
            step_location=(x+1)*16+y+1;
            to_locations.push_back(step_location);
        }
    }
    //north-east
    if(x!=0 && y!=15){
        if(board[x-1][y+1]!='B' && board[x-1][y+1]!='W'){
            step_location=(x-1)*16+y+1;
            to_locations.push_back(step_location);
        }
    }

    //south-west
    if(x!=15 && y!=0){
        if(board[x+1][y-1]!='B' && board[x+1][y-1]!='W'){
            step_location=(x+1)*16+y-1;
            to_locations.push_back(step_location);
        }
    }
    //north
    if(x!=0){
        if(board[x-1][y]!='B' && board[x-1][y]!='W'){
            step_location=(x-1)*16+y;
            to_locations.push_back(step_location);
        }
    }
    //west
    if(y!=0){
        if(board[x][y-1]!='B' && board[x][y-1]!='W'){
            step_location=(x)*16+y-1;
            to_locations.push_back(step_location);
        }
    }
    //east
    if(y!=15){
        if(board[x][y+1]!='B' && board[x][y+1]!='W'){
            step_location=(x)*16+y+1;
            to_locations.push_back(step_location);
        }
    }
    //south
    if(x!=15){
        if(board[x+1][y]!='B' && board[x+1][y]!='W'){
            step_location=(x+1)*16+y;
            to_locations.push_back(step_location);
        }
    }
    return to_locations;
}

bool is_base_empty(char board[16][16],string color){
    int temp;
    if(color=="BLACK"){
    for(int i=0;i<5;i++){
        if(i==2)temp=4;
        else if(i==3)temp=3;
        else if(i==4)temp=2;
        else temp=5;
        for(int j=0;j<temp;j++){
            if(board[i][j]=='B'){
                return false;
            }
        }
    }
    }
    else{
    for(int i=11;i<16;i++){
        if(i==11)temp=14;
        else if(i==12)temp=13;
        else if(i==13)temp=12;
        else temp=11;
        for(int j=temp;j<16;j++){
            if(board[i][j]=='W'){
                return false;
            }
        }
    }
    }
    return true;
}

bool is_played(int a, int b){
    ifstream play;
    play.open("playdata.txt");
    while(!play.eof()){
        int from,to;
        play>>from>>to;
        if(from==a && to==b){
            return true;
        }
    }
    return false;
}

vector<vector<int> > get_valid_moves(char board[16][16],string color){
    vector<vector<int> > list;
    int temp;
    bool validate=is_base_empty(board,color);
        if(validate){
        for(int i=0;i<16;i++){
            for(int j=0;j<16;j++){
                if(board[i][j]==color[0]){
                    int location=i*16+j;
                    vector<int> possible_directions=directions(board,location);
                    if(!possible_directions.empty()){
                    if(location==190 || location==191 || (location>=205 && location<=207) || (location>=220 && location<=223) || (location>=235 && location<=239) || (location>=251 && location<=255)){
                        for(int k=0;k<possible_directions.size();k++){
                            if((possible_directions[k]>=251 && possible_directions[k]<=255) || (possible_directions[k]>=235 && possible_directions[k]<=239) || (possible_directions[k]>=220 && possible_directions[k]<=223) || (possible_directions[k]>=205 && possible_directions[k]<=207) || possible_directions[k]==190 || possible_directions[k]==191){
                                bool check=is_played(location,possible_directions[k]);
                                if(!check){
                                    vector<int> m;
                                    m.push_back(location);
                                    m.push_back(possible_directions[k]);
                                    list.push_back(m);
                                }
                            }
                        }
                    }
                    else if(location==64 || location==65 || (location>=48 && location<=50) || (location>=32 && location<=35) || (location>=16 && location<=20) || (location>=0 && location<=4)){
                        for(int k=0;k<possible_directions.size();k++){
                            if((possible_directions[k]>=0 && possible_directions[k]<=4) || (possible_directions[k]>=16 && possible_directions[k]<=20) || (possible_directions[k]>=32 && possible_directions[k]<=35) || (possible_directions[k]>=48 && possible_directions[k]<=50) || possible_directions[k]==64 || possible_directions[k]==65){
                                bool check=is_played(location,possible_directions[k]);
                                if(!check){
                                    //cout<<"_"<<endl;
                                    vector<int> m;
                                    m.push_back(location);
                                    m.push_back(possible_directions[k]);
                                    list.push_back(m);
                                }
                            }
                        }
                    }
                    else{
                        for(int k=0;k<possible_directions.size();k++){
                            vector<int> m;
                            m.push_back(location);
                            m.push_back(possible_directions[k]);
                            list.push_back(m);
                        }
                    }
                    }
                }
            }
        }
        }
        else if(color=="BLACK"){
        bool flag=false;
        for(int i=0;i<5;i++){
            if(i==2)temp=4;
            else if(i==3)temp=3;
            else if(i==4)temp=2;
            else temp=5;
            for(int j=0;j<temp;j++){
                if(board[i][j]=='B'){
                    int location=i*16+j;
                    vector<int> possible_directions=directions(board,location);
                    if(!possible_directions.empty()){
                    for(int k=0;k<possible_directions.size();k++){
                        if((possible_directions[k]>4 && possible_directions[k]<=15) || (possible_directions[k]>20 && possible_directions[k]<=31) || (possible_directions[k]>35 && possible_directions[k]<=47) || (possible_directions[k]>50 && possible_directions[k]<=63) || (possible_directions[k]>65)){
                        vector<int> m;
                        m.push_back(location);
                        m.push_back(possible_directions[k]);
                        list.push_back(m);
                        flag=true;
                        }
                    }
                    }
                }
            }
        }
        if(flag==false){
            for(int i=0;i<5;i++){
                if(i==2)temp=4;
                else if(i==3)temp=3;
                else if(i==4)temp=2;
                else temp=5;
                for(int j=0;j<temp;j++){
                    if(board[i][j]=='B'){
                        int location=i*16+j;
                        vector<int> possible_directions=directions(board,location);
                        if(!possible_directions.empty()){
                        for(int k=0;k<possible_directions.size();k++){
                            int x=possible_directions[k]/16;
                            int y=possible_directions[k]%16;
                            if(x-i>=0 && y-j>=0){
                                vector<int> m;
                                m.push_back(location);
                                m.push_back(possible_directions[k]);
                                list.push_back(m);
                                flag=true;
                            }
                        }
                        }
                    }
                }
            }
        }
        if(flag==false){
            for(int i=0;i<16;i++){
               for(int j=0;j<16;j++){
                   if(board[i][j]=='B'){
                       int location=i*16+j;
                       vector<int> possible_directions=directions(board,location);
                       if(!possible_directions.empty()){
                           for(int k=0;k<possible_directions.size();k++){
                               vector<int> m;
                               m.push_back(location);
                               m.push_back(possible_directions[k]);
                               list.push_back(m);
                            }
                        }
                    }
                }
            }
        }
        }
        else if(color=="WHITE"){
            bool flag=false;
        for(int i=15;i>=11;i--){
            if(i==11)temp=14;
            else if(i==12)temp=13;
            else if(i==13)temp=12;
            else temp=11;
            for(int j=15;j>=temp;j--){
                if(board[i][j]=='W'){
                    int location=i*16+j;
                    vector<int> possible_directions=directions(board,location);
                    if(!possible_directions.empty()){
                    for(int k=0;k<possible_directions.size();k++){
                        if((possible_directions[k]<251 && possible_directions[k]>=240) || (possible_directions[k]<235 && possible_directions[k]>=224) || (possible_directions[k]<220 && possible_directions[k]>=208) || (possible_directions[k]<205 && possible_directions[k]>=192) || (possible_directions[k]<190)){
                        vector<int> m;
                        m.push_back(location);
                        m.push_back(possible_directions[k]);
                        list.push_back(m);
                        flag=true;
                        }
                    }
                    }
                }
            }
        }
        if(flag==false){
            for(int i=15;i>=11;i--){
                if(i==11)temp=14;
                else if(i==12)temp=13;
                else if(i==13)temp=12;
                else temp=11;
                for(int j=15;j>=temp;j--){
                    if(board[i][j]=='W'){
                        int location=i*16+j;
                        vector<int> possible_directions=directions(board,location);
                        if(!possible_directions.empty()){
                        for(int k=0;k<possible_directions.size();k++){
                            int x=possible_directions[k]/16;
                            int y=possible_directions[k]%16;
                            if(x-i<=0 && y-j<=0){
                                vector<int> m;
                                m.push_back(location);
                                m.push_back(possible_directions[k]);
                                list.push_back(m);
                                flag=true;
                            }
                        }
                        }
                    }
                }
            }
        }
        if(flag==false){
            for(int i=15;i>=0;i--){
               for(int j=15;j>=0;j--){
                   if(board[i][j]=='W'){
                       int location=i*16+j;
                       vector<int> possible_directions=directions(board,location);
                       if(!possible_directions.empty()){
                           for(int k=0;k<possible_directions.size();k++){
                               vector<int> m;
                               m.push_back(location);
                               m.push_back(possible_directions[k]);
                               list.push_back(m);
                            }
                        }
                    }
                }
            }
        }
        }
        /*for(int i=0;i<list.size();i++){
            cout<<color<<'\t';
            for(int j=0;j<list[i].size();j++){
                cout<<list[i][j]<<'\t';
            }
            cout<<endl;
        }*/
        return list;

        /*for(int i=0;i<list_of_moves.size();i++){
            cout<<list_of_moves[i][0]/16<<'\t'<<list_of_moves[i][0]%16<<'\t'<<list_of_moves[i][1]/16<<'\t'<<list_of_moves[i][1]%16<<endl;
        }*/
}

bool is_goal_state(char board[16][16]){
    int temp;
    int black_in_black=0,black_in_white=0,white_in_white=0,white_in_black=0;
    for(int i=0;i<5;i++){
        if(i==2)temp=4;
        else if(i==3)temp=3;
        else if(i==4)temp=2;
        else temp=5;
        for(int j=0;j<temp;j++){
            if(board[i][j]=='B')black_in_black++;
            else if(board[i][j]=='W')white_in_black++;
        }
    }
    for(int i=11;i<16;i++){
        if(i==11)temp=14;
        else if(i==12)temp=13;
        else if(i==13)temp=12;
        else temp=11;
        for(int j=temp;j<16;j++){
            if(board[i][j]=='B')black_in_white++;
            else if(board[i][j]=='W')white_in_white++;
        }
    }
    if((black_in_black+white_in_black==19 && black_in_black!=19) || (black_in_white+white_in_white==19 && white_in_white!=19))return true;
    else return false;
}

float minimax(char board[16][16],string color,float alpha,float beta,int depth,bool isMax,float time_given,int flag){
    vector <vector <float> >list;
    float score;
    if(!isMax){
        if(flag==1){score=get_score1(board,player);}
        else score=get_score(board,player);
    }
    else{
        if(flag==1){score=get_score1(board,opponent);}
        else score=get_score(board,opponent);
        score=score*(-1);
    }
    if(depth==0){
        return score;
    }
    if(is_goal_state(board))return score;

    float t=1.0 * clock() / CLOCKS_PER_SEC;
    if(t==time_given-0.01){
        return score;
    }

    if(isMax){
        float best_eval=-1000;
        float eval;
        vector<vector<int> > list_of_moves;
        list_of_moves=get_valid_moves(board,color);
        for(int i=0;i<list_of_moves.size();i++){
            int x1=list_of_moves[i][0]/16;
            int y1=list_of_moves[i][0]%16;
            int x2=list_of_moves[i][1]/16;
            int y2=list_of_moves[i][1]%16;
            char temp=board[x1][y1];
            board[x1][y1]=board[x2][y2];
            board[x2][y2]=temp;
            /*vector<float>move1;
                move1.push_back(list_of_moves[i][0]);
                move1.push_back(list_of_moves[i][1]);
                move1.push_back(eval);
                list.push_back(move1);*/
            eval=minimax(board,opponent,alpha,beta,depth-1,!isMax,t,flag);
            if(eval>best_eval){
                vector<float>move;
                list.clear();
                move.push_back(list_of_moves[i][0]);
                move.push_back(list_of_moves[i][1]);
                move.push_back(eval);
                list.push_back(move);
            }
            best_eval=max(best_eval,eval);
            temp=board[x1][y1];
            board[x1][y1]=board[x2][y2];
            board[x2][y2]=temp;
            alpha=max(alpha,eval);
            if(beta<=alpha)
                break;
        }
        /*for(int i=0; i<list.size(); i++){
            for(int j=0;j<list[i].size();j++){
                cout<<list[i][j]<<'\t';
            }
        cout<<endl;
        }*/
        //cout<<eval<<endl;
        final_from=list[list.size()-1][0];
        final_to=list[list.size()-1][1];
        return best_eval;
    }
    else{
        float best_eval=1000;
        float eval;
        vector<vector<int> > list_of_moves;
        list_of_moves=get_valid_moves(board,color);
        for(int i=0;i<list_of_moves.size();i++){
            int x1=list_of_moves[i][0]/16;
            int y1=list_of_moves[i][0]%16;
            int x2=list_of_moves[i][1]/16;
            int y2=list_of_moves[i][1]%16;
            char temp=board[x1][y1];
            board[x1][y1]=board[x2][y2];
            board[x2][y2]=temp;
            eval=minimax(board,player,alpha,beta,depth-1,!isMax,t,flag);
            best_eval=min(best_eval,eval);
            temp=board[x1][y1];
            board[x1][y1]=board[x2][y2];
            board[x2][y2]=temp;
            beta=min(beta,eval);
            if(beta<=alpha)
                break;
        }
        return best_eval;
    }
}

vector<int> print_output(char board[16][16],string type_of_game, string color){
    int x,y;
    bool visited[16][16];
    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++)
        visited[i][j]=false;
    }
    int k=0;
    vector <int> from_location;
    vector <int> jump_location;
    from_location.push_back(final_from);
    jump_location.push_back(final_from);

    while(k<jump_location.size()){
        x=jump_location[k]/16;
        y=jump_location[k]%16;
        visited[x][y]=true;
        //north-west
        if(x>1 && y>1){
        if(board[x-1][y-1]=='B' || board[x-1][y-1]=='W'){
            if(board[x-2][y-2]=='.' && visited[x-2][y-2]!=true){
                from_location.push_back(x*16+y);
                jump_location.push_back((x-2)*16+(y-2));
                visited[x-2][y-2]=true;
            }
        }
        }
        //north-east
        if(x>1 && y<14){
        if(board[x-1][y+1]=='B' || board[x-1][y+1]=='W'){
            if(board[x-2][y+2]=='.' && visited[x-2][y+2]!=true){
                from_location.push_back(x*16+y);
                jump_location.push_back((x-2)*16+(y+2));
                visited[x-2][y+2]=true;
            }
        }
        }
        //south-east
        if(x<14 && y<14){
        if(board[x+1][y+1]=='B' || board[x+1][y+1]=='W'){
            if(board[x+2][y+2]=='.' && visited[x+2][y+2]!=true){
                from_location.push_back(x*16+y);
                jump_location.push_back((x+2)*16+(y+2));
                visited[x+2][y+2]=true;
            }
        }
        }
        //south-west
        if(x<14 && y>1){
        if(board[x+1][y-1]=='B' || board[x+1][y-1]=='W'){
            if(board[x+2][y-2]=='.' && visited[x+2][y-2]!=true){
                from_location.push_back(x*16+y);
                jump_location.push_back((x+2)*16+(y-2));
                visited[x+2][y-2]=true;
            }
        }
        }
        //north
        if(x>1){
        if(board[x-1][y]=='B' || board[x-1][y]=='W'){
            if(board[x-2][y]=='.' && visited[x-2][y]!=true){
                from_location.push_back(x*16+y);
                jump_location.push_back((x-2)*16+y);
                visited[x-2][y]=true;
            }
        }
        }
        //west
        if(y>1){
        if(board[x][y-1]=='B' || board[x][y-1]=='W'){
            if(board[x][y-2]=='.' && visited[x][y-2]!=true){
                from_location.push_back(x*16+y);
                jump_location.push_back((x)*16+(y-2));
                visited[x][y-2]=true;
            }
        }
        }
        //east
        if(y<14){
        if(board[x][y+1]=='B' || board[x][y+1]=='W'){
            if(board[x][y+2]=='.' && visited[x][y+2]!=true){
                from_location.push_back(x*16+y);
                jump_location.push_back((x)*16+(y+2));
                visited[x][y+2]=true;
            }
        }
        }
        //south
        if(x<14){
        if(board[x+1][y]=='B' || board[x+1][y]=='W'){
            if(board[x+2][y]=='.' && visited[x+2][y]!=true){
                from_location.push_back(x*16+y);
                jump_location.push_back((x+2)*16+y);
                visited[x+2][y]=true;
            }
        }
        }
        k++;
    }
    k=jump_location.size()-1;
    int find=final_to;
    vector<int> jump;
    while(k>=0){
        if(jump_location[k]==find){
            jump.push_back(find);
            find=from_location[k];
            k--;
        }
        else k--;
    }
    return jump;
}

int main(){
    string type_of_game,color;
    float time;
    ifstream inputFile;
    inputFile.open("input.txt");
    ofstream outputFile;
    outputFile.open("output.txt");
    ofstream playdata;
    playdata.open("playdata.txt",ios_base::app);

    if(inputFile.is_open()){
        inputFile>>type_of_game>>color;
        inputFile>>time;
    }
    char board[16][16];
    if(inputFile.is_open()){
        for(int i=0; i<16; i++){
            for(int j=0;j<16;j++){
                inputFile>>board[i][j];
            }
        }
    }
    inputFile.close();
    if(color=="BLACK"){
        player="BLACK";
        opponent="WHITE";
    }
    else if(color=="WHITE"){
        player="WHITE";
        opponent="BLACK";
    }
    /*for(int i=0; i<16; i++){
        for(int j=0;j<16;j++){
            cout<<board[i][j]<<'\t';
        }
        cout<<endl;
    }*/
    float best_move;
    int alpha=-1000,beta=1000;
    if(type_of_game=="SINGLE")
        best_move=minimax(board,player,alpha,beta,1,true,time,0);
    else{
        float s=get_score(board,player);
        //cout<<s<<endl;
        if(player=="BLACK" && abs(s-138.166)<epsilon){
            final_from=2*16+3;
            final_to=3*16+4;
        }
        else if(abs(s-138.166)<epsilon && player=="WHITE"){
            final_from=12*16+13;
            final_to=11*16+12;
        }
        else if(abs(s-139.579)<epsilon && player=="BLACK"){
            final_from=0*16+3;
            final_to=4*16+5;
        }
        else if(abs(s-139.579)<epsilon && player=="WHITE"){
            final_from=12*16+15;
            final_to=10*16+11;
        }
        else if(abs(s-143.922)<epsilon && player=="BLACK"){
            final_from=1*16+1;
            final_to=5*16+5;
        }
        else if(abs(s-143.922)<epsilon && player=="WHITE"){
            final_from=14*16+14;
            final_to=10*16+10;
        }
        //else if(abs(s-449.503)<=10.00){
        //   best_move=minimax(board,player,alpha,beta,1,true,time);
        //}
        else{
            int temp;
            int countw=0,countb=0;
            for(int i=0;i<5;i++){
                if(i==2)temp=4;
                else if(i==3)temp=3;
                else if(i==4)temp=2;
                else temp=5;
                for(int j=0;j<temp;j++){
                    if(board[i][j]=='W'){countw++;}
                }
            }
            for(int i=11;i<16;i++){
                if(i==11)temp=14;
                else if(i==12)temp=13;
                else if(i==13)temp=12;
                else temp=11;
                for(int j=temp;j<16;j++){
                    if(board[i][j]=='B')countb++;
                }
            }
            if(player=="WHITE" && countw>=16)
                best_move=minimax(board,player,alpha,beta,1,true,time,1);
            else if(player=="BLACK" && countb>=16)
                best_move=minimax(board,player,alpha,beta,1,true,time,1);
            else
                best_move=minimax(board,player,alpha,beta,3,true,time,0);
        }
    }
    //cout<<best_move<<endl;
    vector<int>jump;
    jump=print_output(board,type_of_game,player);
    if(!jump.empty()){
        for(int k=jump.size()-1;k>0;k--){
            outputFile<<'J'<<" "<<jump[k]%16<<","<<jump[k]/16<<" "<<jump[k-1]%16<<","<<jump[k-1]/16<<"\n";
            //cout<<'J'<<" "<<jump[k]%16<<","<<jump[k]/16<<" "<<jump[k-1]%16<<","<<jump[k-1]/16<<endl;
        }
        //outputFile<<"__________________________"<<endl;
    }
    else if(abs(final_from-final_to)==17 || abs(final_from-final_to)==16 || abs(final_from-final_to)==15 || abs(final_from-final_to)==1){
        outputFile<<'E'<<" "<<final_from%16<<","<<final_from/16<<" "<<final_to%16<<","<<final_to/16<<"\n";
        //cout<<'E'<<" "<<final_from%16<<","<<final_from/16<<" "<<final_to%16<<","<<final_to/16<<endl;
    }
    if(type_of_game=="GAME"){
        if(color=="BLACK"){
            if(final_from==190 || final_from==191 || (final_from>=205 && final_from<=207) || (final_from>=220 && final_from<=223) || (final_from>=235 && final_from<=239) || (final_from>=251 && final_from<=255)){
                if((final_to>=251 && final_to<=255) || (final_to>=235 && final_to<=239) || (final_to>=220 && final_to<=223) || (final_to>=205 && final_to<=207) || final_to==190 || final_to==191){
                    playdata<<final_to<<'\t'<<final_from<<endl;
                }
            }
        }
        else{
            if(final_from==64 || final_from==65 || (final_from>=48 && final_from<=50) || (final_from>=32 && final_from<=35) || (final_from>=16 && final_from<=20) || (final_from>=0 && final_from<=4)){
                if((final_to>=0 && final_to<=4) || (final_to>=16 && final_to<=20) || (final_to>=32 && final_to<=35) || (final_to>=48 && final_to<=50) || final_to==64 || final_to==65){
                    playdata<<final_to<<'\t'<<final_from<<endl;
                }
            }
        }
        //float s=get_score(board,color);
        //if(abs(s-449.503)<=10.00){
          //  playdata<<final_to<<'\t'<<final_from<<endl;
        //}
    }
    outputFile.close();
    playdata.close();

    ofstream p;
    p.open("p.txt",ios_base::app);
        p<< 1.0 * clock() / CLOCKS_PER_SEC << "\n";
    p.close();
    return 0;
}
